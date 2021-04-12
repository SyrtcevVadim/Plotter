#include<QtWidgets>
#include"plotter.h"
#include"functionbox.h"
#include"mainwindow.h"
#include"constantbox.h"
#include"functionboxlist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    window.showMaximized();
    return a.exec();
}
