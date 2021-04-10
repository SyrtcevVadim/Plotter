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
    /// Stores predefined and defined by user constants' values
    static QMap<QString, QString> constants;
    /// Stores operand quantity for every function/operation
    static QMap<QString, int> operandQuantity;
    /// Stores parameters' names
    static QStringList parameters;


    /// Associates user-defind constant with it's value
    static void AddConstant(QString constant, QString value);
    /// Remove constant from defined constants
    static void RemoveConstant(QString constant);

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
    static bool IsTokenCorrect(const QString &expression);

    /// Checks, whether string contains constants or not
    static bool HasConstants(const QString &expression);


};


#endif // MATHHELPER_H
