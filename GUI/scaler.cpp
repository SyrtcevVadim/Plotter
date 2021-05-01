#include "scaler.h"
#include <QtWidgets>

Scaler::Scaler(QWidget *parent): QWidget(parent)
{
    resize(160,50);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *scaleLbl = new QLabel(tr("Scale"));
    QLabel *scaleOneLbl = new QLabel("1");
    QLabel *scaleTwoLbl = new QLabel("2");
    QLabel *scaleFourLbl = new QLabel("4");
    QLabel *scaleEightLbl = new QLabel("8");


    scaleOneBtn = new QRadioButton();
    scaleOneBtn->setChecked(true);
    scaleTwoBtn = new QRadioButton();
    scaleFourBtn = new QRadioButton();
    scaleEightBtn = new QRadioButton();
    QButtonGroup *radioButtonGroup = new QButtonGroup();
    radioButtonGroup->addButton(scaleOneBtn, 1);
    radioButtonGroup->addButton(scaleTwoBtn,2);
    radioButtonGroup->addButton(scaleFourBtn, 4);
    radioButtonGroup->addButton(scaleEightBtn, 8);


    QGridLayout *layout = new QGridLayout();
    layout->addWidget(scaleLbl,0,0,1, -1);
    layout->addWidget(scaleOneLbl, 1,0);
    layout->addWidget(scaleOneBtn,1,1);
    layout->addWidget(scaleTwoLbl, 1,3);
    layout->addWidget(scaleTwoBtn, 1,4);
    layout->addWidget(scaleFourLbl, 1,6);
    layout->addWidget(scaleFourBtn, 1,7);
    layout->addWidget(scaleEightLbl, 1, 9);
    layout->addWidget(scaleEightBtn, 1,10);
    setLayout(layout);

    connect(radioButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(changeScale(int)));

    scaleTwoBtn->setChecked(true);
}

void Scaler::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawRect(0,0, width()-1, height()-1);
}

void Scaler::changeScale(int id)
{
    emit(scaleChanged(id));
}


QSize Scaler::sizeHint() const
{
    return QSize(width(), height());
}
