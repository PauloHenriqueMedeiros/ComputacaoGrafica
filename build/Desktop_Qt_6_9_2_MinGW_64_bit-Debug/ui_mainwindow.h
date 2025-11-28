/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
<<<<<<< HEAD
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
=======
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
>>>>>>> f47fb501572eaae1e3824d4e48f38cf1010be12a
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
<<<<<<< HEAD
    QWidget *canvasWidget;
    QListWidget *listWidget_objetos;
    QLineEdit *lineEdit_sy;
    QLineEdit *lineEdit_dy;
    QLineEdit *lineEdit_sx;
    QLineEdit *lineEdit_dx;
    QLineEdit *lineEdit_angulo;
    QPushButton *pushButton_rotacionar;
    QPushButton *pushButton_escalar;
    QPushButton *pushButton_transladar;
    QPushButton *pushButton_addReta;
    QPushButton *pushButton_addPoligono;
    QPushButton *pushButton_finalizarDesenho;
    QLineEdit *lineEdit_nomeObjeto;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QCheckBox *checkBox_usarPontoEspecifico;
    QLineEdit *lineEdit_rotacao_px;
    QLineEdit *lineEdit_rotacao_py;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *pushButton_addPonto;
    QPushButton *pushButton_excluir;
    QGroupBox *groupBox;
    QLineEdit *lineEdit_w_xmin;
    QLineEdit *lineEdit_w_ymin;
    QLineEdit *lineEdit_w_xmax;
    QLineEdit *lineEdit_w_ymax;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
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
    QMenuBar *menubar;
    QStatusBar *statusbar;
=======
    QHBoxLayout *horizontalLayout;
    QWidget *canvasWidget;
    QWidget *controlPanelWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QPushButton *pushButton_adicionar_ponto;
    QListWidget *listWidget_pontos_atuais;
    QGroupBox *groupBox_2;
    QListWidget *listWidget_objetos;
    QPushButton *pushButton_apagar_tudo;
    QPushButton *pushButton_finalizar_objeto;
    QLineEdit *lineEdit_manual_x;
    QLineEdit *lineEdit_manual_y;
