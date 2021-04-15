#include"LibForPlotter/valuetable.h"
#include"LibForPlotter/mathcalculator.h"
#include"LibForPlotter/mathexpression.h"
#include<qmath.h>
#include<QDebug>
ValueTable::ValueTable(const MathExpression *expression, double step)
{
    if(step != 0)
    {
        singleStep = step;
        minimumVariableValue = expression->GetMinimumVarValue();
        maximumVariableValue = expression->GetMaximumVarValue();
        length = qAbs(maximumVariableValue-minimumVariableValue)/singleStep+1;
        if((valuesArr = new(std::nothrow) double[length]) == nullptr)
        {
            qDebug() << "Не удалось выделить память под таблицу значений";
        }
        else
        {
            MathCalculator calculator(*expression);
            double var{minimumVariableValue};
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

double ValueTable::get(double varValue)
{
    int index{static_cast<int>((qAbs(minimumVariableValue-varValue))/singleStep)};
    return valuesArr[index];
}

double ValueTable::getMax() const
{
    return maximumVariableValue;
}

double ValueTable::getMin() const
{
    return minimumVariableValue;
}

double ValueTable::getSingleStep() const
{
    return singleStep;
}
