#include "GUI/mainwindow.h"
#include "GUI/aboutprogdialog.h"
#include<QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    functionBoxList = new FunctionBoxList(500);
    constantBoxList = new ConstantBoxList(500);
    paintingArea = new PaintingArea(QSize(600,600));


    topLevelMenu = new QMenuBar(this);
    topLevelMenu->addSeparator();
    // Defining menu items
    fileMenu = new QMenu(tr("&File"));
    settingsMenu = new QMenu(tr("&Settings"));
    helpMenu = new QMenu(tr("&Help"));
    topLevelMenu->addMenu(fileMenu);
    topLevelMenu->addMenu(settingsMenu);
    topLevelMenu->addMenu(helpMenu);

    topLevelMenu->showNormal();


    helpMenu->addAction(tr("&Introduction"));
    helpMenu->addSeparator();
    helpMenu->addAction(tr("&About program"), this, SLOT(showAboutProgramInfo()));

    settingsMenu->addAction(tr("&Make picture"), paintingArea, SLOT(makePicture()));

    fileMenu->addAction(tr("Load functions"), functionBoxList, SLOT(loadFunctionListFromFile()));
    fileMenu->addAction(tr("Save functions"), functionBoxList, SLOT(saveFunctionListToFile()));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Load constants"), constantBoxList, SLOT(loadConstantListFromFile()));
    fileMenu->addAction(tr("Save constants"), constantBoxList, SLOT(saveConstantListToFile()));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("&Exit"), this, SLOT(close()), Qt::CTRL + Qt::Key_Q);

    // Sets layout
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(5,50,5,5);
    mainLayout->addWidget(constantBoxList, 1, Qt::AlignTop);
    mainLayout->addWidget(functionBoxList, 1, Qt::AlignTop);

    // Stores widgets for adjusting settings of painting area
    QHBoxLayout *settingsLayout = new QHBoxLayout();
    settingsLayout->setAlignment(Qt::AlignLeft);

    QVBoxLayout *paintingAreaLayout= new QVBoxLayout();
    paintingAreaLayout->setAlignment(Qt::AlignTop);
    paintingAreaLayout->addLayout(settingsLayout);
    paintingAreaLayout->addWidget(paintingArea);

    mainLayout->addLayout(paintingAreaLayout, 1);

    setLayout(mainLayout);

    connect(constantBoxList, SIGNAL(constantsUpdated()), functionBoxList, SLOT(update()));
    connect(functionBoxList, SIGNAL(newFunctionAdded(MathExpression*)), paintingArea, SLOT(addFunction(MathExpression*)));
    connect(functionBoxList, SIGNAL(expressionDeleted(int)), paintingArea, SLOT(removeGraph(int)));
    connect(functionBoxList, SIGNAL(graphColorChanged(int, QColor)), paintingArea, SLOT(changeGraphColor(int, QColor)));
    connect(functionBoxList, SIGNAL(expressionChanged(int)), paintingArea, SLOT(recalculateGraph(int)));
    connect(functionBoxList, SIGNAL(graphCleared(int)), paintingArea, SLOT(clearGraph(int)));
    connect(functionBoxList, SIGNAL(drawGraph(int)), paintingArea, SLOT(drawGraph(int)));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // If user have worked with several function before closing the application
    if(functionBoxList->getLength() > 0)
    {
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, tr("Save data before exit"),
                                              tr("Do you want to save list of functions before exit?"),
                                              QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        int userAnswer = msgBox->exec();
        delete msgBox;

        if(userAnswer == QMessageBox::Yes)
        {
            // Open the QFileDialog to store info to output file
            functionBoxList->saveFunctionListToFile();
        }
        else if(userAnswer==QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
}

void MainWindow::showAboutProgramInfo()
{
    AboutProgDialog *aboutProg = new AboutProgDialog();
    aboutProg->exec();
}
