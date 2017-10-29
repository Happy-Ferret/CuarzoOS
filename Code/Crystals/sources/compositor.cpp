#include "../headers/compositor.h"

// Compositor setup

Compositor::Compositor():QWaylandCompositor()
{

    // Start compositor
    create();

    // Set the screen resolution
    setScreenResolution(QGuiApplication::primaryScreen()->size());

    // Event when wayland surface is created
    connect(this, &QWaylandCompositor::surfaceCreated, this, &Compositor::onSurfaceCreated);

    // Event when surface wants to change the cursor
    connect(defaultSeat(), &QWaylandSeat::cursorSurfaceRequest, this, &Compositor::adjustCursorSurface);

    // Event when drag starts
    connect(defaultSeat()->drag(), &QWaylandDrag::dragStarted, this, &Compositor::startDrag);

    // Event when a wlShellSurface is created ( Wrongly used to identify a view by its title )
    connect(wlShell,&QWaylandWlShell::wlShellSurfaceCreated,this,&Compositor::onWlShellCreated);

    // Delete previusly created unix sockets server
    server->removeServer("com.cuarzo.crystals");

    // Creates the new unix sockets server
    server->listen("com.cuarzo.crystals");

    // Event when a unix socket is connected ( A client )
    connect(server,SIGNAL(newConnection()),this,SLOT(newClientConnected()));

}

// New client Unix socket

void Compositor::newClientConnected()
{
    // Gets the new socket
    Socket *socket = new Socket(server->nextPendingConnection());

    // Store the socket
    sockets.append(socket);

    // Event when socket is disconnected
    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));

    // Event when socket sends a message
    connect(socket,SIGNAL(messageIn()),this,SLOT(newClientMessage()));

}

// New client Unix Message ( Crystals messaging protocol )

void Compositor::newClientMessage()
{
    // Get the socket
    Socket *socket = qobject_cast<Socket *>(sender());

    // Reads the message
    QByteArray data = socket->socket->readAll();

    // Detects the message type
    unsigned int type = *(unsigned int*)data.mid(0,sizeof(unsigned int)).data();

    // Switch for message types
    switch ( type ) {

        // Register App ( Asociate the client process id with the socket )
        case REGISTER_APP:{

            // Parse the message
            RegisterAppStruct *message = ( RegisterAppStruct * ) data.data();

            // Asociate client to this socket
            socket->processID = message->pid;

            // Assigns the application type
            socket->appType = message->appType;

            // If is the Paradiso Application
            if( socket->appType  == PARADISO_TYPE )
            {
                // Save socket
                paradisoSocket = socket;

                // Now can open apps
                readyToLaunchApps();

            }

            // Sends confirmation response
            RegisteredAppStruct reply;

            // Copy message to a char pointer
            char data[sizeof(RegisteredAppStruct)];
            memcpy(data,&reply,sizeof(RegisteredAppStruct));

            // Send message
            socket->socket->write(data,sizeof(RegisteredAppStruct));


        }break;

        // Full initial surface configuration ( Size, Position, Opacity, etc )
        case SURFACE_CONFIG:{

            // Parse the message
            SurfaceConfigStruct *message = (SurfaceConfigStruct*)data.data();

            // Find view that matches the given surface id
            View *view = findViewByIdAndPid( message->id, socket->processID );

            if ( view == nullptr ) return;

            // Assign the surface position
            view->setPosition( QPointF( message->x, message->y ) );

            // Assign the surface role
            view->setRole( message->role );

            // Flag the surface ass configured
            view->configured = true;

            // Save surface if it's Paradiso ( CuarzoOS TopBar )
            if( message->role == PARADISO_MODE )
            {
                window->paradisoView = view;
                qDebug() << "Paradiso";
            }
            // Save surface if it's a menu
            if( message->role == MENU_MODE )
            {
                menus.append(view);
                qDebug() << "New Menu";
            }

            // Triggers OpenGL render
            triggerRender();

        }break;

        // Change surface role
        case SURFACE_ROLE:{

            // Parse the message
            SurfaceRoleStruct *msg = (SurfaceRoleStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->id,socket->processID);

            if ( view == nullptr ) return;

            // Set surface role
            view->setRole(msg->role);

             // Triggers OpenGL render
            triggerRender();


        }break;

        // Change the surface position
        case SURFACE_POS:{

            // Parse the message
            SurfacePosStruct *msg = (SurfacePosStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->id,socket->processID);

            if ( view == nullptr ) return;

            // Sets surface position
            view->setPosition(QPointF(msg->x,msg->y));

            // Triggers OpenGL render
            triggerRender();

        }break;

        // Change the surface position
        case SURFACE_GRAB:{

            // Parse the message
            SurfaceGrabStruct *msg = (SurfaceGrabStruct*)data.data();

            if( window->mouseView == nullptr) return;

            if( window->mouseView->surfaceId == msg->id)
                window->mouseGrabBegin();

            // Triggers OpenGL render
            triggerRender();

        }break;

        // Change surface opacity
        case SURFACE_OPACITY:{

            // Parse the message
            SurfaceOpacityStruct *msg = (SurfaceOpacityStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->id,socket->processID);

            if ( view == nullptr ) return;

            // Sets surface opacity
            view->setOpacity(msg->opacity);

            // Triggers OpenGL render
            triggerRender();

        }break;

        // New Blur Widget
        case SURFACE_BLUR_CREATE:{

            // Parse the message
            SurfaceBlurCreateStruct *msg = (SurfaceBlurCreateStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->surfaceId,socket->processID);

            if ( view == nullptr ) return;

            //  Saves the data
            view->blurWidgets.insert( msg->blurId, msg);

            // Triggers OpenGL render
            triggerRender();

        }break;

        // Changes blur level
    case SURFACE_BLUR_LEVEL:{

            // Parse the message
            SurfaceBlurLevelStruct *msg = (SurfaceBlurLevelStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->surfaceId,socket->processID);

            if ( view == nullptr ) return;

            // Sets  level
           if( view->blurWidgets.contains(msg->blurId) )
               view->blurWidgets[msg->blurId]->level = msg->level;


            // Triggers OpenGL render
            triggerRender();

        }break;

        // Changes blur rect
    case SURFACE_BLUR_RECT:{

            // Parse the message
            SurfaceBlurRectStruct *msg = (SurfaceBlurRectStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->surfaceId,socket->processID);

            if ( view == nullptr ) return;

            // Sets  level
           if( view->blurWidgets.contains(msg->blurId) )
           {
               SurfaceBlurCreateStruct *blur = view->blurWidgets[msg->blurId];
               blur->x = msg->x;
               blur->y = msg->y;
               blur->w = msg->w;
               blur->h = msg->h;
           }

            // Triggers OpenGL render
            triggerRender();

        }break;

        // Changes blur tint level
    case SURFACE_BLUR_TINT:{

            // Parse the message
            SurfaceBlurTintStruct *msg = (SurfaceBlurTintStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->surfaceId,socket->processID);

            if ( view == nullptr ) return;

            // Sets  level
           if( view->blurWidgets.contains(msg->blurId))
               view->blurWidgets[msg->blurId]->tint = msg->tint;

            // Triggers OpenGL render
            triggerRender();

        }break;

        // Remove blur
    case SURFACE_BLUR_REMOVE:{

            // Parse the message
            SurfaceBlurRemoveStruct *msg = (SurfaceBlurRemoveStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->surfaceId,socket->processID);

            if ( view == nullptr ) return;

            // Sets  level
           if( view->blurWidgets.contains(msg->blurId) )
               delete view->blurWidgets.take(msg->blurId);

            // Triggers OpenGL render
            triggerRender();

        }break;

    }
}

