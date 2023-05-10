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

Appdata RenderRoute::BindRenderingGeometry(Mesh* mesh,std::string f,Pipeline* pipeline)
{
	mesh->LoadMesh(f);
	pipeline->SetPositionBuffer(mesh->position);//���ù�����Ķ���
	pipeline->SetNormalBuffer(mesh->normal);
	pipeline->SetTexcoordBuffer(mesh->texcoord);
	pipeline->SetFaceBuffer(mesh->p_index, mesh->n_index, mesh->uv_index);
	Appdata appdata;
	//�����ж�ʹ��ʲô���͵����ݽṹ�� ����OBJʶ��ͬ�Ľṹ��
	appdata.POSITION = mesh->position;
	appdata.NORMAL = mesh->normal;
	appdata.TEXCOORD0 = mesh->texcoord;
	appdata.P_INDEX = mesh->p_index;
	appdata.N_INDEX = mesh->n_index;
	appdata.UV_INDEX = mesh->uv_index;
	return appdata;
}

void RenderRoute::loop()
{
	//���߳�ʼ��
	pipeline->initialize();

	while (!stopped)
	{
		/*
		ģ�ͼ��� ׼��
		*/
		Mesh* mesh = new Mesh;
		//std::string meshfile= "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube.obj";
		std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/UAZ_Bobik.obj";
		//std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Obj02.obj";
		Appdata a = BindRenderingGeometry(mesh, meshfile, pipeline);
		/*
		����Ⱦ���ڡ�
		*/ 
		//��Ⱦѭ��While�ڽ���һ֡���ƺõ�ͼ�����ΪĬ����ɫ �������Ϊ��ɫ
		pipeline->clearBuffer(vec4{0, 0, 0, 1.0f});
		//��Ⱦѭ��While�ں��ĺ������������ͼ��
		pipeline->drawIndex(Pipeline::DEPTH3D,a);
		//˫���彻�� ��ΪDrawIndex���Ƶ���back 
		pipeline->swapBuffer();
		emit RenderRoute::frameOut(pipeline->output());
	}
}