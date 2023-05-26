#include <Mesh.h>
#include "Mesh.h"

Mesh& Mesh::operator=(const Mesh& msh)
{
	vertices = msh.vertices;
	index = msh.index;
	return *this;
}

void Mesh::setVertices(Vertex* v, int count)
{
	vertices.resize(static_cast<unsigned long>(count));
	new(&vertices[0])std::vector<Vertex>(v, v + count);
}

void Mesh::setIndex(int* i, int count)
{
	index.resize(static_cast<unsigned long >(count));
	new(&index)std::vector<unsigned int>(i, i + count);
}

/*void Mesh::triangle(vec4& v1, vec4& v2, vec4& v3)
{
	vertices.resize(3);
	index.resize(3);
	vertices[0].Position = v1;
	vertices[0].Normal = { 0.0, 0.0, 1.0 };
	vertices[0].Color = { 1.f, 0.f, 0.f, 1.f };
	vertices[0].texcoord0 = vec2{ 0.f, 0.f };
	vertices[1].Position = v2;
	vertices[1].Normal = vec3{ 0.f, 0.f, 1.f };
	vertices[1].Color = vec4{ 0.f, 1.f, 0.f, 1.f };
	vertices[1].texcoord0 = vec2{ 1.f, 0.f };
	vertices[2].Position = v3;
	vertices[2].Normal = vec3{ 0.f, 0.f, 1.f };
	vertices[2].Color = vec4{ 0.f, 0.f, 1.f, 1.f };
	vertices[2].texcoord0 = vec2{ 0.5f, 1.f };
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
}*/

//Load OBJ Mesh
void Mesh::LoadMesh(const std::string filename)
{
	std::ifstream in;
	in.open(filename, std::ifstream::in);
	if (in.fail())return;
	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		//判断所在行是否有v 有则为顶点位置
		if (!line.compare(0,2,"v "))
		{
			iss >> trash;
			vec3 v;
			for(int i = 0; i < 3; i++)iss >> v[i];
			position.push_back(v);//存储顶点
		}
		//判断所在行是否有vn 有则为法线
		else if(!line.compare(0,3,"vn "))
		{
			iss >> trash >> trash;//将vn放入垃圾桶 以便获取正确数据
			vec3 n;
			for (int i = 0; i < 3; i++)iss >> n[i];
			normal.push_back(n);

		}
		//判断所在行是否有vt 有则为uv
		else if(!line.compare(0,3,"vt "))
		{
			iss >> trash >> trash;//将vt放入垃圾桶 以便获取正确数据
			vec2 uv;
			for (int i = 0; i < 2; i++)iss >> uv[i];
			texcoord.push_back({ uv.x,uv.y });
		}
		//判断所在行是否有f 有则为三角面信息
		else if(!line.compare(0,2,"f "))
		{
			int f, n, t;
			iss >> trash;
			int cnt;
			/*
			f 面数据的格式为 f 1/2/3 其顺序为位置信息 纹理索引 法线信息 
			*/
			while (iss>>f>>trash>>t>>trash>>n)
			{
				//这里--f 是因为模型索引从1开始 而vector索引从0开始
				p_index.push_back(--f);
				n_index.push_back(--n);
				uv_index.push_back(--t);
				cnt++;
			}
			//检测模型是否出现三角面
			if (3!=cnt)
			{
				std::cerr << "ERROR:OBJ 模型只支持加载三角面" << std::endl;
			}
			
		}
	}
	return;
}