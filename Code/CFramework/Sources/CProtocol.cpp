#include "CProtocol.h"

CProtocol::CProtocol(QApplication *)
{
    // Connected to Crystals
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));

    // Message from Crystals
    connect(socket,SIGNAL(readyRead()),this,SLOT(messageIn()));

    // Connects to Crystals
    socket->connectToServer("com.cuarzo.crystals");

    // Wait until connect to Crystals
    socket->waitForReadyRead();

}

void CProtocol::connected()
{
    // Register App in Crystals
    RegisterAppStruct message;
    message.pid = QApplication::applicationPid();

    // Copy message to a char pointer
    char data[sizeof(RegisterAppStruct)];
    memcpy(data,&message,sizeof(RegisterAppStruct));

    // Send message
    socket->write(data,sizeof(RegisterAppStruct));

}

// Message from Crystals
void CProtocol::messageIn()
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

        // Gets the widget
        CWindow *widget = findCWindowById(reply->id);

        if ( widget == nullptr ) return;

        // Save the wiidget
        windows.insert( reply->id, widget );

        // Send Surface Configuration
        SurfaceConfigStruct conf;
        conf.id = widget ->winId();
        conf.x = widget->pos().x();
        conf.y = widget->pos().y();
        conf.role = widget->mode();

        // Copy message to a char pointer
        char data[sizeof(SurfaceConfigStruct)];
        memcpy(data,&conf,sizeof(SurfaceConfigStruct));

        // Send message
        socket->write(data,sizeof(SurfaceConfigStruct));

        // Connects widget's events
        connect(widget,SIGNAL(positionChanged(QPoint)),this,SLOT(sendPosition(QPoint)));
        connect(widget,SIGNAL(modeChanged(uint)),this,SLOT(modeChanged(uint)));
        //connect(widget,SIGNAL(blurStateChanged(bool)),this,SLOT(blurStateChanged(bool)));
        connect(widget,SIGNAL(opacityChanged(float)),this,SLOT(opacityChanged(float)));
        connect(widget,SIGNAL(mouseGrabEvent()), this,SLOT(mouseGrab()));


    }break;
    case SURFACE_SCALED:{

        // Parse Message
        SurfaceScaledStruct *req = (SurfaceScaledStruct*)message.data();

        if ( !windows.contains(req->id) ) return;

        // Gets the widget
        CWindow *widget = windows[req->id];

        // Apply the changes
        widget->resize(req->width,req->height);

    }break;
    case SURFACE_MOVED:{

        // Parse Message
        SurfaceMovedStruct *req = (SurfaceMovedStruct*)message.data();

        if ( !windows.contains(req->id) ) return;

        // Gets the widget
        CWindow *widget = windows[req->id];

        // Apply the changes
        widget->QWidget::move(req->x,req->y);

    }break;

    }

}

