#ifndef MATHFORMCONVERTER_H
#define MATHFORMCONVERTER_H
#include<QString>
#include<QMap>
#include"mathexpression.h"

class MathFormConverter
{
private:
    /// Stores a precedence for every correct operation and function
    static QMap<QString, int> precedence;

public:
    /// Converts mathematical expression from infix notation to postfix notation
    static QString InfixToPostfix(const QString &expression);
};

#endif // MATHFORMCONVERTER_H
