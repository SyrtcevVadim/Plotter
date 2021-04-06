#ifndef FUNCTIONBOX_H
#define FUNCTIONBOX_H
#include<QtWidgets>

/// Виджет для хранения математической функции и задания ограничений для него
class FunctionBox : public QWidget
{
    Q_OBJECT
private:
    static int lineEditHeight;

    /// Метка для выражения "y="
    QLabel *functionName;
    /// Поле ввода тела функции
    QLineEdit *functionBody;

    /// Метка для отображения ошибок
    QLabel *errorLabel;
    QLabel *errorText;

    /// Отображает название параметра a
    QLabel *aLbl;
    /// Поле ввода значения параметра а
    QLineEdit *aParamBox;
    /// Отображает название параметра b
    QLabel *bLbl;
    /// Поле ввода значения параметра b
    QLineEdit *bParamBox;
    /// Отображает название параметра c
    QLabel *cLbl;
    /// Поле ввода значения параметра c
    QLineEdit *cParamBox;
    /// Отображает название параметра d
    QLabel *dLbl;
    /// Поле ввода значения параметра d
    QLineEdit *dParamBox;

    /// Отображает название переменной
    QLabel *xLbl;

    /// Поле для ввода минимально возможного значения
    /// переменной x
    QLineEdit *minimumVarValueBox;
    /// Поле для ввода максимально возможного значения
    /// перменной x
    QLineEdit *maximumVarValueBox;

    QPushButton *removeBtn;


public:
    explicit FunctionBox(QWidget *parent = nullptr);

};

#endif // FUNCTIONBOX_H
