#include "Paradiso.h"
#include "Headers.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(SYSTEM_PATH + "/System/Library/Fonts/Coves/Coves Light.otf");
    Paradiso *w = new Paradiso();
    return a.exec();
}
