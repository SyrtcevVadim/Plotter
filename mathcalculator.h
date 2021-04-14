#ifndef MATHCALCULATOR_H
#define MATHCALCULATOR_H
#include"mathexpression.h"
#include<QMap>
#include<QString>
#include<functional>
#include<QMetaType>

class MathCalculator
{
private:
    /// Mathematical expression for value table computations
    MathExpression expression;

    /// Strores pointers to mathematical function handlers
    static QMap<QString, std::function<double(double, double)>> functionHandlers;

    /// Is used for un+ operation
    static double Nothing(double value, double unused);

    static double Negate(double value, double unused);

    static double Sum(double lVal, double rVal);

    static double Difference(double rVal, double lVal);

    static double Product(double rVal, double lVal);

    static double Quotient(double divisor, double dividend);

    static double Absolute(double value, double unused);

    static double Pow(double power, double base);

    static double Sqrt(double value, double unused);

    static double Sinus(double angle, double unused);

    static double Cosine(double angle, double unused);

    static double Tangent(double angle, double unused);

    static double Cotangent(double angle, double unused);

    static double Arcsinus(double value, double unused);

    static double Arccosine(double value, double unused);

    static double Arctangent(double value, double unused);

    static double Arccotangent(double value, double unused);

    static double Ln(double value, double unused);

    static double Lg(double value, double unused);

    static double Log(double value, double base);

public:
    MathCalculator()=default;
    MathCalculator(const MathExpression &expression);
    MathCalculator(QString expression);
    /// Is used for expressions with variables
    double Calculate(double varValue=0.0);
};
Q_DECLARE_METATYPE(MathCalculator)
#endif // MATHCALCULATOR_H
