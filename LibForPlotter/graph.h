#ifndef GRAPH_H
#define GRAPH_H
#include"LibForPlotter/mathexpression.h"
#include<QtWidgets>

class Graph
{
private:
    /// Math expression for which table of values is built
    MathExpression *expression;

    /// Length of table of values
    int length;
    /// Single step of variable in table of values
    double singleStep;
    /// Table of values
    double *valuesArr;
    /// Shows whether graph have to be drawn on painting area or not
    bool drawn{false};
    /// Color of graph
    QColor color;

public:
    Graph(MathExpression *expression, double step=0.01);
    ~Graph();
    /// Recalculates the value-table
    void recalculate();

    double get(double variableValue);
    /// Returns the minimum variable's value
    double getMin()const;
    /// Returns the maximum variable's value
    double getMax()const;
    void setSingleStep(double value);
    /// Returns the single step of variable
    double getSingleStep()const;
    /// Sets the value of drawn
    void setDrawn(bool val = true);
    /// Returns the value of drawn. If drawn value is true, graph has to be drawn at plotter. False otherwise
    bool isDrawn();

    MathExpression* getExpression();

    QColor getColor()const;
    void setColor(QColor color);

    double operator[](double variableValue);
};

#endif // GRAPH_H
