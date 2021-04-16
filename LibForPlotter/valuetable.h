#ifndef VALUETABLE_H
#define VALUETABLE_H
#include"LibForPlotter/mathexpression.h"

class ValueTable
{
private:
    MathExpression *expression;

    /// Length of table of values
    int length;
    /// Single step of variable in table of values
    double singleStep;
    /// Table of values
    double *valuesArr;
    /// Shows whether table of values have to be drawn at a plotter object or not
    bool drawn{false};

public:
    ValueTable(MathExpression *expression, double step=0.01);
    ~ValueTable();
    void recalculate();
    double get(double varValue);
    double getMin()const;
    double getMax()const;
    double getSingleStep()const;

    void setDrawn();
    bool isDrawn();

    MathExpression* getExpression();

};

#endif // VALUETABLE_H
