#include "CCore.h"
#include "CWidget.h"
#include <QApplication>
#include <QLocalSocket>

#ifndef CAPPLICATION
#define CAPPLICATION

/* ------------------ CApplication ------------------ */

class CApplication : public QApplication
{
    Q_OBJECT

public:

    CApplication(int &argc,char **argv):QApplication(argc,argv){

        // Configure screen
        setAttribute(Qt::AA_UseHighDpiPixmaps);
        setAttribute(Qt::AA_UseOpenGLES);

        // Connected to Crystals
        connect(socket,SIGNAL(connected()),this,SLOT(connected()));

        // Message from Crystals
        connect(socket,SIGNAL(readyRead()),this,SLOT(messageIn()));

        // Connects to Crystals
        socket->connectToServer("com.cuarzo.crystals");

        // Wait until connect to Crystals
        socket->waitForReadyRead();
    }

    QLocalSocket *socket = new QLocalSocket(this); // Unix socket

public slots:

    void connected()
    {
        // Register App in Crystals
        RegisterAppStruct message;
        message.pid = QApplication::applicationPid();

        // Copy message to a char pointer
        char data[sizeof(RegisterAppStruct)];
        memcpy(data,&message,sizeof(RegisterAppStruct));

        // Send message
        socket->write(data,sizeof(RegisterAppStruct));

        qDebug() << "Connected to Crystals";
    }

    // Message from Crystals
    void messageIn()
    {
        // Store message
        QByteArray message = socket->readAll();

        // Message type
        unsigned int type = *(unsigned int*)message.mid(0,sizeof(unsigned int)).data();

        switch (type)
        {
        case REGISTERED_APP:{
            qDebug() << "Connected to Crystals";
        }break;
        case REGISTERED_SURFACE:{

            // Parse Message
            RegisteredSurfaceStruct *reply = (RegisteredSurfaceStruct*)message.data();

            // Search the registered widget
            Q_FOREACH(QWidget *wid,allWidgets())
            {
                if(wid->winId() == reply->id)
                {
                    CWidget *widget = qobject_cast<CWidget*>(wid);

                    // Send Surface Configuration
                    SurfaceConfigStruct conf;
                    conf.id = wid->winId();
                    conf.x = wid->pos().x();
                    conf.y = wid->pos().y();
                    conf.role = widget->mode();
                    strcpy(conf.title,widget->windowTitle().toUtf8());

                    // Copy message to a char pointer
                    char data[sizeof(SurfaceConfigStruct)];
                    memcpy(data,&conf,sizeof(SurfaceConfigStruct));

                    // Send message
                    socket->write(data,sizeof(SurfaceConfigStruct));

                    // Connects widget's events
                    connect(widget,SIGNAL(positionChanged(QPoint)),this,SLOT(sendPosition(QPoint)));
                    connect(widget,SIGNAL(titleChanged(QString)),this,SLOT(titleChanged(QString)));
                    connect(widget,SIGNAL(modeChanged(uint)),this,SLOT(modeChanged(uint)));
                    connect(widget,SIGNAL(blurStateChanged(bool)),this,SLOT(blurStateChanged(bool)));
                    connect(widget,SIGNAL(opacityChanged(uint)),this,SLOT(opacityChanged(uint)));


                    return;
                }

            }
        }break;

        }


    }

    // Widget events
    void sendPosition(const QPoint &pos)
    {
        CWidget *widget = qobject_cast<CWidget*>(sender());

        // Send surface pos to Crystals
        SurfacePosStruct message;
        message.id = widget->winId();
        message.x = pos.x();
        message.y = pos.y();

        // Copy message to a char pointer
        char data[sizeof(SurfacePosStruct)];
        memcpy(data,&message,sizeof(SurfacePosStruct));

        // Send message
        socket->write(data,sizeof(SurfacePosStruct));
    }

    void titleChanged(QString title)
    {
        CWidget *widget = qobject_cast<CWidget*>(sender());

        // Send surface title to Crystals
        SurfaceTitleStruct message;
        message.id = widget->winId();
        strcpy(message.title,title.toUtf8());

        // Copy message to a char pointer
        char data[sizeof(SurfaceTitleStruct)];
        memcpy(data,&message,sizeof(SurfaceTitleStruct));

        // Send message
        socket->write(data,sizeof(SurfaceTitleStruct));
    }

    void modeChanged(uint mode)
    {
        CWidget *widget = qobject_cast<CWidget*>(sender());

        // Send surface title to Crystals
        SurfaceRoleStruct message;
        message.id = widget->winId();
        message.role = mode;

        // Copy message to a char pointer
        char data[sizeof(SurfaceRoleStruct)];
        memcpy(data,&message,sizeof(SurfaceRoleStruct));

        // Send message
        socket->write(data,sizeof(SurfaceRoleStruct));
    }

    void opacityChanged(uint opacity)
    {
        CWidget *widget = qobject_cast<CWidget*>(sender());

        // Send surface title to Crystals
        SurfaceOpacityStruct message;
        message.id = widget->winId();
        message.opacity = opacity;

        // Copy message to a char pointer
        char data[sizeof(SurfaceOpacityStruct)];
        memcpy(data,&message,sizeof(SurfaceOpacityStruct));

        // Send message
        socket->write(data,sizeof(SurfaceOpacityStruct));
    }

    void blurStateChanged(bool mode)
    {
        CWidget *widget = qobject_cast<CWidget*>(sender());

        // Send surface title to Crystals
        SurfaceBlurStruct message;
        message.id = widget->winId();
        message.activate = mode;

        // Copy message to a char pointer
        char data[sizeof(SurfaceBlurStruct)];
        memcpy(data,&message,sizeof(SurfaceBlurStruct));

        // Send message
        socket->write(data,sizeof(SurfaceBlurStruct));
    }

signals:
    void run();

};

#endif


