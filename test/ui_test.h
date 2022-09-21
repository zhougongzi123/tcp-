/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testClass
{
public:
    QWidget *centralWidget;
    QPushButton *test;
    QPushButton *UnCompress;
    QLineEdit *filename;
    QLineEdit *formFilename;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *testClass)
    {
        if (testClass->objectName().isEmpty())
            testClass->setObjectName(QStringLiteral("testClass"));
        testClass->resize(600, 400);
        centralWidget = new QWidget(testClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        test = new QPushButton(centralWidget);
        test->setObjectName(QStringLiteral("test"));
        test->setGeometry(QRect(60, 210, 75, 23));
        UnCompress = new QPushButton(centralWidget);
        UnCompress->setObjectName(QStringLiteral("UnCompress"));
        UnCompress->setGeometry(QRect(160, 210, 75, 23));
        filename = new QLineEdit(centralWidget);
        filename->setObjectName(QStringLiteral("filename"));
        filename->setGeometry(QRect(60, 170, 271, 20));
        formFilename = new QLineEdit(centralWidget);
        formFilename->setObjectName(QStringLiteral("formFilename"));
        formFilename->setGeometry(QRect(60, 140, 271, 20));
        testClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(testClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        testClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(testClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        testClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(testClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        testClass->setStatusBar(statusBar);

        retranslateUi(testClass);

        QMetaObject::connectSlotsByName(testClass);
    } // setupUi

    void retranslateUi(QMainWindow *testClass)
    {
        testClass->setWindowTitle(QApplication::translate("testClass", "test", nullptr));
        test->setText(QApplication::translate("testClass", "\345\216\213\347\274\251", nullptr));
        UnCompress->setText(QApplication::translate("testClass", "\350\247\243\345\216\213", nullptr));
        filename->setText(QApplication::translate("testClass", "D:\\\351\241\271\347\233\256\\QT\345\255\246\344\271\240\\test.zip", nullptr));
        formFilename->setText(QApplication::translate("testClass", "D:\\\351\241\271\347\233\256\\QT\345\255\246\344\271\240\\test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testClass: public Ui_testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
