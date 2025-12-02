#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget_objetos, &QListWidget::itemChanged, this, &MainWindow::on_listWidget_objetos_itemChanged);

    connect(ui->listWidget_objetos, &QListWidget::itemClicked, this, [this](QListWidgetItem* item){
        this->setFocus();
    });

    double w_xmin_default = -250.0;
    double w_ymin_default = -250.0;
    double w_zmin_default = -150.0;
    double w_xmax_default = 250.0;
    double w_ymax_default = 250.0;
    double w_zmax_default = 150.0;

    a_window = new WindowGrafica("Window", Ponto(w_xmin_default, w_ymin_default, 0), Ponto(w_xmax_default, w_ymax_default, 0));
    a_window->setZMin(w_zmin_default);
    a_window->setZMax(w_zmax_default);
    a_window->setVisivel(true);
    displayFile.prepend(a_window);

    transformador = new TransformadorCoordenadas();
    clipper = new Clipping();

    ui->lineEdit_w_xmin->setText(QString::number(w_xmin_default));
    ui->lineEdit_w_ymin->setText(QString::number(w_ymin_default));
    ui->lineEdit_w_xmax->setText(QString::number(w_xmax_default));
    ui->lineEdit_w_ymax->setText(QString::number(w_ymax_default));
    ui->lineEdit_zmin->setText(QString::number(w_zmin_default));
    ui->lineEdit_zmax->setText(QString::number(w_zmax_default));

    orbitDistancia = 600.0;
    orbitRotX = 20.0;
    orbitRotY = 0.0;
    cameraFoco = Ponto(0, 0, 0);
    usoPerspectiva = true;

    isDragging = false;
    this->setFocusPolicy(Qt::StrongFocus);

    atualizarListaObjetos();
}

MainWindow::~MainWindow() {
    qDeleteAll(displayFile);
    displayFile.clear();
    delete transformador;
    delete clipper;
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    setupViewport();
}

void MainWindow::setupViewport() {
    int canvas_width = ui->Tela->width();
    int canvas_height = ui->Tela->height();

    int padding = 0;

    int v_xmin = padding;
    int v_ymin = padding;
    int v_xmax = std::max(padding + 1, canvas_width - padding);
    int v_ymax = std::max(padding + 1, canvas_height - padding);

    transformador->setViewport(v_xmin, v_ymin, v_xmax, v_ymax);

    ui->lineEdit_v_xmin->setText(QString::number(v_xmin));
    ui->lineEdit_v_ymin->setText(QString::number(v_ymin));
    ui->lineEdit_v_xmax->setText(QString::number(v_xmax));
    ui->lineEdit_v_ymax->setText(QString::number(v_ymax));

    update();
}

