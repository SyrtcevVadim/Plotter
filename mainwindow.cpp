#include "mainwindow.h"
#include<QtWidgets>
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    resize(1500,700);
    topLevelMenu = new QMenuBar(this);

    // Defining menu items
    fileMenu = new QMenu("&Файл");
    helpMenu = new QMenu("&Help");

    topLevelMenu->addMenu(fileMenu);
    topLevelMenu->addMenu(helpMenu);


    //helpMenu->addAction("&User's guide", this, )


    fileMenu->addSeparator();
    fileMenu->addAction("&Выйти", this, SLOT(close()), Qt::CTRL + Qt::Key_Q);

    plotter = new Plotter(new QPoint(400,50), new QSize(700,700), this);
    functionBoxList = new FunctionBoxList(500,this);
    functionBoxList->move(10, 50);
}
