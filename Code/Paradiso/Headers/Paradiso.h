#ifndef PARADISO_H
#define PARADISO_H

#include "Headers.h"

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

public slots:

    // Connected to Crystals
    void connectedToCrystals();

    // Message from Crystals
    void messageFromCrystals();

    // Message from Client
    //void messageFromClient();


};

#endif // PARADISO_H
