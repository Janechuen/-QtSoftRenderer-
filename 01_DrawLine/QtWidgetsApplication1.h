#pragma once
#include <QtWidgets/QMainWindow>
#include "ui__DrawLine.h"
//#include "Qpainter.h"

class QtWidgetsApplication1 : public QMainWindow //：继承自Qmainwindow类
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);//构造函数
    ~QtWidgetsApplication1(); //析构函数
    void paintEvent(QPaintEvent* event);
    

private:
    Ui::_DrawLineClass ui;
};
