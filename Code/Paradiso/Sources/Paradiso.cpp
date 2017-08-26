#include "Paradiso.h"

Paradiso::Paradiso()
{
    // Configure Paradiso
    setMode(PARADISO_MODE);
    setFixedSize(QApplication::primaryScreen()->size().width(), 28);
    setPalette(Qt::transparent);

    // Event when connects to Crystals
    connect(crystalsSocket,SIGNAL(connected()),this,SLOT(connectedToCrystals()));

    // Event when Crystals message arrive
    connect(crystalsSocket,SIGNAL(readyRead()),this,SLOT(messageFromCrystals()));

    // Connects to Crystals Core
    crystalsSocket->connectToServer("com.cuarzo.crystals");

    // Wait until connect to Crystals
    crystalsSocket->waitForReadyRead();

    // Display Top Bar
    show();
}

void Paradiso::connectedToCrystals()
{
    // Creates register the message
    RegisterAppStruct msg;

    // Asign the app process id
    msg.pid = QApplication::applicationPid();

    // Asign the app type
    msg.appType = PARADISO_TYPE;

    // Copy message to a char pointer
    char data[sizeof(RegisterAppStruct)];
    memcpy(data,&msg,sizeof(RegisterAppStruct));

    // Sends the message
    crystalsSocket->write(data,sizeof(RegisterAppStruct));
}

void Paradiso::messageFromCrystals()
{
        // Store the message
        QByteArray message = crystalsSocket->readAll();

        // Message type
        unsigned int type = *(unsigned int*)message.mid(0,sizeof(unsigned int)).data();

        switch (type)
        {
            case REGISTERED_SURFACE:{

                // Parse Message
                RegisteredSurfaceStruct *reply = (RegisteredSurfaceStruct*)message.data();

                CWindow *widget = nullptr;

                // Gets the widget
                if(reply->id == winId() )
                {
                    qDebug() << "HELLO PARADISO";
                    widget = this;
                }

                // Send Surface Configuration
                SurfaceConfigStruct conf;
                conf.id = widget ->winId();
                conf.x = widget->pos().x();
                conf.y = widget->pos().y();
                conf.role = widget->mode();
                strcpy(conf.title,widget->windowTitle().toUtf8());

                // Copy message to a char pointer
                char data[sizeof(SurfaceConfigStruct)];
                memcpy(data,&conf,sizeof(SurfaceConfigStruct));

                // Send message
                crystalsSocket->write(data,sizeof(SurfaceConfigStruct));



            }break;
        }
}

