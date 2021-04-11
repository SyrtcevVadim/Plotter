#include "functionboxlist.h"
#include<QtWidgets>

FunctionBoxList::FunctionBoxList(int height, QWidget *parent): QWidget(parent)
{
    listBody = new QWidget();
    listBody->setFixedWidth(330);

    listLayout = new QVBoxLayout();
    listBody->setLayout(listLayout);

    scrollArea = new QScrollArea(parent);
    scrollArea->setFixedSize(350, height);
    scrollArea->setWidget(listBody);


    addNewWidgetBtn = new QPushButton();
    saveToFileBtn = new QPushButton();
    loadFromFileBtn = new QPushButton();
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

    // necessary command after every insertion of widget
    listBody->adjustSize();

    // Setting appropriate layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(btnLayout);
    btnLayout->addWidget(addNewWidgetBtn);
    btnLayout->addWidget(saveToFileBtn);
    btnLayout->addWidget(loadFromFileBtn);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);
    // Linking signals with slots

    connect(saveToFileBtn, SIGNAL(pressed()), this, SLOT(OnSaveToFileBtnClick()));
    connect(loadFromFileBtn, SIGNAL(pressed()), this, SLOT(OnLoadFromFileBtnClick()));
    connect(addNewWidgetBtn, SIGNAL(pressed()), this, SLOT(OnAddNewWidgetBtnClick()));
}

void FunctionBoxList::move(int x, int y)
{
    scrollArea->move(x,y);
}

FunctionBox* FunctionBoxList::addNewWidget()
{
    FunctionBox *newBox = new FunctionBox();
    connect(newBox, SIGNAL(elementRemoved(FunctionBox*)), this, SLOT(OnRemoveBtnClick(FunctionBox*)));
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
    }
    listOfWidgets.clear();
    listBody->adjustSize();
}

void FunctionBoxList::OnSaveToFileBtnClick()
{
    QString pathToOutputFile = QFileDialog::getSaveFileName(this, "Save data to output file");
    QFile outputFile(pathToOutputFile);
    outputFile.open(QIODevice::WriteOnly);
    QDataStream outStream(&outputFile);

    outStream << listOfWidgets.length();
    for(auto *expression: listOfWidgets)
    {
        outStream << *expression->GetMathExpression();
        qDebug() << *expression->GetMathExpression();
    }
    outputFile.close();
}

void FunctionBoxList::OnLoadFromFileBtnClick()
{
    QString pathToInputFile = QFileDialog::getOpenFileName(this, "Load stored data");
    QFile inputFile(pathToInputFile);
    inputFile.open(QIODevice::ReadOnly);
    QDataStream in(&inputFile);
    // Clears previos list content
    clear();
    int length;
    in >> length;
    for(int i{0}; i < length; i++)
    {
        FunctionBox *currBox = addNewWidget();
        MathExpression *currExp = currBox->GetMathExpression();
        qDebug() << *currExp;
        in >> *currExp;
        currBox->functionBody->setText(currExp->GetInitialExpression());
        currBox->aParamBox->setText(currExp->GetParameterValue("a"));
        currBox->bParamBox->setText(currExp->GetParameterValue("b"));
        currBox->cParamBox->setText(currExp->GetParameterValue("c"));
        currBox->dParamBox->setText(currExp->GetParameterValue("d"));

        currBox->minimumVarValueBox->setText(QString().setNum(currExp->GetMinimumVarValue()));
        currBox->maximumVarValueBox->setText(QString().setNum(currExp->GetMaximumVarValue()));
    }
    qDebug() << "Loading is finished";
    inputFile.close();
}

void FunctionBoxList::OnAddNewWidgetBtnClick()
{
    addNewWidget();
}

void FunctionBoxList::OnRemoveBtnClick(FunctionBox *box)
{
    listOfWidgets.takeAt(listOfWidgets.indexOf(box));
    delete listLayout->takeAt(listLayout->indexOf(box));
    delete box;
    listBody->adjustSize();
}
