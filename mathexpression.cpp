#include "mathhelper.h"
#include "mathexpression.h"
#include "mathparser.h"
#include "mathformconverter.h"
#include<QMap>
#include<QDataStream>
#include<QDebug>
#include<QString>



MathExpression::MathExpression()
{
    // Sets 1 as an initial value of the parameters
    for(auto param: MathHelper::parameters)
    {
        parameters[param] = 1.0;
    }
    initialExpression="";
    infixExpression = "";
    postfixExpression="";
}

MathExpression::MathExpression(QString expression): MathExpression()
{
    initialExpression = expression.trimmed();
    infixExpression = " ";
    for(auto token: MathParser::CreateTokenList(expression))
    {
        infixExpression += token + " ";
    }
    infixExpression = SubstituteConstants(infixExpression);
    postfixExpression = SubstituteParameters(MathFormConverter::InfixToPostfix(infixExpression));
}

QString MathExpression::GetInitialExpression() const
{
    return initialExpression;
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

double MathExpression::GetParameterValue(QString parameter)const
{
    return parameters[parameter];
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
    initialExpression = expression;
    infixExpression = " ";
    for(auto token: MathParser::CreateTokenList(expression))
    {
        infixExpression += token + " ";
    }
    infixExpression = SubstituteConstants(infixExpression);
    postfixExpression = SubstituteParameters(MathFormConverter::InfixToPostfix(infixExpression));
}

QString MathExpression::SubstituteConstants(QString infixExpression)
{
    QString resultExpression{""};
    for(auto key: (infixExpression.trimmed()).split(" "))
    {
        if(MathHelper::predefinedConstants.contains(key))
        {
            resultExpression += MathHelper::predefinedConstants[key] + " ";
        }
        else if(MathHelper::userDefinedConstants.contains(key))
        {
            resultExpression += MathHelper::userDefinedConstants[key] + " ";
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

QDataStream& operator<<(QDataStream &stream, const MathExpression &expression)
{
    // Inserting all info about math expression into output file
    stream << expression.initialExpression <<
              expression.infixExpression << expression.postfixExpression <<
              expression.parameters["a"] << expression.parameters["b"] <<
              expression.parameters["c"] << expression.parameters["d"] <<
              expression.minimumVarValue << expression.maximumVarValue;
    return stream;
}

QDataStream& operator>>(QDataStream &stream,MathExpression &expression)
{
    stream >> expression.initialExpression >>
            expression.infixExpression >> expression.postfixExpression >>
            expression.parameters["a"] >> expression.parameters["b"] >>
            expression.parameters["c"] >> expression.parameters["d"] >>
            expression.minimumVarValue >> expression.maximumVarValue;
    return stream;
}

QDebug operator<<(QDebug stream, const MathExpression &expression)
{
    stream << "Infix: " << expression.GetInfixExpression() <<"\nPostfix: " << expression.GetPostfixExpression()<< "\nA: " <<
              expression.parameters["a"] << "| B: " << expression.parameters["b"] <<"| C: "<<expression.parameters["c"] <<
              "| D: "<<expression.parameters["d"] <<"\nMinXVal: " << expression.minimumVarValue << "| MaxXVal: "<<expression.maximumVarValue;
    return stream;
}
