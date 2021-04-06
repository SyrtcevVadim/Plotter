#ifndef CONSTANTBOX_H
#define CONSTANTBOX_H

#include <QtWidgets>

class ConstantBox : public QWidget
{
    Q_OBJECT
private:
    QLabel *constantNameLbl;
    QLineEdit *constantBox;
    QLabel *constantValueLbl;
    QLineEdit *valueBox;
    QPushButton *removeButton;


public:
    explicit ConstantBox(QWidget *parent = nullptr);

};

#endif // CONSTANTBOX_H
