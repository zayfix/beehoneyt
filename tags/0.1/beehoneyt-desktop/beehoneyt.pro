#-------------------------------------------------
#
# Project created by QtCreator 2020-02-06T11:00:30
#
#-------------------------------------------------

QT       += core gui widgets charts mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = beehoneyt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    ihm.cpp \
    communication.cpp \
    nouvelleruche.cpp \
    reglageruche.cpp \
    configuration.cpp

HEADERS += \
    ihm.h \
    communication.h \
    nouvelleruche.h \
    reglageruche.h \
    configuration.h \
    ruche.h

FORMS += \
    ihm.ui \
    nouvelleruche.ui \
    reglageruche.ui

RESOURCES += \
    ico.qrc

COPIES += configuration
configuration.files = configuration.ini
configuration.path = $$OUT_PWD/
configuration.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
