#include <QApplication>
#include <QDir>
#include "init.h"
#include "CApplication.h"

#include <QFontDatabase>

QString blue = "#2687FB";
QString red = "#FF1D25";
QString green = "#7AC943";
QString orange = "#FF931E";
QString lightGray = "#CCC";

QString path = QDir::homePath() + "/Music";

#define SYSTEM_PATH QString("/home/e/Escritorio/CuarzoOS/CuarzoOS")

int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    qputenv("QT_SCALE_FACTOR", "1");

    CApplication a(argc, argv);
    QFontDatabase::addApplicationFont(SYSTEM_PATH + "/System/Library/Fonts/Coves/Coves Light.otf");

    a.setQuitOnLastWindowClosed(true);
    Init run;
    return a.exec();
}
