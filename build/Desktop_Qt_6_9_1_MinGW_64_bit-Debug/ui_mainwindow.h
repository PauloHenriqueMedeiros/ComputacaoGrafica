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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSpinBox *spinBox_lados;
    QPushButton *pushButton_desenhar;
    QPushButton *pushButton_apagar;
    QSpinBox *spinBox_manual_x;
    QSpinBox *spinBox_manual_y;
    QPushButton *pushButton_adicionar_ponto;
    QListWidget *listWidget_pontos;
    QPushButton *pushButton_desenhar_manual;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        spinBox_lados = new QSpinBox(centralwidget);
        spinBox_lados->setObjectName("spinBox_lados");
        spinBox_lados->setGeometry(QRect(11, 370, 81, 25));
        pushButton_desenhar = new QPushButton(centralwidget);
        pushButton_desenhar->setObjectName("pushButton_desenhar");
        pushButton_desenhar->setGeometry(QRect(100, 370, 80, 24));
        pushButton_apagar = new QPushButton(centralwidget);
        pushButton_apagar->setObjectName("pushButton_apagar");
        pushButton_apagar->setGeometry(QRect(190, 370, 80, 24));
        spinBox_manual_x = new QSpinBox(centralwidget);
        spinBox_manual_x->setObjectName("spinBox_manual_x");
        spinBox_manual_x->setGeometry(QRect(640, 0, 71, 31));
        spinBox_manual_x->setMaximum(9999999);
        spinBox_manual_y = new QSpinBox(centralwidget);
        spinBox_manual_y->setObjectName("spinBox_manual_y");
        spinBox_manual_y->setGeometry(QRect(720, 0, 71, 31));
        spinBox_manual_y->setMaximum(9999999);
        pushButton_adicionar_ponto = new QPushButton(centralwidget);
        pushButton_adicionar_ponto->setObjectName("pushButton_adicionar_ponto");
        pushButton_adicionar_ponto->setGeometry(QRect(660, 40, 111, 24));
        listWidget_pontos = new QListWidget(centralwidget);
        listWidget_pontos->setObjectName("listWidget_pontos");
        listWidget_pontos->setGeometry(QRect(660, 70, 111, 231));
        pushButton_desenhar_manual = new QPushButton(centralwidget);
        pushButton_desenhar_manual->setObjectName("pushButton_desenhar_manual");
        pushButton_desenhar_manual->setGeometry(QRect(640, 310, 141, 24));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_desenhar->setText(QCoreApplication::translate("MainWindow", "Desenhar", nullptr));
        pushButton_apagar->setText(QCoreApplication::translate("MainWindow", "Apagar", nullptr));
        pushButton_adicionar_ponto->setText(QCoreApplication::translate("MainWindow", "Adicionar Ponto", nullptr));
        pushButton_desenhar_manual->setText(QCoreApplication::translate("MainWindow", "Desenhar Forma Manual", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
