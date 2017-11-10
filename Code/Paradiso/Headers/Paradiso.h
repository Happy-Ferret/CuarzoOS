#ifndef PARADISO_H
#define PARADISO_H

#include "Headers.h"
#include "PMenu.h"

class Paradiso : public CWindow
{
    Q_OBJECT

public:

    // Setup
    Paradiso();

    // IPC with Clients
    QLocalServer *clientsServer = new QLocalServer(this);

    // TopBar
    QWidget *topBar = new QWidget(this);

    // Main layout
    QHBoxLayout *layout = new QHBoxLayout(topBar);

    // Cuarzo Menu
    PMenu *cuarzoMenu = new PMenu(QPixmap(SYSTEM_PATH + "/System/Library/Icons/OS/Logo/64x64.png"));

    // Active menu
    PMenu *activeMenu = nullptr;

    // Demo text menus
    PMenu *textMenu = new PMenu("Crystals");
    PMenu *textMenuB = new PMenu("Hello my friends how are you");


public slots:

    // Event filter
    bool eventFilter(QObject *watched, QEvent *event);

    // Message from Crystals
    void messageFromCrystals();

};

#endif // PARADISO_H
