    #include<QDebug>
#include "functionbox.h"
#include "mathparser.h"
#include"mathexpression.h"
#include"mathhelper.h"
#include"mathchecker.h"

FunctionBox::FunctionBox(QWidget *parent) : QWidget(parent)
{
    expression = new MathExpression();
    resize(200,100);
    // Инициализируем все внутренние виджеты
    functionName = new QLabel("y=");
    functionBody = new QLineEdit();
    functionBody->setToolTip("Тело функции");

    aLbl = new QLabel("a");
    bLbl = new QLabel("b");
    cLbl = new QLabel("c");
    dLbl = new QLabel("d");

    aParamBox = new QLineEdit();
    aParamBox->setToolTip("Значение параметра a");
    bParamBox = new QLineEdit();
    bParamBox->setToolTip("Значение параметра b");
    cParamBox = new QLineEdit();
    cParamBox->setToolTip("Значение параметра c");
    dParamBox = new QLineEdit();
    dParamBox->setToolTip("Значение параметра d");

    // Set default values
    aParamBox->setText("1");
    bParamBox->setText("1");
    cParamBox->setText("1");
    dParamBox->setText("1");


    xLbl = new QLabel("<=X<=");

    minimumVarValueBox = new QLineEdit();
    minimumVarValueBox->setToolTip("Минимальное значение переменной x");
    maximumVarValueBox = new QLineEdit();
    maximumVarValueBox->setToolTip("Максимальное значение переменной x");

    errorText = new QLabel();

    removeBtn = new QPushButton();
    removeBtn->setToolTip("Удалить блок функции");
    QPixmap removeImage(":/images/Images/RemoveWidgetImage.png");
    removeBtn->setIcon(removeImage);

    // Соединяем сигналы с обработчиками
    QObject::connect(functionBody, SIGNAL(textChanged(const QString)),this, SLOT(MathExpressionChanged(const QString)));
    QObject::connect(aParamBox, SIGNAL(textChanged(const QString)), this, SLOT(AParamChanged(const QString)));
    QObject::connect(bParamBox, SIGNAL(textChanged(const QString)), this, SLOT(BParamChanged(const QString)));
    QObject::connect(cParamBox, SIGNAL(textChanged(const QString)), this, SLOT(CParamChanged(const QString)));
    QObject::connect(dParamBox, SIGNAL(textChanged(const QString)), this, SLOT(DParamChanged(const QString)));
    QObject::connect(minimumVarValueBox, SIGNAL(textChanged(const QString)), this, SLOT(MinimumVarValueChanged(const QString)));
    QObject::connect(maximumVarValueBox, SIGNAL(textChanged(const QString)), this, SLOT(MaximumVarValueChanged(const QString)));
    connect(removeBtn, SIGNAL(pressed()), this, SLOT(RemoveBtnClick()));

    // Set default values
    minimumVarValueBox->setText("-10");
    maximumVarValueBox->setText("10");

    QGridLayout *grid = new QGridLayout();

    grid->addWidget(removeBtn, 3, 8);

    grid->addWidget(functionName, 0,0);
    grid->addWidget(functionBody, 0, 1,1,-1);

    grid->addWidget(errorText, 1,0, 1, -1);

    grid->addWidget(aLbl, 2, 0);
    grid->addWidget(aParamBox, 2, 1);

    grid->addWidget(bLbl, 2, 3);
    grid->addWidget(bParamBox, 2, 4);

    grid->addWidget(minimumVarValueBox, 2,5);
    grid->addWidget(xLbl, 2, 6);
    grid->addWidget(maximumVarValueBox, 2, 7);

    grid->addWidget(cLbl, 3, 0);
    grid->addWidget(cParamBox, 3, 1);

    grid->addWidget(dLbl, 3,3);
    grid->addWidget(dParamBox,3,4);

    setLayout(grid);
}

void FunctionBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Draws a rectangle border
    painter.drawRect(0,0, width()-5, height()-5);
}

void FunctionBox::MathExpressionChanged(const QString &str)
{
    // При изменении математического выражения в поле ввода
    // меняем это выражение и внутри объекта

    // Проверяем введённое математическое выражение на корректность
    MathChecker checker(str);

    if(!(str.trimmed()).isEmpty())
    {
        if(!checker.AreAllTokensCorrect() || !checker.AreBracketsCorrespond() || !checker.AreArgumentsCorresepond())
        {
            errorText->setText(checker.GetErrorMessage());
        }
        else
        {
            errorText->clear();
            expression->SetExpression(str);
            qDebug() << *expression;
        }
    }
    else
    {
        errorText->clear();
    }

}

void FunctionBox::AParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'a' parameter isn't a decimal number!");
        return;
    }
    errorText->clear();
    expression->SetParameter("a", value.toDouble());
}

void FunctionBox::BParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'b' parameter isn't a decimal number!");
        return;
    }
    errorText->clear();
    expression->SetParameter("b", value.toDouble());
}

void FunctionBox::CParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'c' parameter isn't a decimal number!");
        return;
    }
    errorText->clear();
    expression->SetParameter("c", value.toDouble());
}

void FunctionBox::DParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'd' parameter isn't a decimal number!");
        return;
    }
    errorText->clear();
    expression->SetParameter("d", value.toDouble());
}

void FunctionBox::MinimumVarValueChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Minimum possible variable's value must be a decimal number");
        return;
    }
    errorText->clear();
    expression->SetMinimumVarValue(value.toDouble());
    // Minimum variable value can't exceeds the maximum one
    if(expression->GetMinimumVarValue() > expression->GetMaximumVarValue())
    {
        errorText->setText("Minimum variable value is greater than the maximum one!");
    }

}

void FunctionBox::MaximumVarValueChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Maximum possible variable's value must be a decimal number");
        return;
    }
    errorText->clear();
    expression->SetMaximumVarValue(value.toDouble());
    // Maximum variable value have to be greater than the minimum one
    if(expression->GetMaximumVarValue() < expression->GetMinimumVarValue())
    {
        errorText->setText("Minimum possible varialbe's value is greater than the maximum one!");
    }
}

MathExpression* FunctionBox::GetMathExpression()
{
    return expression;
}

void FunctionBox::RemoveBtnClick()
{
    emit(elementRemoved(this));
}
