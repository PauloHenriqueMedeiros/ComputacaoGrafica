#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QTextStream>
#include <QRegularExpression>
#include <QShowEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

#include "objetografico.h"
#include "transformador.h"
#include "windowgrafica.h"
#include "clipping.h"

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
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

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

    // NOVO SLOT: Você deve conectar este botão na interface gráfica
    void on_pushButton_alternar_projecao_clicked();

private:
    void atualizarListaObjetos();
    void setupViewport();

    Ui::MainWindow *ui;
    QVector<ObjetoGrafico*> displayFile;

    TransformadorCoordenadas* transformador;
    WindowGrafica* a_window;
    Clipping* clipper;

    double orbitDistancia;
    double orbitRotX;
    double orbitRotY;
    Ponto cameraFoco;

    QPoint lastMousePos;
    bool isDragging;

    // NOVA VARIÁVEL: Controla o modo de visualização
    bool usoPerspectiva;
};
#endif // MAINWINDOW_H
