QT       += widgets network

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
    Headers/CWindow.h

SOURCES += \
    Sources/CApplication.cpp \
    Sources/CWindow.cpp \
    Sources/CLabel.cpp
