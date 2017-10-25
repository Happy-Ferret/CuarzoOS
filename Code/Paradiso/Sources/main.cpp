#include "Paradiso.h"
#include "Headers.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Configure screen
    a.setAttribute(Qt::AA_EnableHighDpiScaling);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setAttribute(Qt::AA_UseOpenGLES);

    QFontDatabase::addApplicationFont(SYSTEM_PATH + "/System/Library/Fonts/Coves/Coves Light.otf");
    Paradiso *w = new Paradiso();
    return a.exec();
}
