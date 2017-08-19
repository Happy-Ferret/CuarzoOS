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

    // Wait until connect to Crystals
    socket->waitForReadyRead();

}

TitleBar *CrystalsGui::findTitlebarByIdAndPid(uint id, uint pid)
{
    Q_FOREACH(TitleBar *titleBar, titleBars)
    {
        if(titleBar->surfaceID == id && titleBar->processID == pid)
            return titleBar;
    }
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
    // Reads the message
    QByteArray data = socket->readAll();

    // Detects the message type
    unsigned int type = *(unsigned int*)data.mid(0,sizeof(unsigned int)).data();

    // Switch for message types
    switch (type) {

        case TITLEBAR_REQUEST:{

            // Parse the message
            TitlebarRequestStruct *message = (TitlebarRequestStruct*)data.data();

            // Creates a new TitleBar
            TitleBar *titleBar = new TitleBar();
            titleBar->surfaceID = message->forId;
            titleBar->processID = message->forPid;
            titleBar->title->setText(message->title);
            titleBar->setFixedWidth(message->width);

            // Send the confirmation
            TitlebarCreatedStruct res;
            res.forId = message->forId;
            res.forPid = message->forPid;
            res.id = titleBar->winId();

            // Copy message to a char pointer
            char data[sizeof(TitlebarCreatedStruct)];
            memcpy(data,&res,sizeof(TitlebarCreatedStruct));

            // Sends the message
            socket->write(data,sizeof(TitlebarCreatedStruct));

        }break;
    }
}












