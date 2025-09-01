#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QPoint>
#include <QPainter>

#include <QPushButton>
#include <QSpinBox>
#include <QListWidget>

enum class TipoObjeto {
    PONTO,
    RETA,
    POLIGONO
};

struct ObjetoGrafico {
    QString nome;
    TipoObjeto tipo;
    QList<QPoint> pontos;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_pushButton_desenhar_clicked();
    void on_pushButton_apagar_clicked();

    void on_pushButton_adicionar_ponto_clicked();
    void on_pushButton_desenhar_manual_clicked();

private:
    Ui::MainWindow *ui;

    QList<ObjetoGrafico> displayFile;


    QList<QPoint> pontosManuais;

    void desenharPonto(QPainter &painter, const QPoint &p);
    void desenharReta(QPainter &painter, const QPoint &p1, const QPoint &p2);
    void desenharPoligono(QPainter &painter, const QList<QPoint> &pontos);
    ObjetoGrafico criarPoligonoRegular(int numLados, const QPoint &centro, int raio, const QString &nome);
};
#endif
