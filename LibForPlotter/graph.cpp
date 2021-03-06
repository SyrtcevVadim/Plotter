#include"LibForPlotter/graph.h"
#include"LibForPlotter/mathcalculator.h"
#include"LibForPlotter/mathexpression.h"
#include<qmath.h>
#include<QtWidgets>

double Graph::singleStep;

double Graph::minimumXValue;
double Graph::maximumXValue;

Graph::Graph(MathExpression *expression)
{
    this->expression = expression;
    valuesArr = nullptr;
    drawn = false;
    if(!expression->getInfixExpression().isEmpty())
    {
        // Calculating a number of values inside the table

        qDebug() << "max: " << maximumXValue;
        qDebug() << "min: " << minimumXValue;
        length = qAbs((maximumXValue+10-minimumXValue))/singleStep;
        // Check the correctness of allocating memory
        if((valuesArr = new(std::nothrow) double[length]) == nullptr)
        {
            qDebug() << "Не удалось выделить память под таблицу значений";
        }
        else
        {
            //qDebug() << "length: "<< length;
            MathCalculator calculator(*expression);
            double var{expression->getMinimumVarValue()};
            for(int i{0}; i < length; i++)
            {
                // It fixes the problem of double number precision near the zero value
                if(qAbs(var-0.0) < 0.0001)
                {
                    var = 0.0;
                }
                valuesArr[i] = calculator.Calculate(var);

                //qDebug() << "x: "<<var << " |y: " << valuesArr[i];
                var += singleStep;
            }
        }
    }
}

Graph::~Graph()
{
    if(valuesArr != nullptr)
    {
        delete[] valuesArr;
    }
}

void Graph::setBorders(double leftBorder, double rightBorder)
{
    minimumXValue = leftBorder;
    maximumXValue = rightBorder;
}

void Graph::recalculate()
{
    if(valuesArr != nullptr)
    {
        // Deletes old table of values
        delete[] valuesArr;
        valuesArr =nullptr;
    }

    if(!expression->getInitialExpression().isEmpty())
    {
        qDebug() << "max: " << maximumXValue;
        qDebug() << "min: " << minimumXValue;
        length = qAbs((maximumXValue+10-minimumXValue))/singleStep;
        if((valuesArr = new(std::nothrow) double[length])==nullptr)
        {
            qDebug() << "Ну удалось выделить память под таблицу значений";
        }
        else
        {
            qDebug() << "Length: "<< length;
            MathCalculator calculator(*expression);
            double var{expression->getMinimumVarValue()};
            for(int i{0}; i < length; i++)
            {
                if(qAbs(var-0.0) < 0.0001)
                {
                    var = 0.0;
                }
                valuesArr[i] = calculator.Calculate(var);
                //qDebug() << "x: "<<var << " |y: " << valuesArr[i];
                var += singleStep;
            }
        }
    }
}

double Graph::get(double variableValue)
{
    int index{static_cast<int>((qAbs(expression->getMinimumVarValue()-variableValue))/singleStep)};
    return valuesArr[index];
}

double Graph::getRightBorder()
{
    return expression->getMaximumVarValue();
}

double Graph::getLeftBorder()
{
    return expression->getMinimumVarValue();
}

void Graph::setSingleStep(double value)
{
    singleStep = value;
}

double Graph::getSingleStep()
{
    return singleStep;
}

void Graph::setDrawn(bool value)
{
    drawn = value;
}

bool Graph::isDrawn()
{
    return drawn;
}

QColor Graph::getColor() const
{
    return color;
}

void Graph::setColor(QColor color)
{
    this->color = color;
}

MathExpression* Graph::getExpression()
{
    return expression;
}

double Graph::operator[](double variableValue)
{
    return get(variableValue);
}
