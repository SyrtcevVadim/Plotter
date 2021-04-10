#include<QFile>
#include<QCoreApplication>
#include "mathparser.h"
#include<QDebug>
#include<QTextStream>
#include<QRegExp>

QStringList MathParser::delimitersForParsing({"(","[","{",")","]","}",
                                              "+","-","*","/","^",
                                              ",",";"});


QStringList MathParser::CreateTokenList(QString expression)
{
    // Insert spaces on the left and on the right of every delimiter
    for(QString delimiter: delimitersForParsing)
    {

        expression = expression.replace(QRegExp(R"(\s*\)"+delimiter+R"(\s*)"), " "+delimiter+" ");
    }
    // Deleting useless spaces from the end and from the start of expression
    expression = expression.trimmed();
    return expression.split(QRegExp(R"(\s+)"));
}


