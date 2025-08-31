#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QPoint>
#include <QPainter>

// --- Includes para os componentes da interface ---
#include <QPushButton>
#include <QSpinBox>
#include <QListWidget>

// Enum para identificar o tipo de objeto
enum class TipoObjeto {
    PONTO,
    RETA,
    POLIGONO
};

// Estrutura que representa um objeto gráfico no Display File
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
    // Evento chamado sempre que a janela precisa ser redesenhada
    void paintEvent(QPaintEvent *event) override;

private slots:
    // Slots para a criação de polígonos regulares
    void on_pushButton_desenhar_clicked();
    void on_pushButton_apagar_clicked();

    // Slots para a nova funcionalidade de desenho manual
    void on_pushButton_adicionar_ponto_clicked();
    void on_pushButton_desenhar_manual_clicked();

private:
    Ui::MainWindow *ui;

    // O Display File principal
    QList<ObjetoGrafico> displayFile;

    // Lista temporária para guardar os pontos do desenho manual
    QList<QPoint> pontosManuais;

    // Funções Auxiliares de Desenho e Criação
    void desenharPonto(QPainter &painter, const QPoint &p);
    void desenharReta(QPainter &painter, const QPoint &p1, const QPoint &p2);
    void desenharPoligono(QPainter &painter, const QList<QPoint> &pontos);
    ObjetoGrafico criarPoligonoRegular(int numLados, const QPoint &centro, int raio, const QString &nome);
};
#endif // MAINWINDOW_H
