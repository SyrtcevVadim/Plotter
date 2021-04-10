#include<QtWidgets>
#include"plotter.h"
#include"functionbox.h"
#include"constantbox.h"
#include"widgetlist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget parentWidget;
    parentWidget.resize(700,700);
    /*//Plotter *plotter = new Plotter(new QPoint(70,70), new QSize(500,500), &parentWidget);
    FunctionBox *first = new FunctionBox(&parentWidget);
    //FunctionBox *second = new FunctionBox(&parentWidget);
    ConstantBox *constant = new ConstantBox(&parentWidget);
    constant->move(0, 200);
    */
    WidgetList<FunctionBox> *list = new WidgetList<FunctionBox>(200, &parentWidget);

    parentWidget.show();
    return a.exec();
}
