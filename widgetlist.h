#ifndef WIDGETLIST_H
#define WIDGETLIST_H

#include <QtWidgets>
// TODO сделать шаблонным
class WidgetList : public QWidget
{

private:
    QScrollArea *scrollArea;
    /// Body of the list
    QWidget *listBody;
    /// Body's layout
    QVBoxLayout *listLayout;

    QPushButton *addNewItemBtn;

    QPushButton *removeItemBtn;

public:
    explicit WidgetList(int height = 100,QWidget *parent = nullptr);

    void move(int x, int y);
};

#endif // WIDGETLIST_H
