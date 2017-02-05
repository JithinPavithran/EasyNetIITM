#-------------------------------------------------
#
# Project created by QtCreator 2017-01-25T22:59:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyNetIITM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\

HEADERS  += mainwindow.h\
# following python files should be added here?
        UsrValidation.py\
        NetApprove.py

FORMS    += mainwindow.ui

LIBS += -lpython2.7

DISTFILES += \
    Readme
