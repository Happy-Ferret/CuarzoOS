#include "CApplication.h"
#include <QFontDatabase>

CApplication::CApplication(int &argc,char **argv):QApplication(argc,argv){

    // Creates the message protocol
    protocol = new CProtocol( this );

    // Turn off style alerts
    setDesktopSettingsAware(false);


    // Configure screen
    setAttribute(Qt::AA_EnableHighDpiScaling);
    setAttribute(Qt::AA_UseHighDpiPixmaps);
    setAttribute(Qt::AA_UseOpenGLES);

    QFontDatabase::addApplicationFont(SYSTEM_PATH + "/System/Library/Fonts/Roboto/Roboto-Regular.ttf");

}

