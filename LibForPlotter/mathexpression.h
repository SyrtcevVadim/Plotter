#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H
#include<QString>
#include<QMap>
#include<QStringList>
#include<QDebug>
#include<QDataStream>
#include<QMetaType>

class MathExpression
{
private:
    /// Counts the number of created MathExpression objects
    static int counter;

    /// Identificator of current MathExpression object
    int id;
    QString initialExpression;
    /// Expression written in infix notation. Every constant inside it is replaced by it's value
    QString infixExpression;
    /// Expression written in postfix notation. Every parameter inside in is replaced by it's value
    QString postfixExpression;
    /// Stores parameters' values
    QMap<QString, double> parameters;

    /// Minimum possible variable's value
    double minimumVarValue{-10.0};
    /// Maximum possible variable's value
    double maximumVarValue{10.0};

    /// Replaces constants by it's value recursively
    QString SubstituteConstants(QString infixExpression);
    /// Replaces parameters by it's values
    QString SubstituteParameters(QString postfixExpression);

public:
    MathExpression();
    MathExpression(QString expression);
    /// Sets a value to the corresponding parameter
    void SetParameter(QString parameter, double value);

    double getParameterValue(QString parameter)const;

    /// Sets values to the parameters
    void setParameters(double aValue=1.0,double bValue=1.0, double cValue=1.0, double dValue=1.0);
    /// Sets a mathematical expression in infix notation
    void setExpression(QString expression);
    /// Substitutes variables' values into a postfix expression and returns a result
    QString substituteVariableValue(const double varValue = 0.0);
    QString getInitialExpression()const;
    /// Returns mathematical expression in infix notation
    QString getInfixExpression()const;
    /// Returns mathematical expression in postfix notation
    QString getPostfixExpression()const;
    /// Sets the minimum possible value of variable
    void setMinimumVarValue(double value);
    /// Sets the maximum possible value of variable
    void setMaximumVarValue(double value);
    /// Returns the minimum possible value of variable
    double getMinimumVarValue()const;
    /// Returns the maximum possible value of variable
    double getMaximumVarValue()const;

    int getId()const;

    friend QDataStream& operator<<(QDataStream &stream, const MathExpression &expression);
    friend QDataStream& operator>>(QDataStream &stream, MathExpression &expression);
    friend QDebug operator<<(QDebug stream, const MathExpression &expression);
};

Q_DECLARE_METATYPE(MathExpression)
#endif // MATHEXPRESSION_H
