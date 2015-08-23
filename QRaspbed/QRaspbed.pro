#-------------------------------------------------
#
# Project created by QtCreator 2015-08-18T16:24:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRaspbed
TEMPLATE = app


SOURCES += main.cpp\
    SerialPort.cpp \
    Raspbed.cpp \
    Bed.cpp \
    Settings.cpp

HEADERS  += \
    SerialPort.hpp \
    Raspbed.hpp \
    Bed.hpp \
    Settings.hpp

FORMS    += \
    raspbed.ui \
    settings.ui

CONFIG += c++11

LIBS += \
       -lboost_system\

DISTFILES += uncrustify.cfg
