#include "mathparser.h"
#include<QFile>
#include<QCoreApplication>
#include<QDebug>
#include<QTextStream>
#include<QRegExp>

QStringList MathParser::delimitersForParsing({"(","[","{",")","]","}",
                                              "+","-","*","/","^",
                                              ",",";"});


QStringList MathParser::CreateTokenList(QString expression)
{
    if(!expression.isEmpty())
    {
        // Insert spaces on the left and on the right of every delimiter
        for(QString delimiter: delimitersForParsing)
        {
            expression = expression.replace(QRegExp(R"(\s*\)"+delimiter+R"(\s*)"), " "+delimiter+" ");
        }
        // Deleting useless spaces from the end and from the start of expression
        expression = expression.trimmed();
        qDebug() << expression.split(QRegExp(R"(\s+)"));
        return expression.split(QRegExp(R"(\s+)"));

    }
    return QStringList();
}


