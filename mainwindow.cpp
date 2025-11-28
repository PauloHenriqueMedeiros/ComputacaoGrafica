#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget_objetos, &QListWidget::itemChanged, this, &MainWindow::on_listWidget_objetos_itemChanged);

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
    int canvas_width = ui->canvasWidget->width();
    int canvas_height = ui->canvasWidget->height();

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
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(obj->isVisivel() ? Qt::Checked : Qt::Unchecked);
        ui->listWidget_objetos->addItem(item);
    }
    ui->listWidget_objetos->blockSignals(false);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setClipRect(ui->canvasWidget->geometry());
    painter.fillRect(ui->canvasWidget->geometry(), Qt::black);

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

    double centroX = (limites3D.xmin + limites3D.xmax) / 2.0;
    double centroY = (limites3D.ymin + limites3D.ymax) / 2.0;
    double centroZ = (limites3D.zmin + limites3D.zmax) / 2.0;
    double distanciaCamera = 650.0;
    Matrix T_trans_centro = Matrix::criarMatrizTranslacao(-centroX, -centroY, -centroZ);
    Matrix T_trans_dist = Matrix::criarMatrizTranslacao(0, 0, -distanciaCamera);
    Matrix T_rot_cam = Matrix::criarMatrizRotacaoY(camAnguloY) * Matrix::criarMatrizRotacaoX(camAnguloX) * Matrix::criarMatrizRotacaoZ(camAnguloZ);
    Matrix T_view = T_rot_cam * T_trans_dist * T_trans_centro;
    Matrix T_proj = Matrix::criarMatrizProjecaoPerspectiva(45.0, aspect, 0.1, 5000.0);
    Matrix T_final = T_proj * T_view;

    auto desenharPoligono3D = [&](const QVector<Ponto>& vertices, const QBrush& brush) {
        QPolygonF poligono_tela;
        for (const Ponto& p_mundo : vertices) {
            Matrix p_clip = T_final * p_mundo;
            double w = p_clip.at(3, 0);

            if (w < 0.1) { return; }
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

    QVector<Ponto> vertices_caixa;
    vertices_caixa.append(Ponto(limites3D.xmin, limites3D.ymin, limites3D.zmin));
    vertices_caixa.append(Ponto(limites3D.xmax, limites3D.ymin, limites3D.zmin));
    vertices_caixa.append(Ponto(limites3D.xmax, limites3D.ymax, limites3D.zmin));
    vertices_caixa.append(Ponto(limites3D.xmin, limites3D.ymax, limites3D.zmin));
    vertices_caixa.append(Ponto(limites3D.xmin, limites3D.ymin, limites3D.zmax));
    vertices_caixa.append(Ponto(limites3D.xmax, limites3D.ymin, limites3D.zmax));
    vertices_caixa.append(Ponto(limites3D.xmax, limites3D.ymax, limites3D.zmax));
    vertices_caixa.append(Ponto(limites3D.xmin, limites3D.ymax, limites3D.zmax));

    QVector<Ponto> face_fundo = {vertices_caixa[4], vertices_caixa[5], vertices_caixa[6], vertices_caixa[7]};
    QVector<Ponto> face_chao = {vertices_caixa[0], vertices_caixa[1], vertices_caixa[5], vertices_caixa[4]};
    QVector<Ponto> face_teto = {vertices_caixa[3], vertices_caixa[2], vertices_caixa[6], vertices_caixa[7]};
    QVector<Ponto> face_esquerda = {vertices_caixa[0], vertices_caixa[4], vertices_caixa[7], vertices_caixa[3]};
    QVector<Ponto> face_direita = {vertices_caixa[1], vertices_caixa[2], vertices_caixa[6], vertices_caixa[5]};

    desenharPoligono3D(face_fundo, QBrush(QColor(0, 50, 0)));
    desenharPoligono3D(face_teto, QBrush(QColor(50, 50, 0)));
    desenharPoligono3D(face_chao, QBrush(QColor(50, 0, 0)));
    desenharPoligono3D(face_esquerda, QBrush(QColor(0, 0, 50)));
    desenharPoligono3D(face_direita, QBrush(QColor(0, 0, 50)));

    painter.setPen(QPen(Qt::white, 1));

    for (const auto& objOriginal : displayFile) {
        if (!objOriginal || !objOriginal->isVisivel()) continue;

        if (objOriginal->getTipo() == TipoObjeto::OBJETO3D) {
            Objeto3D* obj3D = static_cast<Objeto3D*>(objOriginal);
            for (const auto& face : obj3D->getFaces()) {
                for (int i = 0; i < face.size(); ++i) {

                    Ponto p1_mundo = objOriginal->getPontos()[face[i]];
                    Ponto p2_mundo = objOriginal->getPontos()[face[(i + 1) % face.size()]];
                    Ponto p1_clipped = p1_mundo;
                    Ponto p2_clipped = p2_mundo;

                    if (clipper->clipReta3D(p1_clipped, p2_clipped, limites3D)) {
                        Matrix p1_clip = T_final * p1_clipped;
                        double w1 = p1_clip.at(3, 0);
                        Matrix p2_clip = T_final * p2_clipped;
                        double w2 = p2_clip.at(3, 0);

                        if (w1 < 0.1 && w2 < 0.1) {
                            continue;
                        }

                        if (w1 <= 0.1) w1 = 1e-6;
                        if (w2 <= 0.1) w2 = 1e-6;

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
    Objeto3D* novoPokemon = new Objeto3D(fileInfo.baseName());
    if (novoPokemon->carregarDeOBJ(filePath)) {
        Ponto centroObjeto = novoPokemon->calcularCentro();
        novoPokemon->aplicarTransformacao(Matrix::criarMatrizTranslacao(-centroObjeto.getX(), -centroObjeto.getY(), -centroObjeto.getZ()));
        double maxDim = 0.0;
        for(const Ponto& p : novoPokemon->getPontos()) {
            maxDim = std::max({maxDim, std::abs(p.getX()), std::abs(p.getY()), std::abs(p.getZ())});
        }
        double fatorEscala = (maxDim > 0) ? (150.0 / maxDim) : 1.0;
        novoPokemon->aplicarTransformacao(Matrix::criarMatrizEscala(fatorEscala, fatorEscala, fatorEscala));

        LimitesWindow limites3D = a_window->getLimites();
        double cX = (limites3D.xmin + limites3D.xmax) / 2.0;
        double cY = (limites3D.ymin + limites3D.ymax) / 2.0;
        double cZ = (limites3D.zmin + limites3D.zmax) / 2.0;
        novoPokemon->aplicarTransformacao(Matrix::criarMatrizTranslacao(cX, cY, cZ));

        displayFile.append(novoPokemon);
        atualizarListaObjetos();
        update();
    } else {
        delete novoPokemon;
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
    Ponto centro = displayFile[index]->calcularCentro();
    Matrix T1 = Matrix::criarMatrizTranslacao(-centro.getX(), -centro.getY(), -centro.getZ());
    Matrix S = Matrix::criarMatrizEscala(sx, sy, sz);
    Matrix T2 = Matrix::criarMatrizTranslacao(centro.getX(), centro.getY(), centro.getZ());
    displayFile[index]->aplicarTransformacao(T2 * S * T1);
    update();
}

void MainWindow::on_pushButton_rotacionar_x_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    double anguloX = ui->lineEdit_angulo_x->text().toDouble();
    if (index <= 0) { camAnguloX += anguloX; }
    else {
        Ponto pivo = displayFile[index]->calcularCentro();
        Matrix T1 = Matrix::criarMatrizTranslacao(-pivo.getX(), -pivo.getY(), -pivo.getZ());
        Matrix R = Matrix::criarMatrizRotacaoX(anguloX);
        Matrix T2 = Matrix::criarMatrizTranslacao(pivo.getX(), pivo.getY(), pivo.getZ());
        displayFile[index]->aplicarTransformacao(T2 * R * T1);
    }
    update();
}

void MainWindow::on_pushButton_rotacionar_y_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    double anguloY = ui->lineEdit_angulo_y->text().toDouble();
    if (index <= 0) { camAnguloY += anguloY; }
    else {
        Ponto pivo = displayFile[index]->calcularCentro();
        Matrix T1 = Matrix::criarMatrizTranslacao(-pivo.getX(), -pivo.getY(), -pivo.getZ());
        Matrix R = Matrix::criarMatrizRotacaoY(anguloY);
        Matrix T2 = Matrix::criarMatrizTranslacao(pivo.getX(), pivo.getY(), pivo.getZ());
        displayFile[index]->aplicarTransformacao(T2 * R * T1);
    }
    update();
}

void MainWindow::on_pushButton_rotacionar_z_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    double anguloZ = ui->lineEdit_angulo_z->text().toDouble();
    if (index <= 0) { camAnguloZ += anguloZ; }
    else {
        Ponto pivo = displayFile[index]->calcularCentro();
        Matrix T1 = Matrix::criarMatrizTranslacao(-pivo.getX(), -pivo.getY(), -pivo.getZ());
        Matrix R = Matrix::criarMatrizRotacaoZ(anguloZ);
        Matrix T2 = Matrix::criarMatrizTranslacao(pivo.getX(), pivo.getY(), pivo.getZ());
        displayFile[index]->aplicarTransformacao(T2 * R * T1);
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
