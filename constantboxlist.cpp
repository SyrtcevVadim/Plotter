#include "constantboxlist.h"
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
    connect(saveToFileBtn, SIGNAL(pressed()), this, SLOT(SaveFunctionListToFile()));
    connect(loadFromFileBtn, SIGNAL(pressed()), this, SLOT(LoadFunctionListFromFile()));
    connect(addNewWidgetBtn, SIGNAL(pressed()), this, SLOT(AddNewWidgetToFunctionList()));
    connect(clearAllContentBtn, SIGNAL(pressed()),this, SLOT(Clear()));
}

ConstantBox* ConstantBoxList::addNewWidget()
{
    ConstantBox *newBox = new ConstantBox();
    connect(newBox, SIGNAL(elementRemoved(ConstantBox*)), this, SLOT(RemoveWidget(ConstantBox*)));
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
        listOfWidgets.takeAt(listOfWidgets.indexOf(item));
        listLayout->takeAt(listLayout->indexOf(item));
        listBody->adjustSize();
        delete item;
    }
}

void ConstantBoxList::Clear()
{
    if(listOfWidgets.length() > 0)
    {
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Подтверждение очищения списка констант",
                                              "Вы точно хотите удалить все константы из списка?",
                                              QMessageBox::Yes | QMessageBox::No);
        int result = msgBox->exec();
        if(result==QMessageBox::Yes)
        {
            clear();
        }
    }
}


int ConstantBoxList::getListOfWidgetsLength() const
{
    return listOfWidgets.length();
}

void ConstantBoxList::SaveFunctionListToFile()
{
    QString pathToOutputFile = QFileDialog::getSaveFileName(this, "Сохранить константы в файл", "constants.izum","Izum files (*.izum *.dat)");
    QFile outputFile(pathToOutputFile);
    outputFile.open(QIODevice::WriteOnly);
    QDataStream outStream(&outputFile);

    outStream << listOfWidgets.length();
    for(auto *expression: listOfWidgets)
    {
        // TODO
    }
    outputFile.close();
}

void ConstantBoxList::LoadFunctionListFromFile()
{
    QString pathToInputFile = QFileDialog::getOpenFileName(this, "Загрузить функции из файла","","*.izum *.dat");
    if(!pathToInputFile.isEmpty())
    {
        QFile inputFile(pathToInputFile);
        inputFile.open(QIODevice::ReadOnly);
        QDataStream in(&inputFile);
        // Clears previos list content
        Clear();
        int length;
        in >> length;
        for(int i{0}; i < length; i++)
        {
            // TODO
        }
        inputFile.close();
    }
}

void ConstantBoxList::AddNewWidgetToFunctionList()
{
    addNewWidget();
}

void ConstantBoxList::RemoveWidget(ConstantBox *box)
{
    listOfWidgets.takeAt(listOfWidgets.indexOf(box));
    delete listLayout->takeAt(listLayout->indexOf(box));
    delete box;
    listBody->adjustSize();
}

QSize ConstantBoxList::sizeHint() const
{
    return QSize(m_width, m_height);
}
