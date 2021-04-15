#include"LibForPlotter/mathcalculator.h"
#include"LibForPlotter/mathformconverter.h"
#include"LibForPlotter/mathexpression.h"
#include"LibForPlotter/mathhelper.h"
#include<QStack>
#include<QStringList>
#include<QDebug>
#include<QMap>
#include<utility>
#include<QtMath>
#include<QString>
#include<functional>

using std::function;
using std::pair;


QMap<QString, function<double(double, double)>> MathCalculator::functionHandlers({pair<QString, function<double(double,double)>>("un-",Negate),
                                                                                  pair<QString, function<double(double,double)>>("un+", Nothing),
                                                                                  pair<QString, function<double(double,double)>>("+", Sum),
                                                                                  pair<QString, function<double(double,double)>>("-", Difference),
                                                                                  pair<QString, function<double(double,double)>>("*", Product),
                                                                                  pair<QString, function<double(double,double)>>("/", Quotient),
                                                                                  pair<QString, function<double(double,double)>>("^", Pow),
                                                                                  pair<QString, function<double(double,double)>>("abs", Absolute),
                                                                                  pair<QString, function<double(double,double)>>("pow", Pow),
                                                                                  pair<QString, function<double(double,double)>>("sin", Sinus),
                                                                                  pair<QString, function<double(double,double)>>("cos", Cosine),
                                                                                  pair<QString, function<double(double,double)>>("tg", Tangent),
                                                                                  pair<QString, function<double(double,double)>>("ctg", Cotangent),
                                                                                  pair<QString, function<double(double,double)>>("arcsin", Arcsinus),
                                                                                  pair<QString, function<double(double,double)>>("arccos", Arccosine),
                                                                                  pair<QString, function<double(double,double)>>("arctg", Arctangent),
                                                                                  pair<QString, function<double(double,double)>>("arcctg", Arccotangent),
                                                                                  pair<QString, function<double(double,double)>>("sqrt", Sqrt),
                                                                                  pair<QString, function<double(double,double)>>("lg",Lg),
                                                                                  pair<QString, function<double(double,double)>>("ln", Ln),
                                                                                  pair<QString, function<double(double,double)>>("log", Log)
                                                                                 });


double MathCalculator::Negate(double value, double unused)
{
    Q_UNUSED(unused);
    return -value;
}

double MathCalculator::Nothing(double value, double unused)
{
    Q_UNUSED(unused)
    return value;
}

double MathCalculator::Sum(double lVal, double rVal)
{
    return lVal + rVal;
}

double MathCalculator::Product(double rVal, double lVal)
{
    return lVal*rVal;
}

double MathCalculator::Difference(double rVal, double lVal)
{
    return lVal - rVal;
}

double MathCalculator::Quotient(double divisor, double dividend)
{
    return (dividend/divisor);
}

double MathCalculator::Absolute(double value, double unused)
{
    Q_UNUSED(unused);
    return qAbs(value);
}

double MathCalculator::Pow(double power, double base)
{
    return qPow(base, power);
}

double MathCalculator::Sqrt(double value, double unused)
{
    Q_UNUSED(unused)
    return qSqrt(value);
}

double MathCalculator::Sinus(double angle, double unused)
{
    Q_UNUSED(unused)
    return qSin(angle);
}

double MathCalculator::Cosine(double angle, double unused)
{
    Q_UNUSED(unused)
    return qCos(angle);
}

double MathCalculator::Tangent(double angle, double unused)
{
    Q_UNUSED(unused)
    return qTan(angle);
}

double MathCalculator::Cotangent(double angle, double unused)
{
    Q_UNUSED(unused)
    return 1.0/qTan(angle);
}

double MathCalculator::Arcsinus(double value, double unused)
{
    Q_UNUSED(unused);
    return qAsin(value);
}

double MathCalculator::Arccosine(double value, double unused)
{
    Q_UNUSED(unused);
    return qAcos(value);
}

double MathCalculator::Arctangent(double value, double unused)
{
    Q_UNUSED(unused);
    return qAtan(value);
}

double MathCalculator::Arccotangent(double value, double unused)
{

    Q_UNUSED(unused);
    return MathHelper::predefinedConstants["pi"].toDouble()/2 - qAtan(value);
}

double MathCalculator::Ln(double value, double unused)
{
    Q_UNUSED(unused)
    return qLn(value);
}

double MathCalculator::Lg(double value, double unused)
{
    Q_UNUSED(unused)
    return qLn(value)/qLn(10);
}

double MathCalculator::Log(double value, double base)
{
    return qLn(value)/qLn(base);
}

MathCalculator::MathCalculator(const MathExpression &expression)
{
    this->expression = expression;
}

MathCalculator::MathCalculator(QString expression)
{
    this->expression.SetExpression(expression);
}

double MathCalculator::Calculate(double varValue)
{
    // Substitute variable value
    QString expressionWithSubstitutedValues(expression.SubstituteVariableValue(varValue));
    // For intermediate values
    QStack<QString> stack;

    // Iterate through the postfixFormExpression
    for(auto token: (expressionWithSubstitutedValues.trimmed()).split(" "))
    {
        if(MathHelper::IsTokenNumber(token))
        {
            stack.push(token);
        }
        else if(MathHelper::IsTokenFunction(token) || MathHelper::IsTokenOperation(token))
        {
            // Checking for necessary operands quantity
            if(!stack.isEmpty() && stack.count() >= MathHelper::operandQuantity[token])
            {
                double firstOperand = stack.pop().toDouble();
                double secondOperand{};
                if(MathHelper::operandQuantity[token] == 2)
                {
                    secondOperand = stack.pop().toDouble();
                }
                double result = functionHandlers[token](firstOperand, secondOperand);
                // Pushs result back to stack
                stack.push(QString().setNum(result));
            }
        }
    }
    return stack.pop().toDouble();
}
