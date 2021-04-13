#ifndef CONSTANTBOXLIST_H
#define CONSTANTBOXLIST_H
#include<QtWidgets>
#include"constantbox.h"

class ConstantBoxList : public QWidget
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
    QList<ConstantBox*> listOfWidgets;
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
    ConstantBoxList(int height = 400, QWidget *parent = nullptr);
    ConstantBox* addNewWidget();
    int getListOfWidgetsLength()const;
    void clear();

public slots:
    void AddNewWidgetToFunctionList();
    void SaveFunctionListToFile();
    void LoadFunctionListFromFile();
    void RemoveWidget(ConstantBox*);
    void Clear();

};

#endif // CONSTANTBOXLIST_H
