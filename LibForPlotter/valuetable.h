#ifndef VALUETABLE_H
#define VALUETABLE_H
#include"LibForPlotter/mathexpression.h"

class ValueTable
{
private:
    /// Minimum possible variable's value
    double minimumVariableValue;
    /// Maximum possible variable's value
    double maximumVariableValue;
    /// Length of table of values
    int length;
    /// Single step of variable in table of values
    double singleStep;
    /// Table of values
    double *valuesArr;

public:
    ValueTable(const MathExpression *expression, double step=0.001);
    ~ValueTable();

    double get(double varValue);
    double getMin()const;
    double getMax()const;
    double getSingleStep()const;

    /// Shows whether table of values have to be drawn at plotter object or not
    bool hasToBeDrawn;
};

#endif // VALUETABLE_H
