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
    static bool IsTokenNumber(const QString &token);
    /// Checks whether all tokens in the expression are correct or not. If expression contains incorrect token
    /// function returns false and that incorrect token is stored at incorrectToken field
    bool AreAllTokensCorrect();
    /// Checks whether opening brackets corresponds to closing ones or not. If any bracket is missed, it's
    /// stored at incorrectToken field
    bool AreBracketsCorrespond();
    /// Checks wether every function has appropriate number of arguments or not
    bool AreArgumentsCorresepond();
    /// Returns the error message if mistake is presented
    QString GetErrorMessage()const;
};


Q_DECLARE_METATYPE(MathChecker)

#endif // MATHCHECKER_H
