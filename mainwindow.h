#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"plotter.h"
#include"functionboxlist.h"
#include<QtWidgets>

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    // Menu items
    QMenuBar *topLevelMenu;
    QMenu *fileMenu;
    QMenu *helpMenu;

    // Plotter object
    Plotter *plotter;

    // FunctionBoxList object
    FunctionBoxList *functionBoxList;

public:
    explicit MainWindow(QWidget *parent = nullptr);


};

#endif // MAINWINDOW_H
