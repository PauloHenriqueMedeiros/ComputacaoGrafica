#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sistema Gráfico 2D");

    connect(ui->listWidget_objetos, &QListWidget::itemChanged,
            this, &MainWindow::on_listWidget_objetos_itemChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_adicionar_ponto_clicked()
{
    QString textoX = ui->lineEdit_manual_x->text();
    QString textoY = ui->lineEdit_manual_y->text();

    bool conversaoOkX, conversaoOkY;

    int x = textoX.toInt(&conversaoOkX);
    int y = textoY.toInt(&conversaoOkY);

    if (!conversaoOkX || !conversaoOkY) {
        QMessageBox::warning(this, "Erro de Entrada", "Por favor, insira apenas números inteiros válidos nas coordenadas.");
        return;
    }

    if (x < 0 || y < 0) {
        QMessageBox::warning(this, "Erro de Entrada", "As coordenadas devem ser números positivos (maiores ou iguais a zero).");
        return;
    }

    int canvasWidth = ui->canvasWidget->width();
    int canvasHeight = ui->canvasWidget->height();
    if (x >= canvasWidth || y >= canvasHeight) {
        QString mensagem = QString("Coordenadas fora da área de desenho. O máximo permitido é X: %1, Y: %2.")
                               .arg(canvasWidth - 1)
                               .arg(canvasHeight - 1);
        QMessageBox::warning(this, "Erro de Entrada", mensagem);
        return;
    }

    QPoint novoPonto(x, y);
    pontosManuais.append(novoPonto);

    QString textoPonto = QString("Ponto %1: (%2, %3)").arg(pontosManuais.size()).arg(x).arg(y);
    ui->listWidget_pontos_atuais->addItem(textoPonto);
    update();
}

void MainWindow::on_pushButton_finalizar_objeto_clicked()
{
    if (pontosManuais.isEmpty()) {
        QMessageBox::warning(this, "Aviso", "Nenhum ponto foi adicionado à lista de preparação.");
        return;
    }

    bool ok;
    QString nomeObjeto = QInputDialog::getText(this, "Finalizar Objeto", "Nome do objeto:", QLineEdit::Normal, "Meu Objeto", &ok);

    if (ok && !nomeObjeto.isEmpty()) {
        ObjetoGrafico novoObjeto;
        novoObjeto.nome = nomeObjeto;
        if(pontosManuais.size() == 1) {
            novoObjeto.tipo = TipoObjeto::PONTO;
        } else {
            novoObjeto.tipo = TipoObjeto::POLIGONO;
        }
        novoObjeto.pontos = pontosManuais;
        novoObjeto.visivel = true;
        displayFile.append(novoObjeto);

        QListWidgetItem* item = new QListWidgetItem(nomeObjeto, ui->listWidget_objetos);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
        ui->listWidget_objetos->addItem(item);
    }

    pontosManuais.clear();
    ui->listWidget_pontos_atuais->clear();
    update();
}

void MainWindow::on_pushButton_apagar_tudo_clicked()
{
    displayFile.clear();
    pontosManuais.clear();
    ui->listWidget_objetos->clear();
    ui->listWidget_pontos_atuais->clear();
    update();
}

void MainWindow::on_listWidget_objetos_itemChanged(QListWidgetItem *item)
{
    int index = ui->listWidget_objetos->row(item);
    if (index < 0 || index >= displayFile.size()) return;
    bool isChecked = (item->checkState() == Qt::Checked);
    displayFile[index].visivel = isChecked;
    update();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QRect canvasRect = ui->canvasWidget->geometry();
    painter.setClipRect(canvasRect);
    painter.translate(canvasRect.topLeft());

    painter.setPen(QPen(Qt::cyan, 2));
    for (const auto &objeto : displayFile) {
        if (!objeto.visivel) continue;
        if (objeto.tipo == TipoObjeto::POLIGONO && objeto.pontos.size() >= 2) {
            desenharPoligono(painter, objeto.pontos);
        } else if (objeto.tipo == TipoObjeto::PONTO && !objeto.pontos.isEmpty()) {
            for(const QPoint &p : objeto.pontos) {
                desenharPonto(painter, p);
            }
        }
    }

    if (!pontosManuais.isEmpty()) {
        painter.setPen(QPen(Qt::yellow, 2));
        for(const QPoint &p : pontosManuais) {
            desenharPonto(painter, p);
        }
        if (pontosManuais.size() >= 2) {
            for (int i = 0; i < pontosManuais.size() - 1; ++i) {
                desenharReta(painter, pontosManuais[i], pontosManuais[i+1]);
            }
        }
    }
}


void MainWindow::desenharPonto(QPainter &painter, const QPoint &p) {
    painter.drawPoint(p);
}

void MainWindow::desenharReta(QPainter &painter, const QPoint &p1, const QPoint &p2) {
    float dx = p2.x() - p1.x(), dy = p2.y() - p1.y();
    int passos = std::max(std::abs(dx), std::abs(dy));
    if (passos == 0) { desenharPonto(painter, p1); return; }
    float x_inc = dx / static_cast<float>(passos), y_inc = dy / static_cast<float>(passos);
    float x = p1.x(), y = p1.y();
    for (int i = 0; i <= passos; ++i) {
        painter.drawPoint(round(x), round(y));
        x += x_inc; y += y_inc;
    }
}

void MainWindow::desenharPoligono(QPainter &painter, const QList<QPoint> &pontos) {
    if (pontos.size() < 2) return;
    for (int i = 0; i < pontos.size() - 1; ++i) {
        desenharReta(painter, pontos[i], pontos[i+1]);
    }
    desenharReta(painter, pontos.last(), pontos.first());
}
