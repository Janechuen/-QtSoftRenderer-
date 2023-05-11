//#pragma once
#ifndef RENDERROUTE_H
#define RENDERROUTE_H
#include"QObject"
#include "pipeline.h"
#include "Geometry.h"
#include "Camera.h"
#include <string>
#include <Mesh.h>

//#include <Appdata.h>
#include "Appdata.h"

class RenderRoute :public QObject
{
	Q_OBJECT
signals:
	void frameOut(unsigned char* image) ;
public:
	explicit RenderRoute(int w, int h, QObject* parent = nullptr);
	~RenderRoute() {};
	void stopIt();
public slots:
	void loop();
	//Appdata BindRenderingGeometry(Mesh* mesh, std::string f, Pipeline* pipeline);
private:
	bool stopped;
	int width, height, channel;
	Pipeline* pipeline;
	std::vector<Geometry*> geolist;
};

#endif