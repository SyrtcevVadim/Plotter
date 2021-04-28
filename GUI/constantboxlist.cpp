#include"GUI/constantboxlist.h"
#include"LibForPlotter/mathhelper.h"
#include<QtWidgets>

ConstantBoxList::ConstantBoxList(int height, QWidget *parent) : QWidget(parent)
{
    setToolTip(tr("List of constants"));
    m_width = 350;
    m_height = height+50;
    listBody = new QWidget();
    listBody->setFixedWidth(m_width-20);

    listLayout = new QVBoxLayout();
    listBody->setLayout(listLayout);

    scrollArea = new QScrollArea(parent);
    scrollArea->setFixedSize(m_width, height);
    scrollArea->setWidget(listBody);


    addNewWidgetBtn = new QPushButton();
    addNewWidgetBtn->setToolTip(tr("Add new constant box"));
    saveToFileBtn = new QPushButton();
    saveToFileBtn->setToolTip(tr("Save constants to file"));
    loadFromFileBtn = new QPushButton();
    loadFromFileBtn->setToolTip(tr("Load constants from file"));
    clearAllContentBtn = new QPushButton();
    clearAllContentBtn->setToolTip(tr("Clear list of constant boxes"));

    // Sets images to buttons
    QPixmap addNewWidgetIcon(":/images/Images/AddWidgetImage.png");
    addNewWidgetBtn->setIcon(addNewWidgetIcon);
    QPixmap saveToFileIcon(":/images/Images/SaveImage.png");
    saveToFileBtn->setIcon(saveToFileIcon);
    QPixmap loadFromFileIcon(":/images/Images/LoadImage.png");
    loadFromFileBtn->setIcon(loadFromFileIcon);

    QLabel *constantListLbl = new QLabel(tr("List of constants"));

    // Setting appropriate layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(btnLayout,1);
    btnLayout->addWidget(constantListLbl);
    btnLayout->addWidget(addNewWidgetBtn);
    btnLayout->addWidget(saveToFileBtn);
    btnLayout->addWidget(loadFromFileBtn);
    btnLayout->addWidget(clearAllContentBtn);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);

    // Linking signals with slots
    connect(saveToFileBtn, SIGNAL(pressed()), this, SLOT(saveConstantListToFile()));
    connect(loadFromFileBtn, SIGNAL(pressed()), this, SLOT(loadConstantListFromFile()));
    connect(addNewWidgetBtn, SIGNAL(pressed()), this, SLOT(addNewWidget()));
    connect(clearAllContentBtn, SIGNAL(pressed()),this, SLOT(clear()));
}

void ConstantBoxList::addNewWidget()
{
    ConstantBox *newBox = new ConstantBox();
    connect(newBox, SIGNAL(elementRemoved(ConstantBox*)), this, SLOT(removeWidget(ConstantBox*)));
    connect(newBox, SIGNAL(elementRemoved(ConstantBox*)), this, SLOT(update()));
    connect(newBox, SIGNAL(elementChanged()), this, SLOT(update()));
    // Adjust size of list's body to accommodate new item
    listBody->resize(listBody->width(), listBody->height()+newBox->height()+listLayout->spacing());
    listLayout->addWidget(newBox);
    listOfWidgets.append(newBox);
}

void ConstantBoxList::clear()
{
    if(listOfWidgets.length() > 0)
    {
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, tr("Operation confirmation"),
                                              tr("Do you really want to clear list of constant boxes?"),
                                              QMessageBox::Yes | QMessageBox::No);
        msgBox->buttons()[0]->setText("Да");
        msgBox->buttons()[1]->setText("Нет");
        int result = msgBox->exec();
        if(result==QMessageBox::Yes)
        {
            for(ConstantBox *item:listOfWidgets)
            {
                removeWidget(item);
            }
            emit(constantsUpdated());
        }
    }

}

int ConstantBoxList::getLength() const
{
    return listOfWidgets.length();
}

void ConstantBoxList::saveConstantListToFile()
{

    QString pathToOutputFile = QFileDialog::getSaveFileName(this, tr("Saving constants to file"), "constants.izumc","Izum constants (*.izumc)");
    QFile outputFile(pathToOutputFile);
    outputFile.open(QIODevice::WriteOnly);
    QDataStream outStream(&outputFile);

    outStream << listOfWidgets.length();
    for(auto *expression: listOfWidgets)
    {
        QString constantName = expression->getConstantName();
        QString constantValue = expression->getConstantValue();
        outStream << constantName << constantValue;
    }
    outputFile.close();
}

void ConstantBoxList::loadConstantListFromFile()
{
    QString pathToInputFile = QFileDialog::getOpenFileName(this, tr("Loading constants from file"),"","Izum constants *.izumc");
    if(!pathToInputFile.isEmpty())
    {
        QFile inputFile(pathToInputFile);
        inputFile.open(QIODevice::ReadOnly);
        QDataStream in(&inputFile);
        // Clears previos list content
        clear();
        int length;
        in >> length;
        for(int i{0}; i < length; i++)
        {
            addNewWidget();
            ConstantBox *newConstantBox = listOfWidgets.last();
            QString constantName, constantValue;
            in>>constantName >> constantValue;
            qDebug() << constantName << constantValue;
            newConstantBox->constantBox->setText(constantName);
            newConstantBox->valueBox->setText(constantValue);
        }
        inputFile.close();
    }
    emit(constantsUpdated());
}

void ConstantBoxList::removeWidget(ConstantBox *box)
{
    qDebug() << "\nУдаляем коробку ввода константы";
    listOfWidgets.takeAt(listOfWidgets.indexOf(box));
    qDebug() << "Удалили из контейнера";
    QLayoutItem *item =  listLayout->takeAt(listLayout->indexOf(box));
    qDebug() << "Удалили из списка";
    delete item->widget();
    delete item;
    qDebug() << "Освободили память";
    listBody->adjustSize();
    qDebug() << "Подгоняем размер списка";
    emit(constantsUpdated());
    qDebug() << "Отправляем сигнал";
}

QSize ConstantBoxList::sizeHint() const
{
    return QSize(m_width+10, m_height+10);
}

void ConstantBoxList::update()
{
    emit(constantsUpdated());
}