// System app is launched
void Compositor::readyToLaunchApps()
{
    readyApps++;

    if(readyApps == 1) // Launch Paradiso
        //man.launchZpp(SYSTEM_PATH + "/System/Applications/Paradiso.zpp");
    if(readyApps == 2) {// Launch a Demo App
        //man.launchZpp(SYSTEM_PATH + "/Applications/DemoApp.zpp");
}
}


// Client disconnected

void Compositor::socketDisconnected()
{
    // Gets the asociated socket
    Socket *socket = qobject_cast<Socket *>(sender());

    // Deletes the socket from the list
    delete sockets.takeAt(sockets.indexOf(socket));
}

// Wayland surface created event

void Compositor::onSurfaceCreated(QWaylandSurface *surface)
{

    connect(surface, &QWaylandSurface::surfaceDestroyed, this, &Compositor::surfaceDestroyed);
    connect(surface, &QWaylandSurface::hasContentChanged, this, &Compositor::surfaceHasContentChanged);
    connect(surface, &QWaylandSurface::redraw, this, &Compositor::triggerRender);
    connect(surface, &QWaylandSurface::sizeChanged, this, &Compositor::surfaceSizeChanged);

    View *view = new View(this);
    view->setSurface(surface);
    view->setOutput(outputFor(window));
    views << view;

    connect(view, &QWaylandView::surfaceDestroyed, this, &Compositor::viewSurfaceDestroyed);

}

void Compositor::onWlShellCreated(QWaylandWlShellSurface *wlShellSurface)
{
    connect(wlShellSurface,SIGNAL(titleChanged()),this,SLOT(titleChanged()));
}

// Wrongly used to identify a surface
void Compositor::titleChanged()
{
    QWaylandWlShellSurface *surface = qobject_cast< QWaylandWlShellSurface*>(sender());

    qDebug() << "New Window";

    // Find equivalent view
    View* view = findView(surface->surface());

    // Asign the ID
    view->surfaceId = surface->title().toInt();

    // Send response
    RegisteredSurfaceStruct reply;
    reply.id = view->surfaceId;

    // Copy message to a char pointer
    char data[sizeof(RegisteredSurfaceStruct)];
    memcpy(data,&reply,sizeof(RegisteredSurfaceStruct));

    // Ask the surface for a full configuration
    view->socket = findSocketByPId(surface->surface()->client()->processId());

    view->socket->socket->write(data,sizeof(RegisteredSurfaceStruct));

    return;
}

