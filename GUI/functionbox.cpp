#include"GUI/functionbox.h"
#include"GUI/constantbox.h"
#include"LibForPlotter/mathparser.h"
#include"LibForPlotter/mathexpression.h"
#include"LibForPlotter/mathhelper.h"
#include"LibForPlotter/mathchecker.h"
#include<QDebug>

FunctionBox::FunctionBox(QWidget *parent) : QWidget(parent)
{
    setCursor(Qt::OpenHandCursor);

    expression = new MathExpression();
    resize(250, 120);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    functionName = new QLabel("y=");
    functionBody = new QLineEdit();
    functionBody->setToolTip(tr("Function's body"));

    aLbl = new QLabel("a");
    bLbl = new QLabel("b");
    cLbl = new QLabel("c");
    dLbl = new QLabel("d");

    aParamBox = new QDoubleSpinBox();
    aParamBox->setCursor(Qt::ArrowCursor);
    aParamBox->setRange(-10'000.0, 10'000.0);
    aParamBox->setSingleStep(0.05);
    aParamBox->setDecimals(2);
    aParamBox->setToolTip(tr("a parameter's value"));

    bParamBox = new QDoubleSpinBox();
    bParamBox->setCursor(Qt::ArrowCursor);
    bParamBox->setRange(-10'000.0, 10'000.0);
    bParamBox->setSingleStep(0.05);
    bParamBox->setDecimals(2);
    bParamBox->setToolTip(tr("b parameter's value"));

    cParamBox = new QDoubleSpinBox();
    cParamBox->setCursor(Qt::ArrowCursor);
    cParamBox->setRange(-10'000.0, 10'000.0);
    cParamBox->setSingleStep(0.05);
    cParamBox->setDecimals(2);
    cParamBox->setToolTip(tr("c parameter's value"));

    dParamBox = new QDoubleSpinBox();
    dParamBox->setCursor(Qt::ArrowCursor);
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

    minimumVarValueBox = new QDoubleSpinBox();
    minimumVarValueBox->setCursor(Qt::ArrowCursor);
    minimumVarValueBox->setRange(-10'000.0, 10'000.0);
    minimumVarValueBox->setSingleStep(0.1);
    minimumVarValueBox->setToolTip(tr("Minimum variable's value"));

    maximumVarValueBox = new QDoubleSpinBox();
    maximumVarValueBox->setCursor(Qt::ArrowCursor);
    maximumVarValueBox->setRange(-10'000.0, 10'000.0);
    maximumVarValueBox->setSingleStep(0.1);
    maximumVarValueBox->setToolTip(tr("Maximum variable's value"));

    errorText = new QLabel();

    removeBtn = new QPushButton();
    removeBtn->setCursor(Qt::ArrowCursor);
    removeBtn->setToolTip(tr("Delete function block"));
    QPixmap removeImage(":/images/Images/RemoveWidgetImage.png");
    removeBtn->setIcon(removeImage);

    changeColorBtn = new QPushButton();
    changeColorBtn->setCursor(Qt::ArrowCursor);
    changeColorBtn->setAutoFillBackground(true);
    changeColorBtn->setToolTip(tr("Set graph's color"));

    clearFromPlotterBtn = new QPushButton();
    clearFromPlotterBtn->setCursor(Qt::ArrowCursor);
    clearFromPlotterBtn->setToolTip(tr("Clear graph"));

    // Соединяем сигналы с обработчиками
    connect(functionBody, SIGNAL(textChanged(const QString)),this, SLOT(changeMathExpression(const QString)));
    connect(aParamBox, SIGNAL(valueChanged(double)), this, SLOT(changeAParamValue(double)));
    connect(bParamBox, SIGNAL(valueChanged(double)), this, SLOT(changeBParamValue(double)));
    connect(cParamBox, SIGNAL(valueChanged(double)), this, SLOT(changeCParamValue(double)));
    connect(dParamBox, SIGNAL(valueChanged(double)), this, SLOT(changeDParamValue(double)));
    connect(minimumVarValueBox, SIGNAL(valueChanged(double)), this, SLOT(changeMinimumVariableValue(double)));
    connect(maximumVarValueBox, SIGNAL(valueChanged(double)), this, SLOT(changeMaximumVariableValue(double)));
    connect(removeBtn, SIGNAL(pressed()), this, SLOT(removeFunction()));
    connect(changeColorBtn, SIGNAL(pressed()), this, SLOT(changeGraphColor()));
    connect(clearFromPlotterBtn, SIGNAL(pressed()), this, SLOT(clearGraph()));

    // Set default values
    minimumVarValueBox->setValue(-10.0);
    maximumVarValueBox->setValue(10.0);

    QGridLayout *grid = new QGridLayout();


    grid->addWidget(changeColorBtn, 2, 8);
    grid->addWidget(removeBtn, 3, 8);
    grid->addWidget(clearFromPlotterBtn, 3, 7);



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

QColor FunctionBox::getGraphColor() const
{
    return graphColor;
}

void FunctionBox::setGraphColor(QColor color)
{
    graphColor = color;
    repaint();
}

void FunctionBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);


    drawBorders(painter, graphColor);
}

