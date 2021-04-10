#include "widgetlist.h"
#include "functionbox.h"
#include<QtWidgets>

WidgetList::WidgetList(int height, QWidget *parent) : QWidget(parent)
{
    listBody = new QWidget();
    listBody->setFixedWidth(330);
    listLayout = new QVBoxLayout();
    listBody->setLayout(listLayout);

    scrollArea = new QScrollArea(parent);
    scrollArea->setFixedSize(340, height);
    scrollArea->setWidget(listBody);


    FunctionBox *box1 = new FunctionBox();
    FunctionBox *box2 = new FunctionBox();
    FunctionBox *box3 = new FunctionBox();

    listLayout->addWidget(box1);
    listLayout->addWidget(box2);
    listLayout ->addWidget(box3);


    // Нужно прописывать команду при каждом добавлении нового элемента
    listBody->adjustSize();


}

void WidgetList::move(int x, int y)
{
    scrollArea->move(x,y);
}
