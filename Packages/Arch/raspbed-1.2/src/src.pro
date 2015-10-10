#-------------------------------------------------
#
# Project created by QtCreator 2015-08-18T16:24:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The application version
VERSION = 1.2

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

TARGET = raspbed
TEMPLATE = app


SOURCES += main.cpp\
    SerialPort.cpp \
    Raspbed.cpp \
    Bed.cpp \
    Settings.cpp \
    Data.cpp

HEADERS  += \
    SerialPort.hpp \
    Raspbed.hpp \
    Bed.hpp \
    Settings.hpp \
    Data.hpp

FORMS    += \
    raspbed.ui \
    settings.ui

CONFIG += c++11

LIBS += \
       -lboost_system

RESOURCES += \
    resources.qrc

# For deployed version
DEFINES += QT_NO_DEBUG_OUTPUT
