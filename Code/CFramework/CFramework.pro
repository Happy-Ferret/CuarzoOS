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
    Headers/CApplication.h \
    Headers/CCore.h \
    Headers/CLabel.h \
    Headers/CWindow.h \
    Headers/CPushButton.h \
    Headers/CImage.h \
    Headers/CProtocol.h \
    Headers/CIconButton.h \
    Headers/CMaterialIcon.h \
    Headers/CBlurWidget.h

SOURCES += \
    Sources/CApplication.cpp \
    Sources/CWindow.cpp \
    Sources/CLabel.cpp \
    Sources/CPushButton.cpp \
    Sources/CImage.cpp \
    Sources/CProtocol.cpp \
    Sources/CIconButton.cpp \
    Sources/CBlurWidget.cpp
