#include "Camera.h"

void Camera::SetCamera(double near, double far, double cfov, vec3 t, vec3 r)
{

	cameranear = near;
	camerafar = far;
	fov = cfov;
	Translate = t;
	Rotate = r;
}