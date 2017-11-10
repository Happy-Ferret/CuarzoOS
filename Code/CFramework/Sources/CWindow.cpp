#include "CWindow.h"
#include <QDebug>

CWindow::CWindow(uint mode)
{
    // Wrongly used to identify a surface
    QWidget::setWindowTitle("{\"id\":" + QString::number(winId()) + ",\"pid\":" + QString::number(QApplication::applicationPid()) + "}" );

    // Set mode
    setMode(mode);

    // Prevent app crash
    move(winId(),winId());

    // Deletes blue Qt frame
    setWindowFlags(Qt::FramelessWindowHint);

    // Asigns parent
    QWidget::setParent(nullptr);

    // Transparent background
    setPalette( Qt::transparent );

    firstTopLayout = new QHBoxLayout(topBarItems);

    // Window icons
    QString path = SYSTEM_PATH + "/System/Library/Icons/Crystals/";

    // Create the Buttons
    closeButton = new CIconButton(
                QPixmap( path + "close_active.png"),
                QPixmap( path + "close_focus.png"),
                QPixmap( path + "close_unfocus.png"),
                QPixmap( path + "close_hover.png"),
                this
    );

    minimizeButton = new CIconButton(
                QPixmap( path + "minimize_active.png"),
                QPixmap( path + "minimize_focus.png"),
                QPixmap( path + "minimize_unfocus.png"),
                QPixmap( path + "minimize_hover.png"),
                this
    );

    expandButton = new CIconButton(
                QPixmap( path + "maximize_active.png"),
                QPixmap( path + "maximize_focus.png"),
                QPixmap( path + "maximize_unfocus.png"),
                QPixmap( path + "maximize_hover.png"),
                this
    );

    // Set buttons sizes
    int buttonSize = 16;
    closeButton->setFixedSize( buttonSize, buttonSize);
    minimizeButton->setFixedSize( buttonSize, buttonSize);
    expandButton->setFixedSize( buttonSize, buttonSize);

    // Add buttons to the layout
    horizontalLayout->setMargin(8);
    horizontalLayout->setSpacing(8);
    horizontalLayout->addWidget(closeButton);
    horizontalLayout->addWidget(minimizeButton);
    horizontalLayout->addWidget(expandButton);
    horizontalLayout->addWidget( topBarItems , 1);

    // Setup Title
    _title->setAlignment( Qt::AlignCenter );
    _title->enableEllipsis(true);
    _title->setFontColor( QColor(GRAY) );

    // Titlebar background
    topBar->setObjectName("QZTP");
    topBar->setAutoFillBackground(true);

    verticalLayout->addWidget(topBar,0,Qt::AlignTop);
    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(0);


    topBar->installEventFilter(this);
    refreshtemsPositions();

    connectToCrystals();

}

void CWindow::connectToCrystals()
{

    /* CRYSTALS PROTOCOL */

    // Connected to Crystals
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));

    // Message from Crystals
    connect(socket,SIGNAL(readyRead()),this,SLOT(newMessage()));

    // Connects to Crystals
    socket->connectToServer("com.cuarzo.crystals");

    qDebug() << "Connecting to Crystals...";
}

// Assign and send position to Crystals
void CWindow::move(const QPoint &pos)
{
    QWidget::move(pos);
    sendPosition(pos);
}
void CWindow::move(int x, int y)
{
    QWidget::move(x,y);
    sendPosition(QPoint(x,y));
}

// Sends title to Crystals
void CWindow::setWindowTitle(const QString &title)
{
    _title->setText(title);
}

// Gets local title
QString CWindow::windowTitle()
{
    return _title->text();
}

// Sends surface mode
void CWindow::setMode(unsigned int mode)
{
    localMode = mode;

    if (mode != WINDOW_MODE)
        topBar->hide();
    modeChanged(mode);
}

// Gets surface mode
uint CWindow::mode()
{
    return localMode;
}


void CWindow::refreshtemsPositions()
{
    _title->resize(topBar->width() - 300, topBar->height());
    _title->move( 150, 0 );
}

void CWindow::resizeEvent(QResizeEvent *)
{
    refreshtemsPositions();
}

