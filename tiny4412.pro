#-------------------------------------------------
#
# Project created by QtCreator 2017-08-17T04:18:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tiny4412
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    unitchange.cpp \
    configure.cpp \
    about.cpp \
    sensor.cpp \
    adjust.cpp \
    simpleadjust.cpp \
    login.cpp \
    qextserialbase.cpp \
    posix_qextserialport.cpp \
    serial.cpp \
    contoller.cpp \
    keyboard.cpp \
    machine.cpp \
    remoteeth.cpp \
    commandlist.cpp

HEADERS  += mainwindow.h \
    unitchange.h \
    configure.h \
    about.h \
    sensor.h \
    adjust.h \
    simpleadjust.h \
    login.h \
    qextserialbase.h \
    posix_qextserialport.h \
    serial.h \
    contoller.h \
    keyboard.h \
    machine.h \
    remoteeth.h \
    commandList.h

FORMS    += mainwindow.ui \
    unitchange.ui \
    configure.ui \
    about.ui \
    sensor.ui \
    adjust.ui \
    simpleadjust.ui \
    login.ui \
    serial.ui \
    contoller.ui \
    keyboard.ui \
    machine.ui \
    remoteeth.ui

RESOURCES += \
    image.qrc
