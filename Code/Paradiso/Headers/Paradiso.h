#ifndef PARADISO_H
#define PARADISO_H

#include "Headers.h"
#include "Menu.h"

class Paradiso : public CWindow
{
    Q_OBJECT

public:

    // Setup
    Paradiso();

    // IPC with Crystals
    QLocalSocket *crystalsSocket = new QLocalSocket(this);

    // IPC with Clients
    QLocalServer *clientsServer = new QLocalServer(this);

    // TopBar
    QWidget *topBar = new QWidget(this);

    // Main layout
    QHBoxLayout *layout = new QHBoxLayout(topBar);

    // Cuarzo Menu
    Menu *cuarzoMenu = new Menu(QPixmap(SYSTEM_PATH + "/System/Library/Icons/OS/Logo/64x64.png"));

    // Active menu
    Menu *activeMenu = nullptr;

    // Demo text menus
    Menu *textMenu = new Menu("Crystals");
    Menu *textMenuB = new Menu("Hello my friends how are you");


public slots:

    // Event filter
    bool eventFilter(QObject *watched, QEvent *event);

    // Connected to Crystals
    void connectedToCrystals();

    // Message from Crystals
    void messageFromCrystals();

    // Message from Client
    //void messageFromClient();


};

#endif // PARADISO_H
