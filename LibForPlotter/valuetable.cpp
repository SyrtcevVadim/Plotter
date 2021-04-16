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
        length = qAbs(expression->GetMaximumVarValue()-
                      expression->GetMinimumVarValue())/singleStep+1;
        if((valuesArr = new(std::nothrow) double[length]) == nullptr)
        {
            qDebug() << "Не удалось выделить память под таблицу значений";
        }
        else
        {
            MathCalculator calculator(*expression);
            double var{expression->GetMinimumVarValue()};
            for(int i{0}; i < length; i++)
            {
                valuesArr[i] = calculator.Calculate(var);
                var+=singleStep;
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

    length = qAbs(expression->GetMaximumVarValue()-expression->GetMinimumVarValue())/singleStep+1;
    if((valuesArr = new(std::nothrow) double[length])==nullptr)
    {
        qDebug() << "Ну удалось выделить память под таблицу значений";
    }
    else
    {
        MathCalculator calculator(*expression);
        double var{expression->GetMinimumVarValue()};
        for(int i{0}; i < length; i++)
        {
            valuesArr[i] = calculator.Calculate(var);
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

void ValueTable::setDrawn()
{
    drawn = true;
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
