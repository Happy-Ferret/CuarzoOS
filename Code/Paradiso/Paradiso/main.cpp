#include "headers.h"
#include "topbar.h"

extern QString blue = "#006ADB";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_EnableHighDpiScaling);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);

    TopBar topBar;

    return a.exec();
}
