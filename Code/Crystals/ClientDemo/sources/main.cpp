#include "CApplication.h"
#include "window.h"
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    CApplication *app = new CApplication(argc, argv);
    QFontDatabase::addApplicationFont(SYSTEM_PATH + "/System/Library/Fonts/Coves/Coves Light.otf");
    Window *w = new Window();
    w->show();

    return app->exec();
}
