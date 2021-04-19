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
            errorMessage = QString("Получено неизвестное выражение \"%1\"").arg(token);
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
                errorMessage = "Пропущена открывающая круглая скобка";
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
                errorMessage = "Пропущена открывающая квадратная скобка";
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
                errorMessage = "Пропущена открывающая фигурная скобка";
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
            errorMessage = "Пропущена закрывающая круглая скобка";
        }
        else if(stack.top() == "[")
        {
            errorMessage = "Пропущена закрывающая квадратная скобка";
        }
        else if(stack.top() == "{")
        {
            errorMessage = "Пропущена закрывающая фигурная скобка";
        }
        return false;
    }
    errorMessage.clear();
    return true;
}

bool MathChecker::HasEmptyBrackets()
{
    qDebug() << expression;
    QString previousToken{""};
    for(auto token: expression)
    {
        if(MathHelper::IsTokenOpeningBracket(previousToken)&&
                MathHelper::IsTokenClosingBracket(token))
        {
            errorMessage = QString("Пропущено выражение между %1 и %2").arg(previousToken, token);
            return true;
        }
        previousToken=token;
    }
    errorMessage.clear();
    return false;
}

bool MathChecker::HasMissedOperations()
{
    qDebug() << expression;
    QString previousToken{""};
    for(auto token: expression)
    {
        if((MathHelper::IsTokenNumber(previousToken)||MathHelper::IsTokenParameter(previousToken)||
            MathHelper::IsTokenConstant(previousToken)||MathHelper::IsTokenVariable(previousToken))&&MathHelper::IsTokenOpeningBracket(token))
        {
            qDebug() << previousToken << " " <<token;
            continue;
        }
        if((MathHelper::IsTokenNumber(previousToken)||MathHelper::IsTokenParameter(previousToken)||MathHelper::IsTokenVariable(previousToken)||
            MathHelper::IsTokenConstant(previousToken))&&
           (MathHelper::IsTokenNumber(token)||MathHelper::IsTokenParameter(token)||MathHelper::IsTokenVariable(token)||
            MathHelper::IsTokenConstant(token)))
        {
            errorMessage = QString("Пропущена операция между \"%1\" и \"%2\"").arg(previousToken, token);
            return true;
        }

        previousToken = token;
    }
    return false;
}

bool MathChecker::HasMissedOperands()
{
    qDebug() << expression;
    QString strExpRepr{""};
    for(auto token: expression)
    {
        strExpRepr+= token +" ";
    }
    strExpRepr = strExpRepr.trimmed();
    MathExpression mathExp{strExpRepr};

    // Substitute variable's value
    QString expressionWithSubstitutedValues(mathExp.SubstituteVariableValue(0));
    qDebug() <<expressionWithSubstitutedValues;
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
            double first, second;
            // Checking for necessary operands quantity
            if(!stack.isEmpty() && stack.count() >= MathHelper::operandQuantity[token])
            {
                first = stack.pop().toDouble();
                if(MathHelper::operandQuantity[token] == 2)
                {
                    second = stack.pop().toDouble();
                }
                // Pushs result back to stack
                stack.push("1");
            }
            else
            {
                errorMessage = QString("Недостаточно операндов для %1:  %2 %3").arg(token, previousToken, token);
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
    return this->errorMessage;
}
