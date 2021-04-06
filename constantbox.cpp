#include "constantbox.h"

ConstantBox::ConstantBox(QWidget *parent) : QWidget(parent)
{
    resize(300, 60);
    constantNameLbl = new QLabel("Константа:");
    constantValueLbl = new QLabel("Значение:");

    constantBox = new QLineEdit();
    valueBox = new QLineEdit();

    removeButton = new QPushButton();

    QGridLayout *grid = new QGridLayout(this);

    grid->addWidget(removeButton, 0, 9);

    grid->addWidget(constantNameLbl, 0,0);
    grid->addWidget(constantBox, 0,1,1,8);

    grid->addWidget(constantValueLbl, 2, 0);
    grid->addWidget(valueBox, 2, 1, 1, 8);


    setLayout(grid);

}
