#include "GUI/functionboxlist.h"
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
    connect(saveToFileBtn, SIGNAL(pressed()), this, SLOT(saveFunctionListToFile()));
    connect(loadFromFileBtn, SIGNAL(pressed()), this, SLOT(loadFunctionListFromFile()));
    connect(addNewWidgetBtn, SIGNAL(pressed()), this, SLOT(addNewWidget()));
    connect(clearAllContentBtn, SIGNAL(pressed()),this, SLOT(clearList()));
}


void FunctionBoxList::clearList()
{
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
            for(FunctionBox *item: listOfWidgets)
            {
                removeWidget(item);
            }
        }
    }
}


int FunctionBoxList::getListOfWidgetsLength() const
{
    return listOfWidgets.length();
}

void FunctionBoxList::saveFunctionListToFile()
{
    QString pathToOutputFile = QFileDialog::getSaveFileName(this, "Сохранить функции в файл", "functions.izumf","Izum functions (*.izumf)");
    QFile outputFile(pathToOutputFile);
    outputFile.open(QIODevice::WriteOnly);
    QDataStream outStream(&outputFile);

    outStream << listOfWidgets.length();
    for(auto *expression: listOfWidgets)
    {
        outStream << *expression->getMathExpression();
    }
    outputFile.close();
}

void FunctionBoxList::loadFunctionListFromFile()
{
    QString pathToInputFile = QFileDialog::getOpenFileName(this, "Загрузить функции из файла","","*.izumf");
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
            addNewWidget();
            FunctionBox *newFunctionBox = listOfWidgets.last();
            MathExpression *currExp = newFunctionBox->getMathExpression();
            in >> *currExp;
            newFunctionBox->functionBody->setText(currExp->getInitialExpression());
            newFunctionBox->aParamBox->setValue(currExp->getParameterValue("a"));
            newFunctionBox->bParamBox->setValue(currExp->getParameterValue("b"));
            newFunctionBox->cParamBox->setValue(currExp->getParameterValue("c"));
            newFunctionBox->dParamBox->setValue(currExp->getParameterValue("d"));
            newFunctionBox->minimumVarValueBox->setText(QString().setNum(currExp->GetMinimumVarValue()));
            newFunctionBox->maximumVarValueBox->setText(QString().setNum(currExp->GetMaximumVarValue()));
        }
        inputFile.close();
    }
}

void FunctionBoxList::addNewWidget()
{
    FunctionBox *newBox = new FunctionBox();
    connect(newBox, SIGNAL(elementRemoved(FunctionBox*)), this, SLOT(removeWidget(FunctionBox*)));
    listBody->resize(listBody->width(), listBody->height()+newBox->height()+20);

    // Adds new FunctionBox object to widget list
    listLayout->addWidget(newBox);
    listOfWidgets.append(newBox);
}

void FunctionBoxList::removeWidget(FunctionBox *box)
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

void FunctionBoxList::update()
{
    for(auto *box: listOfWidgets)
    {
        // Updates math expression
        box->changeMathExpression("");
    }
}
