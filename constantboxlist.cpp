#include "constantboxlist.h"
#include"mathhelper.h"
#include<QtWidgets>

ConstantBoxList::ConstantBoxList(int height, QWidget *parent) : QWidget(parent)
{
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
    addNewWidgetBtn->setToolTip("Добавить новый блок ввода констант");
    saveToFileBtn = new QPushButton();
    saveToFileBtn->setToolTip("Сохранить список констант в файл");
    loadFromFileBtn = new QPushButton();
    loadFromFileBtn->setToolTip("Загрузить список констант из файла");
    clearAllContentBtn = new QPushButton();
    clearAllContentBtn->setToolTip("Очистить список функций");

    // Sets images to buttons
    QPixmap addNewWidgetIcon(":/images/Images/AddWidgetImage.png");
    addNewWidgetBtn->setIcon(addNewWidgetIcon);
    QPixmap saveToFileIcon(":/images/Images/SaveImage.png");
    saveToFileBtn->setIcon(saveToFileIcon);
    QPixmap loadFromFileIcon(":/images/Images/LoadImage.png");
    loadFromFileBtn->setIcon(loadFromFileIcon);

    // Test data
    for(int i{0}; i < 1; i++)
    {
        addNewWidget();
    }

    // Setting appropriate layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(btnLayout,1);
    btnLayout->addWidget(addNewWidgetBtn);
    btnLayout->addWidget(saveToFileBtn);
    btnLayout->addWidget(loadFromFileBtn);
    btnLayout->addWidget(clearAllContentBtn);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);

    // Linking signals with slots
    connect(saveToFileBtn, SIGNAL(pressed()), this, SLOT(saveConstantListToFile()));
    connect(loadFromFileBtn, SIGNAL(pressed()), this, SLOT(loadConstantListFromFile()));
    connect(addNewWidgetBtn, SIGNAL(pressed()), this, SLOT(addNewWidgetToFunctionList()));
    connect(clearAllContentBtn, SIGNAL(pressed()),this, SLOT(clearList()));
}

ConstantBox* ConstantBoxList::addNewWidget()
{
    ConstantBox *newBox = new ConstantBox();
    connect(newBox, SIGNAL(elementRemoved(ConstantBox*)), this, SLOT(removeWidget(ConstantBox*)));
    connect(newBox, SIGNAL(elementRemoved(ConstantBox*)), this, SLOT(update()));
    connect(newBox, SIGNAL(elementChanged()), this, SLOT(update()));
    listBody->resize(listBody->width(), listBody->height()+newBox->height()+20);
    listLayout->addWidget(newBox);
    listOfWidgets.append(newBox);
    return newBox;
}

void ConstantBoxList::clear()
{

    QList<ConstantBox*> temp(listOfWidgets);
    for(ConstantBox *item: temp)
    {
        // Deletes ConstantBox objects from layout and widgets list
        listOfWidgets.takeAt(listOfWidgets.indexOf(item));
        listLayout->takeAt(listLayout->indexOf(item));
        listBody->adjustSize();

        // Deletes constant from the list of correct constants
        MathHelper::RemoveConstant(item->GetConstantName());
        delete item;
    }
}

void ConstantBoxList::clearList()
{
    if(listOfWidgets.length() > 0)
    {
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Подтверждение очищения списка констант",
                                              "Вы точно хотите удалить все константы из списка?",
                                              QMessageBox::Yes | QMessageBox::No);
        msgBox->buttons()[0]->setText("Да");
        msgBox->buttons()[1]->setText("Нет");
        int result = msgBox->exec();
        if(result==QMessageBox::Yes)
        {
            clear();
            emit(constantsUpdated());
        }
    }

}

int ConstantBoxList::getListOfWidgetsLength() const
{
    return listOfWidgets.length();
}

void ConstantBoxList::saveConstantListToFile()
{

    QString pathToOutputFile = QFileDialog::getSaveFileName(this, "Сохранить константы в файл", "constants.izumc","Izum constants (*.izumc)");
    QFile outputFile(pathToOutputFile);
    outputFile.open(QIODevice::WriteOnly);
    QDataStream outStream(&outputFile);

    outStream << listOfWidgets.length();
    for(auto *expression: listOfWidgets)
    {
        QString constantName = expression->GetConstantName();
        QString constantValue = expression->GetConstantValue();
        outStream << constantName << constantValue;
    }
    outputFile.close();
}

void ConstantBoxList::loadConstantListFromFile()
{
    QString pathToInputFile = QFileDialog::getOpenFileName(this, "Загрузить функции из файла","","Izum constants *.izumc");
    if(!pathToInputFile.isEmpty())
    {
        QFile inputFile(pathToInputFile);
        inputFile.open(QIODevice::ReadOnly);
        QDataStream in(&inputFile);
        // Clears previos list content
        clearList();
        int length;
        in >> length;
        for(int i{0}; i < length; i++)
        {
            ConstantBox *newConstantBox = addNewWidget();
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

void ConstantBoxList::addNewWidgetToFunctionList()
{
    addNewWidget();
}

void ConstantBoxList::removeWidget(ConstantBox *box)
{
    listOfWidgets.takeAt(listOfWidgets.indexOf(box));
    delete listLayout->takeAt(listLayout->indexOf(box));
    delete box;
    listBody->adjustSize();
    emit(constantsUpdated());
}

QSize ConstantBoxList::sizeHint() const
{
    return QSize(m_width, m_height);
}

void ConstantBoxList::update()
{
    emit(constantsUpdated());
}
