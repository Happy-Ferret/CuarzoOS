QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/headers

INCLUDEPATH += /home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/include
LIBS += -L/home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/lib -lCFramework
HEADERS += \
    headers/window.h \


SOURCES += \
    sources/main.cpp \
    sources/window.cpp




