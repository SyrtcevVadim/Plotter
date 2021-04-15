#ifndef CONSTANTBOXLIST_H
#define CONSTANTBOXLIST_H
#include<QtWidgets>
#include"GUI/constantbox.h"

class ConstantBoxList : public QWidget
{
    Q_OBJECT
private:
    /// Width of widget
    int m_width;
    /// Height of widget
    int m_height;
    /// Scroll area of this list
    QScrollArea *scrollArea;
    /// Body of this list
    QWidget *listBody;
    /// Body's layout
    QVBoxLayout *listLayout;
    /// Container for storing widgets
    QList<ConstantBox*> listOfWidgets;

protected:
    QSize sizeHint()const;

public:
    /// Button for adding new elements of ConstantBox type
    QPushButton *addNewWidgetBtn;
    /// Button for opening a file dialog with OS to save the content of list of widgets
    QPushButton *saveToFileBtn;
    /// Button for opening file dialof with OS to load the content of saved list of widgets
    QPushButton *loadFromFileBtn;
    /// Clears the content of the list
    QPushButton *clearAllContentBtn;

    ConstantBoxList(int height = 400, QWidget *parent = nullptr);
    /// Returns the length of list
    int getLength()const;

signals:
    /// Is emmited when user changes any constant, i.e. alters, removes, clears
    void constantsUpdated();

public slots:
    /// Updates the content of list
    void update();
    /// Adds new ConstantBox to list
    void addNewWidget();
    /// Saves constants to file
    void saveConstantListToFile();
    /// Loads constants from file
    void loadConstantListFromFile();
    /// Removes ConstantBox object from list
    void removeWidget(ConstantBox*);
    /// Clears list's content
    void clear();

};

#endif // CONSTANTBOXLIST_H
