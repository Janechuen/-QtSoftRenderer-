/********************************************************************************
** Form generated from reading UI file 'DrawLine.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWLINE_H
#define UI_DRAWLINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawLineClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DrawLineClass)
    {
        if (DrawLineClass->objectName().isEmpty())
            DrawLineClass->setObjectName(QString::fromUtf8("DrawLineClass"));
        DrawLineClass->resize(600, 400);
        menuBar = new QMenuBar(DrawLineClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        DrawLineClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DrawLineClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DrawLineClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(DrawLineClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        DrawLineClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DrawLineClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DrawLineClass->setStatusBar(statusBar);

        retranslateUi(DrawLineClass);

        QMetaObject::connectSlotsByName(DrawLineClass);
    } // setupUi

    void retranslateUi(QMainWindow *DrawLineClass)
    {
        DrawLineClass->setWindowTitle(QCoreApplication::translate("DrawLineClass", "DrawLine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DrawLineClass: public Ui_DrawLineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWLINE_H
