#include "_DrawTriangle.h"
#include <QtWidgets/QApplication>//qt�����ļ�
#include <vector>
#include <Core.h>

int main(int argc, char* argv[]) //����ʹ������������main ��Ҫͨ�������δ���QTӦ�ó���
{
	QApplication a(argc, argv); //Ӧ��ʵ������ ֻ��һ��
	_DrawTriangle w;  //�������ڶ���
	w.show();//��ʾ����
	return a.exec();//��Ϣѭ�� �����¼�
}