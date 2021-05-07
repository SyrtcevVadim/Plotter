#ifndef FUNCTIONBOXLIST_H
#define FUNCTIONBOXLIST_H
#include <QtWidgets>
#include "GUI/functionbox.h"

class FunctionBoxList : public QWidget
{
    Q_OBJECT
private:
    int m_width;
    int m_height;
    QScrollArea *scrollArea;
    /// Body of the list
    QWidget *listBody;
    /// Body's layout
    QVBoxLayout *listLayout;
    /// Container for storing widgets
    QList<FunctionBox*> listOfWidgets;
    /// Button for adding new elements of T widget
    QPushButton *addNewWidgetBtn;
    /// Opens the file explorer to save the content of list of widgets
    QPushButton *saveToFileBtn;
    /// Opens the file explorer to load the content of saved list of widgets
    QPushButton *loadFromFileBtn;
    /// Clears the content of the list
    QPushButton *clearAllContentBtn;

protected:
    QSize sizeHint()const;

public:
    FunctionBoxList(int height = 400,QWidget *parent = nullptr);
    /// Returns the length of list
    int getLength()const;

signals:
    void newFunctionAdded(MathExpression*);
    void expressionChanged(int);
    void expressionDeleted(int);
    void drawGraph(int);
    void graphColorChanged(int, QColor);
    void graphCleared(int);

public slots:
    /// Updates the content of list
    void update();
    /// Adds new FunctionBox to list
    void addNewWidget();
    /// Saves functions to file
    void saveFunctionListToFile();
    /// Loads functions from file
    void loadFunctionListFromFile();
    /// Removes functions from list
    void removeWidget(FunctionBox*);
    /// Clears list's content
    void clear();
    void repaintGraph(int, QColor);
    void clearGraph(int);
    void onExpressionChanged(int);


};

#endif // FUNCTIONBOXLIST_H
