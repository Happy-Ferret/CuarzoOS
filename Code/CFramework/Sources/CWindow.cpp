#include "CWindow.h"
#include <QDebug>

CWindow::CWindow( WindowRole role )
{
    // Wrongly used to identify a surface
    QWidget::setWindowTitle("{\"id\":" + QString::number(winId()) + ",\"pid\":" + QString::number(QApplication::applicationPid()) + "}" );

    // Set window role
    setWindowRole(role);

    // Prevent app crash
    move(200,200);

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

    closeButton->installEventFilter( this );
    minimizeButton->installEventFilter( this );
    expandButton->installEventFilter( this );

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

    // Setup Window Layout
    verticalLayout->addWidget(topBar,0,Qt::AlignTop);
    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(0);

    // Events
    topBar->installEventFilter(this);
    refreshtemsPositions();

    // Connect to the compositor
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

}

// Assign and send position to Crystals
void CWindow::move(const QPoint &pos)
{
    QPoint p = pos;

    if ( p.y() < 0)
        p.setY(0);

    sendPosition(p);
    QWidget::move(p);
}
void CWindow::move(int x, int y)
{
    QPoint p = QPoint(x,y);

    if ( p.y() < 0)
        p.setY(0);

    sendPosition(p);
    QWidget::move(p);
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
void CWindow::setWindowRole(WindowRole role)
{
    localRole = role;

    if (role != WindowRole::Frame)
        topBar->hide();
    windowRoleChanged(role);
}

// Gets surface mode
WindowRole CWindow::windowRole()
{
    return localRole;
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

    if ( event->type() == QEvent::MouseButtonRelease)
    {
        if( watched == closeButton )
        {
            close();
            return false;
        }
        else if( watched == minimizeButton )
        {
            minimize();
            return false;
        }
        else if( watched == expandButton )
        {
            maximize(CurrentWorkspace,!localMaximized);
            return false;
        }

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


void CWindow::close()
{
    if( beforeClose() )
        QWidget::close();
}

void CWindow::minimize(bool state)
{
    if( !socket->open() ) return;

    // Send surface title to Crystals
    SurfaceMinimizeStruct message;
    message.minimize = state;

    // Copy message to a char pointer
    uint msgSize =  sizeof(SurfaceMinimizeStruct);
    char data[msgSize];
    memcpy(data,&message,msgSize);

    // Send message
    socket->write(data,msgSize);
}

void CWindow::maximize(MaximizeMode mode, bool state)
{
    if( !socket->open() ) return;
    if( state == localMaximized ) return;

    localMaximized = state;

    if( QApplication::primaryScreen()->size().width() > QWidget::maximumWidth() )
    {
        maximizedSize.setWidth( QWidget::maximumWidth() );
        maximizedPos.setX( (QApplication::primaryScreen()->size().width() - QWidget::maximumWidth()) / 2 );
    }
    else
        maximizedSize.setWidth( QApplication::primaryScreen()->size().width() );

    if( QApplication::primaryScreen()->size().height() > QWidget::maximumHeight() )
        maximizedSize.setHeight( QWidget::maximumHeight() );
    else
        maximizedSize.setHeight( QApplication::primaryScreen()->size().height() );

    maximizedPos.setY(0);

    if( localMaximized )
    {
        unmaximizedPos = pos();
        unmaximizedSize = size();

         if( unmaximizedPos.x() < maximizedPos.x() )
             dxMaxim = qFabs( unmaximizedPos.x() - maximizedPos.x()) / maximizeSteps;

         if( unmaximizedPos.x() > maximizedPos.x() )
             dxMaxim = -qFabs( unmaximizedPos.x() - maximizedPos.x()) / maximizeSteps;

         if( unmaximizedPos.y() < maximizedPos.y() )
             dyMaxim = qFabs( unmaximizedPos.y() - maximizedPos.y()) / maximizeSteps;

         if( unmaximizedPos.y() > maximizedPos.y() )
             dyMaxim = -qFabs( unmaximizedPos.y() - maximizedPos.y()) / maximizeSteps;

         if( unmaximizedSize.width() < maximizedSize.width() )
             dwMaxim = qFabs( unmaximizedSize.width() - maximizedSize.width()) / maximizeSteps;

         if( unmaximizedSize.width() > maximizedSize.width() )
             dwMaxim = -qFabs( unmaximizedSize.width() - maximizedSize.width()) / maximizeSteps;

         if( unmaximizedSize.height() < maximizedSize.height() )
             dhMaxim = qFabs( unmaximizedSize.height() - maximizedSize.height()) / maximizeSteps;

         if( unmaximizedSize.height() > maximizedSize.height() )
             dhMaxim = -qFabs( unmaximizedSize.height() - maximizedSize.height()) / maximizeSteps;
    }
    else
    {
        if( unmaximizedPos.x() < maximizedPos.x() )
            dxMaxim = -qFabs( unmaximizedPos.x() - maximizedPos.x()) / maximizeSteps;

        if( unmaximizedPos.x() > maximizedPos.x() )
            dxMaxim = qFabs( unmaximizedPos.x() - maximizedPos.x()) / maximizeSteps;

        if( unmaximizedPos.y() < maximizedPos.y() )
            dyMaxim = -qFabs( unmaximizedPos.y() - maximizedPos.y()) / maximizeSteps;

        if( unmaximizedPos.y() > maximizedPos.y() )
            dyMaxim = qFabs( unmaximizedPos.y() - maximizedPos.y()) / maximizeSteps;

        if( unmaximizedSize.width() < maximizedSize.width() )
            dwMaxim = -qFabs( unmaximizedSize.width() - maximizedSize.width()) / maximizeSteps;

        if( unmaximizedSize.width() > maximizedSize.width() )
            dwMaxim = qFabs( unmaximizedSize.width() - maximizedSize.width()) / maximizeSteps;

        if( unmaximizedSize.height() < maximizedSize.height() )
            dhMaxim = -qFabs( unmaximizedSize.height() - maximizedSize.height()) / maximizeSteps;

        if( unmaximizedSize.height() > maximizedSize.height() )
            dhMaxim = qFabs( unmaximizedSize.height() - maximizedSize.height()) / maximizeSteps;
    }

    qDebug() << "X:" << dxMaxim << "Y:" << dyMaxim;

    currentMaximizeStep = 0;
    connect(animationTimer,SIGNAL(timeout()), this, SLOT(maximizeAnimation()));
    animationTimer->start(0);

    // Send surface title to Crystals
    SurfaceExpandStruct message;
    message.expand = state;
    message.expandMode = mode;

    // Copy message to a char pointer
    uint msgSize =  sizeof(SurfaceExpandStruct);
    char data[msgSize];
    memcpy(data,&message,msgSize);

    // Send message
    socket->write(data,msgSize);
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
    message.role = windowRole();
    message.appType = ApplicationType::Client;
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

void CWindow::maximizeAnimation()
{
    if( currentMaximizeStep < maximizeSteps )
    {
        resize( size().width() + dwMaxim, size().height() + dhMaxim );
        move( pos().x() + dxMaxim, pos().y() + dyMaxim);
        currentMaximizeStep++;
        animationTimer->start(18);
    }
    else
    {
        if( localMaximized )
        {
            resize(maximizedSize);
            move(maximizedPos);
        }
        else
        {
            resize(unmaximizedSize);
            move(unmaximizedPos);
        }
        disconnect(animationTimer,SIGNAL(timeout()),this,SLOT(maximizeAnimation()));
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


void CWindow::windowRoleChanged(WindowRole role)
{

    if( !socket->open() ) return;

    // Send surface title to Crystals
    SurfaceRoleStruct message;
    message.role = role;

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
