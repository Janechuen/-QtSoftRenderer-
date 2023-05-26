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
		//�ж��������Ƿ���v ����Ϊ����λ��
		if (!line.compare(0,2,"v "))
		{
			iss >> trash;
			vec3 v;
			for(int i = 0; i < 3; i++)iss >> v[i];
			position.push_back(v);//�洢����
		}
		//�ж��������Ƿ���vn ����Ϊ����
		else if(!line.compare(0,3,"vn "))
		{
			iss >> trash >> trash;//��vn��������Ͱ �Ա��ȡ��ȷ����
			vec3 n;
			for (int i = 0; i < 3; i++)iss >> n[i];
			normal.push_back(n);

		}
		//�ж��������Ƿ���vt ����Ϊuv
		else if(!line.compare(0,3,"vt "))
		{
			iss >> trash >> trash;//��vt��������Ͱ �Ա��ȡ��ȷ����
			vec2 uv;
			for (int i = 0; i < 2; i++)iss >> uv[i];
			texcoord.push_back({ uv.x,uv.y });
		}
		//�ж��������Ƿ���f ����Ϊ��������Ϣ
		else if(!line.compare(0,2,"f "))
		{
			int f, n, t;
			iss >> trash;
			int cnt;
			/*
			f �����ݵĸ�ʽΪ f 1/2/3 ��˳��Ϊλ����Ϣ �������� ������Ϣ 
			*/
			while (iss>>f>>trash>>t>>trash>>n)
			{
				//����--f ����Ϊģ��������1��ʼ ��vector������0��ʼ
				p_index.push_back(--f);
				n_index.push_back(--n);
				uv_index.push_back(--t);
				cnt++;
			}
			//���ģ���Ƿ����������
			if (3!=cnt)
			{
				std::cerr << "ERROR:OBJ ģ��ֻ֧�ּ���������" << std::endl;
			}
			
		}
	}
	return;
}