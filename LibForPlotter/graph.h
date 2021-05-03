 #ifndef GRAPH_H
#define GRAPH_H
#include"LibForPlotter/mathexpression.h"
#include<QtWidgets>

class Graph
{
private:
    /// Single step of variable in table of values
    static double singleStep;

    /// Minimum possible x variable's value
    static double minimumXValue;

    /// Maximum possible x variables' value
    static double maximumXValue;
    /// Math expression for which table of values is built
    MathExpression *expression;

    /// Length of table of values
    int length;

    /// Table of values
    double *valuesArr;
    /// Shows whether graph have to be drawn on painting area or not
    bool drawn{false};
    /// Color of graph
    QColor color;

public:
    /// Sets the value of single step of variable
    static void setSingleStep(double value);
    /// Returns the single step of variable
    static double getSingleStep();

    Graph(MathExpression *expression);
    ~Graph();

    /// Recalculates the value-table
    void recalculate();

    double get(double variableValue);

    /// Sets the restrictions for graphs
    static void setBorders(double leftBorder, double rightBorder);

    /// Returns the minimum variable's value
    double getLeftBorder();
    /// Returns the maximum variable's value
    double getRightBorder();
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