void MainWindow::atualizarListaObjetos() {
    ui->listWidget_objetos->blockSignals(true);
    ui->listWidget_objetos->clear();
    for (ObjetoGrafico* obj : displayFile) {
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(QString("%1 (%2)").arg(obj->getNome()).arg(tipoParaString(obj->getTipo())));
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setCheckState(obj->isVisivel() ? Qt::Checked : Qt::Unchecked);
        ui->listWidget_objetos->addItem(item);
    }
    ui->listWidget_objetos->blockSignals(false);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        lastMousePos = event->pos();
        isDragging = true;
        this->setFocus();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (!isDragging) return;

    double dx = event->x() - lastMousePos.x();
    double dy = event->y() - lastMousePos.y();
    double sensitivity = 0.5;

    if (event->modifiers() & Qt::ControlModifier) {
        int index = ui->listWidget_objetos->currentRow();
        if (index > 0 && index < displayFile.size()) {
            ObjetoGrafico* obj = displayFile[index];
            if (event->buttons() & Qt::LeftButton) {
                double radY = orbitRotY * M_PI / 180.0;
                double cosY = cos(radY);
                double sinY = sin(radY);
                double moveSpeed = 2.0;
                double transX = dx * moveSpeed * cosY;
                double transZ = dx * moveSpeed * sinY;
                double transY = -dy * moveSpeed;
                obj->aplicarTransformacao(Matrix::criarMatrizTranslacao(transX, transY, transZ));
            }
        }
    } else {
        if (event->buttons() & Qt::LeftButton) {
            orbitRotY += dx * sensitivity;
            orbitRotX += dy * sensitivity;
            if (orbitRotX > 90.0) orbitRotX = 90.0;
            if (orbitRotX < -90.0) orbitRotX = -90.0;
        } else if (event->buttons() & Qt::RightButton) {
            int index = ui->listWidget_objetos->currentRow();
            if (index > 0 && index < displayFile.size()) {
                ObjetoGrafico* obj = displayFile[index];
                Ponto centroLocal = obj->calcularCentro();
                Matrix model = obj->getMatrizModel();
                Matrix centroWorldMat = model * centroLocal;
                Ponto centroWorld(centroWorldMat.at(0,0), centroWorldMat.at(1,0), centroWorldMat.at(2,0));
                Matrix T1 = Matrix::criarMatrizTranslacao(-centroWorld.getX(), -centroWorld.getY(), -centroWorld.getZ());
                Matrix RotY = Matrix::criarMatrizRotacaoY(dx * sensitivity);
                Matrix RotX = Matrix::criarMatrizRotacaoX(dy * sensitivity);
                Matrix T2 = Matrix::criarMatrizTranslacao(centroWorld.getX(), centroWorld.getY(), centroWorld.getZ());
                obj->aplicarTransformacao(T2 * RotX * RotY * T1);
            }
        }
    }
    lastMousePos = event->pos();
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        isDragging = false;
    }
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        int index = ui->listWidget_objetos->currentRow();
        if (index > 0 && index < displayFile.size()) {
            ObjetoGrafico* obj = displayFile[index];
            double scaleFactor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
            Ponto centroLocal = obj->calcularCentro();
            Matrix model = obj->getMatrizModel();
            Matrix centroWorldMat = model * centroLocal;
            Ponto centroWorld(centroWorldMat.at(0,0), centroWorldMat.at(1,0), centroWorldMat.at(2,0));
            Matrix T1 = Matrix::criarMatrizTranslacao(-centroWorld.getX(), -centroWorld.getY(), -centroWorld.getZ());
            Matrix S = Matrix::criarMatrizEscala(scaleFactor, scaleFactor, scaleFactor);
            Matrix T2 = Matrix::criarMatrizTranslacao(centroWorld.getX(), centroWorld.getY(), centroWorld.getZ());
            obj->aplicarTransformacao(T2 * S * T1);
            update();
        }
    } else {
        double delta = (event->angleDelta().y() > 0) ? -50.0 : 50.0;
        orbitDistancia += delta;
        if (orbitDistancia < 10.0) orbitDistancia = 10.0;
        update();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    double velocidade = 15.0;
    double radY = orbitRotY * M_PI / 180.0;
    double sinY = sin(radY);
    double cosY = cos(radY);

    switch (event->key()) {
    case Qt::Key_W:
        cameraFoco.setX(cameraFoco.getX() + sinY * velocidade);
        cameraFoco.setZ(cameraFoco.getZ() - cosY * velocidade);
        break;
    case Qt::Key_S:
        cameraFoco.setX(cameraFoco.getX() - sinY * velocidade);
        cameraFoco.setZ(cameraFoco.getZ() + cosY * velocidade);
        break;
    case Qt::Key_D:
        cameraFoco.setX(cameraFoco.getX() + cosY * velocidade);
        cameraFoco.setZ(cameraFoco.getZ() + sinY * velocidade);
        break;
    case Qt::Key_A:
        cameraFoco.setX(cameraFoco.getX() - cosY * velocidade);
        cameraFoco.setZ(cameraFoco.getZ() - sinY * velocidade);
        break;
    case Qt::Key_Space:
        cameraFoco.setY(cameraFoco.getY() + velocidade);
        break;
    case Qt::Key_Shift:
        cameraFoco.setY(cameraFoco.getY() - velocidade);
        break;
    default:
        QMainWindow::keyPressEvent(event);
        return;
    }
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setClipRect(ui->Tela->geometry());
    painter.fillRect(ui->Tela->geometry(), Qt::black);

    int v_xmin = ui->lineEdit_v_xmin->text().toInt();
    int v_ymin = ui->lineEdit_v_ymin->text().toInt();
    int v_xmax = ui->lineEdit_v_xmax->text().toInt();
    int v_ymax = ui->lineEdit_v_ymax->text().toInt();

    double viewportWidth = v_xmax - v_xmin;
    double viewportHeight = v_ymax - v_ymin;
    if (viewportWidth <= 0) viewportWidth = 1;
    if (viewportHeight <= 0) viewportHeight = 1;
    double aspect = viewportWidth / viewportHeight;
    if (aspect <= 0) aspect = 1.0;

    LimitesWindow limites3D = a_window->getLimites();

    // Definição da LUZ para a Sombra (Ponto de Luz no Teto)
    // Se a caixa tem limites tipo +/- 250, colocamos a luz em Y=400 (bem acima)
    Ponto luz(0, 400.0, 0);
    double yChao = limites3D.ymin;
    Matrix matrizSombraGlobal = Matrix::criarMatrizSombra(luz, yChao);

    // Camera
    Matrix T_pan = Matrix::criarMatrizTranslacao(-cameraFoco.getX(), -cameraFoco.getY(), -cameraFoco.getZ());
    Matrix T_rot = Matrix::criarMatrizRotacaoX(orbitRotX) * Matrix::criarMatrizRotacaoY(orbitRotY);
    Matrix T_zoom = Matrix::criarMatrizTranslacao(0, 0, -orbitDistancia);
    Matrix T_view = T_zoom * T_rot * T_pan;

    Matrix T_proj;
    if (usoPerspectiva) {
        T_proj = Matrix::criarMatrizProjecaoPerspectiva(60.0, aspect, 10.0, 5000.0);
    } else {
        double halfHeight = orbitDistancia * tan(30.0 * M_PI / 180.0);
        double halfWidth = halfHeight * aspect;
        T_proj = Matrix::criarMatrizProjecaoOrtogonal(-halfWidth, halfWidth, -halfHeight, halfHeight, 10.0, 5000.0);
    }

    Matrix T_final = T_proj * T_view;

    auto desenharPoligono3D = [&](const QVector<Ponto>& vertices, const QBrush& brush) {
        QPolygonF poligono_tela;
        for (const Ponto& p_mundo : vertices) {
            Matrix p_clip = T_final * p_mundo;
            double w = p_clip.at(3, 0);

            if (usoPerspectiva && w < 0.1) { return; }
            if (w == 0) w = 1e-6;

            double x_ndc = p_clip.at(0, 0) / w;
            double y_ndc = p_clip.at(1, 0) / w;

            double x_tela = (x_ndc + 1.0) / 2.0 * viewportWidth + v_xmin;
            double y_tela = (1.0 - y_ndc) / 2.0 * viewportHeight + v_ymin;
            poligono_tela << QPointF(x_tela, y_tela);
        }
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);
        painter.drawPolygon(poligono_tela);
    };

    // Cenário
    QVector<Ponto> vertices_caixa;
    vertices_caixa.append(Ponto(limites3D.xmin, limites3D.ymin, limites3D.zmin));
    vertices_caixa.append(Ponto(limites3D.xmax, limites3D.ymin, limites3D.zmin));
    vertices_caixa.append(Ponto(limites3D.xmax, limites3D.ymax, limites3D.zmin));
    vertices_caixa.append(Ponto(limites3D.xmin, limites3D.ymax, limites3D.zmin));
    vertices_caixa.append(Ponto(limites3D.xmin, limites3D.ymin, limites3D.zmax));
    vertices_caixa.append(Ponto(limites3D.xmax, limites3D.ymin, limites3D.zmax));
    vertices_caixa.append(Ponto(limites3D.xmax, limites3D.ymax, limites3D.zmax));
    vertices_caixa.append(Ponto(limites3D.xmin, limites3D.ymax, limites3D.zmax));

    QVector<Ponto> face_chao     = {vertices_caixa[0], vertices_caixa[1], vertices_caixa[5], vertices_caixa[4]};
    QVector<Ponto> face_fundo    = {vertices_caixa[4], vertices_caixa[5], vertices_caixa[6], vertices_caixa[7]};
    QVector<Ponto> face_esquerda = {vertices_caixa[0], vertices_caixa[4], vertices_caixa[7], vertices_caixa[3]};
    QVector<Ponto> face_direita  = {vertices_caixa[1], vertices_caixa[2], vertices_caixa[6], vertices_caixa[5]};

    desenharPoligono3D(face_chao, QBrush(QColor(50, 50, 50)));
    desenharPoligono3D(face_fundo, QBrush(QColor(30, 50, 30)));
    desenharPoligono3D(face_esquerda, QBrush(QColor(30, 30, 50)));
    desenharPoligono3D(face_direita, QBrush(QColor(50, 30, 30)));

    int selectedIndex = ui->listWidget_objetos->currentRow();

    for (int idx = 0; idx < displayFile.size(); ++idx) {
        ObjetoGrafico* objOriginal = displayFile[idx];
        if (!objOriginal || !objOriginal->isVisivel()) continue;

        if (objOriginal->getTipo() == TipoObjeto::OBJETO3D) {
            Objeto3D* obj3D = static_cast<Objeto3D*>(objOriginal);
            Matrix matrizModelo = objOriginal->getMatrizModel();

            // ========================================================================
            // 1. DESENHAR SOMBRA (Antes do objeto)
            // ========================================================================
            // A matriz final da sombra é: MatrizSombra * MatrizModeloDoObjeto
            // Isso projeta o objeto no chão na posição correta.

            painter.save();
            painter.setPen(QPen(Qt::darkGray, 1, Qt::SolidLine)); // Cor da Sombra

            for (const auto& face : obj3D->getFaces()) {
                for (int i = 0; i < face.size(); ++i) {
                    Ponto p1_local = objOriginal->getPontos()[face[i]];
                    Ponto p2_local = objOriginal->getPontos()[face[(i + 1) % face.size()]];

                    // Aplica Modelo -> Depois Aplica Sombra -> Vira coordenada de Mundo Sombreada
                    Matrix m1_sombra = matrizSombraGlobal * (matrizModelo * p1_local);
                    Matrix m2_sombra = matrizSombraGlobal * (matrizModelo * p2_local);

                    // Atenção: A matriz de sombra resulta em W != 1, precisa normalizar
                    // Mas T_final fará a divisão por W no final. Porém, a matriz de sombra
                    // pode gerar W negativo ou zero se o ponto estiver acima da luz (raro aqui).

                    Ponto p1_sombra_mundo(m1_sombra.at(0,0), m1_sombra.at(1,0), m1_sombra.at(2,0));
                    Ponto p2_sombra_mundo(m2_sombra.at(0,0), m2_sombra.at(1,0), m2_sombra.at(2,0));

                    // Passamos w da sombra adiante? Não, o Ponto simplificado perde o W.
                    // Para corrigir perfeitamente precisaria vetor 4D.
                    // Mas como a sombra projeta no plano (y fixo), e T_final recalcula W,
                    // geralmente funciona se dividirmos pelo W da sombra aqui.

                    double w1_s = m1_sombra.at(3,0);
                    double w2_s = m2_sombra.at(3,0);

                    if (std::abs(w1_s) > 0.001) {
                        p1_sombra_mundo.setX(p1_sombra_mundo.getX() / w1_s);
                        p1_sombra_mundo.setY(p1_sombra_mundo.getY() / w1_s);
                        p1_sombra_mundo.setZ(p1_sombra_mundo.getZ() / w1_s);
                    }
                    if (std::abs(w2_s) > 0.001) {
                        p2_sombra_mundo.setX(p2_sombra_mundo.getX() / w2_s);
                        p2_sombra_mundo.setY(p2_sombra_mundo.getY() / w2_s);
                        p2_sombra_mundo.setZ(p2_sombra_mundo.getZ() / w2_s);
                    }

                    // Clipar Sombra (como se fosse um objeto no mundo)
                    if (clipper->clipReta3D(p1_sombra_mundo, p2_sombra_mundo, limites3D)) {
                        Matrix p1_c = T_final * p1_sombra_mundo;
                        double w1 = p1_c.at(3, 0);
                        Matrix p2_c = T_final * p2_sombra_mundo;
                        double w2 = p2_c.at(3, 0);

                        if (usoPerspectiva) {
                            if (w1 < 0.1 && w2 < 0.1) continue;
                            if (w1 <= 0.1) w1 = 1e-6;
                            if (w2 <= 0.1) w2 = 1e-6;
                        } else {
                            if (w1 == 0) w1 = 1.0;
                            if (w2 == 0) w2 = 1.0;
                        }

                        double x1_t = (p1_c.at(0,0)/w1 + 1.0)/2.0 * viewportWidth + v_xmin;
                        double y1_t = (1.0 - p1_c.at(1,0)/w1)/2.0 * viewportHeight + v_ymin;
                        double x2_t = (p2_c.at(0,0)/w2 + 1.0)/2.0 * viewportWidth + v_xmin;
                        double y2_t = (1.0 - p2_c.at(1,0)/w2)/2.0 * viewportHeight + v_ymin;

                        painter.drawLine(x1_t, y1_t, x2_t, y2_t);
                    }
                }
            }
            painter.restore();

            // ========================================================================
            // 2. DESENHAR OBJETO REAL
            // ========================================================================

            QColor corObjeto = (idx == selectedIndex && idx > 0) ? QColor(255, 255, 0) : Qt::white;
            painter.setPen(QPen(corObjeto, 1));

            for (const auto& face : obj3D->getFaces()) {
                for (int i = 0; i < face.size(); ++i) {
                    Ponto p1_local = objOriginal->getPontos()[face[i]];
                    Ponto p2_local = objOriginal->getPontos()[face[(i + 1) % face.size()]];

                    Matrix m1_world = matrizModelo * p1_local;
                    Matrix m2_world = matrizModelo * p2_local;
                    Ponto p1_mundo(m1_world.at(0,0), m1_world.at(1,0), m1_world.at(2,0));
                    Ponto p2_mundo(m2_world.at(0,0), m2_world.at(1,0), m2_world.at(2,0));

                    Ponto p1_clipped = p1_mundo;
                    Ponto p2_clipped = p2_mundo;

                    if (clipper->clipReta3D(p1_clipped, p2_clipped, limites3D)) {
                        Matrix p1_clip = T_final * p1_clipped;
                        double w1 = p1_clip.at(3, 0);
                        Matrix p2_clip = T_final * p2_clipped;
                        double w2 = p2_clip.at(3, 0);

                        if (usoPerspectiva) {
                            if (w1 < 0.1 && w2 < 0.1) continue;
                            if (w1 <= 0.1) w1 = 1e-6;
                            if (w2 <= 0.1) w2 = 1e-6;
                        } else {
                            if (w1 == 0) w1 = 1.0;
                            if (w2 == 0) w2 = 1.0;
                        }

                        double x1_ndc = p1_clip.at(0, 0) / w1;
                        double y1_ndc = p1_clip.at(1, 0) / w1;
                        double x2_ndc = p2_clip.at(0, 0) / w2;
                        double y2_ndc = p2_clip.at(1, 0) / w2;

                        double x1_tela = (x1_ndc + 1.0) / 2.0 * viewportWidth + v_xmin;
                        double y1_tela = (1.0 - y1_ndc) / 2.0 * viewportHeight + v_ymin;
                        double x2_tela = (x2_ndc + 1.0) / 2.0 * viewportWidth + v_xmin;
                        double y2_tela = (1.0 - y2_ndc) / 2.0 * viewportHeight + v_ymin;

                        painter.drawLine(x1_tela, y1_tela, x2_tela, y2_tela);
                    }
                }
            }
        }
    }
}

