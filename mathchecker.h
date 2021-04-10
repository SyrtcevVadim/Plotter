#ifndef MATHCHECKER_H
#define MATHCHECKER_H
#include<QStringList>
#include<QMetaType>
#include"mathexpression.h"

class MathChecker
{
private:
    /// Stores mathematical expression it checks
    MathExpression expression;
    /// Checks whether token is decimal number or not
    bool IsTokenNumber(QString &token)const;
    /// Stores incorrect token after executing check-methods
    QString errorMessage;
public:

    MathChecker() = default;

    MathChecker(const MathExpression &expression);

    MathChecker(const QString &expression);
    /// Sets the mathematical expression
    void SetExpression(const MathExpression &expression);
    /// Sets the mathematical expression from it's string representation
    void SetExpression(const QString &expression);

    /// Checks whether all tokens in the expression are correct or not. If expression contains incorrect token
    /// function returns false and that incorrect token is stored at incorrectToken field
    bool AreAllTokensCorrect();
    /// Checks whether opening brackets corresponds to closing ones or not. If any bracket is missed, it's
    /// stored at incorrectToken field
    bool AreBracketsCorrespond();
    /// Returns the error message if mistake is presented
    QString GetErrorMessage()const;
};

Q_DECLARE_METATYPE(MathChecker)

#endif // MATHCHECKER_H
