QT       += core gui network widgets

INCLUDEPATH += $$PWD/Headers
INCLUDEPATH += /home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/include
LIBS += -L/home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/lib -lCFramework

HEADERS += \
    Headers/crystalsgui.h \
    Headers/headers.h \
    Headers/titlebar.h

SOURCES += \
    Sources/crystalsgui.cpp \
    Sources/main.cpp \
    Sources/titlebar.cpp

