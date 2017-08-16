QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/CFramework
INCLUDEPATH += $$PWD/headers

HEADERS += \
    CFramework/CApplication.h \
    CFramework/CCore.h \
    CFramework/CWidget.h \
    headers/window.h \
    CFramework/CLabel.h \
    CFramework/CPushButton.h

SOURCES += \
    sources/main.cpp \
    sources/window.cpp




