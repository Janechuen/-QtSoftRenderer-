#include "Shader.h"
V2F Shader::vertexShader(const Vertex& in) {
	V2F ret;
	ret.posM2W = in.Position;
	ret.posV2P = in.Position;
	ret.color = in.Color;
	ret.normal = in.Normal;
	ret.oneDivZ = 1.0;
	ret.texcoord = in.texcoord0;
	return ret;
}
vec4 Shader::fragmentShader(const V2F& in)
{
	vec4 retColor;
	retColor = in.color;
	return retColor;
}