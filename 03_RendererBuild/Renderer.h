#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>
#include "ui_Renderer.h"
#include <Core.h>
#include "QPushButton.h"
#include "Qpainter.h"
#include <algorithm>
#include <RenderRoute.h>
#include "QThread.h"
class Renderer : public QMainWindow
{
	Q_OBJECT

public:
	Renderer(QWidget* parent = nullptr);
	~Renderer();
	//»æÖÆÍ¼ÐÎº¯Êý

	void receiveFrame(unsigned char* data);

	QThread* loopThread;
	RenderRoute* loop;
	unsigned char* data;
private:
	Ui::RendererClass* ui;
	QImage* RenderWindow;
	void paintEvent(QPaintEvent* event) override;
};
