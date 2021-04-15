QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/aboutprogdialog.cpp \
    GUI/constantbox.cpp \
    GUI/constantboxlist.cpp \
    GUI/functionbox.cpp \
    GUI/functionboxlist.cpp \
    GUI/mainwindow.cpp \
    GUI/plotter.cpp \
    LibForPlotter/mathcalculator.cpp \
    LibForPlotter/mathchecker.cpp \
    LibForPlotter/mathexpression.cpp \
    LibForPlotter/mathformconverter.cpp \
    LibForPlotter/mathhelper.cpp \
    LibForPlotter/mathparser.cpp \
    LibForPlotter/valuetable.cpp \
    main.cpp \



HEADERS += \
    GUI/aboutprogdialog.h \
    GUI/constantbox.h \
    GUI/constantboxlist.h \
    GUI/functionbox.h \
    GUI/functionboxlist.h \
    GUI/mainwindow.h \
    GUI/plotter.h \
    LibForPlotter/mathcalculator.h \
    LibForPlotter/mathchecker.h \
    LibForPlotter/mathexpression.h \
    LibForPlotter/mathformconverter.h \
    LibForPlotter/mathhelper.h \
    LibForPlotter/mathparser.h \
    LibForPlotter/valuetable.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
