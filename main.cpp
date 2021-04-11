#include<QtWidgets>
#include"plotter.h"
#include"functionbox.h"
#include"constantbox.h"
#include"widgetlist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget parentWidget;
    parentWidget.resize(1700,1700);
    Plotter *plotter = new Plotter(new QPoint(500,0), new QSize(500,500), &parentWidget);


    WidgetList<FunctionBox> *list = new WidgetList<FunctionBox>(400, &parentWidget);

    parentWidget.show();
    return a.exec();
}
