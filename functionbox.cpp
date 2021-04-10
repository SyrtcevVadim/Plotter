#include<QDebug>
#include "functionbox.h"
#include"../LibForPlotter/MathExpressionFunctionality/mathexpression.h"
#include"../LibForPlotter/MathExpressionFunctionality/mathchecker.h"
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


    xLbl = new QLabel("<=X<=");

    minimumVarValueBox = new QLineEdit();
    maximumVarValueBox = new QLineEdit();

    errorLabel = new QLabel("Error:");
    errorText = new QLabel("everything is good!");

    removeBtn = new QPushButton();

    QGridLayout *grid = new QGridLayout();

    grid->addWidget(removeBtn, 0, 8);

    grid->addWidget(functionName, 0,0);
    grid->addWidget(functionBody, 0, 1,1,7);

    grid->addWidget(errorLabel, 1, 0);
    grid->addWidget(errorText, 1,1, 1, 7);

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
    QObject::connect(functionBody, SIGNAL(textEdited(const QString)),this, SLOT(OnMathExpressionChanged(const QString)));
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
    // Очищаем старую ошибку
    errorText->setText("");
    // При изменении математического выражения в поле ввода
    // меняем это выражение и внутри объекта
    qDebug() << "Str: " << str;


    // Проверяем введённое математическое выражение на корректность
    MathChecker checker(str);

    if(str.isEmpty())
    {
        // Это нормальный случай, ничего не делаем
    }
    else if(!checker.AreAllTokensCorrect())
    {
        // В выражении присутствуют недопустимые символы
        errorText->setText(checker.GetErrorMessage());
    }
    else if(!checker.AreBracketsCorrespond())
    {
        // В выражении скобки расставлены неправильно
        errorText->setText(checker.GetErrorMessage());
    }
    else
    {
        qDebug() << "Math expression is correct!";
        expression->SetExpression(str);
    }

}

