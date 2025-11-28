#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QVector>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QTextStream>
#include <QRegularExpression>
#include <QShowEvent>
#include "objetografico.h"
#include "transformador.h"
#include "windowgrafica.h"
#include "clipping.h"
=======
#include <QList>
#include <QString>
#include <QPoint>
#include <QPainter>
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
    bool visivel;
};
>>>>>>> f47fb501572eaae1e3824d4e48f38cf1010be12a

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
    void showEvent(QShowEvent *event) override;

private slots:
    void on_pushButton_transladar_clicked();
    void on_pushButton_escalar_clicked();
    void on_pushButton_rotacionar_x_clicked();
    void on_pushButton_rotacionar_y_clicked();
    void on_pushButton_rotacionar_z_clicked();
    void on_pushButton_excluir_clicked();
    void on_listWidget_objetos_itemChanged(QListWidgetItem *item);
    void on_pushButton_aplicar_wv_clicked();
    void on_pushButton_carregarOBJ_clicked();

private:
    void atualizarListaObjetos();
    void setupViewport();

    Ui::MainWindow *ui;
    QVector<ObjetoGrafico*> displayFile;

    TransformadorCoordenadas* transformador;
    WindowGrafica* a_window;
    Clipping* clipper;

    double camAnguloX = 0.0;
    double camAnguloY = 0.0;
    double camAnguloZ = 0.0;
};
#endif // MAINWINDOW_H
