#ifndef CRYSTALSGUI_H
#define CRYSTALSGUI_H

#include "headers.h"
#include "CCore.h"
#include "titlebar.h"

class CrystalsGui : public QObject
{

    Q_OBJECT

public:
    CrystalsGui(); // Setup
    QLocalSocket *socket = new QLocalSocket(this); // Unix Socket for IPC with Crystals
    QList<TitleBar*>titleBars; // Stored title bars

    TitleBar *findTitlebarByIdAndPid(uint id, uint pid); // Returns the required TitleBar
public slots:

    // Connected to Crystals
    void connected();

    // New message from Crystals
    void newMessage();
};

#endif // CRYSTALSGUI_H
