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

    aLbl = new QLabel("a");
    bLbl = new QLabel("b");
    cLbl = new QLabel("c");
    dLbl = new QLabel("d");

    aParamBox = new QLineEdit();
    bParamBox = new QLineEdit();
    cParamBox = new QLineEdit();
    dParamBox = new QLineEdit();
    // Set default values
    aParamBox->setText("1");
    bParamBox->setText("1");
    cParamBox->setText("1");
    dParamBox->setText("1");


    xLbl = new QLabel("<=X<=");

    minimumVarValueBox = new QLineEdit();
    maximumVarValueBox = new QLineEdit();
    // Set default values
    minimumVarValueBox->setText("-10");
    maximumVarValueBox->setText("10");
    errorText = new QLabel();

    removeBtn = new QPushButton();

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

    // Соединяем сигналы с обработчиками
    QObject::connect(functionBody, SIGNAL(textChanged(const QString)),this, SLOT(OnMathExpressionChanged(const QString)));
    QObject::connect(aParamBox, SIGNAL(textChanged(const QString)), this, SLOT(OnAParamChanged(const QString)));
    QObject::connect(bParamBox, SIGNAL(textChanged(const QString)), this, SLOT(OnBParamChanged(const QString)));
    QObject::connect(cParamBox, SIGNAL(textChanged(const QString)), this, SLOT(OnCParamChanged(const QString)));
    QObject::connect(dParamBox, SIGNAL(textChanged(const QString)), this, SLOT(OnDParamChanged(const QString)));
    QObject::connect(minimumVarValueBox, SIGNAL(textChanged(const QString)), this, SLOT(OnMinimumVarValueChanged(const QString)));
    QObject::connect(maximumVarValueBox, SIGNAL(textChanged(const QString)), this, SLOT(OnMaximumVarValueChanged(const QString)));
}

void FunctionBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Draws a rectangle border
    painter.drawRect(0,0, width()-5, height()-5);
}

void FunctionBox::OnMathExpressionChanged(const QString &str)
{
    // При изменении математического выражения в поле ввода
    // меняем это выражение и внутри объекта
    qDebug() << MathParser::CreateTokenList(str);

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
            //qDebug() << "Math expression is correct!";
            errorText->setText("");
            expression->SetExpression(str);
        }
    }
    else
    {
        errorText->setText("");
    }

}

void FunctionBox::OnAParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'a' parameter isn't a decimal number!");
        return;
    }
    expression->SetParameter("a", value.toDouble());
    errorText->clear();
    qDebug() << "A: " << value;

}

void FunctionBox::OnBParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'b' parameter isn't a decimal number!");
        return;
    }
    expression->SetParameter("b", value.toDouble());
    errorText->clear();
    qDebug() << "B" << value;
}

void FunctionBox::OnCParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'c' parameter isn't a decimal number!");
        return;
    }
    expression->SetParameter("c", value.toDouble());
    errorText->clear();
    qDebug() << "C" << value;
}

void FunctionBox::OnDParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'd' parameter isn't a decimal number!");
        return;
    }
    expression->SetParameter("d", value.toDouble());
    errorText->clear();
    qDebug() << "D" << value;

}

void FunctionBox::OnMinimumVarValueChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Minimum possible variable's value must be a decimal number");
    }
    expression->SetMinimumVarValue(value.toDouble());
    errorText->clear();
    qDebug() << "Minimum: " << value;
}

void FunctionBox::OnMaximumVarValueChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Maximum possible variable's value must be a decimal number");
    }
    expression->SetMaximumVarValue(value.toDouble());
    errorText->clear();
    qDebug() << "Maximum: " << value;
}