>>>>>>> f47fb501572eaae1e3824d4e48f38cf1010be12a

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
<<<<<<< HEAD
        MainWindow->resize(805, 715);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        canvasWidget = new QWidget(centralwidget);
        canvasWidget->setObjectName("canvasWidget");
        canvasWidget->setGeometry(QRect(0, 0, 801, 281));
        canvasWidget->setAutoFillBackground(false);
        listWidget_objetos = new QListWidget(centralwidget);
        listWidget_objetos->setObjectName("listWidget_objetos");
        listWidget_objetos->setGeometry(QRect(10, 310, 201, 141));
        lineEdit_sy = new QLineEdit(centralwidget);
        lineEdit_sy->setObjectName("lineEdit_sy");
        lineEdit_sy->setGeometry(QRect(630, 310, 51, 22));
        lineEdit_dy = new QLineEdit(centralwidget);
        lineEdit_dy->setObjectName("lineEdit_dy");
        lineEdit_dy->setGeometry(QRect(630, 350, 51, 22));
        lineEdit_sx = new QLineEdit(centralwidget);
        lineEdit_sx->setObjectName("lineEdit_sx");
        lineEdit_sx->setGeometry(QRect(570, 310, 51, 22));
        lineEdit_dx = new QLineEdit(centralwidget);
        lineEdit_dx->setObjectName("lineEdit_dx");
        lineEdit_dx->setGeometry(QRect(570, 350, 51, 22));
        lineEdit_angulo = new QLineEdit(centralwidget);
        lineEdit_angulo->setObjectName("lineEdit_angulo");
        lineEdit_angulo->setGeometry(QRect(570, 400, 51, 22));
        pushButton_rotacionar = new QPushButton(centralwidget);
        pushButton_rotacionar->setObjectName("pushButton_rotacionar");
        pushButton_rotacionar->setGeometry(QRect(490, 400, 75, 24));
        pushButton_escalar = new QPushButton(centralwidget);
        pushButton_escalar->setObjectName("pushButton_escalar");
        pushButton_escalar->setGeometry(QRect(490, 310, 75, 24));
        pushButton_transladar = new QPushButton(centralwidget);
        pushButton_transladar->setObjectName("pushButton_transladar");
        pushButton_transladar->setGeometry(QRect(490, 350, 75, 24));
        pushButton_addReta = new QPushButton(centralwidget);
        pushButton_addReta->setObjectName("pushButton_addReta");
        pushButton_addReta->setGeometry(QRect(230, 340, 111, 24));
        pushButton_addPoligono = new QPushButton(centralwidget);
        pushButton_addPoligono->setObjectName("pushButton_addPoligono");
        pushButton_addPoligono->setGeometry(QRect(230, 380, 111, 24));
        pushButton_finalizarDesenho = new QPushButton(centralwidget);
        pushButton_finalizarDesenho->setObjectName("pushButton_finalizarDesenho");
        pushButton_finalizarDesenho->setGeometry(QRect(350, 380, 101, 24));
        lineEdit_nomeObjeto = new QLineEdit(centralwidget);
        lineEdit_nomeObjeto->setObjectName("lineEdit_nomeObjeto");
        lineEdit_nomeObjeto->setGeometry(QRect(330, 310, 91, 22));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(230, 310, 91, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 290, 91, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(570, 380, 41, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(590, 290, 21, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(650, 290, 21, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(590, 330, 21, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(650, 330, 21, 16));
        checkBox_usarPontoEspecifico = new QCheckBox(centralwidget);
        checkBox_usarPontoEspecifico->setObjectName("checkBox_usarPontoEspecifico");
        checkBox_usarPontoEspecifico->setGeometry(QRect(630, 380, 171, 20));
        lineEdit_rotacao_px = new QLineEdit(centralwidget);
        lineEdit_rotacao_px->setObjectName("lineEdit_rotacao_px");
        lineEdit_rotacao_px->setGeometry(QRect(640, 420, 51, 22));
        lineEdit_rotacao_py = new QLineEdit(centralwidget);
        lineEdit_rotacao_py->setObjectName("lineEdit_rotacao_py");
        lineEdit_rotacao_py->setGeometry(QRect(700, 420, 51, 22));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(660, 400, 21, 16));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(720, 400, 21, 16));
        pushButton_addPonto = new QPushButton(centralwidget);
        pushButton_addPonto->setObjectName("pushButton_addPonto");
        pushButton_addPonto->setGeometry(QRect(230, 420, 111, 24));
        pushButton_excluir = new QPushButton(centralwidget);
        pushButton_excluir->setObjectName("pushButton_excluir");
        pushButton_excluir->setGeometry(QRect(10, 460, 111, 24));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 500, 161, 141));
        lineEdit_w_xmin = new QLineEdit(groupBox);
        lineEdit_w_xmin->setObjectName("lineEdit_w_xmin");
        lineEdit_w_xmin->setGeometry(QRect(10, 40, 51, 22));
        lineEdit_w_ymin = new QLineEdit(groupBox);
        lineEdit_w_ymin->setObjectName("lineEdit_w_ymin");
        lineEdit_w_ymin->setGeometry(QRect(90, 40, 51, 22));
        lineEdit_w_xmax = new QLineEdit(groupBox);
        lineEdit_w_xmax->setObjectName("lineEdit_w_xmax");
        lineEdit_w_xmax->setGeometry(QRect(10, 100, 51, 22));
        lineEdit_w_ymax = new QLineEdit(groupBox);
        lineEdit_w_ymax->setObjectName("lineEdit_w_ymax");
        lineEdit_w_ymax->setGeometry(QRect(90, 100, 51, 22));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 20, 61, 16));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(90, 20, 61, 16));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 80, 61, 16));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(90, 80, 61, 16));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(190, 500, 161, 141));
        lineEdit_v_xmin = new QLineEdit(groupBox_2);
        lineEdit_v_xmin->setObjectName("lineEdit_v_xmin");
        lineEdit_v_xmin->setGeometry(QRect(10, 40, 51, 22));
        lineEdit_v_ymin = new QLineEdit(groupBox_2);
        lineEdit_v_ymin->setObjectName("lineEdit_v_ymin");
        lineEdit_v_ymin->setGeometry(QRect(90, 40, 51, 22));
        lineEdit_v_xmax = new QLineEdit(groupBox_2);
        lineEdit_v_xmax->setObjectName("lineEdit_v_xmax");
        lineEdit_v_xmax->setGeometry(QRect(10, 100, 51, 22));
        lineEdit_v_ymax = new QLineEdit(groupBox_2);
        lineEdit_v_ymax->setObjectName("lineEdit_v_ymax");
        lineEdit_v_ymax->setGeometry(QRect(90, 100, 51, 22));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 20, 61, 16));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(90, 20, 61, 16));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 80, 61, 16));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(90, 80, 61, 16));
        pushButton_aplicar_wv = new QPushButton(centralwidget);
        pushButton_aplicar_wv->setObjectName("pushButton_aplicar_wv");
        pushButton_aplicar_wv->setGeometry(QRect(280, 640, 75, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 805, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
=======
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        canvasWidget = new QWidget(centralwidget);
        canvasWidget->setObjectName("canvasWidget");
        canvasWidget->setEnabled(true);

        horizontalLayout->addWidget(canvasWidget);

        controlPanelWidget = new QWidget(centralwidget);
        controlPanelWidget->setObjectName("controlPanelWidget");
        verticalLayout = new QVBoxLayout(controlPanelWidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(controlPanelWidget);
        groupBox->setObjectName("groupBox");
        pushButton_adicionar_ponto = new QPushButton(groupBox);
        pushButton_adicionar_ponto->setObjectName("pushButton_adicionar_ponto");
        pushButton_adicionar_ponto->setGeometry(QRect(20, 70, 191, 24));
        listWidget_pontos_atuais = new QListWidget(groupBox);
        listWidget_pontos_atuais->setObjectName("listWidget_pontos_atuais");
        listWidget_pontos_atuais->setGeometry(QRect(20, 100, 191, 211));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(240, 30, 120, 241));
        listWidget_objetos = new QListWidget(groupBox_2);
        listWidget_objetos->setObjectName("listWidget_objetos");
        listWidget_objetos->setGeometry(QRect(10, 30, 101, 201));
        pushButton_apagar_tudo = new QPushButton(groupBox);
        pushButton_apagar_tudo->setObjectName("pushButton_apagar_tudo");
        pushButton_apagar_tudo->setGeometry(QRect(240, 280, 121, 21));
        pushButton_finalizar_objeto = new QPushButton(groupBox);
        pushButton_finalizar_objeto->setObjectName("pushButton_finalizar_objeto");
        pushButton_finalizar_objeto->setGeometry(QRect(20, 320, 191, 24));
        lineEdit_manual_x = new QLineEdit(groupBox);
        lineEdit_manual_x->setObjectName("lineEdit_manual_x");
        lineEdit_manual_x->setGeometry(QRect(20, 30, 91, 31));
        lineEdit_manual_x->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_manual_y = new QLineEdit(groupBox);
        lineEdit_manual_y->setObjectName("lineEdit_manual_y");
        lineEdit_manual_y->setGeometry(QRect(120, 30, 91, 31));
        lineEdit_manual_y->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(groupBox);


        horizontalLayout->addWidget(controlPanelWidget);

        MainWindow->setCentralWidget(centralwidget);
>>>>>>> f47fb501572eaae1e3824d4e48f38cf1010be12a

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
<<<<<<< HEAD
        pushButton_rotacionar->setText(QCoreApplication::translate("MainWindow", "Rotacionar", nullptr));
        pushButton_escalar->setText(QCoreApplication::translate("MainWindow", "Escalonar", nullptr));
        pushButton_transladar->setText(QCoreApplication::translate("MainWindow", "Transladar", nullptr));
        pushButton_addReta->setText(QCoreApplication::translate("MainWindow", "Adicionar Reta", nullptr));
        pushButton_addPoligono->setText(QCoreApplication::translate("MainWindow", "Adicionar Poligino", nullptr));
        pushButton_finalizarDesenho->setText(QCoreApplication::translate("MainWindow", "Finalizar Poligino", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nome do Objeto", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Lista de Objetos", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Angulo", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        checkBox_usarPontoEspecifico->setText(QCoreApplication::translate("MainWindow", "Rotacionar Ponto Espec\303\255fico", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        pushButton_addPonto->setText(QCoreApplication::translate("MainWindow", "Desenhar Ponto", nullptr));
        pushButton_excluir->setText(QCoreApplication::translate("MainWindow", "Excluir Objeto", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Window", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "X m\303\255nimo", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Y m\303\255nimo", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "X m\303\241ximo", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Y m\303\241ximo", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Viewport", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "X m\303\255nimo", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Y m\303\255nimo", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "X m\303\241ximo", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Y m\303\241ximo", nullptr));
        pushButton_aplicar_wv->setText(QCoreApplication::translate("MainWindow", "Aplicar", nullptr));
=======
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        pushButton_adicionar_ponto->setText(QCoreApplication::translate("MainWindow", "Adicionar Ponto", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Objetos existentes", nullptr));
        pushButton_apagar_tudo->setText(QCoreApplication::translate("MainWindow", "Limpar Tudo", nullptr));
        pushButton_finalizar_objeto->setText(QCoreApplication::translate("MainWindow", "Criar Objeto", nullptr));
        lineEdit_manual_x->setPlaceholderText(QCoreApplication::translate("MainWindow", "Coordenada X", nullptr));
        lineEdit_manual_y->setPlaceholderText(QCoreApplication::translate("MainWindow", "Coordenada Y", nullptr));
>>>>>>> f47fb501572eaae1e3824d4e48f38cf1010be12a
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
