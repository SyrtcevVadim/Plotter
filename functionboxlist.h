#ifndef FUNCTIONBOXLIST_H
#define FUNCTIONBOXLIST_H
#include <QtWidgets>
#include "functionbox.h"

class FunctionBoxList : public QWidget
{
    Q_OBJECT
private:
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

public:

    FunctionBoxList(int height = 400,QWidget *parent = nullptr);
    FunctionBox* addNewWidget();


    void clear();
public slots:
    void AddNewWidgetToFunctionList();
    void SaveFunctionListToFile();
    void LoadFunctionListFromFile();
    void RemoveWidget(FunctionBox*);
    void Clear();

};

#endif // FUNCTIONBOXLIST_H
