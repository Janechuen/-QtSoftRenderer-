#include "DrawLine.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawLine w;
    w.show();
    return a.exec();
}
