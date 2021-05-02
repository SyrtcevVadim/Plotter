#include"LibForPlotter/graph.h"
#include"LibForPlotter/mathcalculator.h"
#include"LibForPlotter/mathexpression.h"
#include<qmath.h>
#include<QtWidgets>

double Graph::singleStep;


Graph::Graph(MathExpression *expression)
{
    this->expression = expression;
    valuesArr = nullptr;
    drawn = false;
    maxAbsoluteValue=0.0;
    if(!expression->getInfixExpression().isEmpty())
    {
        // Calculating a number of values inside the table
        length = (expression->getMaximumVarValue()-
                  expression->getMinimumVarValue())/singleStep;
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
                maxAbsoluteValue = qMax(maxAbsoluteValue, qAbs(valuesArr[i]));
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

void Graph::recalculate()
{
    maxAbsoluteValue = 0.0;
    if(valuesArr != nullptr)
    {
        // Deletes old table of values
        delete[] valuesArr;
        valuesArr =nullptr;
    }

    if(!expression->getInitialExpression().isEmpty())
    {

        length = (expression->getMaximumVarValue()-expression->getMinimumVarValue())/singleStep;
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
                maxAbsoluteValue = qMax(maxAbsoluteValue, qAbs(valuesArr[i]));
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

double Graph::getRightBorder() const
{
    return expression->getMaximumVarValue();
}

double Graph::getLeftBorder() const
{
    return expression->getMinimumVarValue();
}

double Graph::getMaxAbsoluteValue() const
{
    return maxAbsoluteValue;
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
