#include "Renderer.h"
#include <QtWidgets/QApplication>//qt�����ļ�
#include <Mesh.h>
int main(int argc, char* argv[]) //����ʹ������������main ��Ҫͨ�������δ���QTӦ�ó���
{
	int i = 0;
	QApplication a(argc, argv); //Ӧ��ʵ������ ֻ��һ��
	Renderer w;  //�������ڶ���
	w.show();//��ʾ����
	return a.exec();//��Ϣѭ�� �����¼�
}
