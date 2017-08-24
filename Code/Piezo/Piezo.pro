QT += core widgets multimedia svg network concurrent

TARGET = Piezo
TEMPLATE = app
ICON = $$PWD/Resources/Icons/icon.icns

INCLUDEPATH += $$PWD/Headers
INCLUDEPATH += $$PWD/Libraries/TagLib.zlib/include/
INCLUDEPATH += $$PWD/Libraries/VLC-Qt.zlib/include/

INCLUDEPATH += /home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/include
LIBS += -L/home/e/Escritorio/CuarzoOS/CuarzoOS/System/Library/Frameworks/CFramework/lib -lCFramework

LIBS += -L$$OUT_PWD../Libraries/VLC-Qt.zlib/lib/ -lVLCQtCore


LIBS += -L$$PWD/Libraries/VLC-Qt.zlib/lib/ -lVLCQtCore
LIBS += -L$$PWD/Libraries/TagLib.zlib/lib/ -ltag
LIBS += -L/usr/lib/
LIBS += -L/usr/local/
LIBS += -lz


HEADERS += \
    Headers/album.h \
    Headers/albumsong.h \
    Headers/artistlistitem.h \
    Headers/artistview.h \
    Headers/artistviewtitle.h \
    Headers/bottombar.h \
    Headers/croplabel.h \
    Headers/filemanager.h \
    Headers/googledrive.h \
    Headers/icon.h \
    Headers/init.h \
    Headers/leftbar.h \
    Headers/leftbaritem.h \
    Headers/library.h \
    Headers/login.h \
    Headers/maths.h \
    Headers/menu.h \
    Headers/middleview.h \
    Headers/network.h \
    Headers/opbutton.h \
    Headers/pie.h \
    Headers/pix.h \
    Headers/player.h \
    Headers/playerbuttons.h \
    Headers/playerwindow.h \
    Headers/rectpix.h \
    Headers/reply.h \
    Headers/searchbar.h \
    Headers/selectlist.h \
    Headers/selectlistitem.h \
    Headers/songinfo.h \
    Headers/songmenu.h \
    Headers/storagebar.h \
    Headers/tableview.h \
    Headers/tageditor.h \
    Headers/timebar.h \
    Headers/titlebar.h \
    Headers/topbar.h \
    Headers/userpicture.h \
    Headers/volumebar.h \


SOURCES += \
    Sources/albumsong.cpp \
    Sources/artistlistitem.cpp \
    Sources/bottombar.cpp \
    Sources/googledrive.cpp \
    Sources/leftbar.cpp \
    Sources/leftbaritem.cpp \
    Sources/library.cpp \
    Sources/login.cpp \
    Sources/main.cpp \
    Sources/menu.cpp \
    Sources/player.cpp \
    Sources/playerbuttons.cpp \
    Sources/playerwindow.cpp \
    Sources/searchbar.cpp \
    Sources/timebar.cpp \
    Sources/titlebar.cpp \
    Sources/volumebar.cpp \

RESOURCES += \
    resources.qrc





