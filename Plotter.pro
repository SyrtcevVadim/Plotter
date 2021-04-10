QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    constantbox.cpp \
    functionbox.cpp \
    main.cpp \
    mathcalculator.cpp \
    mathchecker.cpp \
    mathexpression.cpp \
    mathformconverter.cpp \
    mathhelper.cpp \
    mathparser.cpp \
    plotter.cpp \
    widgetlist.cpp

HEADERS += \
    constantbox.h \
    functionbox.h \
    mathcalculator.h \
    mathchecker.h \
    mathexpression.h \
    mathformconverter.h \
    mathhelper.h \
    mathparser.h \
    plotter.h \
    widgetlist.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
