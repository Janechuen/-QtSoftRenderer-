#pragma once
#include <iostream> 
#include <fstream>//
#include <sstream>//读取文件用
#include <string>

#include <vector>
#include <cassert>
#include <cmath>
#include <Core.h>
#include <Vertex.h>

class Mesh 
{	
public:
	
	std::vector<Vertex> vertices; //position 属性
	std::vector<unsigned int> index; //index 索引属性//【临时功能】后续删除
	//从OBJ中获取的数据
	std::vector<vec3>position;
	std::vector<vec3>normal;
	std::vector<vec2>texcoord;
	std::vector<int>p_index;
	std::vector<int>n_index;
	std::vector<int>uv_index;


	Mesh() {}
	~Mesh() {}
	Mesh(const Mesh& msh) :vertices(msh.vertices), index(msh.index) {}
	Mesh& operator=(const Mesh& msh);
	void setVertices(Vertex* v, int count);//设置
	void setIndex(int* i, int count); //设置EBO索引序列
	void triangle(vec4& v1, vec4& v2, vec4& v3);//【临时功能】后续删除
	void LoadMesh(const std::string filename);//OBJ模型加载功能

};
