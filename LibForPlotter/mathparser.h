#ifndef MATHPARSER_H
#define MATHPARSER_H
#include<QStringList>
#include<QString>

class MathParser
{
private:
    /// Stores the delimiters which help when an expression is parsed
    static QStringList delimitersForParsing;
public:
    /// Creates a token list based on string representation of mathematical expression
    static QStringList CreateTokenList(QString expression);
};

#endif // MATHPARSER_H
