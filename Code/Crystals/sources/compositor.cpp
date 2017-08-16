#include "../headers/compositor.h"

// Compositor setup

Compositor::Compositor():QWaylandCompositor()
{
    // Creates the compositor
    create();

    // Set the screen resolution
    setScreenResolution(QGuiApplication::primaryScreen()->size());

    // Delete previusly created unix sockets server
    server->removeServer("com.cuarzo.crystals");

    // Creates the unix sockets server
    server->listen("com.cuarzo.crystals");

    // Event when wayland surface is created
    connect(this, &QWaylandCompositor::surfaceCreated, this, &Compositor::onSurfaceCreated);

    // Event when wayland subsurface has changed
    connect(this, &QWaylandCompositor::subsurfaceChanged, this, &Compositor::onSubsurfaceChanged);

    // Event when surface wants to change the cursor
    connect(defaultSeat(), &QWaylandSeat::cursorSurfaceRequest, this, &Compositor::adjustCursorSurface);

    // Event when drag starts
    connect(defaultSeat()->drag(), &QWaylandDrag::dragStarted, this, &Compositor::startDrag);

    // Event when a wlShellSurface is created ( Wrongly used to identify a view by its title )
    connect(wlShell,&QWaylandWlShell::wlShellSurfaceCreated,this,&Compositor::onWlShellCreated);

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

    // Prints the event
    qDebug()<<"Client Connected";
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
    switch (type) {

        // Register App ( Asociate the client process id with the socket )
        case REGISTER_APP:{

            // Parse the message
            RegisterAppStruct *message = (RegisterAppStruct*)data.data();

            // Asociate client to this socket
            socket->processID = message->pid;

            // Assigns the application type
            socket->appType = message->appType;

            // If is the Crystals Gui Application
            if(socket->appType  == CRYSTALS_TYPE)
            {
                // Remove the socket from the client list
                crystalsGuiSocket = sockets.takeAt(sockets.indexOf(socket));

                // Prints the event
                qDebug() << "Crystals Gui Connected";
            }

            // Sends confirmation response
            RegisteredAppStruct reply;

            // Copy message to a char pointer
            char data[sizeof(RegisteredAppStruct)];
            memcpy(data,&reply,sizeof(RegisteredAppStruct));

            // Send message
            socket->socket->write(data,sizeof(RegisteredAppStruct));

            // Prints the event
            qDebug() << "App registered PID: " + QString::number(socket->processID);

        }break;

        // Configure a surface ( Size, Position, Title, etc )
        case SURFACE_CONFIG:{

            // Parse the message
            SurfaceConfigStruct *message = (SurfaceConfigStruct*)data.data();

            // Find view that matches the given surface id
            View *view = findViewByIdAndPid(message->id,socket->processID);

            // Assign the surface position
            view->setPosition(QPointF(message->x,message->y));

            // Assign the surface role
            view->role = message->role;

            // Assign surface title
            view->title = message->title;

            // Triggers OpenGL render
            triggerRender();

            // Prints the event
            qDebug() << "Surface Title Changed";

        }break;

        // Change surface role
        case SURFACE_ROLE:{

            // Parse the message
            SurfaceRoleStruct *msg = (SurfaceRoleStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->id,socket->processID);

            // Set surface role
            view->role = msg->role;

             // Triggers OpenGL render
            triggerRender();

            // Prints the event
            qDebug() << "Surface Role Changed";

        }break;

        // Change the surface position
        case SURFACE_POS:{

            // Parse the message
            SurfacePosStruct *msg = (SurfacePosStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->id,socket->processID);

            // Sets surface position
            view->setPosition(QPointF(msg->x,msg->y));

            // Triggers OpenGL render
            triggerRender();

            // Prints the event
            qDebug() << "Surface Position Changed" ;

        }break;

        // Change surface opacity
        case SURFACE_OPACITY:{

            // Parse the message
            SurfaceOpacityStruct *msg = (SurfaceOpacityStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->id,socket->processID);

            // Sets surface opacity
            view->opacity = msg->opacity;

            // Triggers OpenGL render
            triggerRender();

            // Prints the event
            qDebug() << "Surface Opacity Changed";

        }break;

        // Blur request
        case SURFACE_BLUR:{

            // Parse the message
            SurfaceBlurStruct *msg = (SurfaceBlurStruct*)data.data();

            // Find view that matches the given surface id and process id
            View *view = findViewByIdAndPid(msg->id,socket->processID);

            // Set surface blur state
            view->blur = msg->activate;

            // Triggers OpenGL render
            triggerRender();

            // Prints the event
            qDebug() << "Surface Blur Activated";

        }break;
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
    connect(surface, &QWaylandSurface::subsurfacePositionChanged, this, &Compositor::onSubsurfacePositionChanged);
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


void Compositor::onSubsurfaceChanged(QWaylandSurface *child, QWaylandSurface *parent)
{
    View *view = findView(child);
    View *parentView = findView(parent);
    view->setParentView(parentView);
}

void Compositor::onSubsurfacePositionChanged(const QPoint &position)
{
    QWaylandSurface *surface = qobject_cast<QWaylandSurface*>(sender());
    if (!surface)
        return;

    View *view = findView(surface);
    view->setPosition(position);
    triggerRender();
}

void Compositor::triggerRender()
{
    window->requestUpdate();
}



void Compositor::startRender()
{
    QWaylandOutput *out = defaultOutput();
    if (out)
        out->frameStarted();
}

void Compositor::endRender()
{
    QWaylandOutput *out = defaultOutput();
    if (out)
        out->sendFrameCallbacks();
}

void Compositor::updateCursor()
{
    cursor.advance();
    QImage image = cursor.currentBuffer().image();
    if (!image.isNull())
        window->setCursor(QCursor(QPixmap::fromImage(image), m_cursorHotspotX, m_cursorHotspotY));
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
    switch (me->type()) {
        case QEvent::MouseButtonPress:
            input->sendMousePressEvent(me->button());
            if (surface != input->keyboardFocus()) {
                if (surface == nullptr) {
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

// Wrongly used to identify a surface
void Compositor::titleChanged()
{
    QWaylandWlShellSurface *surface = qobject_cast< QWaylandWlShellSurface*>(sender());

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

    // Send message
    findSocketByPId(surface->surface()->client()->processId())->socket->write(data,sizeof(RegisteredSurfaceStruct));

    qDebug() << "Surface Registered sId: "+QString::number(view->surfaceId);
    return;


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

View *Compositor::findViewById(uint id)
{
    Q_FOREACH(View *view,views)
    {
        if(view->surfaceId == id)
            return view;
    }
}

View *Compositor::findViewByIdAndPid(uint id, uint pid)
{
    // Find equivalent view
    Q_FOREACH (View* view, views)
    {
        if (view->surfaceId == id && pid == view->surface()->client()->processId())
            return view;
    }
}

Socket *Compositor::findSocketByPId(uint id)
{
    Q_FOREACH(Socket *socket,sockets)
    {
        if(socket->processID == id)
            return socket;
    }
}




static int findEndOfChildTree(const QList<View*> &list, int index)
{
    int n = list.count();
    View *parent = list.at(index);
    while (index + 1 < n) {
        if (list.at(index+1)->parentView() != parent)
            break;
        index = findEndOfChildTree(list, index + 1);
    }
    return index;
}

void Compositor::raise(View *view)
{
    int startPos = views.indexOf(view);
    int endPos = findEndOfChildTree(views, startPos);

    int n = views.count();
    int tail =  n - endPos - 1;

    //bubble sort: move the child tree to the end of the list
    for (int i = 0; i < tail; i++) {
        int source = endPos + 1 + i;
        int dest = startPos + i;
        for (int j = source; j > dest; j--)
            views.swap(j, j-1);
    }
}

void Compositor::setScreenResolution(QSize size)
{
    window->resize(size);
    QWaylandOutputMode mode = QWaylandOutputMode(size, 60000);
    output->addMode(mode, true);
    output->setCurrentMode(mode);
}


