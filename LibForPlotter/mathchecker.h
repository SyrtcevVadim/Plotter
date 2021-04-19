#ifndef MATHCHECKER_H
#define MATHCHECKER_H
#include<QStringList>
#include<QMetaType>
#include"mathexpression.h"

class MathChecker
{
private:
    /// Stores mathematical expression it checks
    QStringList expression;
    /// Checks whether token is decimal number or not

    /// Stores incorrect token after executing check-methods
    QString errorMessage;

public:
    MathChecker() = default;
    MathChecker(const QString &expression);

    /// Checks whether all tokens in the expression are correct or not. If expression contains incorrect token
    /// function returns false and that incorrect token is stored at incorrectToken field
    bool AreAllTokensCorrect();
    /// Checks whether opening brackets corresponds to closing ones or not. If any bracket is missed, it's
    /// stored at incorrectToken field
    bool AreBracketsCorrespond();
    /// Checks whether mathematical expression constists of empty brackets or not
    bool HasEmptyBrackets();
    /// Checks whether there're missed operations between operands or not
    bool HasMissedOperations();
    /// Checks whether every function/operation has enough operands or not
    bool HasMissedOperands();

    /// Returns the error message if mistake is presented
    QString GetErrorMessage()const;
};


Q_DECLARE_METATYPE(MathChecker)

#endif // MATHCHECKER_H
