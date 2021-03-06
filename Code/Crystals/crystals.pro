QT += gui network core waylandcompositor

DISTFILES += \
    res/shaders/fshader.glsl \
    res/shaders/vshader.glsl

INCLUDEPATH += $$PWD/headers
INCLUDEPATH += /home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/include

HEADERS += \
    headers/background.h \
    headers/compositor.h \
    headers/headers.h \
    headers/server.h \
    headers/socket.h \
    headers/view.h \
    headers/window.h \
    headers/launchman.h

SOURCES += \
    sources/background.cpp \
    sources/compositor.cpp \
    sources/main.cpp \
    sources/socket.cpp \
    sources/view.cpp \
    sources/window.cpp

RESOURCES += \
    res/resources.qrc


