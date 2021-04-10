QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../LibForPlotter/MathExpressionFunctionality/mathcalculator.cpp \
    ../LibForPlotter/MathExpressionFunctionality/mathchecker.cpp \
    ../LibForPlotter/MathExpressionFunctionality/mathexpression.cpp \
    ../LibForPlotter/MathExpressionFunctionality/mathformconverter.cpp \
    ../LibForPlotter/MathExpressionFunctionality/mathhelper.cpp \
    ../LibForPlotter/MathExpressionFunctionality/mathparser.cpp \
    constantbox.cpp \
    functionbox.cpp \
    functionboxlist.cpp \
    main.cpp \
    plotter.cpp

HEADERS += \
    ../LibForPlotter/MathExpressionFunctionality/mathcalculator.h \
    ../LibForPlotter/MathExpressionFunctionality/mathchecker.h \
    ../LibForPlotter/MathExpressionFunctionality/mathexpression.h \
    ../LibForPlotter/MathExpressionFunctionality/mathformconverter.h \
    ../LibForPlotter/MathExpressionFunctionality/mathhelper.h \
    ../LibForPlotter/MathExpressionFunctionality/mathparser.h \
    constantbox.h \
    functionbox.h \
    functionboxlist.h \
    plotter.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
