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

    // Eventos de Input
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

private:
    void atualizarListaObjetos();
    void setupViewport();

    Ui::MainWindow *ui;
    QVector<ObjetoGrafico*> displayFile;

    TransformadorCoordenadas* transformador;
    WindowGrafica* a_window;
    Clipping* clipper;

    // --- Variáveis da Câmera Orbital ---
    double orbitDistancia; // Distância da câmera ao ponto de foco (Zoom)
    double orbitRotX;      // Rotação Vertical (Pitch)
    double orbitRotY;      // Rotação Horizontal (Yaw)
    Ponto cameraFoco;      // O ponto central para onde a câmera olha

    // --- Variáveis do Mouse ---
    QPoint lastMousePos;
    bool isDragging;
};
#endif // MAINWINDOW_H
