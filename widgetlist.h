#ifndef WIDGETLIST_H
#define WIDGETLIST_H
#include <QtWidgets>
#include "functionbox.h"

template<typename T>
class WidgetList : public QWidget
{

private:
    QScrollArea *scrollArea;
    /// Body of the list
    QWidget *listBody;
    /// Body's layout
    QVBoxLayout *listLayout;
    /// Button for adding new elements of T widget
    QPushButton *addNewWidgetBtn;
    /// Container for storing widgets
    QList<T> *listOfWidgets;


public:
    explicit WidgetList(int height = 100,QWidget *parent = nullptr);
    /// Moves widget to the (x,y) point
    void move(int x, int y);
};


template<typename T>
WidgetList<T>::WidgetList(int height, QWidget *parent) : QWidget(parent)
{
    listBody = new QWidget();
    listBody->setFixedWidth(330);
    listLayout = new QVBoxLayout();
    listBody->setLayout(listLayout);

    scrollArea = new QScrollArea(parent);
    scrollArea->setFixedSize(350, height);
    scrollArea->setWidget(listBody);

    addNewWidgetBtn = new QPushButton();

    // Test data
    FunctionBox *box1 = new FunctionBox();
    FunctionBox *box2 = new FunctionBox();
    FunctionBox *box3 = new FunctionBox();

    listLayout->addWidget(box1);
    listLayout->addWidget(box2);
    listLayout ->addWidget(box3);
    // necessary command after every insertion of widget
    listBody->adjustSize();

    // Setting appropriate layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(btnLayout);
    btnLayout->addWidget(addNewWidgetBtn);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);
}


template<typename T>
void WidgetList<T>::move(int x, int y)
{
    scrollArea->move(x,y);
}


#endif // WIDGETLIST_H
