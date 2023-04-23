#pragma once
#include <Core.h>
#include <QtWidgets/QMainWindow>
#include "Qpainter.h"
#include "ui__DrawTriangle.h"
#include <vector>
#include <cmath>
class _DrawTriangle :public QMainWindow
{
	Q_OBJECT
public:
	_DrawTriangle(QWidget * parent = nullptr);
	bool PixelinTriangle(vec2 p1, vec2 p2, vec2 p3, int x, int y);
	vec3 PixelinTriangleColor(vec2 p1, vec2 p2, vec2 p3, int x, int y);
	void paintEvent(QPaintEvent* event);
private:
	Ui::_DrawTriangleClass ui;
};

