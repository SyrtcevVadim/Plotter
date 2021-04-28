#include<QtWidgets>
#include"GUI/paintingarea.h"
#include"GUI/scaler.h"
#include"GUI/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(":/translations/Translations/Language_ru.qm");
    a.installTranslator(&translator);
//    MainWindow window;
//    window.show();
    QWidget parent;
    Scaler *scaler = new Scaler(&parent);
    parent.show();
    return a.exec();
}
