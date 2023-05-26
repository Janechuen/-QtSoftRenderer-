/********************************************************************************
** Form generated from reading UI file '_DrawLine.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI__DRAWLINE_H
#define UI__DRAWLINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui__DrawLineClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *_DrawLineClass)
    {
        if (_DrawLineClass->objectName().isEmpty())
            _DrawLineClass->setObjectName(QString::fromUtf8("_DrawLineClass"));
        _DrawLineClass->resize(600, 400);
        menuBar = new QMenuBar(_DrawLineClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        _DrawLineClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(_DrawLineClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        _DrawLineClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(_DrawLineClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        _DrawLineClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(_DrawLineClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        _DrawLineClass->setStatusBar(statusBar);

        retranslateUi(_DrawLineClass);

        QMetaObject::connectSlotsByName(_DrawLineClass);
    } // setupUi

    void retranslateUi(QMainWindow *_DrawLineClass)
    {
        _DrawLineClass->setWindowTitle(QCoreApplication::translate("_DrawLineClass", "_DrawLine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class _DrawLineClass: public Ui__DrawLineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI__DRAWLINE_H
