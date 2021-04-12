#include "mainwindow.h"
#include<QtWidgets>
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    QSize displaySize = QGuiApplication::screens()[0]->availableSize();
    qDebug() << displaySize;
    functionBoxList = new FunctionBoxList(500,this);
    functionBoxList->move(10, 50);
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