void MainWindow::on_pushButton_carregarOBJ_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Carregar Modelo 3D", "", "Wavefront OBJ (*.obj)");
    if (filePath.isEmpty()) return;
    QFileInfo fileInfo(filePath);
    Objeto3D* novoObjeto = new Objeto3D(fileInfo.baseName());
    if (novoObjeto->carregarDeOBJ(filePath)) {
        Ponto centroLocal = novoObjeto->calcularCentro();
        novoObjeto->aplicarTransformacao(Matrix::criarMatrizTranslacao(-centroLocal.getX(), -centroLocal.getY(), -centroLocal.getZ()));

        double maxDim = 0.0;
        for(const Ponto& p : novoObjeto->getPontos()) {
            maxDim = std::max({maxDim, std::abs(p.getX()), std::abs(p.getY()), std::abs(p.getZ())});
        }
        double fatorEscala = (maxDim > 0) ? (150.0 / maxDim) : 1.0;
        novoObjeto->aplicarTransformacao(Matrix::criarMatrizEscala(fatorEscala, fatorEscala, fatorEscala));

        displayFile.append(novoObjeto);
        atualizarListaObjetos();
        ui->listWidget_objetos->setCurrentRow(displayFile.size() - 1);
        update();
    } else {
        delete novoObjeto;
        QMessageBox::warning(this, "Erro", "Não foi possível ler ou processar o arquivo .obj selecionado.");
    }
}

