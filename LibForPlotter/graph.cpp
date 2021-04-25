#include"LibForPlotter/graph.h"
#include"LibForPlotter/mathcalculator.h"
#include"LibForPlotter/mathexpression.h"
#include<qmath.h>
#include<QtWidgets>

Graph::Graph(MathExpression *expression, double step)
{
    this->expression = expression;
    if(step != 0)
    {
        singleStep = step;
        // Calculating a number of values inside the table
        length = (expression->GetMaximumVarValue()-
                      expression->GetMinimumVarValue())/singleStep;
        // Check the correctness of allocating memory
        if((valuesArr = new(std::nothrow) double[length]) == nullptr)
        {
            qDebug() << "Не удалось выделить память под таблицу значений";
        }
        // In case mathematic expression isn't empty we need to calculate the table of values
        else if(!expression->getInitialExpression().isEmpty())
        {
            MathCalculator calculator(*expression);
            double var{expression->GetMinimumVarValue()};
            for(int i{0}; i < length; i++)
            {
                // It fixes the problem of double number precision near the zero value
                if(qAbs(var-0.0) < 0.0001)
                {
                    var = 0.0;
                }
                valuesArr[i] = calculator.Calculate(var);
                qDebug() << "x: "<<var << " |y: " << valuesArr[i];
                var += singleStep;
            }
        }
    }

}

Graph::~Graph()
{
    delete[] valuesArr;
}

void Graph::recalculate()
{
    // Deletes old table of values
    delete[] valuesArr;

    length = (expression->GetMaximumVarValue()-expression->GetMinimumVarValue())/singleStep;
    if((valuesArr = new(std::nothrow) double[length])==nullptr)
    {
        qDebug() << "Ну удалось выделить память под таблицу значений";
    }
    else if(!expression->getInitialExpression().isEmpty())
    {
        qDebug() << "expression: "<<*expression;
        MathCalculator calculator(*expression);
        double var{expression->GetMinimumVarValue()};
        for(int i{0}; i < length; i++)
        {
            if(qAbs(var-0.0) < 0.0001)
            {
                var = 0.0;
            }
            valuesArr[i] = calculator.Calculate(var);

            qDebug() << "x: "<<var << " |y: " << valuesArr[i];
            var += singleStep;

        }
    }
}

double Graph::get(double variableValue)
{
    int index{static_cast<int>((qAbs(expression->GetMinimumVarValue()-variableValue))/singleStep)};
    return valuesArr[index];
}

double Graph::getMax() const
{
    return expression->GetMaximumVarValue();
}

double Graph::getMin() const
{
    return expression->GetMinimumVarValue();
}

void Graph::setSingleStep(double value)
{
    singleStep = value;
}

double Graph::getSingleStep() const
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
    qDebug() << "Returning expression: "<< *expression;
    return expression;
}

double Graph::operator[](double variableValue)
{
    return get(variableValue);
}
