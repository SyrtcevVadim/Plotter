#ifndef CONSTANTBOX_H
#define CONSTANTBOX_H
#include <QtWidgets>

class ConstantBox : public QWidget
{
    Q_OBJECT
private:
    /// Name of the constant
    QString constantName;
    /// Value of the constant tied with constant name
    QString constantValue;

    QLabel *constantNameLbl;
    QLabel *constantValueLbl;
    /// Label for displaying errors of declaring a constant
    QLabel *errorText;

protected:
    void paintEvent(QPaintEvent *event);
    QSize sizeHint()const;

public:
    /// LineEdit for entering the constant's name
    QLineEdit *constantBox;
    /// LineEdit for entering the constant's value
    QLineEdit *valueBox;
    /// Removes current ConstantBox object
    QPushButton *removeButton;

    explicit ConstantBox(QWidget *parent = nullptr);
    /// Returns constant's name
    QString getConstantName()const;
    /// Return constant's value
    QString getConstantValue()const;

    bool isCorrect();

public slots:
    /// Removes this ConstantBox object
    void removeConstant();
    /// Sets the constant's name
    void setConstantName(const QString&);
    /// Sets the constant's value
    void setConstantValue(const QString&);



signals:
    /// Is emmited when user changes constant inside constantBox object
    void elementChanged();
    /// Is emmited when user deletes constant box
    void elementRemoved(ConstantBox*);
};

#endif // CONSTANTBOX_H
