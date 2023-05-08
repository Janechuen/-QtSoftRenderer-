#pragma once
#include <iostream> 
#include <fstream>//
#include <sstream>//��ȡ�ļ���
#include <string>

#include <vector>
#include <cassert>
#include <cmath>
#include <Core.h>
#include <Vertex.h>

class Mesh 
{	
public:
	
	std::vector<Vertex> vertices; //position ����
	std::vector<unsigned int> index; //index ��������//����ʱ���ܡ�����ɾ��
	//��OBJ�л�ȡ������
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
	void setVertices(Vertex* v, int count);//����
	void setIndex(int* i, int count); //����EBO��������
	void triangle(vec4& v1, vec4& v2, vec4& v3);//����ʱ���ܡ�����ɾ��
	void LoadMesh(const std::string filename);//OBJģ�ͼ��ع���

};
