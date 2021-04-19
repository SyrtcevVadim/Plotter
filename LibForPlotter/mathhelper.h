#ifndef MATHHELPER_H
#define MATHHELPER_H
#include<QMap>
#include<QStringList>
#include<QString>

class MathHelper
{
public:
    /// Stores the correct tokens for mathematical expressions
    static QStringList correctTokens;
    /// Stores the correct operations
    static QStringList operations;
    /// Stores the correct functions
    static QStringList functions;
    /// Stores predefined constants' values
    static QMap<QString, QString> predefinedConstants;
    /// Stores user-defined constants' values
    static QMap<QString, QString> userDefinedConstants;
    /// Stores operand quantity for every functio/operation
    static QMap<QString, int> operandQuantity;
    /// Stores parameters' names
    static QStringList parameters;


    /// Checks whether token is a decimal number or not
    static bool IsTokenNumber(const QString &token);
    /// Checks whether token is a separator or not
    static bool IsTokenSeparator(const QString &token);
    /// Checks whether token is a variable or not
    static bool IsTokenVariable(const QString &token);
    /// Checks whether token is a parameter or not
    static bool IsTokenParameter(const QString &token);
    /// Checks whether token is a constant or not
    static bool IsTokenConstant(const QString &token);
    /// Checks whether token is an operation or not
    static bool IsTokenOperation(const QString &expression);
    /// Checks whether token is a function or not
    static bool IsTokenFunction(const QString &expression);
    /// Checks whether token is correct or not
    static bool IsTokenCorrect(const QString &token);
    /// Checks whether token is an opening bracket or not
    static bool IsTokenOpeningBracket(const QString &token);
    /// Checks whether token is a closing bracket or not
    static bool IsTokenClosingBracket(const QString &token);
    /// Checks, whether string contains constants or not
    static bool HasConstants(const QString &expression);


    /// Create new user-defined constant with provided value
    static void AddConstant(const QString &constant, const QString &value);
    /// Removes constant from user-defined constants
    static void RemoveConstant(const QString &constant);
    /// Alters existing user-defined constant's value
    static void AlterConstantValue(const QString &constant, const QString &value);


};


#endif // MATHHELPER_H
