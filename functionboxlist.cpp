#include "functionboxlist.h"
#include "functionbox.h"
#include<QtWidgets>

FunctionBoxList::FunctionBoxList(int height, QWidget *parent) : QWidget(parent)
{
    listBody = new QWidget();
    listBody->setFixedWidth(300);
    listLayout = new QVBoxLayout();
    listBody->setLayout(listLayout);

    scrollArea = new QScrollArea(parent);
    scrollArea->setFixedSize(320, height);
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
