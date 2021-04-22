#include "GUI/mainwindow.h"
#include "GUI/aboutprogdialog.h"
#include<QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    functionBoxList = new FunctionBoxList(500);
    constantBoxList = new ConstantBoxList(500);
    plotter = new Plotter(new QSize(600,600));


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

    settingsMenu->addAction("&Change language");

    fileMenu->addAction(tr("Load functions"), functionBoxList, SLOT(loadFunctionListFromFile()));
    fileMenu->addAction(tr("Save functions"), functionBoxList, SLOT(saveFunctionListToFile()));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Load constants"), constantBoxList, SLOT(loadConstantListFromFile()));
    fileMenu->addAction(tr("Save constants"), constantBoxList, SLOT(saveConstantListToFile()));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("&Exit"), this, SLOT(close()), Qt::CTRL + Qt::Key_Q);

    // Sets layout

    QHBoxLayout *itemLayout = new QHBoxLayout();
    itemLayout->setContentsMargins(5,50,5,5);
    itemLayout->addWidget(functionBoxList, 1, Qt::AlignTop);
    itemLayout->addWidget(constantBoxList, 1, Qt::AlignTop);
    itemLayout->addWidget(plotter,1, Qt::AlignTop);

    setLayout(itemLayout);

    connect(constantBoxList, SIGNAL(constantsUpdated()), functionBoxList, SLOT(update()));
    connect(functionBoxList, SIGNAL(newFunctionAdded(MathExpression*)), plotter, SLOT(addFunction(MathExpression*)));
    connect(functionBoxList, SIGNAL(expressionDeleted(MathExpression*)), plotter, SLOT(removeFunction(MathExpression*)));
    connect(functionBoxList, SIGNAL(graphColorChanged(MathExpression*, QColor)), plotter, SLOT(changeGraphColor(MathExpression*, QColor)));
    connect(functionBoxList, SIGNAL(expressionChanged(MathExpression*)), plotter, SLOT(createTableValue(MathExpression*)));
    connect(functionBoxList, SIGNAL(graphCleared(MathExpression*)), plotter, SLOT(clearGraph(MathExpression*)));
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