void MainWindow::on_pushButton_transladar_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    if (index <= 0) return;
    double dx = ui->lineEdit_dx->text().toDouble();
    double dy = ui->lineEdit_dy->text().toDouble();
    double dz = ui->lineEdit_dz->text().toDouble();
    displayFile[index]->aplicarTransformacao(Matrix::criarMatrizTranslacao(dx, dy, dz));
    update();
}

void MainWindow::on_pushButton_escalar_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    if (index <= 0) return;
    double sx = ui->lineEdit_sx->text().toDouble();
    double sy = ui->lineEdit_sy->text().toDouble();
    double sz = ui->lineEdit_sz->text().toDouble();
    ObjetoGrafico* obj = displayFile[index];
    Ponto centroLocal = obj->calcularCentro();
    Matrix model = obj->getMatrizModel();
    Matrix centroWorldMat = model * centroLocal;
    Ponto centroWorld(centroWorldMat.at(0,0), centroWorldMat.at(1,0), centroWorldMat.at(2,0));
    Matrix T1 = Matrix::criarMatrizTranslacao(-centroWorld.getX(), -centroWorld.getY(), -centroWorld.getZ());
    Matrix S = Matrix::criarMatrizEscala(sx, sy, sz);
    Matrix T2 = Matrix::criarMatrizTranslacao(centroWorld.getX(), centroWorld.getY(), centroWorld.getZ());
    obj->aplicarTransformacao(T2 * S * T1);
    update();
}

