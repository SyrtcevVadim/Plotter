#include<QtWidgets>
#include"plotter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget parentWidget;

    Plotter *plotter = new Plotter(new QPoint(10,10), new QSize(200,200), &parentWidget);
    parentWidget.resize(300,300);
    parentWidget.show();
    return a.exec();
}
