#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H
#include<QString>
#include<QMap>
#include<QStringList>
#include<QMetaType>

class MathExpression
{
private:

    /// Expression written in infix notation. Every constant inside it is replaced by it's value
    QString infixExpression;
    /// Expression written in postfix notation. Every parameter inside in is replaced by it's value
    QString postfixExpression;
    /// Stores parameters' values
    QMap<QString, double> parameters;

    /// Replaces constants by it's value recursively
    QString SubstituteConstants(QString infixExpression);
    /// Replaces parameters by it's values
    QString SubstituteParameters(QString postfixExpression);

public:
    MathExpression();
    MathExpression(QString expression);
    /// Sets a value to the corresponding parameter
    void SetParameter(QString parameter, double value);
    /// Sets values to the parameters
    void SetParameters(double aValue=1.0,double bValue=1.0, double cValue=1.0, double dValue=1.0);
    /// Sets a mathematical expression in infix notation
    void SetExpression(QString expression);
    /// Substitutes variables' values into a postfix expression and returns a result
    QString SubstituteVariableValue(const double varValue = 0.0);
    /// Returns mathematical expression in infix notation
    QString GetInfixExpression()const;
    /// Returns mathematical expression in postfix notation
    QString GetPostfixExpression()const;

};

Q_DECLARE_METATYPE(MathExpression)
#endif // MATHEXPRESSION_H
