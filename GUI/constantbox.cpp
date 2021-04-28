#include "GUI/constantbox.h"
#include "GUI/constantboxlist.h"
#include "LibForPlotter/mathhelper.h"
#include "LibForPlotter/mathchecker.h"

ConstantBox::ConstantBox(QWidget *parent) : QWidget(parent)
{
    resize(300, 100);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    constantNameLbl = new QLabel(tr("Name:"));
    constantValueLbl = new QLabel(tr("Value:"));
    errorText = new QLabel();

    constantBox = new QLineEdit();
    QRegExpValidator *boxValidator  = new QRegExpValidator(QRegExp("[a-zA-Z]*"));
    constantBox->setValidator(boxValidator);
    valueBox = new QLineEdit();

    removeButton = new QPushButton();
    removeButton->setToolTip(tr("Delete constant block"));
    removeButton->setIcon(QPixmap(":/images/Images/RemoveWidgetImage.png"));

    QGridLayout *grid = new QGridLayout(this);

    grid->addWidget(removeButton, 0, 9);

    grid->addWidget(constantNameLbl, 0,0);
    grid->addWidget(constantBox, 0,1,1,8);



    grid->addWidget(constantValueLbl, 1, 0);
    grid->addWidget(valueBox, 1, 1, 1, 8);

    grid->addWidget(errorText,2,0, 1,-1);


    setLayout(grid);

    // Linking signals with slots
    connect(removeButton, SIGNAL(pressed()), this, SLOT(removeConstant()));
    connect(constantBox, SIGNAL(textChanged(const QString)), this, SLOT(setConstantName(const QString)));
    connect(valueBox, SIGNAL(textChanged(const QString)), this, SLOT(setConstantValue(const QString)));

    isCorrect();
}


void ConstantBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Draws a rectangle border
    painter.drawRect(0,0, width()-2, height()-2);
}

void ConstantBox::removeConstant()
{
    MathHelper::RemoveConstant(constantName);
    emit(elementRemoved(this));
    emit(elementChanged());
}

void ConstantBox::setConstantName(const QString &str)
{
    // Constant's name is changed, it have to be removed from the list with correct constants
    MathHelper::RemoveConstant(constantName);
    constantName = str;
    qDebug() << "New constant's name: " << str;
    if(isCorrect())
    {
        // New constant is added to the list with correct constants
        MathHelper::AddConstant(constantName, constantValue);
        qDebug() << "User-defined constants: "<< MathHelper::userDefinedConstants;
    }
    qDebug() << "Constant's name: "<<constantName <<"| value: " << constantValue;
    emit(elementChanged());
}

void ConstantBox::setConstantValue(const QString &str)
{
    MathHelper::RemoveConstant(constantName);
    constantValue = str;
    qDebug() << "New constant's value: "<<str;
    if(isCorrect())
    {
        MathHelper::AddConstant(constantName, constantValue);
        qDebug() << "User-defined constants: "<<MathHelper::userDefinedConstants;       
    }
    qDebug() << "Constant's name: "<<constantName <<"| value: " << constantValue;
    emit(elementChanged());
}

QString ConstantBox::getConstantName() const
{
    return constantName;
}

QString ConstantBox::getConstantValue() const
{
    return constantValue;
}

bool ConstantBox::isCorrect()
{
    errorText->clear();

    QString userConstantName{constantBox->text()};
    QString constantValue{valueBox->text()};

    if(!userConstantName.isEmpty())
    {
        // Checks a constant's name. It can't equals to the predefined names
        if(MathHelper::IsTokenCorrect(userConstantName))
        {
            errorText->setText(tr("You can't redefine \"%1\"").arg(userConstantName));
        }
    }
    else
    {
        errorText->setText(tr("Constant's name is empty"));
    }

    if(!errorText->text().isEmpty())
    {
        return false;
    }

    //Checks a correctness of a constant's value
    if(!constantValue.isEmpty())
    {
        MathChecker checker(constantValue);
        if(!checker.AreAllTokensCorrect())
        {
           errorText->setText(checker.GetErrorMessage());
        }
        else if(!checker.AreBracketsCorrespond())
        {
            errorText->setText(checker.GetErrorMessage());
        }
        else if(checker.HasEmptyBrackets())
        {
            errorText->setText(checker.GetErrorMessage());
        }
        else if(checker.HasMissedOperations())
        {
            errorText->setText(checker.GetErrorMessage());
        }
        else if(checker.HasMissedOperands())
        {
            errorText->setText(checker.GetErrorMessage());
        }
    }
    else
    {
        errorText->setText(tr("Constant's value is empty"));
    }

    if(!errorText->text().isEmpty())
    {
        return false;
    }

   // Check for recursion
    if((userConstantName == constantValue)&&!userConstantName.isEmpty()&&!constantValue.isEmpty())
    {
        errorText->setText(tr(R"(Value of constant can't equals to the constant's name)"));
        return false;
    }

    return true;

}

QSize ConstantBox::sizeHint()const
{
    return QSize(width(), height());
}

