#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DrawLine.h"

class DrawLine : public QMainWindow
{
    Q_OBJECT

public:
    DrawLine(QWidget *parent = nullptr);
    ~DrawLine();

private:
    Ui::DrawLineClass ui;
};
