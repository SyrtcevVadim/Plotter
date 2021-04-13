#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"plotter.h"
#include"functionboxlist.h"
#include"constantboxlist.h"
#include<QtWidgets>

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    // Menu items
    QMenuBar *topLevelMenu;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *settingsMenu;

    Plotter *plotter;
    FunctionBoxList *functionBoxList;
    ConstantBoxList *constantBoxList;


protected:
    void closeEvent(QCloseEvent *event);

public:
    explicit MainWindow(QWidget *parent = nullptr);
public slots:
    void ShowAboutProgramMenu();

};

#endif // MAINWINDOW_H
