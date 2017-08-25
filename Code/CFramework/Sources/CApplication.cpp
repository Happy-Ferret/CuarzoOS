#include "CApplication.h"


CApplication::CApplication(int &argc,char **argv):QApplication(argc,argv){

    // Turn off style alerts
    setDesktopSettingsAware(false);


    // Configure screen
    setAttribute(Qt::AA_EnableHighDpiScaling);
    setAttribute(Qt::AA_UseHighDpiPixmaps);
    setAttribute(Qt::AA_UseOpenGLES);


}

