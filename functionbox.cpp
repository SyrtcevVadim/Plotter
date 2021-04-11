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

    errorText = new QLabel();

    removeBtn = new QPushButton();
    QPixmap removeImage(":/images/Images/RemoveWidgetImage.png");
    removeBtn->setIcon(removeImage);

    // Соединяем сигналы с обработчиками
    QObject::connect(functionBody, SIGNAL(textChanged(const QString)),this, SLOT(OnMathExpressionChanged(const QString)));
    QObject::connect(aParamBox, SIGNAL(textChanged(const QString)), this, SLOT(OnAParamChanged(const QString)));
    QObject::connect(bParamBox, SIGNAL(textChanged(const QString)), this, SLOT(OnBParamChanged(const QString)));
    QObject::connect(cParamBox, SIGNAL(textChanged(const QString)), this, SLOT(OnCParamChanged(const QString)));
    QObject::connect(dParamBox, SIGNAL(textChanged(const QString)), this, SLOT(OnDParamChanged(const QString)));
    QObject::connect(minimumVarValueBox, SIGNAL(textChanged(const QString)), this, SLOT(OnMinimumVarValueChanged(const QString)));
    QObject::connect(maximumVarValueBox, SIGNAL(textChanged(const QString)), this, SLOT(OnMaximumVarValueChanged(const QString)));
    connect(removeBtn, SIGNAL(pressed()), this, SLOT(OnRemoveBtnClick()));

    // Set default values
    minimumVarValueBox->setText("-10");
    maximumVarValueBox->setText("10");

    qDebug() << expression->GetMinimumVarValue() << " " << expression->GetMaximumVarValue();

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

void FunctionBox::OnMathExpressionChanged(const QString &str)
{
    // При изменении математического выражения в поле ввода
    // меняем это выражение и внутри объекта
    qDebug() << MathParser::CreateTokenList(str);

    // Проверяем введённое математическое выражение на корректность
    MathChecker checker(str);

    if(!(str.trimmed()).isEmpty())
    {
        qDebug() << "Token list isn't empty";
        if(!checker.AreAllTokensCorrect() || !checker.AreBracketsCorrespond() || !checker.AreArgumentsCorresepond())
        {
            errorText->setText(checker.GetErrorMessage());
        }
        else
        {
            qDebug() << "Math expression is correct!";
            errorText->clear();
            expression->SetExpression(str);
        }
    }
    else
    {
        errorText->clear();
    }

}

void FunctionBox::OnAParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'a' parameter isn't a decimal number!");
        return;
    }
    errorText->clear();
    expression->SetParameter("a", value.toDouble());
    qDebug() << "A"<<value;

}

void FunctionBox::OnBParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'b' parameter isn't a decimal number!");
        return;
    }
    errorText->clear();
    expression->SetParameter("b", value.toDouble());
    qDebug() << "B"<<value;
}

void FunctionBox::OnCParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'c' parameter isn't a decimal number!");
        return;
    }
    errorText->clear();
    expression->SetParameter("c", value.toDouble());
    qDebug() << "C"<<value;
}

void FunctionBox::OnDParamChanged(const QString &value)
{
    if(!MathChecker::IsTokenNumber(value))
    {
        errorText->setText("Value of 'd' parameter isn't a decimal number!");
        return;
    }
    errorText->clear();
    expression->SetParameter("d", value.toDouble());
    qDebug() << "A"<<value;
}

void FunctionBox::OnMinimumVarValueChanged(const QString &value)
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

void FunctionBox::OnMaximumVarValueChanged(const QString &value)
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

MathExpression FunctionBox::GetMathExpression() const
{
    return *expression;
}

void FunctionBox::OnRemoveBtnClick()
{
    emit(elementRemoved(this));
    qDebug()<<"REMOVED BUTTON IS PRESSED";
}
