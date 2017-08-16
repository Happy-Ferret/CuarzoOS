#include "headers.h"
#include "crystalsgui.h"

int main(int argc, char *argv[])
{
    // Creates application
    QApplication a(argc, argv);

    // Creates the interface manager
    CrystalsGui *gui = new CrystalsGui();

    CWidget *w = new CWidget();
    w->resize(200,200);
    w->show();

    // Executes the application
    return a.exec();
}
