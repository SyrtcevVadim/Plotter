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
    FunctionBox *box1 = new FunctionBox();
    FunctionBox *box2 = new FunctionBox();
    FunctionBox *box3 = new FunctionBox();

    listLayout->addWidget(box1);
    listLayout->addWidget(box2);
    listLayout->addWidget(box3);

    listOfWidgets.append(box1);
    listOfWidgets.append(box2);
    listOfWidgets.append(box3);

    for(FunctionBox *item: listOfWidgets)
    {
        qDebug() << item->GetMathExpression();
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

void FunctionBoxList::OnSaveToFileBtnClick()
{
    QString pathToOutputFile = QFileDialog::getSaveFileName(this, "Save data to output file");
    qDebug() << pathToOutputFile;
    QFile outputFile(pathToOutputFile);
    outputFile.open(QIODevice::WriteOnly);
    QDataStream outStream(&outputFile);

    outStream << listOfWidgets.length();
    for(auto *expression: listOfWidgets)
    {
        outStream << expression->GetMathExpression();
    }
    qDebug() << "Info stored into " << pathToOutputFile <<" file!";
    outputFile.close();
}

void FunctionBoxList::OnLoadFromFileBtnClick()
{
    QString pathToInputFile = QFileDialog::getOpenFileName(this, "Load stored data");
    qDebug() << pathToInputFile;
    QFile inputFile(pathToInputFile);
    inputFile.open(QIODevice::ReadOnly);
    QDataStream in(&inputFile);
}

void FunctionBoxList::OnAddNewWidgetBtnClick()
{

}
