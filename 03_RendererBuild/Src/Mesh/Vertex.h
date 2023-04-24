#pragma once
#include <Core.h>
//备忘：获取原始模型数据 将数据整理为可用
/*
* 目前只识别如此信息
01. Position 顶点位置信息
02. UV Texcoord 模型UV坐标
03. Normal 模型发现信息
04. Color 模型顶点色信息
*/
class Vertex
{
public:
	vec4 Position;
	vec2 texcoord0;
	vec3 Normal;
	vec4 Color;
	Vertex() {}//构造函数
	~Vertex() {}
	Vertex(vec4 pos, vec4 col, vec2 tex, vec3 nor) : //复制构造函数
		Position(pos), Color(col), texcoord0(tex), Normal(nor) {}
	Vertex(const Vertex& ver) :  //复制构造函数
		Position(ver.Position),
		Color(ver.Color),
		texcoord0(ver.texcoord0),
		Normal(ver.Normal) {}
private:

};

