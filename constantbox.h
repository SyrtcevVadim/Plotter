#ifndef CONSTANTBOX_H
#define CONSTANTBOX_H

#include <QtWidgets>

class ConstantBox : public QWidget
{
    Q_OBJECT
private:
    QString constantName;
    QString constantValue;



protected:
    void paintEvent(QPaintEvent *event);

public:
    QLabel *constantNameLbl;
    /// LineEdit to enter the constant's name
    QLineEdit *constantBox;
    QLabel *constantValueLbl;
    /// LineEdit to enter the constant's value
    QLineEdit *valueBox;
    /// Removes current ConstantBox object
    QPushButton *removeButton;
    explicit ConstantBox(QWidget *parent = nullptr);
    QString GetConstantName()const;
    QString GetConstantValue()const;

public slots:
    void RemoveBtnClick();
    void SetConstantName(const QString&);
    void SetConstantValue(const QString&);
signals:
    void elementRemoved(ConstantBox*);
};

#endif // CONSTANTBOX_H
