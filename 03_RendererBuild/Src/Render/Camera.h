#include <iostream>
#include "Core.h"
#pragma once
class Camera
{
public:
	//Geo 世界信息
	vec3 Translate;
	vec3 Rotate;
	double cameranear;
	double camerafar;
	double fov;
	Camera() {}
	~Camera() {}
	void SetCamera(double near, double far, double cfov, vec3 t, vec3 r);
private:

};



//Camera::~Camera()
//{
//}