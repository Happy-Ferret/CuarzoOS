#include "crystalsgui.h"

// Setup

CrystalsGui::CrystalsGui()
{

    // Event when connects to Crystals
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));

    // Event when Crystals message arrive
    connect(socket,SIGNAL(readyRead()),this,SLOT(newMessage()));

    // Connects to Crystals Core
    socket->connectToServer("com.cuarzo.crystals");

}

// Connected to Crystals Core

void CrystalsGui::connected()
{

    // Creates register the message
    RegisterAppStruct msg;

    // Asign the app process id
    msg.pid = QApplication::applicationPid();

    // Asign the app type
    msg.appType = CRYSTALS_TYPE;

    // Copy message to a char pointer
    char data[sizeof(RegisterAppStruct)];
    memcpy(data,&msg,sizeof(RegisterAppStruct));

    // Sends the message
    socket->write(data,sizeof(RegisterAppStruct));

}

void CrystalsGui::newMessage()
{

}
