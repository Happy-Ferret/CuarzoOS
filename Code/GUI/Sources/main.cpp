#include "headers.h"
#include "crystalsgui.h"

int main(int argc, char *argv[])
{
    // Creates application
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(SYSTEM_PATH + "/System/Library/Fonts/Coves/Coves Light.otf");

    // Creates the interface manager
    CrystalsGui *gui = new CrystalsGui();

    // Executes the application
    return a.exec();
}