void MainWindow::on_pushButton_rotacionar_x_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    double anguloX = ui->lineEdit_angulo_x->text().toDouble();
    if (index > 0) {
        ObjetoGrafico* obj = displayFile[index];
        Ponto centroLocal = obj->calcularCentro();
        Matrix model = obj->getMatrizModel();
        Matrix centroWorldMat = model * centroLocal;
        Ponto centroWorld(centroWorldMat.at(0,0), centroWorldMat.at(1,0), centroWorldMat.at(2,0));
        Matrix T1 = Matrix::criarMatrizTranslacao(-centroWorld.getX(), -centroWorld.getY(), -centroWorld.getZ());
        Matrix R = Matrix::criarMatrizRotacaoX(anguloX);
        Matrix T2 = Matrix::criarMatrizTranslacao(centroWorld.getX(), centroWorld.getY(), centroWorld.getZ());
        obj->aplicarTransformacao(T2 * R * T1);
    }
    update();
}

void MainWindow::on_pushButton_rotacionar_y_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    double anguloY = ui->lineEdit_angulo_y->text().toDouble();
    if (index > 0) {
        ObjetoGrafico* obj = displayFile[index];
        Ponto centroLocal = obj->calcularCentro();
        Matrix model = obj->getMatrizModel();
        Matrix centroWorldMat = model * centroLocal;
        Ponto centroWorld(centroWorldMat.at(0,0), centroWorldMat.at(1,0), centroWorldMat.at(2,0));
        Matrix T1 = Matrix::criarMatrizTranslacao(-centroWorld.getX(), -centroWorld.getY(), -centroWorld.getZ());
        Matrix R = Matrix::criarMatrizRotacaoY(anguloY);
        Matrix T2 = Matrix::criarMatrizTranslacao(centroWorld.getX(), centroWorld.getY(), centroWorld.getZ());
        obj->aplicarTransformacao(T2 * R * T1);
    }
    update();
}

