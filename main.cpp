#include<QtWidgets>
#include"GUI/paintingarea.h"
#include"GUI/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(":/translations/Translations/Language_ru.qm");
    a.installTranslator(&translator);
    MainWindow window;
    window.show();
    return a.exec();
}
