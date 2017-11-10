#-------------------------------------------------
#
# Project created by QtCreator 2017-08-24T16:16:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH+=$$PWD/Headers
INCLUDEPATH += /home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/include
LIBS += -L/home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/lib -lCFramework


TARGET = Paradiso
TEMPLATE = app

HEADERS += \
    Headers/Paradiso.h \
    Headers/Headers.h \
    Headers/PMenu.h

SOURCES += \
    Sources/main.cpp \
    Sources/Paradiso.cpp \
    Sources/PMenu.cpp
