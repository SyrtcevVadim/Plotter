#ifndef FUNCTIONBOX_H
#define FUNCTIONBOX_H
#include<QtWidgets>
#include"LibForPlotter/mathexpression.h"

/// Widget for creating new mathematic expression, setting it's parameters' values and variable's restrictions
class FunctionBox : public QWidget
{
    Q_OBJECT

private:
    /// Color of the graph of stored function
    QColor graphColor{Qt::black};
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
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QSize sizeHint()const;


public:
    /// Fetchs function's body
    QLineEdit *functionBody;
    /// Fetchs a parameter's value
    QDoubleSpinBox *aParamBox;
    /// Fetchs b parameter's value
    QDoubleSpinBox *bParamBox;
    /// Fetches c parameter's value
    QDoubleSpinBox *cParamBox;
    /// Fetches d parameter's value
    QDoubleSpinBox *dParamBox;

    /// Fetchs minimum possible variable's value
    QDoubleSpinBox *minimumVarValueBox;
    /// Fetchs maximum possible variable's value
    QDoubleSpinBox *maximumVarValueBox;
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
    /// Is emmited when user changes any part of mathematic expression inside a box
    void functionChanged(int);
    /// Is emmited when user changes the color of a graph
    void graphColorChanged(int, QColor);
    /// Is emmited when user clicks clearFromPlotterBtn
    void graphCleared(int);



public slots:
    /// Checks the correctness of provided mathematic expression
    void checkCorrectness();
    /// Changes mathematic expression
    void changeMathExpression(const QString &str);
    /// Draws a rectangle border
    void drawBorders(QPainter &painter, const QColor &color);

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
    void changeMinimumVariableValue(double value);
    /// Changes maximum possible variable's value
    void changeMaximumVariableValue(double value);
    /// Removes this FunctionBox object
    void removeFunction();
    void clearGraph();

};

#endif // FUNCTIONBOX_H
