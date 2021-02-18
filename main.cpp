#include<QtWidgets>
#include"plotter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget parentWidget;

    Plotter *plotter = new Plotter(new QPoint(10,10), new QSize(500,500), &parentWidget);
    parentWidget.resize(1000,1000);
    parentWidget.show();
    return a.exec();
}
