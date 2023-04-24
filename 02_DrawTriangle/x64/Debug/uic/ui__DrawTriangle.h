/********************************************************************************
** Form generated from reading UI file '_DrawTriangle.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI__DRAWTRIANGLE_H
#define UI__DRAWTRIANGLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui__DrawTriangleClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *_DrawTriangleClass)
    {
        if (_DrawTriangleClass->objectName().isEmpty())
            _DrawTriangleClass->setObjectName(QString::fromUtf8("_DrawTriangleClass"));
        _DrawTriangleClass->resize(600, 400);
        menuBar = new QMenuBar(_DrawTriangleClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        _DrawTriangleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(_DrawTriangleClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        _DrawTriangleClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(_DrawTriangleClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        _DrawTriangleClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(_DrawTriangleClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        _DrawTriangleClass->setStatusBar(statusBar);

        retranslateUi(_DrawTriangleClass);

        QMetaObject::connectSlotsByName(_DrawTriangleClass);
    } // setupUi

    void retranslateUi(QMainWindow *_DrawTriangleClass)
    {
        _DrawTriangleClass->setWindowTitle(QCoreApplication::translate("_DrawTriangleClass", "_DrawTriangle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class _DrawTriangleClass: public Ui__DrawTriangleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI__DRAWTRIANGLE_H
