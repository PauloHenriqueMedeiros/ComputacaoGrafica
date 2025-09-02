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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
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

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        pushButton_adicionar_ponto->setText(QCoreApplication::translate("MainWindow", "Adicionar Ponto", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Objetos existentes", nullptr));
        pushButton_apagar_tudo->setText(QCoreApplication::translate("MainWindow", "Limpar Tudo", nullptr));
        pushButton_finalizar_objeto->setText(QCoreApplication::translate("MainWindow", "Criar Objeto", nullptr));
        lineEdit_manual_x->setPlaceholderText(QCoreApplication::translate("MainWindow", "Coordenada X", nullptr));
        lineEdit_manual_y->setPlaceholderText(QCoreApplication::translate("MainWindow", "Coordenada Y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
