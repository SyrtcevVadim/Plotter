#include "mathhelper.h"
#include "mathexpression.h"
#include "mathparser.h"
#include "mathformconverter.h"
#include<QMap>
#include<QDebug>
#include<QString>



MathExpression::MathExpression()
{
    // Sets 1 as an initial value of the parameters

    for(auto param: MathHelper::parameters)
    {
        parameters[param] = 1.0;
    }

    infixExpression = "";
}

MathExpression::MathExpression(QString expression): MathExpression()
{
    infixExpression = " ";
    for(auto token: MathParser::CreateTokenList(expression))
    {
        infixExpression += token + " ";
    }
    infixExpression = SubstituteConstants(infixExpression);
    postfixExpression = SubstituteParameters(MathFormConverter::InfixToPostfix(infixExpression));
}

QString MathExpression::GetInfixExpression()const
{
    return infixExpression.trimmed();
}

QString MathExpression::GetPostfixExpression() const
{
    return postfixExpression.trimmed();
}

void MathExpression::SetParameter(QString parameter, double value)
{
    // Проверяем корректность параметра
    if(!parameters.contains(parameter))
    {
        throw "Incorrect parameter was passed into SetParameter method";
    }
    else
    {
        parameters[parameter] = value;
        postfixExpression = SubstituteParameters(MathFormConverter::InfixToPostfix(infixExpression));
    }
}

void MathExpression::SetParameters(double aValue, double bValue, double cValue, double dValue)
{
    parameters["a"] = aValue;
    parameters["b"] = bValue;
    parameters["c"] = cValue;
    parameters["d"] = dValue;
    postfixExpression = SubstituteParameters(MathFormConverter::InfixToPostfix(infixExpression));
}

void MathExpression::SetExpression(QString expression)
{
    infixExpression = " ";
    for(auto token: MathParser::CreateTokenList(expression))
    {
        infixExpression += token + " ";
    }
    infixExpression = SubstituteConstants(infixExpression);
    postfixExpression = SubstituteParameters(MathFormConverter::InfixToPostfix(infixExpression));
    //qDebug() << "SET EXPRESION: INFIX EXPRESSION: "<<infixExpression<<"| POSTFIX EXPRESSION: "<<postfixExpression;
}

QString MathExpression::SubstituteConstants(QString infixExpression)
{
    QString resultExpression{""};
    for(auto key: MathParser::CreateTokenList(infixExpression))
    {
        if(MathHelper::constants.contains(key))
        {
            resultExpression += MathHelper::constants[key] + " ";
        }
        else
        {
            resultExpression += key + " ";
        }
    }
    if(MathHelper::HasConstants(resultExpression))
    {
        return SubstituteConstants(resultExpression);
    }
    else
    {
        return resultExpression;
    }
}

QString MathExpression::SubstituteParameters(QString postfixExpression)
{
    QString resultExpression{""};
    for(auto key: (postfixExpression.trimmed()).split(" "))
    {
        if(parameters.contains(key))
        {
            resultExpression += QString().setNum(parameters[key]) +" ";
        }
        else
        {
            resultExpression += key + " ";
        }
    }
    return resultExpression.trimmed();
}

QString MathExpression::SubstituteVariableValue(const double varValue)
{
    QString resultExpression{""};
    for(auto key: (postfixExpression.trimmed()).split(" "))
    {
        if(MathHelper::IsTokenVariable(key))
        {
            resultExpression += QString().setNum(varValue) + " ";
        }
        else
        {
            resultExpression += key + " ";
        }
    }
    return resultExpression.trimmed();
}

void MathExpression::SetMinimumVarValue(double value)
{
    minimumVarValue = value;
}

double MathExpression::GetMinimumVarValue()
{
    return minimumVarValue;
}

void MathExpression::SetMaximumVarValue(double value)
{
    maximumVarValue = value;
}

double MathExpression::GetMaximumVarValue()
{
    return maximumVarValue;
}
