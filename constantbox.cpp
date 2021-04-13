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
    removeButton->setIcon(QPixmap(":/images/Images/RemoveWidgetImage.png"));

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
    MathHelper::RemoveConstant(constantName);
    qDebug() << MathHelper::userDefinedConstants;
}

void ConstantBox::SetConstantName(const QString &str)
{
    // Constant's name is changed, it have to be removed from the list with correct constants
    MathHelper::RemoveConstant(constantName);

    qDebug() << "Constant name: " << str;

    // New constant is added to the list with correct constants
    MathHelper::AddConstant(str, constantValue);
    qDebug() << str << ":"<< MathHelper::userDefinedConstants[str];
    constantName = str;
}

void ConstantBox::SetConstantValue(const QString &str)
{
    qDebug() << "Constant value: " << str;
    if(!constantName.isEmpty())
    {
        MathHelper::AlterConstantValue(constantName, str);
        qDebug()<< constantName << ": " << MathHelper::userDefinedConstants[constantName];
    }
    constantValue = str;
}

