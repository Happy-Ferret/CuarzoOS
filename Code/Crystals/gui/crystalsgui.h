#ifndef CRYSTALSGUI_H
#define CRYSTALSGUI_H

#include "headers.h"
#include "capplication.h"

class CrystalsGui : public QObject
{

    Q_OBJECT

public:

    // Setup
    CrystalsGui();

    // Unix Socket for IPC with Crystals
    QLocalSocket *socket = new QLocalSocket(this);

public slots:

    // Connected to Crystals
    void connected();

    // New message from Crystals
    void newMessage();
};

#endif // CRYSTALSGUI_H
