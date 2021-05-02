#include "GUI/functionboxlist.h"
#include<QtWidgets>

FunctionBoxList::FunctionBoxList(int height, QWidget *parent): QWidget(parent)
{
    setToolTip(tr("List of functions"));
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
    addNewWidgetBtn->setToolTip(tr("Add new function block"));
    saveToFileBtn = new QPushButton();
    saveToFileBtn->setToolTip(tr("Save functions to file"));
    loadFromFileBtn = new QPushButton();
    loadFromFileBtn->setToolTip(tr("Load functions from file"));
    clearAllContentBtn = new QPushButton();
    clearAllContentBtn->setToolTip(tr("Clear list of function boxes"));

    // Sets images to buttons
    QPixmap addNewWidgetIcon(":/images/Images/AddWidgetImage.png");
    addNewWidgetBtn->setIcon(addNewWidgetIcon);
    QPixmap saveToFileIcon(":/images/Images/SaveImage.png");
    saveToFileBtn->setIcon(saveToFileIcon);
    QPixmap loadFromFileIcon(":/images/Images/LoadImage.png");
    loadFromFileBtn->setIcon(loadFromFileIcon);

    QLabel *functionListLbl = new QLabel(tr("List of functions"));
    // Setting appropriate layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(btnLayout, 1);
    btnLayout->addWidget(functionListLbl);
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
    connect(clearAllContentBtn, SIGNAL(pressed()),this, SLOT(clear()));

}

void FunctionBoxList::clear()
{
    if(listOfWidgets.length() > 0)
    {
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, tr("Operation confirmation"),
                                              tr("Do you really want to clear list of function boxes?"),
                                              QMessageBox::Yes | QMessageBox::No);


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

int FunctionBoxList::getLength() const
{
    return listOfWidgets.length();
}

void FunctionBoxList::saveFunctionListToFile()
{
    QString pathToOutputFile = QFileDialog::getSaveFileName(this, tr("Saving functions to file"), "functions.izumf","Izum functions (*.izumf)");
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
    QString pathToInputFile = QFileDialog::getOpenFileName(this, tr("Loading functions from file"),"","*.izumf");
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
            FunctionBox *newFunctionBox = listOfWidgets.last();
            MathExpression *currExp = newFunctionBox->getMathExpression();
            in >> *currExp;
            newFunctionBox->functionBody->setText(currExp->getInitialExpression());
            newFunctionBox->aParamBox->setValue(currExp->getParameterValue("a"));
            newFunctionBox->bParamBox->setValue(currExp->getParameterValue("b"));
            newFunctionBox->cParamBox->setValue(currExp->getParameterValue("c"));
            newFunctionBox->dParamBox->setValue(currExp->getParameterValue("d"));
            newFunctionBox->minimumVarValueBox->setValue(currExp->getMinimumVarValue());
            newFunctionBox->maximumVarValueBox->setValue(currExp->getMaximumVarValue());
        }
        inputFile.close();
    }
}

void FunctionBoxList::addNewWidget()
{
    FunctionBox *newBox = new FunctionBox();
    connect(newBox, SIGNAL(elementRemoved(FunctionBox*)), this, SLOT(removeWidget(FunctionBox*)));
    connect(newBox, SIGNAL(functionChanged(int)), this, SLOT(onExpressionChanged(int)));
    connect(newBox, SIGNAL(graphColorChanged(int, QColor)), this,SLOT(repaintGraph(int, QColor)));
    connect(newBox, SIGNAL(graphCleared(int)), this, SLOT(clearGraph(int)));
    listBody->resize(listBody->width(), listBody->height()+newBox->height()+listLayout->spacing());

    // Adds new FunctionBox object to widget list
    listLayout->addWidget(newBox);
    listOfWidgets.append(newBox);
    emit(newFunctionAdded(newBox->getMathExpression()));
}

void FunctionBoxList::removeWidget(FunctionBox *box)
{
    qDebug() << "Отправляем сигнал об удалении";
    emit(expressionDeleted(box->getMathExpression()->getId()));
    qDebug() << "Удаляем блок из контейнера";
    listOfWidgets.takeAt(listOfWidgets.indexOf(box));
    qDebug() << "Удаляем блок из списка виджетов";
    QLayoutItem *item = listLayout->takeAt(listLayout->indexOf(box));
    qDebug() << "Очищаем память блока";
    delete item->widget();
    delete item;
    qDebug() << "Подгоняем размеры";
    listBody->adjustSize();
    qDebug() << "Подогнали";
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
        emit(expressionChanged(box->getMathExpression()->getId()));
    }
}

void FunctionBoxList::onExpressionChanged(int id)
{
    emit(expressionChanged(id));
}

void FunctionBoxList::repaintGraph(int id, QColor color)
{
    emit(graphColorChanged(id, color));
}

void FunctionBoxList::clearGraph(int id)
{
    emit(graphCleared(id));
}
