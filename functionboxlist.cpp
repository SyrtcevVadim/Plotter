#include "functionboxlist.h"
#include<QtWidgets>

FunctionBoxList::FunctionBoxList(int height, QWidget *parent): QWidget(parent)
{
    m_height = height+50;
    m_width = 370;
    listBody = new QWidget();
    listBody->setFixedWidth(m_width-20);

    listLayout = new QVBoxLayout();
    listBody->setLayout(listLayout);

    scrollArea = new QScrollArea(parent);
    scrollArea->setFixedSize(m_width, height);
    scrollArea->setWidget(listBody);


    addNewWidgetBtn = new QPushButton();
    addNewWidgetBtn->setToolTip("Добавить новый блок ввода функции");
    saveToFileBtn = new QPushButton();
    saveToFileBtn->setToolTip("Сохранить список функций в файл");
    loadFromFileBtn = new QPushButton();
    loadFromFileBtn->setToolTip("Загрузить список функций из файла");
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
    mainLayout->addLayout(btnLayout, 1);
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

FunctionBox* FunctionBoxList::addNewWidget()
{
    FunctionBox *newBox = new FunctionBox();
    connect(newBox, SIGNAL(elementRemoved(FunctionBox*)), this, SLOT(RemoveWidget(FunctionBox*)));
    listBody->resize(listBody->width(), listBody->height()+newBox->height()+20);
    listLayout->addWidget(newBox);
    listOfWidgets.append(newBox);
    return newBox;
}

void FunctionBoxList::clear()
{
    QList<FunctionBox*> temp(listOfWidgets);
    for(FunctionBox *item: temp)
    {
        listOfWidgets.takeAt(listOfWidgets.indexOf(item));
        listLayout->takeAt(listLayout->indexOf(item));
        listBody->adjustSize();
        delete item;
    }
}

void FunctionBoxList::Clear()
{
    // TODO добавить предупреждение
    if(listOfWidgets.length() > 0)
    {
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Подтверждение очищения списка функций",
                                              "Вы точно хотите удалить все функции из списка?",
                                              QMessageBox::Yes | QMessageBox::No);

        msgBox->buttons()[0]->setText("Да");
        msgBox->buttons()[1]->setText("Нет");

        int result = msgBox->exec();
        if(result==QMessageBox::Yes)
        {
            clear();
        }
    }
}


int FunctionBoxList::getListOfWidgetsLength() const
{
    return listOfWidgets.length();
}

void FunctionBoxList::SaveFunctionListToFile()
{
    QString pathToOutputFile = QFileDialog::getSaveFileName(this, "Сохранить функции в файл", "functions.izumf","Izum functions (*.izumf)");
    QFile outputFile(pathToOutputFile);
    outputFile.open(QIODevice::WriteOnly);
    QDataStream outStream(&outputFile);

    outStream << listOfWidgets.length();
    for(auto *expression: listOfWidgets)
    {
        outStream << *expression->GetMathExpression();
    }
    outputFile.close();
}

void FunctionBoxList::LoadFunctionListFromFile()
{
    QString pathToInputFile = QFileDialog::getOpenFileName(this, "Загрузить функции из файла","","*.izumf");
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
            FunctionBox *currBox = addNewWidget();
            MathExpression *currExp = currBox->GetMathExpression();
            in >> *currExp;
            currBox->functionBody->setText(currExp->GetInitialExpression());
            currBox->aParamBox->setValue(currExp->GetParameterValue("a"));
            currBox->bParamBox->setValue(currExp->GetParameterValue("b"));
            currBox->cParamBox->setValue(currExp->GetParameterValue("c"));
            currBox->dParamBox->setValue(currExp->GetParameterValue("d"));

            currBox->minimumVarValueBox->setText(QString().setNum(currExp->GetMinimumVarValue()));
            currBox->maximumVarValueBox->setText(QString().setNum(currExp->GetMaximumVarValue()));
        }
        inputFile.close();
    }
}

void FunctionBoxList::AddNewWidgetToFunctionList()
{
    addNewWidget();
}

void FunctionBoxList::RemoveWidget(FunctionBox *box)
{
    listOfWidgets.takeAt(listOfWidgets.indexOf(box));
    delete listLayout->takeAt(listLayout->indexOf(box));
    delete box;
    listBody->adjustSize();
}

QSize FunctionBoxList::sizeHint() const
{
    return QSize(m_width, m_height);
}
