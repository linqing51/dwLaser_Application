#-------------------------------------------------
#
# Project created by QtCreator 2026-02-05T23:32:16
#
#-------------------------------------------------

QT       += core gui  serialport  serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled3
TEMPLATE = app
CONFIG += c++11 console  # libgpiod需要C++17

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
    gpiocontrol.cpp \
    gpiointerrupt.cpp \
    gpioqueryinput.cpp \
    i2cmaster.cpp \
        main.cpp \
        mainwindow.cpp \
    customcheckbox.cpp \
    customimagebutton.cpp \
    menu1.cpp \
    menu2.cpp \
    modbusuart4master.cpp \
    numberkeyboard.cpp \
    roundplot.cpp \
    menu3.cpp \
    arcslider.cpp \
    menu4.cpp \
    customslider.cpp \
    ThreeStateImageLabel.cpp \
    menu5.cpp \
    customdoublespinbox.cpp \
    numberkeyboard1.cpp \
    serialportmanager.cpp \
    shareddata.cpp \
    spimaster.cpp \
    spimodbusmaster.cpp

HEADERS += \
    gpiocontrol.h \
    gpiointerrupt.h \
    gpioqueryinput.h \
    i2cmaster.h \
        mainwindow.h \
    customcheckbox.h \
    customimagebutton.h \
    menu1.h \
    menu2.h \
    modbusuart4master.h \
    numberkeyboard.h \
    roundplot.h \
    menu3.h \
    arcslider.h \
    menu4.h \
    customslider.h \
    ThreeStateImageLabel.h \
    menu5.h \
    customdoublespinbox.h \
    numberkeyboard1.h \
    serialportmanager.h \
    shareddata.h \
    spimaster.h \
    spimodbusmaster.h

# 链接libgpiod库（核心）
LIBS += -lgpiod
LIBS += -lpigpio -lpthread

DEFINES += RASPBERRY_PI_CM5

FORMS += \
        mainwindow.ui \
    menu1.ui \
    menu2.ui \
    menu3.ui \
    menu4.ui \
    menu5.ui

RESOURCES += \
    images.qrc
