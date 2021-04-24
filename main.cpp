#include<QtWidgets>
#include"GUI/paintingarea.h"
#include"GUI/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(":/translations/Translations/Language_ru.qm");
    a.installTranslator(&translator);
    QWidget parent;
    parent.resize(800,800);
    PaintingArea *area = new PaintingArea(QSize(600,600), &parent);
    area->move(30,30);
    parent.show();
    //MainWindow window;
    //window.show();
    return a.exec();
}