void MainWindow::on_pushButton_rotacionar_z_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    double anguloZ = ui->lineEdit_angulo_z->text().toDouble();
    if (index > 0) {
        ObjetoGrafico* obj = displayFile[index];
        Ponto centroLocal = obj->calcularCentro();
        Matrix model = obj->getMatrizModel();
        Matrix centroWorldMat = model * centroLocal;
        Ponto centroWorld(centroWorldMat.at(0,0), centroWorldMat.at(1,0), centroWorldMat.at(2,0));
        Matrix T1 = Matrix::criarMatrizTranslacao(-centroWorld.getX(), -centroWorld.getY(), -centroWorld.getZ());
        Matrix R = Matrix::criarMatrizRotacaoZ(anguloZ);
        Matrix T2 = Matrix::criarMatrizTranslacao(centroWorld.getX(), centroWorld.getY(), centroWorld.getZ());
        obj->aplicarTransformacao(T2 * R * T1);
    }
    update();
}

void MainWindow::on_pushButton_excluir_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    if (index <= 0) {
        QMessageBox::warning(this, "Aviso", "Não é possível excluir a window. Selecione outro objeto.");
        return;
    }
    delete displayFile[index];
    displayFile.removeAt(index);
    atualizarListaObjetos();
    update();
}

void MainWindow::on_listWidget_objetos_itemChanged(QListWidgetItem *item) {
    int index = ui->listWidget_objetos->row(item);
    if (index >= 0 && index < displayFile.size()) {
        displayFile[index]->setVisivel(item->checkState() == Qt::Checked);
        update();
    }
}

void MainWindow::on_pushButton_aplicar_wv_clicked() {
    double w_xmin = ui->lineEdit_w_xmin->text().toDouble();
    double w_ymin = ui->lineEdit_w_ymin->text().toDouble();
    double w_xmax = ui->lineEdit_w_xmax->text().toDouble();
    double w_ymax = ui->lineEdit_w_ymax->text().toDouble();
    a_window->atualizarLimites(w_xmin, w_ymin, w_xmax, w_ymax);
    double w_zmin = ui->lineEdit_zmin->text().toDouble();
    double w_zmax = ui->lineEdit_zmax->text().toDouble();
    a_window->setZMin(w_zmin);
    a_window->setZMax(w_zmax);
    int v_xmin = ui->lineEdit_v_xmin->text().toInt();
    int v_ymin = ui->lineEdit_v_ymin->text().toInt();
    int v_xmax = ui->lineEdit_v_xmax->text().toInt();
    int v_ymax = ui->lineEdit_v_ymax->text().toInt();
    transformador->setViewport(v_xmin, v_ymin, v_xmax, v_ymax);
    update();
}

void MainWindow::on_pushButton_alternar_projecao_clicked() {
    usoPerspectiva = !usoPerspectiva;
    update();
}
