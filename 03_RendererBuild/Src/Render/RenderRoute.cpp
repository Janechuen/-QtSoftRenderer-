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

void RenderRoute::loop()
{
	////���߳�ʼ��
	pipeline->initialize();

	////��ģ�� ����01��
	////std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube.obj";
	//std::string meshfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube03.obj";
	//vec3 translate = vec3{ 0,1,-4 };
	//vec3 rotate = vec3{220 * 3.14 / 180.f,220 * 3.14 / 180.f,0 };//220 * 3.14 / 180.f;
	//vec3 scale = vec3{ 2,2,2 };
	//Geometry* geo01 = new Geometry();//������Ⱦ������
	//geo01->SetMesh(meshfile, translate, rotate, scale);//�O�ü�����
	//geolist.push_back(geo01);//��������ѹ�뼸�����б�
	//Shader* shader01 = new Shader();//������ɫ��
	////std::string diffusefile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/S0043_GLOW_1.tga";
	//std::string diffusefile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/D.tga";
	//std::string normalfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/nor03.tga";
	//shader01->SetTexture(diffusefile,Shader::DiffuseTex);
	//shader01->SetTexture(normalfile, Shader::NormalTex);
	//shaderlist.push_back(shader01); //����ɫ��ѹ����ɫ���б�
	////��Camera������ԡ�
	//Camera* cam = new Camera();//�����ʼ��
	//vec3 campos = vec3{ 0,1,0 };
	//vec3 camrote = vec3{ 0,0,0 };
	//cam->SetCamera(0.3, 50, 90 * 3.14 / 180.f, campos, camrote);
	////��DirectionLight���ԡ�
	//DirectionLight* dirLight = new DirectionLight();//������ʼ��
	//dirLight->intensity = 1;
	//dirLight->pos = vec4{ 0,0,1,0 };
	//dirLight->color = vec4{ 1,0.92,0.56,0 };




	//��ģ�� ��01��
	//std::string meshfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Sphere.obj";
	//vec3 translate = vec3{ 0,0,-2 };
	//vec3 rotate = vec3{0,0,0 };//220 * 3.14 / 180.f;
	//vec3 scale = vec3{ 1,1,1 };
	//Geometry* geo01 = new Geometry();//������Ⱦ������
	//geo01->SetMesh(meshfile, translate, rotate, scale);//�O�ü�����
	//geolist.push_back(geo01);//��������ѹ�뼸�����б�
	//Shader* shader01 = new Shader();//������ɫ��
	////std::string diffusefile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/D.tga";
	////shader01->SetTexture(diffusefile, Shader::DiffuseTex);
	////std::string normalfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/nor01.tga";
	////shader01->SetTexture(normalfile, Shader::NormalTex);
	//shaderlist.push_back(shader01); //����ɫ��ѹ����ɫ���б�
	////��Camera������ԡ�
	//Camera* cam = new Camera();//�����ʼ��
	//vec3 campos = vec3{ 0,0,-2 };
	//vec3 camrote = vec3{ 0,0,0 };

	////��DirectionLight���ԡ�
	//DirectionLight* dirLight = new DirectionLight();//������ʼ��
	//dirLight->intensity = 1;
	//dirLight->pos = vec4{ 1,1,-1,0 };
	//dirLight->color = vec4{ 1,0.92,0.56,0 };


	//��ģ�� ����02��
	//std::string cubeMeshfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube.obj";
	//vec3 translate1 = vec3{ 3,0,7 };
	//vec3 rotate1 = vec3{ 20,0,0 };//220 * 3.14 / 180.f;
	//vec3 scale1 = vec3{ 0.8,0.8,0.8 };
	//Geometry* geo02 = new Geometry();//������Ⱦ������
	//geo02->SetMesh(cubeMeshfile, translate1, rotate1, scale1);
	//geolist.push_back(geo02);
	//Shader* shader02 = new Shader();//������ɫ��
	//shaderlist.push_back(shader02); //����ɫ��ѹ����ɫ���б�

	//��ģ�� ���ճ���
	std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/UAZ_Bobik.obj";
	vec3 translate = vec3{ 0,0,0 };
	//vec3 rotate = vec3{ 90 * 3.14 / 180.f,90 * 3.14 / 180.f,0 };//220 * 3.14 / 180.f;
	vec3 rotate = vec3{ 0,200 * 3.14 / 180.f,0 };//220 * 3.14 / 180.f;
	vec3 scale = vec3{ 0.01,0.01,0.01 };
	Geometry* geo01 = new Geometry();//������Ⱦ������
	geo01->SetMesh(meshfile, translate, rotate, scale);//�O�ü�����
	geolist.push_back(geo01);//��������ѹ�뼸�����б�
	Shader* shader01 = new Shader();//������ɫ��
	std::string diffusefile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/Car_01.tga";
	shader01->SetTexture(diffusefile, Shader::DiffuseTex);
	std::string normalfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/Car_01_N.tga";
	shader01->SetTexture(normalfile, Shader::NormalTex);
	shaderlist.push_back(shader01); //����ɫ��ѹ����ɫ���б�
	//��Camera������ԡ�
	Camera* cam = new Camera();//�����ʼ��
	vec3 campos = vec3{ 0,0.5,-1.5 };
	vec3 camrote = vec3{ 0,0,0 };
	cam->SetCamera(0.3, 50, 90 * 3.14 / 180.f, campos, camrote);
	//��DirectionLight���ԡ�
	DirectionLight* dirLight = new DirectionLight();//������ʼ��
	dirLight->intensity = 1;
	dirLight->pos = vec4{ 0,0,-1,0 };
	dirLight->color = vec4{ 1,0.92,0.56,0 };


	while (!stopped)
	{
		pipeline->clearBuffer(vec4{ 0, 0, 0, 1.0f });//��Ⱦѭ��While�ڽ���һ֡���ƺõ�ͼ�����ΪĬ����ɫ �������Ϊ��ɫ
		//geo01->SetRotate(0.01);
		//����Ⱦ���ڡ�
		
		//����Ҫ�����ж��ٸ�ģ�� �����ٰ��Ż���
		for (int i =0;i<geolist.size();i++)
		{
			pipeline->SetCamera(cam);//�������
			pipeline->SetGeometry(geolist[i]);//���������������������Ⱦ
			pipeline->SetShader(shaderlist[i]);//��������󶨵���ɫ�����������ɫ
			pipeline->SetLight(dirLight);
			pipeline->drawIndex(Pipeline::Fill3D);  //��Ⱦѭ��While�ں��ĺ������������ͼ��  	
		}
		pipeline->swapBuffer();//˫���彻�� ��ΪDrawIndex���Ƶ���back 
		emit RenderRoute::frameOut(pipeline->output()); //���Buffer �����Ƴɹ���Buffer�������ϼ�Render
	}
}