// Widget events
void CProtocol::sendPosition(const QPoint &pos)
{
    CWindow *widget = qobject_cast<CWindow*>(sender());

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


void CProtocol::modeChanged(uint mode)
{
    CWindow *widget = qobject_cast<CWindow*>(sender());

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

void CProtocol::opacityChanged(float opacity)
{
    CWindow *widget = qobject_cast<CWindow*>(sender());

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

void CProtocol::mouseGrab()
{
    CWindow *widget = qobject_cast<CWindow*>(sender());

    // Send surface title to Crystals
    SurfaceGrabStruct message;
    message.id = widget->winId();

    // Copy message to a char pointer
    char data[sizeof(SurfaceGrabStruct)];
    memcpy(data,&message,sizeof(SurfaceGrabStruct));

    // Send message
    socket->write(data,sizeof(SurfaceGrabStruct));

}

void CProtocol::blurLevel(float level)
{
    CBlurWidget *widget = qobject_cast<CBlurWidget*>(sender());

    // Send surface title to Crystals
    SurfaceBlurLevelStruct message;
    message.surfaceId = widget->window()->winId();
    message.blurId = widget->winId();
    message.level = level;

    // Copy message to a char pointer
    char data[sizeof( SurfaceBlurLevelStruct )];
    memcpy(data,&message,sizeof( SurfaceBlurLevelStruct ));

    // Send message
    socket->write(data,sizeof( SurfaceBlurLevelStruct ));
}

void CProtocol::blurTint(float tint)
{
    CBlurWidget *widget = qobject_cast<CBlurWidget*>(sender());

    // Send surface title to Crystals
    SurfaceBlurTintStruct message;
    message.surfaceId = widget->window()->winId();
    message.blurId = widget->winId();
    message.tint = tint;

    // Copy message to a char pointer
    char data[sizeof( SurfaceBlurTintStruct )];
    memcpy(data,&message,sizeof( SurfaceBlurTintStruct ));

    // Send message
    socket->write(data,sizeof( SurfaceBlurTintStruct ));
}

void CProtocol::blurRect()
{
    CBlurWidget *widget = qobject_cast<CBlurWidget*>(sender());

    QPoint pos = widget->mapTo( widget->window(), widget->pos());

    // Send surface title to Crystals
    SurfaceBlurRectStruct message;
    message.surfaceId = widget->window()->winId();
    message.blurId = widget->winId();
    message.x = pos.x();
    message.y = pos.y() - widget->window()->height() + widget->height();
    message.w = widget->width();
    message.h = widget->height();

    // Copy message to a char pointer
    char data[sizeof( SurfaceBlurRectStruct )];
    memcpy(data,&message,sizeof( SurfaceBlurRectStruct ));

    // Send message
    socket->write(data,sizeof( SurfaceBlurRectStruct ));
}

void CProtocol::blurRemove(bool mode)
{

    CBlurWidget *widget = qobject_cast<CBlurWidget*>(sender());

    if (mode)
    {

        QPoint pos = widget->mapTo(widget->window(), widget->pos());

        // Send surface title to Crystals
        SurfaceBlurCreateStruct message;
        message.blurId = widget->winId();
        message.surfaceId = widget->window()->winId();
        message.x = pos.x();
        message.y = pos.y() - widget->window()->height() + widget->height();
        message.w = widget->width();
        message.h = widget->height();
        message.tint = widget->blurTint();
        message.level = widget->blurLevel();


        // Copy message to a char pointer
        char data[sizeof(SurfaceBlurCreateStruct)];
        memcpy(data,&message,sizeof(SurfaceBlurCreateStruct));

        // Send message
        socket->write(data,sizeof(SurfaceBlurCreateStruct));
    }
    else{

        // Send surface title to Crystals
        SurfaceBlurRemoveStruct message;
        message.surfaceId = widget->window()->winId();
        message.blurId = widget->winId();

        // Copy message to a char pointer
        char data[sizeof( SurfaceBlurRemoveStruct )];
        memcpy(data,&message,sizeof( SurfaceBlurRemoveStruct ));

        // Send message
        socket->write(data,sizeof( SurfaceBlurRemoveStruct ));
    }
}

void CProtocol::connectBlurWidget(CBlurWidget *widget)
{

    QPoint pos = widget->mapTo(widget->window(), widget->pos());

    // Send surface title to Crystals
    SurfaceBlurCreateStruct message;
    message.blurId = widget->winId();
    message.surfaceId = widget->window()->winId();
    message.x = pos.x();
    message.y = pos.y() - widget->window()->height() + widget->height();
    message.w = widget->width();
    message.h = widget->height();
    message.tint = widget->blurTint();
    message.level = widget->blurLevel();


    // Copy message to a char pointer
    char data[sizeof(SurfaceBlurCreateStruct)];
    memcpy(data,&message,sizeof(SurfaceBlurCreateStruct));

    // Send message
    socket->write(data,sizeof(SurfaceBlurCreateStruct));

    connect( widget, SIGNAL( levelChanged( float ) ), this, SLOT( blurLevel( float ) ) );
    connect( widget, SIGNAL( tintChanged( float ) ), this, SLOT( blurTint( float ) ) );
    connect( widget, SIGNAL( geometryChanged() ), this, SLOT( blurRect() ) );
    connect( widget, SIGNAL( stateChanged(bool)), this, SLOT( blurRemove( bool ) ) );

}

// Search the registered widget
CWindow *CProtocol::findCWindowById(uint id)
{
    Q_FOREACH(QWidget *wid, QApplication::allWidgets())
    {
        if(wid->winId() == id)
           return qobject_cast<CWindow*>(wid);
    }

    return nullptr;
}
