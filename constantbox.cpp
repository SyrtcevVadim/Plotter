#include "constantbox.h"
#include "mathhelper.h"
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

    // Linking signals with slots
    connect(removeButton, SIGNAL(pressed()), this, SLOT(RemoveBtnClick()));
    connect(constantBox, SIGNAL(textChanged(const QString)), this, SLOT(SetConstantName(const QString)));
    connect(valueBox, SIGNAL(textChanged(const QString)), this, SLOT(SetConstantValue(const QString)));

}

void ConstantBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Draws a rectangle border
    painter.drawRect(0,0, width()-5, height()-5);
}

void ConstantBox::RemoveBtnClick()
{
    emit(elementRemoved(this));
}

void ConstantBox::SetConstantName(const QString &str)
{
    qDebug() << str;
}

void ConstantBox::SetConstantValue(const QString &str)
{
    qDebug() << str;
}
