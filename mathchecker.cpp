#include "mathchecker.h"
#include "mathhelper.h"
#include "mathparser.h"
#include "mathexpression.h"
#include<QStack>
#include<QString>
#include<QDebug>



MathChecker::MathChecker(const QString &expression)
{
    this->expression = MathParser::CreateTokenList(expression);
}

bool MathChecker::IsTokenNumber(const QString &token)
{
    if(token.isEmpty())
    {
        return false;
    }
    if(MathHelper::operations.contains(token))
    {
        return false;
    }
    for(auto symbol: token)
    {
        if(symbol != '-' && symbol != '+' && !symbol.isDigit())
        {
            return false;
        }
    }
    return true;
}

bool MathChecker::AreAllTokensCorrect()
{
    for(auto token: expression)
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
    for(auto token: expression)
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

bool MathChecker::AreArgumentsCorresepond()
{
    QString previousToken{""};
    for(auto token: expression)
    {
        if(IsTokenNumber(previousToken) && IsTokenNumber(token))
        {
            // Numbers can't go consistently: 5 5 6 - error
            errorMessage = "Operation between " + previousToken + " and " + token +" is missed!";
            return false;
        }
        else if(MathHelper::IsTokenOpeningBracket(previousToken) && MathHelper::IsTokenClosingBracket(token))
        {
            // Brackets can't hold emptiness
            errorMessage = "Empty expression is inside brackets!";
            return false;
        }
        else if(MathHelper::functions.contains(previousToken) && !MathHelper::IsTokenOpeningBracket(token))
        {
            // Function hasn't it's argument list
            errorMessage = "Arguments of function " + previousToken + " are missed!";
            return false;
        }
        previousToken = token;
    }
    // Checking of correct arguments for binary/unary operations
    QVector vec{expression.toVector()};
    for(int i{0}; i < vec.length(); i++)
    {
        if(MathHelper::operations.contains(vec[i]))
        {

            // Checks the left operand
            if(0 > i-1 || !(MathHelper::IsTokenClosingBracket(vec[i-1]) || IsTokenNumber(vec[i-1]) ||
                            MathHelper::IsTokenParameter(vec[i-1]) ||
                            MathHelper::IsTokenConstant(vec[i-1])||
                            MathHelper::IsTokenVariable(vec[i-1])))
            {
                if(vec[i] != "+" && vec[i] != "-")
                {
                    errorMessage = "Missed left argument of " + vec[i] + " operation!";
                    return false;
                }
            }
            //Checks the right operand
            if(vec.length() <= i+1 || !(MathHelper::IsTokenFunction(vec[i+1]) || IsTokenNumber(vec[i+1]) ||
                                        MathHelper::IsTokenConstant(vec[i+1]) ||
                                        MathHelper::IsTokenParameter(vec[i+1])||
                                        MathHelper::IsTokenVariable(vec[i+1])))
            {
                // In case: + + - *
                errorMessage = "Missed right argument of " + vec[i] + " operation!";
                return false;
            }
        }
    }

    // Check the argument separator and functions' operand quantity


    return true;
}
