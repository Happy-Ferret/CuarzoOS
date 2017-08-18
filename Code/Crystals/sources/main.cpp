#include "headers.h"
#include "compositor.h"
#include "launchman.h"

int main(int argc, char *argv[])
{
    // Non Widgets Application
    QGuiApplication app(argc, argv);

    // Creates the Compositor
    Compositor *compositor = new Compositor();

    // Creates the LaunchMan ( Application launcher )
    LaunchMan man;

    // Launch Crystals Gui
    man.launchZpp(SYSTEM_PATH + "/System/Applications/CrystalsGui.zpp");

    // Launch a Demo App
    man.launchZpp(SYSTEM_PATH + "/Applications/DemoApp.zpp");

    // Execute Application
    return app.exec();
}
