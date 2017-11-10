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

    // New surface registration
    if( type == SURFACE_REGISTER )
    {
        // Disconnect messages for the compositor
        disconnect(socket,SIGNAL(messageIn()),this,SLOT(newClientMessage()));

        // Parse the message
        SurfaceRegisterStruct *message = (SurfaceRegisterStruct*)data.data();

        // Find view that matches the given surface id
        View *view = findViewByIdAndPid( message->id, message->pid );

        // If no view found return
        if ( view == nullptr ) return;

        // Assign the socket to the view
        view->setSocket( socket );

        // Assign the surface position
        view->setPosition( QPointF( message->x, message->y ) );

        // Assign the surface role
        view->setRole( message->role );

        // Save surface if it's Paradiso ( CuarzoOS TopBar )
        if( message->role == TopBar)
        {
            window->paradisoView = view;
            qDebug() << "Paradiso";
        }
        // Save surface if it's a menu
        if( message->role == WindowRole::Menu )
        {
            menus.append(view);
            qDebug() << "New Menu";
        }

        // Triggers OpenGL render
        triggerRender();
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

    // Find equivalent view
    View* view = findView(surface->surface());

    // Asign the ID
    QJsonDocument data = QJsonDocument::fromJson(surface->title().toUtf8());
    QVariantMap json = data.toVariant().toMap();
    view->surfaceId = json["id"].toInt();
    view->appId = json["pid"].toInt();

    qDebug() << "New Window" << surface->title();
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
    return nullptr;
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

    if ( target == nullptr) return;

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
    output->setSizeFollowsWindow(true);

}


