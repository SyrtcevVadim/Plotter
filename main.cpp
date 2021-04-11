#include<QtWidgets>
#include"plotter.h"
#include"functionbox.h"
#include"constantbox.h"
#include"functionboxlist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget parentWidget;
    parentWidget.resize(1700,1000);
    Plotter *plotter = new Plotter(new QPoint(500,0), new QSize(500,500), &parentWidget);


    FunctionBoxList *list = new FunctionBoxList(350, &parentWidget);

    parentWidget.show();
    return a.exec();
}