void FunctionBox::drawBorders(QPainter &painter, const QColor &color)
{
    QPen pen(color, 2);
    painter.setPen(pen);

    painter.drawRect(1,1, width()-2, height()-2);
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
    expression->setExpression(functionBody->text());
    checkCorrectness();
    if(!errorText->text().isEmpty())
    {
        expression->setExpression("");
    }
    else
    {
        emit(functionChanged(expression->getId()));
    }

}

void FunctionBox::changeAParamValue(double value)
{
    if(qAbs(value-0.0)<0.0001)
    {
        value = 0;
    }
    expression->SetParameter("a", value);
    emit(functionChanged(expression->getId()));
}

void FunctionBox::changeBParamValue(double value)
{
    if(qAbs(value-0.0)<0.0001)
    {
        value = 0;
    }
    expression->SetParameter("b", value);
    emit(functionChanged(expression->getId()));
}

void FunctionBox::changeCParamValue(double value)
{
    if(qAbs(value-0.0)<0.0001)
    {
        value = 0;
    }
    expression->SetParameter("c", value);
    emit(functionChanged(expression->getId()));
}

void FunctionBox::changeDParamValue(double value)
{
    if(qAbs(value-0.0)<0.0001)
    {
        value = 0;
    }
    expression->SetParameter("d", value);
    emit(functionChanged(expression->getId()));
}

void FunctionBox::changeMinimumVariableValue(double value)
{
    // Minimum variable value can't exceeds the maximum one
    if(value > expression->getMaximumVarValue())
    {
        errorText->setText(QObject::tr("Minimum variable's value exceeds the maximum one"));
    }
    else
    {
        expression->setMinimumVarValue(value);
        checkCorrectness();
    }
    if(errorText->text().isEmpty())
    {
        emit(functionChanged(expression->getId()));
    }

}

void FunctionBox::changeMaximumVariableValue(double value)
{

    // Maximum variable value have to be greater than the minimum one
    if(value < expression->getMinimumVarValue())
    {
        errorText->setText(QObject::tr("Minimum variable's value exceeds the maximum one"));
    }
    else
    {
        expression->setMaximumVarValue(value);
        checkCorrectness();
    }
    if(errorText->text().isEmpty())
    {
        emit(functionChanged(expression->getId()));
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
        graphColor = color;
        repaint();
        emit(graphColorChanged(expression->getId(), color));
    }
}

void FunctionBox::clearGraph()
{
    emit(graphCleared(expression->getId()));
}

void FunctionBox::mousePressEvent(QMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
    if(event->button() == Qt::LeftButton)
    {
        mouseClickPos = event->pos();
    }
}

void FunctionBox::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::OpenHandCursor);
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
    // Writes a MathExpression's identificator to byteArr object
    QByteArray byteArr;
    QDataStream stream(&byteArr, QIODevice::WriteOnly);
    stream << expression->getId();

    // Prepare expression to drag&drop mechanism
    QMimeData *data = new QMimeData;
    data->setData("MathExpression", byteArr);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(data);
    drag->setPixmap(QPixmap(":/images/Images/FunctionBoxDragged.png"));

    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

QSize FunctionBox::sizeHint()const
{
    return QSize(width(), height());
}
