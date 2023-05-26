//#pragma once
#ifndef RENDERROUTE_H
#define RENDERROUTE_H
#include"QObject"
#include <string>
#include "pipeline.h"
#include "Geometry.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "DirectionLight.h"

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
private:
	
	bool stopped;
	int width, height, channel;
	Pipeline* pipeline;
	std::vector<Geometry*> geolist;
	std::vector<Shader*> shaderlist;
};

#endif