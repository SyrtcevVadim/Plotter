#include<QDebug>
#include "functionbox.h"
#include "mathparser.h"
#include"mathexpression.h"
#include"mathhelper.h"
#include"mathchecker.h"

FunctionBox::FunctionBox(QWidget *parent) : QWidget(parent)
{
    expression = new MathExpression();
    resize(250,100);
    // Инициализируем все внутренние виджеты
    functionName = new QLabel("y=");
    functionBody = new QLineEdit();
    functionBody->setToolTip("Тело функции");

    aLbl = new QLabel("a");
    bLbl = new QLabel("b");
    cLbl = new QLabel("c");
    dLbl = new QLabel("d");

    aParamBox = new QDoubleSpinBox();
    aParamBox->setRange(-10'000.0, 10'000.0);
    aParamBox->setSingleStep(0.1);
    aParamBox->setDecimals(1);
    aParamBox->setToolTip("Значение параметра a");

    bParamBox = new QDoubleSpinBox();
    bParamBox->setRange(-10'000.0, 10'000.0);
    bParamBox->setSingleStep(0.1);
    bParamBox->setDecimals(1);
    bParamBox->setToolTip("Значение параметра b");

    cParamBox = new QDoubleSpinBox();
    cParamBox->setRange(-10'000.0, 10'000.0);
    cParamBox->setSingleStep(0.1);
    cParamBox->setDecimals(1);
    cParamBox->setToolTip("Значение параметра c");

    dParamBox = new QDoubleSpinBox();
    dParamBox->setRange(-10'000.0, 10'000.0);
    dParamBox->setSingleStep(0.1);
    dParamBox->setDecimals(1);
    dParamBox->setToolTip("Значение параметра d");

    // Set default values
    aParamBox->setValue(1.0);
    bParamBox->setValue(1.0);
    cParamBox->setValue(1.0);
    dParamBox->setValue(1.0);


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
    QObject::connect(aParamBox, SIGNAL(valueChanged(double)), this, SLOT(aParamChanged(double)));
    QObject::connect(bParamBox, SIGNAL(valueChanged(double)), this, SLOT(bParamChanged(double)));
    QObject::connect(cParamBox, SIGNAL(valueChanged(double)), this, SLOT(cParamChanged(double)));
    QObject::connect(dParamBox, SIGNAL(valueChanged(double)), this, SLOT(dParamChanged(double)));
    QObject::connect(minimumVarValueBox, SIGNAL(textChanged(const QString)), this, SLOT(minimumVariableValueChanged(const QString)));
    QObject::connect(maximumVarValueBox, SIGNAL(textChanged(const QString)), this, SLOT(maximumVariableValueChanged(const QString)));
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

void FunctionBox::aParamChanged(double value)
{
    expression->SetParameter("a", value);
}

void FunctionBox::bParamChanged(double value)
{
    expression->SetParameter("b", value);
}

void FunctionBox::cParamChanged(double value)
{
    expression->SetParameter("c", value);
}

void FunctionBox::dParamChanged(double value)
{
    expression->SetParameter("d", value);
}

void FunctionBox::minimumVariableValueChanged(const QString &strValue)
{
    expression->SetMinimumVarValue(strValue.toDouble());
    // Minimum variable value can't exceeds the maximum one
    if(expression->GetMinimumVarValue() > expression->GetMaximumVarValue())
    {
        errorText->setText("Minimum variable value is greater than the maximum one!");
    }

}

void FunctionBox::maximumVariableValueChanged(const QString &strValue)
{
    expression->SetMaximumVarValue(strValue.toDouble());
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

void FunctionBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouseClickPos = event->pos();
    }
}

void FunctionBox::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        int distance{(event->pos()-mouseClickPos).manhattanLength()};
        if(distance > QApplication::startDragDistance())
        {
            startDrag();
        }
    }
}

void FunctionBox::startDrag()
{
    // Writes MathExpression object to byteArr object
    QByteArray byteArr;
    QDataStream stream(&byteArr, QIODevice::WriteOnly);
    stream << *expression;

    // Prepare expression to drag&drop mechanism
    QMimeData *data = new QMimeData;
    data->setData("MathExpression", byteArr);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(data);
    drag->setPixmap(QPixmap(":/images/Images/FunctionBoxDragged.png"));

    drag->exec();

}
