#include "Vector.h"

//二维向量叉积
double cross_2(const vec2& A, const vec2& B)
{
	double temp = 0;
	temp = (double)(A.x * B.y - A.y * B.x);
	return temp;
}

//三维向量叉积
vec3 cross(const vec3& A, const vec3& B)
{
	return vec<3>{A.y* B.z - A.z * B.y, A.z* B.x - A.x * B.z, A.x* B.y - A.y * B.x};
}

vec4 cross_4(const vec4& A, const vec4& B)
{
	return vec<4>{A.y* B.z - A.z * B.y, A.z* B.x - A.x * B.z, A.x* B.y - A.y * B.x,0};
}