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
    /// Хранит позицию, в которую пользователь кликнул ЛКМ внутри этого виджета
    QPoint mouseClickPos;
    /// Starts drag process
    void startDrag();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


public:
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

    FunctionBox(QWidget *parent = nullptr);
    MathExpression* GetMathExpression();

signals:
    void elementRemoved(FunctionBox*);

private slots:
    void MathExpressionChanged(const QString &str);
    void AParamChanged(const QString &value);
    void BParamChanged(const QString &value);
    void CParamChanged(const QString &value);
    void DParamChanged(const QString &value);
    void MinimumVarValueChanged(const QString &value);
    void MaximumVarValueChanged(const QString &value);
    void RemoveBtnClick();

};

#endif // FUNCTIONBOX_H
