#pragma once
#include <QtWidgets/QMainWindow>
#include "ui__DrawLine.h"
//#include "Qpainter.h"

class QtWidgetsApplication1 : public QMainWindow //���̳���Qmainwindow��
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);//���캯��
    ~QtWidgetsApplication1(); //��������
    void paintEvent(QPaintEvent* event);
    

private:
    Ui::_DrawLineClass ui;
};
