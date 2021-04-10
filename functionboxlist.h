#ifndef FUNCTIONBOXLIST_H
#define FUNCTIONBOXLIST_H

#include <QtWidgets>

class FunctionBoxList : public QWidget
{

private:
    /// Полоса прокрутки списка
    QScrollArea *scrollArea;
    /// Тело списка
    QWidget *listBody;
    QVBoxLayout *listLayout;
    /// Кнопка для создания нового элемента в списке
    QPushButton *addNewItemBtn;
    /// Кнопка для удаления существующего элемента в списке
    QPushButton *removeItemBtn;

public:
    explicit FunctionBoxList(int height = 100,QWidget *parent = nullptr);

    void move(int x, int y);
};

#endif // FUNCTIONBOXLIST_H
