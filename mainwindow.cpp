#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ObjetoGrafico ponto1;
    ponto1.nome = "Ponto";
    ponto1.tipo = TipoObjeto::PONTO;
    ponto1.pontos.append(QPoint(50, 50));
    displayFile.append(ponto1);

    ObjetoGrafico reta1;
    reta1.nome = "Reta";
    reta1.tipo = TipoObjeto::RETA;
    reta1.pontos.append(QPoint(80, 80));
    reta1.pontos.append(QPoint(250, 150));
    displayFile.append(reta1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_desenhar_clicked()
{
    int numLados = ui->spinBox_lados->value();
    QPoint centroDoPoligono(this->width() / 2, this->height() / 2);
    int raio = 100;
    QString nome = QString("Poligono de %1 lados").arg(numLados);
    ObjetoGrafico novoPoligono = criarPoligonoRegular(numLados, centroDoPoligono, raio, nome);
    displayFile.append(novoPoligono);
    update();
}

void MainWindow::on_pushButton_apagar_clicked()
{
    displayFile.clear();
    pontosManuais.clear();
    ui->listWidget_pontos->clear();
    update();
}

void MainWindow::on_pushButton_adicionar_ponto_clicked()
{
    int x = ui->spinBox_manual_x->value();
    int y = ui->spinBox_manual_y->value();
    QPoint novoPonto(x, y);

    pontosManuais.append(novoPonto);


    QString textoPonto = QString("Ponto %1: (%2, %3)").arg(pontosManuais.size()).arg(x).arg(y);
    ui->listWidget_pontos->addItem(textoPonto);
}

void MainWindow::on_pushButton_desenhar_manual_clicked()
{
    if (pontosManuais.size() < 2) {
        return;
    }

    ObjetoGrafico novaForma;
    novaForma.nome = "Forma Manual";
    novaForma.tipo = TipoObjeto::POLIGONO;
    novaForma.pontos = pontosManuais;

    displayFile.append(novaForma);

    pontosManuais.clear();
    ui->listWidget_pontos->clear();

    update();
}


// --- LÓGICA DE DESENHO ---

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2));

    for (const auto &objeto : displayFile) {
        switch (objeto.tipo) {
        case TipoObjeto::PONTO:
            if (!objeto.pontos.isEmpty()) {
                desenharPonto(painter, objeto.pontos.first());
            }
            break;
        case TipoObjeto::RETA:
            if (objeto.pontos.size() >= 2) {
                desenharReta(painter, objeto.pontos[0], objeto.pontos[1]);
            }
            break;
        case TipoObjeto::POLIGONO:
            if (objeto.pontos.size() >= 2) {
                desenharPoligono(painter, objeto.pontos);
            }
            break;
        }
    }
}

void MainWindow::desenharPonto(QPainter &painter, const QPoint &p)
{
    painter.drawPoint(p);
}

void MainWindow::desenharReta(QPainter &painter, const QPoint &p1, const QPoint &p2)
{
    float dx = p2.x() - p1.x();
    float dy = p2.y() - p1.y();
    int passos = std::max(std::abs(dx), std::abs(dy));
    if (passos == 0) {
        desenharPonto(painter, p1);
        return;
    }
    float x_inc = dx / static_cast<float>(passos);
    float y_inc = dy / static_cast<float>(passos);
    float x = p1.x();
    float y = p1.y();
    for (int i = 0; i <= passos; ++i) {
        desenharPonto(painter, QPoint(round(x), round(y)));
        x += x_inc;
        y += y_inc;
    }
}

void MainWindow::desenharPoligono(QPainter &painter, const QList<QPoint> &pontos)
{
    if (pontos.size() < 2) return;
    for (int i = 0; i < pontos.size() - 1; ++i) {
        desenharReta(painter, pontos[i], pontos[i+1]);
    }
    desenharReta(painter, pontos.last(), pontos.first());
}

ObjetoGrafico MainWindow::criarPoligonoRegular(int numLados, const QPoint &centro, int raio, const QString &nome)
{
    ObjetoGrafico poligono;
    poligono.nome = nome;
    poligono.tipo = TipoObjeto::POLIGONO;
    if (numLados < 3) return poligono;
    double anguloStep = 2.0 * M_PI / numLados;
    for (int i = 0; i < numLados; ++i) {
        double anguloAtual = i * anguloStep;
        int x = centro.x() + static_cast<int>(raio * cos(anguloAtual - M_PI / 2.0));
        int y = centro.y() + static_cast<int>(raio * sin(anguloAtual - M_PI / 2.0));
        poligono.pontos.append(QPoint(x, y));
    }
    return poligono;
}
