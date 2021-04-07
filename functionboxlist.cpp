#include "functionboxlist.h"
#include<QtWidgets>

FunctionBoxList::FunctionBoxList(QWidget *parent) : QWidget(parent)
{
    resize(300, 300);
    listBodyHeight = 300;

    listBody = new QWidget();
    listBody->setPalette(QPalette(QPalette::Window, Qt::gray));
    scrollArea = new QScrollArea();
    listLayout = new QVBoxLayout();
    listLayout->setAlignment(Qt::AlignTop);
    // Добавляем полосу прокрутки к телу списка
    scrollArea->setWidget(listBody);
    listBody->setLayout(listLayout);
    listBody->resize(300,200);



    addNewItemBtn = new QPushButton();
    removeItemBtn = new QPushButton();

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout ->setAlignment(Qt::AlignLeft);
    btnLayout->addWidget(addNewItemBtn);
    btnLayout->addWidget(removeItemBtn);


    // Тестовое содержимое списка
    QPushButton *firstBtn = new QPushButton("hello");
    QPushButton *secondBtn = new QPushButton("world!");
    QPushButton *thirdBtn = new QPushButton("dsf");
    QPushButton *fourthBtn = new QPushButton("dsf");
    QPushButton *fifthBtn = new QPushButton("dsf");
    QPushButton *btn1 = new QPushButton("hello");
    QPushButton *btn2 = new QPushButton("world!");
    QPushButton *btn3 = new QPushButton("dsf");
    QPushButton *btn4 = new QPushButton("dsf");
    QPushButton *btn5 = new QPushButton("dsf");


    // Добавляем в список содержимое
    listLayout->addWidget(firstBtn);
    listLayout->addWidget(secondBtn);
    listLayout->addWidget(thirdBtn);
    listLayout->addWidget(fourthBtn);
    listLayout->addWidget(fifthBtn);

    listLayout->addWidget(btn1);
    listLayout->addWidget(btn2);
    listLayout->addWidget(btn3);
    listLayout->addWidget(btn4);
    listLayout->addWidget(btn5);


    // Группируем данные
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(listBody);

    setLayout(mainLayout);
}
