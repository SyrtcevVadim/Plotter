#include"mathhelper.h"
#include"mathformconverter.h"
#include"mathparser.h"
#include"mathexpression.h"
#include<QStack>
#include<utility>
#include<QString>
#include<QDebug>
#include<QMap>

using std::pair;

QMap<QString, int> MathFormConverter::precedence({pair<QString, int>("abs", 1),
                                                 pair<QString, int>("pow", 1),
                                                 pair<QString, int>("sqrt", 1),
                                                 pair<QString, int>("sin", 1),
                                                 pair<QString, int>("cos", 1),
                                                 pair<QString, int>("arcsin", 1),
                                                 pair<QString, int>("arccos", 1),
                                                 pair<QString, int>("arctg", 1),
                                                 pair<QString, int>("arcctg", 1),
                                                 pair<QString, int>("tg", 1),
                                                 pair<QString, int>("ctg", 1),
                                                 pair<QString, int>("lg", 1),
                                                 pair<QString, int>("ln", 1),
                                                 pair<QString, int>("log", 1),
                                                 pair<QString, int>("un-", 1),
                                                 pair<QString, int>("un+", 1),
                                                 pair<QString, int>("^", 2),
                                                 pair<QString, int>("*", 3),
                                                 pair<QString, int>("/", 3),
                                                 pair<QString, int>("+", 4),
                                                 pair<QString, int>("-", 4),
                                                 });


bool MathFormConverter::IsTokenNumber(QString &token)
{
    if(!MathHelper::IsTokenOperation(token) && token[0].isDigit())
    {
        return true;
    }
    return false;
}

bool MathFormConverter::IsTokenSeparator(QString &token)
{
    if(token == "," || token == ";")
    {
        return true;
    }
    return false;
}

QString MathFormConverter::InfixToPostfix(const QString &expression)
{
    // Creates a stack for intermediate values
    QStack<QString> stack;
    QString resultStrExpression{" "};
    QString previousToken{""};
    // Iterates through the expression

    for(auto token: MathParser::CreateTokenList(expression))
    {
        // Processing unary plus and minus
        if((token == "+" || token == "-") && (previousToken.isEmpty() || MathHelper::IsTokenOpeningBracket(previousToken) || IsTokenSeparator(previousToken) ||
                                              MathHelper::IsTokenOperation(previousToken)))
        {
            stack.push("un"+token); // un+ or un-
        }
        // If token is a decimal number, we push it to the result string
        else if(IsTokenNumber(token))
        {
            resultStrExpression += token + " ";
        }
        else if(MathHelper::IsTokenVariable(token))
        {
            resultStrExpression += token + " ";
        }
        else if(MathHelper::IsTokenParameter(token))
        {
            resultStrExpression += token + " ";
        }
        else if(MathHelper::IsTokenConstant(token))
        {
            resultStrExpression += token + " ";
        }
        // Process opening brackets
        else if(MathHelper::IsTokenOpeningBracket(token))
        {
            stack.push(token);
        }
        // Process closing parathesis
        else if(token == ")")
        {
            // Pops everything from stack until we reach opening parenthesis
            while(!stack.isEmpty() && stack.top() != "(")
            {
                resultStrExpression += stack.pop() + " ";
            }
            if(!stack.isEmpty() && stack.top() == "(")
            {
                // Get rid of opening paranthesis
                stack.pop();
            }
        }
        else if(token == "]")
        {
            // Pops everything from stack until we reach opening square bracket
            while(!stack.isEmpty() && stack.top() != "[")
            {
                resultStrExpression += stack.pop() + " ";
            }
            if(!stack.isEmpty() && stack.top() == "[")
            {
                // Get rid of opening paranthesis
                stack.pop();
            }
        }
        else if(token == "}")
        {
            // Pops everything from stack until we reach opening parenthesis
            while(!stack.isEmpty() && stack.top() != "{")
            {
                resultStrExpression += stack.pop() + " ";
            }
            if(!stack.isEmpty() && stack.top() == "{")
            {
                // Get rid of opening paranthesis
                stack.pop();
            }
        }
        else if(IsTokenSeparator(token))
        {
            // Pops everything from the stack until we face with opening bracket
            while(!stack.isEmpty() && !MathHelper::IsTokenOpeningBracket(stack.top()))
            {
                resultStrExpression += stack.pop() + " ";
            }
            if(stack.isEmpty())
            {
                throw "Opening bracket of the function is missed";
            }
        }
        else if(MathHelper::IsTokenFunction(token) || MathHelper::IsTokenOperation(token))
        {
            // every function is pushed to the stack
            // Check the precedence of the function at the stack's top
            if(!stack.isEmpty() && (MathHelper::IsTokenFunction(stack.top()) || MathHelper::IsTokenOperation(stack.top())) && (precedence[stack.top()] < precedence[token] ||
                                                                    (precedence[stack.top()] == precedence[token] && token != "^")))
            {
                resultStrExpression += stack.pop() + " ";
            }
            stack.push(token);
        }
        previousToken = token;
    }
    // If stack isn't empty, we pop everything from it to result
    while(!stack.isEmpty())
    {
        resultStrExpression += stack.pop() + " ";
    }
    return resultStrExpression.trimmed();
}
