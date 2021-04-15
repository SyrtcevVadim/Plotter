QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutprogdialog.cpp \
    constantbox.cpp \
    constantboxlist.cpp \
    functionbox.cpp \
    functionboxlist.cpp \
    main.cpp \
    mainwindow.cpp \
    mathcalculator.cpp \
    mathchecker.cpp \
    mathexpression.cpp \
    mathformconverter.cpp \
    mathhelper.cpp \
    mathparser.cpp \
    plotter.cpp

HEADERS += \
    aboutprogdialog.h \
    constantbox.h \
    constantboxlist.h \
    functionbox.h \
    functionboxlist.h \
    mainwindow.h \
    mathcalculator.h \
    mathchecker.h \
    mathexpression.h \
    mathformconverter.h \
    mathhelper.h \
    mathparser.h \
    plotter.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
