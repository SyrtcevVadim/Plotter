#include "mainwindow.h"
#include<QtWidgets>
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    QSize displaySize = QGuiApplication::screens()[0]->availableSize();
    functionBoxList = new FunctionBoxList(500, this);
    functionBoxList->move(10, 50);

    constantBoxList = new ConstantBoxList(500, this);
    constantBoxList->move(400,50);
    plotter = new Plotter(new QPoint(displaySize.width()-910,50), new QSize(900,900), this);


    topLevelMenu = new QMenuBar(this);
    // Defining menu items
    fileMenu = new QMenu("&Файл");
    helpMenu = new QMenu("&Справка");
    topLevelMenu->addMenu(fileMenu);
    topLevelMenu->addMenu(helpMenu);


    helpMenu->addAction("&Знакомство");


    fileMenu->addAction("&Загрузить список функций", functionBoxList, SLOT(LoadFunctionListFromFile()), Qt::CTRL+Qt::Key_L);
    fileMenu->addAction("&Сохранить список функций", functionBoxList, SLOT(SaveFunctionListToFile()), Qt::CTRL+Qt::Key_S);
    fileMenu->addSeparator();
    fileMenu->addAction("&Выйти", this, SLOT(close()), Qt::CTRL + Qt::Key_Q);


}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // If user have worked with several function before closing the application
    if(functionBoxList->getListOfWidgetsLength() > 0)
    {
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Подтверждение сохранения данных перед выходом",
                                              "Вы хотите сохранить список функций в файл перед выходом из программы?",
                                              QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        int userAnswer = msgBox->exec();
        delete msgBox;

        if(userAnswer == QMessageBox::Yes)
        {
            // Open the QFileDialog to store info to output file
            functionBoxList->SaveFunctionListToFile();
        }
        else if(userAnswer==QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
}
