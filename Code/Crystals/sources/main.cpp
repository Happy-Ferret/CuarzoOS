#include "headers.h"
#include "compositor.h"

int main(int argc, char *argv[])
{
    // Non Widgets Application
    QGuiApplication app(argc, argv);

    // Creates the Compositor
    Compositor *compositor = new Compositor();

    // Launch Crystals Gui
    QProcess::startDetached(QGuiApplication::applicationDirPath() + "/GUI/./gui -platform wayland");

    // Launch a Demo App
    //QProcess::startDetached("DemoApp -platform wayland");

    // Execute Application
    return app.exec();
}
