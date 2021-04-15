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

    /// Метка для выражения "y="
    QLabel *functionName;
    /// Метка для отображения ошибок
    QLabel *errorText;
    /// Отображает название параметра a
    QLabel *aLbl;
    /// Отображает название параметра b
    QLabel *bLbl;
    /// Отображает название параметра c
    QLabel *cLbl;
    /// Отображает название параметра d
    QLabel *dLbl;
    /// Отображает название переменной
    QLabel *xLbl;

    /// Starts drag process
    void startDrag();

protected:
    void paintEvent(QPaintEvent *event);
    // Функции для реализации технологии drag&drop
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


public:
    /// Поле ввода тела функции
    QLineEdit *functionBody;
    /// Поле ввода значения параметра а
    QDoubleSpinBox *aParamBox;
    /// Поле ввода значения параметра b
    QDoubleSpinBox *bParamBox;
    /// Поле ввода значения параметра c
    QDoubleSpinBox *cParamBox;
    /// Поле ввода значения параметра d
    QDoubleSpinBox *dParamBox;
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

public slots:
    void checkCorrectness();
    void changeMathExpression(const QString &str);
private slots:


    void changeAParamValue(double value);
    void changeBParamValue(double value);
    void changeCParamValue(double value);
    void changeDParamValue(double value);
    void changeMinimumVariableValue(const QString &strValue);
    void changeMaximumVariableValue(const QString &strValue);
    void removeBtnClick();

};

#endif // FUNCTIONBOX_H
