#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>//qt�����ļ�

int main(int argc, char *argv[]) //����ʹ������������main ��Ҫͨ�������δ���QTӦ�ó���
{
    int i = 0;
    QApplication a(argc, argv); //Ӧ��ʵ������ ֻ��һ��
    QtWidgetsApplication1 w;  //�������ڶ���
    while (i==1)
    {
        printf("RenderLoop");
    }
    w.show();//��ʾ����
    return a.exec();//��Ϣѭ�� �����¼�
}
