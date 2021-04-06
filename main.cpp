#include<QtWidgets>
#include"plotter.h"
#include"functionbox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget parentWidget;

    //Plotter *plotter = new Plotter(new QPoint(70,70), new QSize(500,500), &parentWidget);
    FunctionBox *first = new FunctionBox(&parentWidget);
    FunctionBox *second = new FunctionBox(&parentWidget);

    QVBoxLayout *vBox = new QVBoxLayout();
    vBox ->addWidget(first);
    vBox ->addWidget(second);

    parentWidget.setLayout(vBox);
    //second->move(0, 150);


    parentWidget.resize(500,700);
    parentWidget.show();
    return a.exec();
}
