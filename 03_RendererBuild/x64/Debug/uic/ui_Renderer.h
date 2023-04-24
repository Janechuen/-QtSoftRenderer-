/********************************************************************************
** Form generated from reading UI file 'Renderer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RendererClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RendererClass)
    {
        if (RendererClass->objectName().isEmpty())
            RendererClass->setObjectName(QString::fromUtf8("RendererClass"));
        RendererClass->resize(600, 400);
        menuBar = new QMenuBar(RendererClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        RendererClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RendererClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RendererClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(RendererClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        RendererClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(RendererClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RendererClass->setStatusBar(statusBar);

        retranslateUi(RendererClass);

        QMetaObject::connectSlotsByName(RendererClass);
    } // setupUi

    void retranslateUi(QMainWindow *RendererClass)
    {
        RendererClass->setWindowTitle(QCoreApplication::translate("RendererClass", "Renderer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RendererClass: public Ui_RendererClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERER_H