bool CWindow::eventFilter(QObject *watched, QEvent *event)
{
    if ( event->type() == QEvent::MouseButtonPress && watched == topBar)
    {
        mouseGrab();
        return true;
    }

    if (event->type() == QEvent::WindowActivate)
    {
        closeButton->setWindowFocus( true );
        minimizeButton->setWindowFocus( true );
        expandButton->setWindowFocus( true );
        topBar->setStyleSheet("#QZTP{background:qlineargradient( x1:0 y1:0, x2:0 y2:1, stop:0 #FFF , stop:1 #e8eaf6);border-bottom:1px solid #CCC}");
        return true;
    }

    if (event->type() == QEvent::WindowDeactivate)
    {
        closeButton->setWindowFocus( false );
        minimizeButton->setWindowFocus( false );
        expandButton->setWindowFocus( false );
        topBar->setStyleSheet("#QZTP{background:#EEE;border-bottom:1px solid #CCC}");
        return true;
    }
        return false;
}



// Set surface Opacity
void CWindow::setWindowOpacity(float opacity)
{
    localOpacity = opacity;
    opacityChanged(opacity);
}

void CWindow::setCentralWidget(QWidget *widget)
{
    widget->setParent(this);
    verticalLayout->insertWidget( 1, widget, 1 );
}

// Gets surface opacity
uint CWindow::windowOpacity()
{
    return localOpacity;
}


/* CRYSTALS PROTOCOL */

void CWindow::connected()
{
    // Register App in Crystals
    SurfaceRegisterStruct message;
    message.id = winId();
    message.pid = QApplication::applicationPid();
    message.opacity = 255;
    message.role = mode();
    message.appType = CLIENT_TYPE;
    message.x = pos().x();
    message.y = pos().y();

    // Copy message to a char pointer
    char data[sizeof(SurfaceRegisterStruct)];
    memcpy(data,&message,sizeof(SurfaceRegisterStruct));

    // Send message
    socket->write(data,sizeof(SurfaceRegisterStruct));
}

// Message from Crystals
void CWindow::newMessage()
{
    // Store message
    QByteArray message = socket->readAll();

    // Message type
    unsigned int type = *(unsigned int*)message.mid(0,sizeof(unsigned int)).data();

    switch (type)
    {
    case SURFACE_SCALED:{

        // Parse Message
        SurfaceScaledStruct *req = (SurfaceScaledStruct*)message.data();

        // Apply the changes
        resize(req->width,req->height);

    }break;
    case SURFACE_MOVED:{

        // Parse Message
        SurfaceMovedStruct *req = (SurfaceMovedStruct*)message.data();

        // Apply the changes
        QWidget::move(req->x,req->y);

    }break;

    }

}


// Widget events
void CWindow::sendPosition(const QPoint &pos)
{
    if( !socket->open() ) return;

    // Send surface pos to Crystals
    SurfacePosStruct message;
    message.x = pos.x();
    message.y = pos.y();

    // Copy message to a char pointer
    char data[sizeof(SurfacePosStruct)];
    memcpy(data,&message,sizeof(SurfacePosStruct));

    // Send message
    socket->write(data,sizeof(SurfacePosStruct));
}


void CWindow::modeChanged(uint mode)
{

    if( !socket->open() ) return;

    // Send surface title to Crystals
    SurfaceRoleStruct message;
    message.role = mode;

    // Copy message to a char pointer
    char data[sizeof(SurfaceRoleStruct)];
    memcpy(data,&message,sizeof(SurfaceRoleStruct));

    // Send message
    socket->write(data,sizeof(SurfaceRoleStruct));
}

void CWindow::opacityChanged(float opacity)
{

    if( !socket->open() ) return;

    // Send surface title to Crystals
    SurfaceOpacityStruct message;
    message.opacity = opacity;

    // Copy message to a char pointer
    char data[sizeof(SurfaceOpacityStruct)];
    memcpy(data,&message,sizeof(SurfaceOpacityStruct));

    // Send message
    socket->write(data,sizeof(SurfaceOpacityStruct));
}

void CWindow::mouseGrab()
{
    if( !socket->open() ) return;

    // Send surface title to Crystals
    SurfaceGrabStruct message;

    // Copy message to a char pointer
    char data[sizeof(SurfaceGrabStruct)];
    memcpy(data,&message,sizeof(SurfaceGrabStruct));

    // Send message
    socket->write(data,sizeof(SurfaceGrabStruct));

}
/*
void C::blurLevel(float level)
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
*/
