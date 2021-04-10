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
    //static QMap<QString, QString> associativity; TODO to support ^ operation
    /// Checks whether token is a number or not
    static bool IsTokenNumber(QString &token);
    /// Checks whether token is a separator or not
    static bool IsTokenSeparator(QString &token);

    /// Checks whether token is an opening bracket
    static bool IsTokenOpeningBracket(QString &token);

public:
    /// Converts mathematical expression from infix notation to postfix notation
    static QString InfixToPostfix(const QString &expression);


};

#endif // MATHFORMCONVERTER_H
