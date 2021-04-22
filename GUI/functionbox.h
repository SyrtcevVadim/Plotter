#ifndef FUNCTIONBOX_H
#define FUNCTIONBOX_H
#include<QtWidgets>
#include"LibForPlotter/mathexpression.h"

/// Widget for creating new mathematic expression, setting it's parameters' values and variable's restrictions
class FunctionBox : public QWidget
{
    Q_OBJECT

private:
    /// User-passed mathematic expression
    MathExpression *expression;
    /// Last left mouse button click position
    QPoint mouseClickPos;

    QLabel *functionName;
    /// Displays error messages
    QLabel *errorText;

    QLabel *aLbl;
    QLabel *bLbl;
    QLabel *cLbl;
    QLabel *dLbl;
    QLabel *xLbl;

    /// Starts drag process
    void startDrag();

protected:
    void paintEvent(QPaintEvent *event);
    // Functions for maintaining drag&drop mechanism
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


public:
    /// Fetchs function's body
    QLineEdit *functionBody;
    /// Fetchs a parameter value
    QDoubleSpinBox *aParamBox;
    /// Fetchs b parameter value
    QDoubleSpinBox *bParamBox;
    /// Fetches c parameter value
    QDoubleSpinBox *cParamBox;
    /// Fetches d parameter value
    QDoubleSpinBox *dParamBox;

    /// Fetchs minimum possible variable's value
    QLineEdit *minimumVarValueBox;
    /// Fetchs maximum possible variable's value
    QLineEdit *maximumVarValueBox;
    /// Removes this object by pressing it
    QPushButton *removeBtn;
    /// Invokes the standart dialog of choosing the color
    QPushButton *changeColorBtn;
    /// Deletes the graph of provided mathematic function from Plotter object
    QPushButton *clearFromPlotterBtn;

    FunctionBox(QWidget *parent = nullptr);
    /// Returns the pointer to inner mathematic expression
    MathExpression* getMathExpression();

signals:
    /// Is emmited when user deletes this functionBox object
    void elementRemoved(FunctionBox*);
    /// Is emmited when user changes any parameter of FunctionBox object
    void expressionChanged(MathExpression*);
    void graphColorChanged(MathExpression*, QColor);
    void graphCleared(MathExpression*);



public slots:
    /// Checks the correctness of provided mathematic expression
    void checkCorrectness();
    /// Changes mathematic expression
    void changeMathExpression(const QString &str);

private slots:
    /// Changes a parameter value
    void changeAParamValue(double value);
    /// Changes b parameter value
    void changeBParamValue(double value);
    /// Changes c parameter value
    void changeCParamValue(double value);
    /// Changes d parameter value
    void changeDParamValue(double value);
    /// Changes the color of graph of provided mathematic function
    void changeGraphColor();
    /// Changes minimum possible variable's value
    void changeMinimumVariableValue(const QString &strValue);
    /// Changes maximum possible variable's value
    void changeMaximumVariableValue(const QString &strValue);
    /// Removes this FunctionBox object
    void removeFunction();
    void clearGraph();

};

#endif // FUNCTIONBOX_H
