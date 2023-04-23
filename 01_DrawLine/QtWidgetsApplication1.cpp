#include "QtWidgetsApplication1.h"
#include "Qwidget"
#include "QPushButton.h"
#include "Qpainter.h"


//主窗口构造函数
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("LightningHawk<SoftEngine>哈哈哈哈");//修改窗口命名
    this->setWindowIcon(QIcon("A:/PROJECT_WORKS/PYTHON_PROJECT/TextureBlendTool/Icon"));//修改窗口ICON
    this->resize(1980, 1080);
    
    //QPushButton *btn= new QPushButton("Button");
    //btn->show();
}

QtWidgetsApplication1:: ~QtWidgetsApplication1()
{

}

void QtWidgetsApplication1::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(QColor(255, 0, 0));
	pen.setWidth(2);
	pen.setStyle(Qt::SolidLine);
	painter.setPen(pen);

    //FLOAT 模式 稍微费一些
    //double x1, x2, y1, y2;
    //x1 = 0;
    //y1 = 0;
    //x2 = 1920;
    //y2 = 1080;
    //double k = double((y2 - y1)/(x2 - x1));//tan k
    //double tmp = 0;
    //if (k<1)
    //{
    //    for (int i =0;i<x2-x1;i++)
    //    {
    //        tmp = tmp + k;
    //        if (tmp<=0.5)//<0.5不满足向上像素绘制的需求
    //        {
    //            painter.drawPoint(QPoint(i,y1));
    //        }
    //        else//满足绘制需求
    //        {
    //            y1 = y1 + 1.0;
    //            painter.drawPoint(QPoint(i,y1));
    //            tmp = tmp - 1;
    //        }
    //    }
    //}

    //INT 模式 节省
	int x1, x2, y1, y2;
	x1 = 0;
	y1 = 0;
	x2 = 1920;
	y2 = 1080;
    int dx = abs((x2 - x1));
    int dy = abs(y2 - y1);
	int dx2 = (2 * dx);
	int dy2 = (2 * dy);
    int e = (-1 * dx);
	if (dy<dx)
	{
		for (int i = x1; i < x2; i++)
		{
            painter.drawPoint(QPoint(i, y1));
            e = e + dy2;
			if (e < 0)//<0.5不满足向上像素绘制的需求
			{   
                printf("绘制顶点序号:%d x:%d y:%d \r\n", i, i, y1);
			}
			else//满足绘制需求
			{
				//painter.drawPoint(QPoint(i, y1));
                printf("绘制顶点序号:%d x:%d y:%d \r\n", i, i, y1);
                y1 = y1 + 1;
				e = e - dx2;
			}
		}
	}
	QPainter painter2(this);
	QPen pen2(QColor(0, 255, 0));
	pen2.setWidth(2);
	pen2.setStyle(Qt::SolidLine);
	painter2.setPen(pen2);
    painter2.drawLine(QPoint(0, 0), QPoint(1980, 1080));
}

