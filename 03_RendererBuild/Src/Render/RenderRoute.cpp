#include "RenderRoute.h"

RenderRoute::RenderRoute(int w, int h, QObject* parent)
	: QObject(parent), width(w), height(h), channel(4)
{
	stopped = false;
	pipeline = new Pipeline(width, height);
}

void RenderRoute::stopIt() {
	stopped = true;
}

//Appdata RenderRoute::BindRenderingGeometry(Mesh* mesh,std::string f,Pipeline* pipeline)
//{
//	//mesh->LoadMesh(f);
//	//pipeline->SetPositionBuffer(mesh->position);//���ù�����Ķ���
//	//pipeline->SetNormalBuffer(mesh->normal);
//	//pipeline->SetTexcoordBuffer(mesh->texcoord);
//	//pipeline->SetFaceBuffer(mesh->p_index, mesh->n_index, mesh->uv_index);
//	//Appdata appdata;
//	//�����ж�ʹ��ʲô���͵����ݽṹ�� ����OBJʶ��ͬ�Ľṹ��
//	//appdata.POSITION = mesh->position;
//	//appdata.NORMAL = mesh->normal;
//	//appdata.TEXCOORD0 = mesh->texcoord;
//	//appdata.P_INDEX = mesh->p_index;
//	//appdata.N_INDEX = mesh->n_index;
//	//appdata.UV_INDEX = mesh->uv_index;
//	//return appdata;
//}

void RenderRoute::loop()
{
	//���߳�ʼ��
	pipeline->initialize();

	//std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Obj02.obj";

	//��ģ�� ���顿
	std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube.obj";
	vec3 translate = vec3{ 0,0,3 };
	vec3 rotate = vec3{ 20,0,0 };//220 * 3.14 / 180.f;
	vec3 scale = vec3{ 1,1,1 };
	vec3 translate1 = vec3{ 3,0,7 };
	vec3 rotate1 = vec3{ 20,0,0 };//220 * 3.14 / 180.f;
	vec3 scale1 = vec3{ 0.8,0.8,0.8 };
	
	//��ģ�� ���ճ���
	//std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/UAZ_Bobik.obj";
	//vec3 translate = vec3{ 0,-5,15 };
	//vec3 rotate = vec3{ 20,0,0 };//220 * 3.14 / 180.f;
	//vec3 scale = vec3{ 0.1,0.1,0.1 };
	//vec3 campos = vec3{ 0,0,-10 };
	//vec3 camrote = vec3{ 0,0,0 };
	Geometry* geo01 = new Geometry();//������Ⱦ������
	geo01->SetMesh(meshfile, translate, rotate, scale);
	geolist.push_back(geo01);

	Geometry* geo02 = new Geometry();//������Ⱦ������
	geo02->SetMesh(meshfile, translate1, rotate1, scale1);
	geolist.push_back(geo02);

	vec3 campos = vec3{ 0,0,-10 };
	vec3 camrote = vec3{ 0,0,0 };
	while (!stopped)
	{
		pipeline->clearBuffer(vec4{ 0, 0, 0, 1.0f });//��Ⱦѭ��While�ڽ���һ֡���ƺõ�ͼ�����ΪĬ����ɫ �������Ϊ��ɫ
		geo01->SetRotate(0.01);
		Camera* cam = new Camera();//�����ʼ��
		cam->SetCamera(0.3, 50, 90 * 3.14 / 180.f, campos, camrote);
		//����Ⱦ���ڡ�
		
		pipeline->SetCamera(cam);
		//����Ҫ�����ж��ٸ�ģ�� �����ٰ��Ż���
		for (int i =0;i<geolist.size();i++)
		{
			pipeline->SetGeometry(geolist[i]);//
			pipeline->drawIndex(Pipeline::Fill3D);  //��Ⱦѭ��While�ں��ĺ������������ͼ��
			   //˫���彻�� ��ΪDrawIndex���Ƶ���back 	
		}
		pipeline->swapBuffer();
		emit RenderRoute::frameOut(pipeline->output());
	}
}