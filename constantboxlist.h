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


protected:
    QSize sizeHint()const;

public:
    ConstantBoxList(int height = 400, QWidget *parent = nullptr);
    ConstantBox* addNewWidget();
    int getListOfWidgetsLength()const;
    void clear();
    /// Button for adding new elements of T widget
    QPushButton *addNewWidgetBtn;
    /// Opens the file explorer to save the content of list of widgets
    QPushButton *saveToFileBtn;
    /// Opens the file explorer to load the content of saved list of widgets
    QPushButton *loadFromFileBtn;
    /// Clears the content of the list
    QPushButton *clearAllContentBtn;


signals:
    /// Invokes after every change of constant, i.e. altering, removing, clearing
    void constantsUpdated();

public slots:
    void update();
    void addNewWidgetToFunctionList();
    void saveConstantListToFile();
    void loadConstantListFromFile();
    void removeWidget(ConstantBox*);
    void clearList();

};

#endif // CONSTANTBOXLIST_H
