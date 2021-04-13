#include "mainwindow.h"
#include<QtWidgets>
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    functionBoxList = new FunctionBoxList(500);
    constantBoxList = new ConstantBoxList(500);
    plotter = new Plotter(new QSize(600,600));


    topLevelMenu = new QMenuBar(this);
    topLevelMenu->addSeparator();
    // Defining menu items
    fileMenu = new QMenu("&Файл");
    settingsMenu = new QMenu("&Настройки");
    helpMenu = new QMenu("&Справка");
    topLevelMenu->addMenu(fileMenu);
    topLevelMenu->addMenu(helpMenu);
    topLevelMenu->addMenu(settingsMenu);
    topLevelMenu->showNormal();


    helpMenu->addAction("&Знакомство");
    helpMenu->addSeparator();
    helpMenu->addAction("&О программе Изюм");


    fileMenu->addAction("&Загрузить список функций", functionBoxList, SLOT(LoadFunctionListFromFile()), Qt::CTRL+Qt::Key_L);
    fileMenu->addAction("&Сохранить список функций", functionBoxList, SLOT(SaveFunctionListToFile()), Qt::CTRL+Qt::Key_S);
    fileMenu->addSeparator();
    fileMenu->addAction("&Выйти", this, SLOT(close()), Qt::CTRL + Qt::Key_Q);

    // Sets layout

    QHBoxLayout *itemLayout = new QHBoxLayout();
    itemLayout->setContentsMargins(5,50,5,5);
    itemLayout->addWidget(functionBoxList, 1, Qt::AlignTop);
    itemLayout->addWidget(constantBoxList, 1, Qt::AlignTop);
    itemLayout->addWidget(plotter,1, Qt::AlignTop);

    setLayout(itemLayout);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // If user have worked with several function before closing the application
    if(functionBoxList->getListOfWidgetsLength() > 0)
    {
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Подтверждение сохранения данных перед выходом",
                                              "Вы хотите сохранить список функций в файл перед выходом из программы?",
                                              QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        msgBox->buttons()[0]->setText("Отмена");
        msgBox->buttons()[1]->setText("Да");
        msgBox->buttons()[2]->setText("Нет");
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

void MainWindow::ShowAboutProgramMenu()
{
    QMessageBox *aboutProgramBox = new QMessageBox(QMessageBox::Information,"О программе Изюм",
                                                   "Программ");
}
