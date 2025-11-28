/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *canvasWidget;
    QListWidget *listWidget_objetos;
    QPushButton *pushButton_addReta;
    QPushButton *pushButton_addPoligono;
    QPushButton *pushButton_finalizarDesenho;
    QLineEdit *lineEdit_nomeObjeto;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_addPonto;
    QPushButton *pushButton_excluir;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_v_xmin;
    QLineEdit *lineEdit_v_ymin;
    QLineEdit *lineEdit_v_xmax;
    QLineEdit *lineEdit_v_ymax;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QPushButton *pushButton_aplicar_wv;
    QPushButton *pushButton_carregarOBJ;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_rotacionar_y;
    QLabel *label_3;
    QLineEdit *lineEdit_angulo_z;
    QLabel *label_8;
    QPushButton *pushButton_rotacionar_z;
    QPushButton *pushButton_rotacionar_x;
    QLineEdit *lineEdit_angulo_x;
    QLineEdit *lineEdit_angulo_y;
    QLabel *label_9;
    QLabel *label_19;
    QLineEdit *lineEdit_sx;
    QPushButton *pushButton_transladar;
    QLineEdit *lineEdit_dx;
    QLineEdit *lineEdit_dy;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_dz;
    QLineEdit *lineEdit_sy;
    QPushButton *pushButton_escalar;
    QLineEdit *lineEdit_sz;
    QLabel *label_7;
    QLabel *label_18;
    QGroupBox *groupBox;
    QLineEdit *lineEdit_w_xmin;
    QLineEdit *lineEdit_w_ymin;
    QLineEdit *lineEdit_w_xmax;
    QLineEdit *lineEdit_w_ymax;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *lineEdit_zmin;
    QLineEdit *lineEdit_zmax;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(947, 713);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        canvasWidget = new QWidget(centralwidget);
        canvasWidget->setObjectName("canvasWidget");
        canvasWidget->setGeometry(QRect(10, 10, 921, 411));
        canvasWidget->setAutoFillBackground(false);
        listWidget_objetos = new QListWidget(centralwidget);
        listWidget_objetos->setObjectName("listWidget_objetos");
        listWidget_objetos->setGeometry(QRect(10, 490, 201, 141));
        pushButton_addReta = new QPushButton(centralwidget);
        pushButton_addReta->setObjectName("pushButton_addReta");
        pushButton_addReta->setGeometry(QRect(220, 490, 111, 24));
        pushButton_addPoligono = new QPushButton(centralwidget);
        pushButton_addPoligono->setObjectName("pushButton_addPoligono");
        pushButton_addPoligono->setGeometry(QRect(220, 520, 111, 24));
        pushButton_finalizarDesenho = new QPushButton(centralwidget);
        pushButton_finalizarDesenho->setObjectName("pushButton_finalizarDesenho");
        pushButton_finalizarDesenho->setGeometry(QRect(220, 580, 111, 24));
        lineEdit_nomeObjeto = new QLineEdit(centralwidget);
        lineEdit_nomeObjeto->setObjectName("lineEdit_nomeObjeto");
        lineEdit_nomeObjeto->setGeometry(QRect(100, 640, 91, 22));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 640, 91, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 470, 91, 16));
        pushButton_addPonto = new QPushButton(centralwidget);
        pushButton_addPonto->setObjectName("pushButton_addPonto");
        pushButton_addPonto->setGeometry(QRect(220, 550, 111, 24));
        pushButton_excluir = new QPushButton(centralwidget);
        pushButton_excluir->setObjectName("pushButton_excluir");
        pushButton_excluir->setGeometry(QRect(220, 610, 111, 24));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(740, 430, 131, 111));
        lineEdit_v_xmin = new QLineEdit(groupBox_2);
        lineEdit_v_xmin->setObjectName("lineEdit_v_xmin");
        lineEdit_v_xmin->setGeometry(QRect(10, 40, 51, 22));
        lineEdit_v_ymin = new QLineEdit(groupBox_2);
        lineEdit_v_ymin->setObjectName("lineEdit_v_ymin");
        lineEdit_v_ymin->setGeometry(QRect(70, 40, 51, 22));
        lineEdit_v_xmax = new QLineEdit(groupBox_2);
        lineEdit_v_xmax->setObjectName("lineEdit_v_xmax");
        lineEdit_v_xmax->setGeometry(QRect(10, 80, 51, 22));
        lineEdit_v_ymax = new QLineEdit(groupBox_2);
        lineEdit_v_ymax->setObjectName("lineEdit_v_ymax");
        lineEdit_v_ymax->setGeometry(QRect(70, 80, 51, 22));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 20, 61, 16));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(70, 20, 61, 16));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 60, 61, 16));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(70, 60, 61, 16));
        pushButton_aplicar_wv = new QPushButton(centralwidget);
        pushButton_aplicar_wv->setObjectName("pushButton_aplicar_wv");
        pushButton_aplicar_wv->setGeometry(QRect(880, 510, 61, 24));
        pushButton_carregarOBJ = new QPushButton(centralwidget);
        pushButton_carregarOBJ->setObjectName("pushButton_carregarOBJ");
        pushButton_carregarOBJ->setGeometry(QRect(220, 640, 141, 24));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(380, 480, 351, 181));
        pushButton_rotacionar_y = new QPushButton(groupBox_3);
        pushButton_rotacionar_y->setObjectName("pushButton_rotacionar_y");
        pushButton_rotacionar_y->setGeometry(QRect(120, 70, 101, 24));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 20, 49, 16));
        lineEdit_angulo_z = new QLineEdit(groupBox_3);
        lineEdit_angulo_z->setObjectName("lineEdit_angulo_z");
        lineEdit_angulo_z->setGeometry(QRect(230, 40, 108, 24));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(120, 20, 49, 16));
        pushButton_rotacionar_z = new QPushButton(groupBox_3);
        pushButton_rotacionar_z->setObjectName("pushButton_rotacionar_z");
        pushButton_rotacionar_z->setGeometry(QRect(230, 70, 101, 24));
        pushButton_rotacionar_x = new QPushButton(groupBox_3);
        pushButton_rotacionar_x->setObjectName("pushButton_rotacionar_x");
        pushButton_rotacionar_x->setGeometry(QRect(10, 70, 101, 24));
        lineEdit_angulo_x = new QLineEdit(groupBox_3);
        lineEdit_angulo_x->setObjectName("lineEdit_angulo_x");
        lineEdit_angulo_x->setGeometry(QRect(10, 40, 108, 24));
        lineEdit_angulo_y = new QLineEdit(groupBox_3);
        lineEdit_angulo_y->setObjectName("lineEdit_angulo_y");
        lineEdit_angulo_y->setGeometry(QRect(120, 40, 108, 24));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(230, 20, 49, 16));
        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(210, 90, 16, 16));
        lineEdit_sx = new QLineEdit(groupBox_3);
        lineEdit_sx->setObjectName("lineEdit_sx");
        lineEdit_sx->setGeometry(QRect(100, 150, 41, 24));
        pushButton_transladar = new QPushButton(groupBox_3);
        pushButton_transladar->setObjectName("pushButton_transladar");
        pushButton_transladar->setGeometry(QRect(10, 110, 80, 24));
        lineEdit_dx = new QLineEdit(groupBox_3);
        lineEdit_dx->setObjectName("lineEdit_dx");
        lineEdit_dx->setGeometry(QRect(100, 110, 41, 24));
        lineEdit_dy = new QLineEdit(groupBox_3);
        lineEdit_dy->setObjectName("lineEdit_dy");
        lineEdit_dy->setGeometry(QRect(150, 110, 41, 24));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(110, 130, 16, 16));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(160, 130, 16, 16));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(110, 90, 16, 16));
        lineEdit_dz = new QLineEdit(groupBox_3);
        lineEdit_dz->setObjectName("lineEdit_dz");
        lineEdit_dz->setGeometry(QRect(200, 110, 41, 24));
        lineEdit_sy = new QLineEdit(groupBox_3);
        lineEdit_sy->setObjectName("lineEdit_sy");
        lineEdit_sy->setGeometry(QRect(150, 150, 41, 24));
        pushButton_escalar = new QPushButton(groupBox_3);
        pushButton_escalar->setObjectName("pushButton_escalar");
        pushButton_escalar->setGeometry(QRect(10, 150, 80, 24));
        lineEdit_sz = new QLineEdit(groupBox_3);
        lineEdit_sz->setObjectName("lineEdit_sz");
        lineEdit_sz->setGeometry(QRect(200, 150, 41, 24));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(160, 90, 16, 16));
        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(210, 130, 16, 16));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(740, 540, 201, 121));
        lineEdit_w_xmin = new QLineEdit(groupBox);
        lineEdit_w_xmin->setObjectName("lineEdit_w_xmin");
        lineEdit_w_xmin->setGeometry(QRect(10, 40, 51, 22));
        lineEdit_w_ymin = new QLineEdit(groupBox);
        lineEdit_w_ymin->setObjectName("lineEdit_w_ymin");
        lineEdit_w_ymin->setGeometry(QRect(70, 40, 51, 22));
        lineEdit_w_xmax = new QLineEdit(groupBox);
        lineEdit_w_xmax->setObjectName("lineEdit_w_xmax");
        lineEdit_w_xmax->setGeometry(QRect(10, 90, 51, 22));
        lineEdit_w_ymax = new QLineEdit(groupBox);
        lineEdit_w_ymax->setObjectName("lineEdit_w_ymax");
        lineEdit_w_ymax->setGeometry(QRect(70, 90, 51, 22));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 20, 61, 16));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(70, 20, 61, 16));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 70, 61, 16));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(70, 70, 61, 16));
        label_20 = new QLabel(groupBox);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(130, 20, 61, 16));
        label_21 = new QLabel(groupBox);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(130, 70, 61, 16));
        lineEdit_zmin = new QLineEdit(groupBox);
        lineEdit_zmin->setObjectName("lineEdit_zmin");
        lineEdit_zmin->setGeometry(QRect(130, 40, 61, 24));
        lineEdit_zmax = new QLineEdit(groupBox);
        lineEdit_zmax->setObjectName("lineEdit_zmax");
        lineEdit_zmax->setGeometry(QRect(130, 90, 61, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 947, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_addReta->setText(QCoreApplication::translate("MainWindow", "Adicionar Reta", nullptr));
        pushButton_addPoligono->setText(QCoreApplication::translate("MainWindow", "Adicionar Poligino", nullptr));
        pushButton_finalizarDesenho->setText(QCoreApplication::translate("MainWindow", "Finalizar Poligino", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nome do Objeto", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Lista de Objetos", nullptr));
        pushButton_addPonto->setText(QCoreApplication::translate("MainWindow", "Desenhar Ponto", nullptr));
        pushButton_excluir->setText(QCoreApplication::translate("MainWindow", "Excluir Objeto", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Viewport", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "X m\303\255nimo", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Y m\303\255nimo", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "X m\303\241ximo", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Y m\303\241ximo", nullptr));
        pushButton_aplicar_wv->setText(QCoreApplication::translate("MainWindow", "Aplicar", nullptr));
        pushButton_carregarOBJ->setText(QCoreApplication::translate("MainWindow", "Carregar Pok\303\251mon (.obj)", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Tranforma\303\247\303\265es", nullptr));
        pushButton_rotacionar_y->setText(QCoreApplication::translate("MainWindow", "Rotacionar em Y", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\303\202ngulo X", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\303\202ngulo Y", nullptr));
        pushButton_rotacionar_z->setText(QCoreApplication::translate("MainWindow", "Rotacionar em Z", nullptr));
        pushButton_rotacionar_x->setText(QCoreApplication::translate("MainWindow", "Rotacionar em X", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\303\202ngulo Z", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        pushButton_transladar->setText(QCoreApplication::translate("MainWindow", "Transladar", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        pushButton_escalar->setText(QCoreApplication::translate("MainWindow", "Escalonar", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Window", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "X m\303\255nimo", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Y m\303\255nimo", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "X m\303\241ximo", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Y m\303\241ximo", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Z m\303\255nimo", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Z m\303\241ximo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
