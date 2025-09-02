#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QPoint>
#include <QPainter>
#include <QListWidget>

// QResizeEvent não é necessário nesta versão
// #include <QResizeEvent>

enum class TipoObjeto {
    PONTO,
    POLIGONO
};

struct ObjetoGrafico {
    QString nome;
    TipoObjeto tipo;
    QList<QPoint> pontos;
    bool visivel;
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
    void on_pushButton_adicionar_ponto_clicked();
    void on_pushButton_finalizar_objeto_clicked();
    void on_pushButton_apagar_tudo_clicked();
    void on_listWidget_objetos_itemChanged(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QList<ObjetoGrafico> displayFile;
    QList<QPoint> pontosManuais;

    // As funções resizeEvent e atualizarLimitesSpinBox foram removidas
    // por não serem mais necessárias com QLineEdit.

    // Funções de desenho
    void desenharPonto(QPainter &painter, const QPoint &p);
    void desenharReta(QPainter &painter, const QPoint &p1, const QPoint &p2);
    void desenharPoligono(QPainter &painter, const QList<QPoint> &pontos);
};
#endif // MAINWINDOW_H
