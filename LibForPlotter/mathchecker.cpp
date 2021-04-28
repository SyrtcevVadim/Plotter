#include "mathchecker.h"
#include "mathhelper.h"
#include "mathparser.h"
#include "mathexpression.h"
#include<QStack>
#include<QString>
#include<QDebug>
#include<QVector>


MathChecker::MathChecker(const QString &expression)
{
    this->expression = MathParser::CreateTokenList(expression);
}


bool MathChecker::AreAllTokensCorrect()
{
    for(auto token: expression)
    {
        if(!(MathHelper::correctTokens.contains(token) || MathHelper::userDefinedConstants.contains(token) ||
             MathHelper::IsTokenNumber(token)))
        {
            errorMessage = QObject::tr("Unexpected expression was received: \"%1\"").arg(token);
            return false;
        }
    }
    errorMessage.clear();
    return true;
}

bool MathChecker::AreBracketsCorrespond()
{
    QStack<QString> stack;
    for(auto token: expression)
    {
        if(MathHelper::IsTokenOpeningBracket(token))
        {
            stack.push(token);
        }
        else if(token == ")")
        {
            if(stack.isEmpty() || stack.top() != "(")
            {
                errorMessage = QObject::tr("Opening parenthesis was missed");
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
                errorMessage = QObject::tr("Opening square bracket was missed");
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
                errorMessage = QObject::tr("Opening curly bracket was missed");
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
            errorMessage = QObject::tr("Closing parenthesis was missed");
        }
        else if(stack.top() == "[")
        {
            errorMessage = QObject::tr("Closing square bracket was missed");
        }
        else if(stack.top() == "{")
        {
            errorMessage = QObject::tr("Closing curly bracket was missed");
        }
        return false;
    }
    errorMessage.clear();
    return true;
}

bool MathChecker::HasEmptyBrackets()
{
    QString previousToken{""};
    for(auto token: expression)
    {
        if(MathHelper::IsTokenOpeningBracket(previousToken)&&
                MathHelper::IsTokenClosingBracket(token))
        {
            errorMessage = QObject::tr("Missed expression between %1 and %2").arg(previousToken, token);
            return true;
        }
        previousToken=token;
    }
    errorMessage.clear();
    return false;
}

bool MathChecker::HasMissedOperations()
{
    QString previousToken{""};
    for(auto token: expression)
    {
        if((MathHelper::IsTokenNumber(previousToken)||MathHelper::IsTokenParameter(previousToken)||
            MathHelper::IsTokenConstant(previousToken)||MathHelper::IsTokenVariable(previousToken))&&MathHelper::IsTokenOpeningBracket(token))
        {
            continue;
        }
        if((MathHelper::IsTokenNumber(previousToken)||MathHelper::IsTokenParameter(previousToken)||MathHelper::IsTokenVariable(previousToken)||
            MathHelper::IsTokenConstant(previousToken))&&
           (MathHelper::IsTokenNumber(token)||MathHelper::IsTokenParameter(token)||MathHelper::IsTokenVariable(token)||
            MathHelper::IsTokenConstant(token)))
        {
            errorMessage = QObject::tr("Missed operation between \"%1\" and \"%2\"").arg(previousToken, token);
            return true;
        }

        previousToken = token;
    }
    return false;
}

bool MathChecker::HasMissedOperands()
{
    QString strExpRepr{""};
    for(auto token: expression)
    {
        strExpRepr+= token +" ";
    }
    strExpRepr = strExpRepr.trimmed();
    MathExpression mathExp{strExpRepr};

    // Substitute variable's value
    QString expressionWithSubstitutedValues(mathExp.substituteVariableValue(0));
    // Stores intermediate values
    QStack<QString> stack;
    QString previousToken{""};
    // Iterate through the expression in postfix form
    for(auto token: (expressionWithSubstitutedValues.trimmed()).split(" "))
    {
        if(MathHelper::IsTokenNumber(token))
        {
            stack.push(token);
        }
        else if(MathHelper::IsTokenFunction(token) || MathHelper::IsTokenOperation(token))
        {
            // Checking for necessary operands quantity
            if(!stack.isEmpty() && stack.count() >= MathHelper::operandQuantity[token])
            {
                stack.pop();
                if(MathHelper::operandQuantity[token] == 2)
                {
                    stack.pop();
                }
                // Pushs result back to stack
                stack.push("1");
            }
            else
            {
                if(token.startsWith("un"))
                {
                    token = token.remove(0,2);
                }
                errorMessage = QObject::tr("Not enough operands for %1").arg(token);
                qDebug() << errorMessage;
                return true;
            }
        }
        previousToken = token;
    }
    return false;
}

QString MathChecker::GetErrorMessage() const
{
    return errorMessage;
}
