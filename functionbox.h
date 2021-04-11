#ifndef FUNCTIONBOX_H
#define FUNCTIONBOX_H
#include<QtWidgets>
#include"mathexpression.h"

/// Виджет для хранения математической функции и задания ограничений для него
class FunctionBox : public QWidget
{
    Q_OBJECT
private:
    /// Высота полей ввода
    static int lineEditHeight;
    /// Математическое выражение, записанное в поле ввода
    MathExpression *expression;
    /// Метка для выражения "y="
    QLabel *functionName;
    /// Поле ввода тела функции
    QLineEdit *functionBody;
    /// Метка для отображения ошибок
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
    /// Кнопка для удаления коробки задания функции
    QPushButton *removeBtn;

protected:
    void paintEvent(QPaintEvent *event);

public:
    FunctionBox(QWidget *parent = nullptr);
    MathExpression GetMathExpression()const;

signals:
    void elementRemoved(FunctionBox*);

private slots:
    void OnMathExpressionChanged(const QString &str);
    void OnAParamChanged(const QString &value);
    void OnBParamChanged(const QString &value);
    void OnCParamChanged(const QString &value);
    void OnDParamChanged(const QString &value);
    void OnMinimumVarValueChanged(const QString &value);
    void OnMaximumVarValueChanged(const QString &value);
    void OnRemoveBtnClick();

};

#endif // FUNCTIONBOX_H
