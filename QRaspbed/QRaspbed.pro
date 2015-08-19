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
    Bed.cpp

HEADERS  += \
    SerialPort.hpp \
    Raspbed.hpp \
    Bed.hpp

FORMS    += \
    raspbed.ui
