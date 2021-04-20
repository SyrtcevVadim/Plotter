#include"LibForPlotter/valuetable.h"
#include"LibForPlotter/mathcalculator.h"
#include"LibForPlotter/mathexpression.h"
#include<qmath.h>
#include<QDebug>
ValueTable::ValueTable(MathExpression *expression, double step)
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
        else if(!expression->getInitialExpression().trimmed().isEmpty())
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

ValueTable::~ValueTable()
{
    delete[] valuesArr;
}

void ValueTable::recalculate()
{
    // Deletes old table of values
    delete[] valuesArr;

    length = (expression->GetMaximumVarValue()-expression->GetMinimumVarValue())/singleStep;
    if((valuesArr = new(std::nothrow) double[length])==nullptr)
    {
        qDebug() << "Ну удалось выделить память под таблицу значений";
    }
    else
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

double ValueTable::get(double varValue)
{
    int index{static_cast<int>((qAbs(expression->GetMinimumVarValue()-varValue))/singleStep)};
    return valuesArr[index];
}

double ValueTable::getMax() const
{
    return expression->GetMaximumVarValue();
}

double ValueTable::getMin() const
{
    return expression->GetMinimumVarValue();
}

double ValueTable::getSingleStep() const
{
    return singleStep;
}

void ValueTable::setDrawn(bool value)
{
    drawn = value;
}

bool ValueTable::isDrawn()
{
    return drawn;
}

MathExpression* ValueTable::getExpression()
{
    qDebug() << "Returning expression: "<< *expression;
    return expression;
}
