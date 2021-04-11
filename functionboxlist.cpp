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
    for(int i{0}; i < 5; i++)
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

void FunctionBoxList::addNewWidget()
{
    FunctionBox *newBox = new FunctionBox();
    connect(newBox, SIGNAL(elementRemoved(FunctionBox*)), this, SLOT(OnRemoveBtnClick(FunctionBox*)));
    listBody->resize(listBody->width(), listBody->height()+newBox->height()+20);
    listLayout->addWidget(newBox);
    listOfWidgets.append(newBox);

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
    qDebug() << "Info is stored into " << pathToOutputFile <<" file!";
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
    addNewWidget();
}

void FunctionBoxList::OnRemoveBtnClick(FunctionBox *box)
{
    qDebug() << "REMOVING EXISTING BOX!";
    listOfWidgets.takeAt(listOfWidgets.indexOf(box));
    delete listLayout->takeAt(listLayout->indexOf(box));
    delete box;
    listBody->adjustSize();
}
