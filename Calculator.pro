#-------------------------------------------------
#
# Project created by QtCreator 2018-08-16T20:52:03
#
#-------------------------------------------------

QT       += core gui

RC_ICONS = logo.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app

INCLUDEPATH+=F:\eigen-eigen-b3f3d4950030\Eigen

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    singlematrix.cpp \
    doublematrix.cpp \
    common.cpp \
    vectorwin.cpp \
    linerequations.cpp

HEADERS += \
        mainwindow.h \
    singlematrix.h \
    doublematrix.h \
    common.h \
    vectorwin.h \
    linerequations.h

FORMS += \
        mainwindow.ui \
    singlematrix.ui \
    doublematrix.ui \
    vectorwin.ui \
    linerequations.ui
