#include "headers.h"
#include "crystalsgui.h"

int main(int argc, char *argv[])
{
    // Creates application
    QApplication a(argc, argv);

    // Configure screen
    a.setAttribute(Qt::AA_EnableHighDpiScaling);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setAttribute(Qt::AA_UseOpenGLES);

    QFontDatabase::addApplicationFont(SYSTEM_PATH + "/System/Library/Fonts/Lucida/Regular.ttf");

    // Creates the interface manager
    CrystalsGui *gui = new CrystalsGui();

    // Executes the application
    return a.exec();
}
