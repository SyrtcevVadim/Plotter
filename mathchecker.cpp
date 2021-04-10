#include "mathchecker.h"
#include "mathhelper.h"
#include "mathformconverter.h"
#include "mathexpression.h"
#include<QStack>
#include<QString>
#include<QDebug>

MathChecker::MathChecker(const MathExpression &expression)
{
    this->expression = expression;
}

MathChecker::MathChecker(const QString &expression)
{
    this->expression.SetExpression(expression);
}

void MathChecker::SetExpression(const MathExpression &expression)
{
    this->expression = expression;
}

void MathChecker::SetExpression(const QString &expression)
{
    this->expression.SetExpression(expression);
}

bool MathChecker::IsTokenNumber(QString &token)const
{
    // For some reasons operations treats by machine as a decimal values..(maybe, it's tied with ASCII..)
    if(token[0].isDigit() && !MathHelper::operations.contains(token))
    {
        return true;
    }
    return false;
}


bool MathChecker::AreAllTokensCorrect()
{
    for(auto token: expression.GetInfixExpression().split(" "))
    {
        if(!MathHelper::correctTokens.contains(token) && !IsTokenNumber(token))
        {
            errorMessage = "Unknown token \""+token+"\" was received!";
            return false;
            break;
        }
    }
    errorMessage ="";
    return true;
}

bool MathChecker::AreBracketsCorrespond()
{
    QStack<QString> stack;
    for(auto token: expression.GetInfixExpression().split(" "))
    {
        if(token == "(" || token == "[" || token == "{")
        {
            stack.push(token);
        }
        else if(token == ")")
        {
            if(stack.isEmpty() || stack.top() != "(")
            {
                errorMessage = "Opening parenthesis '(' is missed!";
                return false;
            }
            if(stack.top() == "(")
            {
                stack.pop();
            }
        }
        else if(token == "]")
        {
            if(stack.isEmpty() || stack.top() != "[")
            {
                errorMessage = "Opening square bracket '[' is missed!";
                return false;
            }
            if(stack.top() == "[")
            {
                stack.pop();
            }
        }
        else if(token == "}")
        {
            if(stack.isEmpty() || stack.top() != "{")
            {
                errorMessage = "Opening curly bracket '{' is missed!";
                return false;
            }
            if(stack.top() == "{")
            {
                stack.pop();
            }
        }
    }
    if(!stack.isEmpty())
    {
        if(stack.top() == "(")
        {
            errorMessage = "Closing parenthesis ')' is missed!";
        }
        else if(stack.top() == "[")
        {
            errorMessage = "Closing square bracket ']' is missed!";
        }
        else if(stack.top() == "{")
        {
            errorMessage = "Closing curly bracket '}' is missed!";
        }
        return false;
    }
    errorMessage = "";
    return true;
}

QString MathChecker::GetErrorMessage() const
{
    return this->errorMessage;
}
