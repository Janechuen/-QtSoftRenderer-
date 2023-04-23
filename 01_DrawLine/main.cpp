#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>//qt窗口文件

int main(int argc, char *argv[]) //必须使用两个参数的main 需要通过两个参创建QT应用程序
{
    int i = 0;
    QApplication a(argc, argv); //应用实例对象 只有一个
    QtWidgetsApplication1 w;  //创建窗口对象
    while (i==1)
    {
        printf("RenderLoop");
    }
    w.show();//显示窗口
    return a.exec();//消息循环 处理事件
}
