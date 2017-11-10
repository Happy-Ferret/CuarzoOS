QT       += core gui widgets network
CONFIG += warn_off alerts_off
TARGET = CFramework
TEMPLATE = lib

DEFINES += CFRAMEWORK_LIBRARY
INCLUDEPATH += $$PWD/Headers

unix
{
    headers.files = $$PWD/Headers/*
    target.path = /home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/lib
    headers.path = /home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/include
    INSTALLS += target
    INSTALLS += headers
}

HEADERS += \
    Headers/CCore.h \
    Headers/CLabel.h \
    Headers/CWindow.h \
    Headers/CPushButton.h \
    Headers/CImage.h \
    Headers/CIconButton.h \
    Headers/CMaterialIcon.h \
    Headers/CBlurWidget.h \
    Headers/CIcon.h \
    Headers/CTopBar.h \
    Headers/CMenu.h \
    Headers/CMenuItem.h

SOURCES += \
    Sources/CWindow.cpp \
    Sources/CLabel.cpp \
    Sources/CPushButton.cpp \
    Sources/CImage.cpp \
    Sources/CIconButton.cpp \
    Sources/CBlurWidget.cpp \
    Sources/CIcon.cpp \
    Sources/CTopBar.cpp \
    Sources/CMenu.cpp \
    Sources/CMenuItem.cpp