void Compositor::surfaceHasContentChanged()
{
    QWaylandSurface *surface = qobject_cast<QWaylandSurface *>(sender());

    if (surface->hasContent()) {
        if (surface->role() == QWaylandWlShellSurface::role()){
            defaultSeat()->setKeyboardFocus(surface);
        }
    }
    triggerRender();
}

void Compositor::surfaceDestroyed()
{
    triggerRender();
}

void Compositor::surfaceSizeChanged()
{
    triggerRender();
}

void Compositor::viewSurfaceDestroyed()
{
    View *view = qobject_cast<View*>(sender());
    view->setBufferLocked(true);
    views.removeAll(view);
    delete view;
}



View * Compositor::findView(const QWaylandSurface *s) const
{
    Q_FOREACH (View* view, views) {
        if (view->surface() == s)
            return view;
    }
    return Q_NULLPTR;
}

void Compositor::triggerRender()
{
    window->requestUpdate();
}


void Compositor::updateCursor()
{
    cursor.advance();
    QImage image = cursor.currentBuffer().image();
    if (!image.isNull())
        window->setCursor(QCursor(QPixmap::fromImage(image), m_cursorHotspotX, m_cursorHotspotY));
    else
        window->setCursor(QCursor(Qt::ArrowCursor));
}

void Compositor::adjustCursorSurface(QWaylandSurface *surface, int hotspotX, int hotspotY)
{
    if ((cursor.surface() != surface)) {
        if (cursor.surface())
            disconnect(cursor.surface(), &QWaylandSurface::redraw, this, &Compositor::updateCursor);
        if (surface)
            connect(surface, &QWaylandSurface::redraw, this, &Compositor::updateCursor);
    }

    cursor.setSurface(surface);
    m_cursorHotspotX = hotspotX;
    m_cursorHotspotY = hotspotY;

    if (surface && surface->hasContent())
        updateCursor();
}




void Compositor::handleMouseEvent(QWaylandView *target, QMouseEvent *me)
{

    QWaylandSeat *input = defaultSeat();
    QWaylandSurface *surface = target ? target->surface() : nullptr;

    switch (me->type())
    {
        case QEvent::MouseButtonPress:

            input->sendMousePressEvent( me->button() );

            if ( surface != input->keyboardFocus() )
            {
                if (surface == nullptr)
                {
                    input->setKeyboardFocus(surface);
                }
            }
            break;
    case QEvent::MouseButtonRelease:
         input->sendMouseReleaseEvent(me->button());
         break;
    case QEvent::MouseMove:
        input->sendMouseMoveEvent(target, me->localPos(), me->globalPos());
    default:
        break;
    }
}



void Compositor::startDrag()
{
    QWaylandDrag *currentDrag = defaultSeat()->drag();
    Q_ASSERT(currentDrag);
    View *iconView = findView(currentDrag->icon());
    iconView->setPosition(window->mapFromGlobal(QCursor::pos()));

    emit dragStarted(iconView);
}



void Compositor::handleDrag(View *target, QMouseEvent *me)
{
    QPointF pos = me->localPos();
    QWaylandSurface *surface = 0;
    if (target) {
        pos -= target->position();
        surface = target->surface();
    }
    QWaylandDrag *currentDrag = defaultSeat()->drag();
    currentDrag->dragMove(surface, pos);
    if (me->buttons() == Qt::NoButton) {
        views.removeOne(findView(currentDrag->icon()));
        currentDrag->drop();
    }
}

View *Compositor::findViewById( int id )
{
    Q_FOREACH(View *view,views)
    {
        if(view->surfaceId == id)
            return view;
    }
    return nullptr;
}

View *Compositor::findViewByIdAndPid( int id, int pid)
{
    // Find equivalent view
    Q_FOREACH (View* view, views)
    {
        if (view->surfaceId == id && pid == view->surface()->client()->processId())
            return view;
    }
    return nullptr;
}

Socket *Compositor::findSocketByPId( uint id )
{
    Q_FOREACH(Socket *socket,sockets)
    {
        if(socket->processID == id)
            return socket;
    }
    return nullptr;
}



void Compositor::raise(View *view)
{
    int index = views.indexOf(view);
    views.move( index, views.length() - 1 );

}

void Compositor::setScreenResolution(QSize size)
{
    window->resize(size);
    QWaylandOutputMode mode(size, 60000);
    output->addMode( mode, true );
    output->setCurrentMode(mode);
    output->setWindow(window);
    //output->setSizeFollowsWindow(true);

}


