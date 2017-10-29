#include "CApplication.h"
#include <QFontDatabase>
#include <QDebug>

CApplication::CApplication(int &argc,char **argv):QApplication(argc,argv){

    // Creates the message protocol
    protocol = new CProtocol( this );

    // Configure screen
    setAttribute(Qt::AA_EnableHighDpiScaling);
    setAttribute(Qt::AA_UseHighDpiPixmaps);

    QFontDatabase::addApplicationFont(SYSTEM_PATH + "/System/Library/Fonts/Roboto/Roboto-Regular.ttf");

}


