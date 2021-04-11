#include "mathhelper.h"
#include "mathparser.h"
#include<utility>
#include<QDebug>

using std::pair;

QStringList MathHelper::correctTokens({"(",")","[","]","{","}",             // Brackets
                                        ",",";",                            // Delimiters
                                        "+","-","*","/","^",                // Operations
                                        "abs", "pow", "sqr","sqrt",         // Basic arithmetic functions
                                        "sin","cos","tg","ctg",             // Trigonometric functions
                                        "ln","lg","log",                    // Logarithmic functions
                                        "arcsin","arccos","arctg","arcctg", // Inverse trigonometric functions
                                        "x","X",                            // Variable
                                        "a","b","c","d",                    // Parameters
                                        "pi", "e"                           // Predefined constants
                                      });

QStringList MathHelper::operations({"+","-","*","/","^"});

QStringList MathHelper::functions({"abs", "pow", "sqr", "sqrt",
                                  "sin","cos","tg","ctg",
                                  "arsin","arccos","arctg", "arcctg",
                                  "ln","lg","log"});

QMap<QString, QString> MathHelper::constants({pair<QString, QString>("e", "2.718281828"),
                                              pair<QString, QString>("pi", "3.141592")
                                            });

QMap<QString, int> MathHelper::operandQuantity({     pair<QString, int>("un-", 1),
                                                     pair<QString, int>("un+", 1),
                                                     pair<QString, int>("+", 2),
                                                     pair<QString, int>("-", 2),
                                                     pair<QString, int>("*", 2),
                                                     pair<QString, int>("/", 2),
                                                     pair<QString, int>("^", 2),
                                                     pair<QString, int>("abs", 1),
                                                     pair<QString, int>("pow", 2),
                                                     pair<QString, int>("sin", 1),
                                                     pair<QString, int>("sqrt", 1),
                                                     pair<QString, int>("cos", 1),
                                                     pair<QString, int>("arcsin", 1),
                                                     pair<QString, int>("arccos", 1),
                                                     pair<QString, int>("arctg", 1),
                                                     pair<QString, int>("arcctg", 1),
                                                     pair<QString, int>("tg", 1),
                                                     pair<QString, int>("ctg", 1),
                                                     pair<QString, int>("lg", 1),
                                                     pair<QString, int>("ln", 1),
                                                     pair<QString, int>("log",2),
                                                    });
QStringList MathHelper::parameters({"a", "b","c","d"});


void MathHelper::AddConstant(QString constant, QString value)
{
    // Check constant for double entry
    if(!correctTokens.contains(constant))
    {
         correctTokens.append(constant);
         constants[constant] = value;
    }
}

void MathHelper::RemoveConstant(QString constant)
{
    constants.remove(constant);
    correctTokens.removeOne(constant);
}

bool MathHelper::IsTokenVariable(const QString &token)
{
    if(token == "x" || token == "X")
    {
        return true;
    }
    return false;
}

bool MathHelper::IsTokenParameter(const QString &token)
{
    if(parameters.contains(token))
    {
        return true;
    }
    return false;
}

bool MathHelper::IsTokenConstant(const QString &token)
{
    if(constants.contains(token))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MathHelper::IsTokenCorrect(const QString &expression)
{
    if(correctTokens.contains(expression))
    {
        return true;
    }
    return false;
}

bool MathHelper::IsTokenOperation(const QString &expression)
{
    if(expression != "," &&operations.contains(expression))
    {
        return true;
    }
    return false;
}

bool MathHelper::IsTokenFunction(const QString &expression)
{
    if(functions.contains(expression))
    {
        return true;
    }
    return false;
}

bool MathHelper::HasConstants(const QString &expression)
{
    for(auto key: (expression.trimmed()).split(" "))
    {
        if(constants.contains(key))
        {
            return true;
        }
    }
    return false;
}

bool MathHelper::IsTokenOpeningBracket(const QString &token)
{
    if(token == "(" || token == "[" || token == "{")
    {
        return true;
    }
    return false;
}

bool MathHelper::IsTokenClosingBracket(const QString &token)
{
    if(token == ")" || token == "]" || token == "}")
    {
        return true;
    }
    return false;
}
