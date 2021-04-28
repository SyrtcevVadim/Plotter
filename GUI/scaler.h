#ifndef SCALER_H
#define SCALER_H
#include<QtWidgets>

class Scaler: public QWidget
{
    Q_OBJECT
protected:
    QSize sizeHint()const;
    void paintEvent(QPaintEvent *event);
public:
    Scaler(QWidget *parent=nullptr);
    QRadioButton *scaleOneBtn;
    QRadioButton *scaleTwoBtn;
    QRadioButton *scaleFourBtn;
    QRadioButton *scaleEightBtn;

signals:
    void scaleChanged(int);
public slots:
    void changeScale(int id);
};

#endif // SCALER_H
