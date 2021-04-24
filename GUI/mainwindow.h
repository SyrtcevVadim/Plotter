#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"GUI/paintingarea.h"
#include"GUI/functionboxlist.h"
#include"GUI/constantboxlist.h"
#include<QtWidgets>

///
/// \brief The MainWindow class
/// Class of main window of Izum program.
/// Consist of every necessary object for creating functions' graphs
///
class MainWindow : public QWidget
{
    Q_OBJECT
private:
    /// Top level menu
    QMenuBar *topLevelMenu;
    /// Menu with file functionality
    QMenu *fileMenu;
    /// Menu with manual functionality
    QMenu *helpMenu;
    /// Menu with adjusting settings functionality
    QMenu *settingsMenu;

    /// Painting area
    PaintingArea *paintingArea;
    /// List of FunctionBox widgets
    FunctionBoxList *functionBoxList;
    /// List of ConstantBox widgets
    ConstantBoxList *constantBoxList;

protected:
    void closeEvent(QCloseEvent *event);

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    /// Invokes dialog window with information about this program
    void showAboutProgramInfo();

};

#endif // MAINWINDOW_H
