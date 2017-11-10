#include <QApplication>
#include "window.h"
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    qputenv("QT_SCALE_FACTOR", "1");
    QApplication *app = new QApplication(argc, argv);
    QFontDatabase::addApplicationFont(SYSTEM_PATH + "/System/Library/Fonts/Roboto/Roboto-Regular.ttf");
    Window *w = new Window();
    w->show();

    return app->exec();
}
