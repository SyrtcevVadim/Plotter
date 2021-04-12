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

public:

    FunctionBoxList(int height = 400,QWidget *parent = nullptr);

    FunctionBox* addNewWidget();

    void clear();

private slots:
    void OnAddNewWidgetBtnClick();
    void OnSaveToFileBtnClick();
    void OnLoadFromFileBtnClick();
    void OnRemoveBtnClick(FunctionBox*);

};

#endif // FUNCTIONBOXLIST_H
