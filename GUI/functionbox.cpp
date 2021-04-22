#include"GUI/functionbox.h"
#include"GUI/constantbox.h"
#include"LibForPlotter/mathparser.h"
#include"LibForPlotter/mathexpression.h"
#include"LibForPlotter/mathhelper.h"
#include"LibForPlotter/mathchecker.h"
#include<QDebug>

FunctionBox::FunctionBox(QWidget *parent) : QWidget(parent)
{
    expression = new MathExpression();
    resize(250,100);

    functionName = new QLabel("y=");
    functionBody = new QLineEdit();
    functionBody->setToolTip(tr("Function's body"));

    aLbl = new QLabel("a");
    bLbl = new QLabel("b");
    cLbl = new QLabel("c");
    dLbl = new QLabel("d");

    aParamBox = new QDoubleSpinBox();
    aParamBox->setRange(-10'000.0, 10'000.0);
    aParamBox->setSingleStep(0.05);
    aParamBox->setDecimals(2);
    aParamBox->setToolTip(tr("a parameter's value"));

    bParamBox = new QDoubleSpinBox();
    bParamBox->setRange(-10'000.0, 10'000.0);
    bParamBox->setSingleStep(0.05);
    bParamBox->setDecimals(2);
    bParamBox->setToolTip(tr("b parameter's value"));

    cParamBox = new QDoubleSpinBox();
    cParamBox->setRange(-10'000.0, 10'000.0);
    cParamBox->setSingleStep(0.05);
    cParamBox->setDecimals(2);
    cParamBox->setToolTip(tr("c parameter's value"));

    dParamBox = new QDoubleSpinBox();
    dParamBox->setRange(-10'000.0, 10'000.0);
    dParamBox->setSingleStep(0.05);
    dParamBox->setDecimals(2);
    dParamBox->setToolTip(tr("d paramter's value"));

    // Set default values
    aParamBox->setValue(1.0);
    bParamBox->setValue(1.0);
    cParamBox->setValue(1.0);
    dParamBox->setValue(1.0);


    xLbl = new QLabel("X");

    minimumVarValueBox = new QLineEdit();
    minimumVarValueBox->setToolTip(tr("Minimum variable's value"));
    maximumVarValueBox = new QLineEdit();
    maximumVarValueBox->setToolTip(tr("Maximum variable's value"));

    // User can write only numbers as a minimum/maximum variable's value
    QDoubleValidator *restrictionValidator = new QDoubleValidator();
    minimumVarValueBox->setValidator(restrictionValidator);
    maximumVarValueBox->setValidator(restrictionValidator);

    errorText = new QLabel();

    removeBtn = new QPushButton();
    removeBtn->setToolTip(tr("Delete function block"));
    QPixmap removeImage(":/images/Images/RemoveWidgetImage.png");
    removeBtn->setIcon(removeImage);

    changeColorBtn = new QPushButton();
    changeColorBtn->setAutoFillBackground(true);
    changeColorBtn->setToolTip(tr("Set graph's color"));

    clearFromPlotterBtn = new QPushButton();
    clearFromPlotterBtn->setToolTip(tr("Clear graph"));

    // Соединяем сигналы с обработчиками
    connect(functionBody, SIGNAL(textChanged(const QString)),this, SLOT(changeMathExpression(const QString)));
    connect(aParamBox, SIGNAL(valueChanged(double)), this, SLOT(changeAParamValue(double)));
    connect(bParamBox, SIGNAL(valueChanged(double)), this, SLOT(changeBParamValue(double)));
    connect(cParamBox, SIGNAL(valueChanged(double)), this, SLOT(changeCParamValue(double)));
    connect(dParamBox, SIGNAL(valueChanged(double)), this, SLOT(changeDParamValue(double)));
    connect(minimumVarValueBox, SIGNAL(textChanged(const QString)), this, SLOT(changeMinimumVariableValue(const QString)));
    connect(maximumVarValueBox, SIGNAL(textChanged(const QString)), this, SLOT(changeMaximumVariableValue(const QString)));
    connect(removeBtn, SIGNAL(pressed()), this, SLOT(removeFunction()));
    connect(changeColorBtn, SIGNAL(pressed()), this, SLOT(changeGraphColor()));
    connect(clearFromPlotterBtn, SIGNAL(pressed()), this, SLOT(clearGraph()));

    // Set default values
    minimumVarValueBox->setText("-10");
    maximumVarValueBox->setText("10");

    QGridLayout *grid = new QGridLayout();

    grid->addWidget(clearFromPlotterBtn, 1, 8);
    grid->addWidget(changeColorBtn, 2, 8);
    grid->addWidget(removeBtn, 3, 8);



    grid->addWidget(functionName, 0,0);
    grid->addWidget(functionBody, 0, 1,1,-1);
    grid->addWidget(errorText, 1,0, 1, 7);

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

void FunctionBox::checkCorrectness()
{
    // Clears all previous errors
    errorText->clear();

    // Checks provided mathematic expression for correctness
    if(!expression->getInitialExpression().isEmpty())
    {
        MathChecker checker(expression->getInitialExpression());
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

        if(maximumVarValueBox->text().toDouble() < minimumVarValueBox->text().toDouble())
        {
            errorText->setText(QObject::tr("Minimum variable's value exceeds the maximum one"));
        }
    }
}

void FunctionBox::changeMathExpression(const QString &str)
{
    Q_UNUSED(str);
    expression->SetExpression(functionBody->text());
    checkCorrectness();
    if(!errorText->text().isEmpty())
    {
        expression->SetExpression("");
    }
    else
    {
        emit(expressionChanged(expression));
    }

}

void FunctionBox::changeAParamValue(double value)
{
    if(qAbs(value-0.0)<0.0001)
    {
        value = 0;
    }
    expression->SetParameter("a", value);
    emit(expressionChanged(expression));
}

void FunctionBox::changeBParamValue(double value)
{
    if(qAbs(value-0.0)<0.0001)
    {
        value = 0;
    }
    expression->SetParameter("b", value);
    emit(expressionChanged(expression));
}

void FunctionBox::changeCParamValue(double value)
{
    if(qAbs(value-0.0)<0.0001)
    {
        value = 0;
    }
    expression->SetParameter("c", value);
    emit(expressionChanged(expression));
}

void FunctionBox::changeDParamValue(double value)
{
    if(qAbs(value-0.0)<0.0001)
    {
        value = 0;
    }
    expression->SetParameter("d", value);
    emit(expressionChanged(expression));
}

void FunctionBox::changeMinimumVariableValue(const QString &strValue)
{
    // Minimum variable value can't exceeds the maximum one
    if(strValue.toDouble() > expression->GetMaximumVarValue())
    {
        errorText->setText(QObject::tr("Minimium variable's value exceeds the maximum one"));
    }
    else
    {
        expression->SetMinimumVarValue(strValue.toDouble());
        checkCorrectness();
    }
    if(errorText->text().isEmpty())
    {
        emit(expressionChanged(expression));
    }

}

void FunctionBox::changeMaximumVariableValue(const QString &strValue)
{

    // Maximum variable value have to be greater than the minimum one
    if(strValue.toDouble() < expression->GetMinimumVarValue())
    {
        errorText->setText(QObject::tr("Minimum variable's value exceeds the maximum one"));
    }
    else
    {
        expression->SetMaximumVarValue(strValue.toDouble());
        checkCorrectness();
    }
    if(errorText->text().isEmpty())
    {
        emit(expressionChanged(expression));
    }
}

MathExpression* FunctionBox::getMathExpression()
{
    return expression;
}

void FunctionBox::removeFunction()
{
    emit(elementRemoved(this));
}

void FunctionBox::changeGraphColor()
{
    QColor color = QColorDialog::getColor().toRgb();
    if(color.isValid())
    {
        emit(graphColorChanged(expression, color));
    }
}

void FunctionBox::clearGraph()
{
    emit(graphCleared(expression));
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
