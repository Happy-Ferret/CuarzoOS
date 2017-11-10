#include "view.h"

View::View(Compositor *_compositor)
{
    compositor = _compositor;
}

void View::setRole(uint newRole)
{
    role = newRole;
    roleChanged(newRole);
}

void View::setOpacity(uint newOpacity)
{
    opacity = newOpacity;
    opacityChanged(newOpacity);
}

void View::setSize(const QSize &size)
{
    if ( socket == nullptr ) return;
    SurfaceScaledStruct msg;
    msg.height = size.height();
    msg.width = size.width();

    // Copy message to a char pointer
    char data[sizeof(SurfaceScaledStruct)];
    memcpy(data,&msg,sizeof(SurfaceScaledStruct));

    // Sends the message
    socket->socket->write(data,sizeof(SurfaceScaledStruct));
}

void View::setSocket(Socket *_socket)
{
    // Assign the socket
    socket = _socket;

    // Flag the surface ass configured
    configured = true;

    // Bind the messages
    connect(socket,SIGNAL(messageIn()),this,SLOT(newMessage()));

}


QOpenGLTexture *View::getTexture()
{
    if (advance())
        texture = currentBuffer().toOpenGLTexture();

    return texture;
}

void View::setPosition(const QPointF &pos)
{

    if ( socket == nullptr ) return;

    QPointF p = pos;

    SurfaceMovedStruct msg;
    msg.x = p.x();
    msg.y = p.y();

    // Copy message to a char pointer
    char data[sizeof(SurfaceMovedStruct)];
    memcpy(data,&msg,sizeof(SurfaceMovedStruct));

    // Sends the message
    socket->socket->write(data,sizeof(SurfaceMovedStruct));

    if (p.y() < 29)
        p.setY(29);

    m_position = p;
}


QSize View::size() const
{
    return surface()->size();
}

bool View::isCursor() const
{
    return surface() && surface()->isCursorSurface();
}

void View::newMessage()
{

    // Reads the message
    QByteArray data = socket->socket->readAll();

    // Detects the message type
    unsigned int type = *(unsigned int*)data.mid(0,sizeof(unsigned int)).data();

    // Switch for message types
    switch ( type ) {

        // Change surface role
        case SURFACE_ROLE:{

            // Parse the message
            SurfaceRoleStruct *msg = (SurfaceRoleStruct*)data.data();

            // Set surface role
            setRole(msg->role);

             // Triggers OpenGL render
            compositor->triggerRender();

        }break;

        // Change the surface position
        case SURFACE_POS:{

            // Parse the message
            SurfacePosStruct *msg = (SurfacePosStruct*)data.data();

            // Sets surface position
            setPosition(QPointF(msg->x,msg->y));

            // Triggers OpenGL render
            compositor->triggerRender();

        }break;

        // Change the surface position
        case SURFACE_GRAB:{

            // Parse the message
            SurfaceGrabStruct *msg = (SurfaceGrabStruct*)data.data();

            if( compositor->window->mouseView == 0) return;

            if( compositor->window->mouseView->surfaceId == surfaceId)
                compositor->window->mouseGrabBegin();

            // Triggers OpenGL render
            compositor->triggerRender();

        }break;

        // Change surface opacity
        case SURFACE_OPACITY:{

            // Parse the message
            SurfaceOpacityStruct *msg = (SurfaceOpacityStruct*)data.data();

            // Sets surface opacity
            setOpacity( msg->opacity );

            // Triggers OpenGL render
            compositor->triggerRender();

        }break;

        // New Blur Widget
        case SURFACE_BLUR_CREATE:{

            // Parse the message
            SurfaceBlurCreateStruct *msg = (SurfaceBlurCreateStruct*)data.data();

            //  Saves the data
            blurWidgets.insert( msg->blurId, msg );

            // Triggers OpenGL render
            compositor->triggerRender();

        }break;

        // Changes blur level
    case SURFACE_BLUR_LEVEL:{

        /*
            // Parse the message
            SurfaceBlurLevelStruct *msg = (SurfaceBlurLevelStruct*)data.data();

            // Sets  level
           if( view->blurWidgets.contains(msg->blurId) )
               view->blurWidgets[msg->blurId]->level = msg->level;


            // Triggers OpenGL render
            triggerRender();
        */
        }break;

        // Changes blur rect
    case SURFACE_BLUR_RECT:{

        /*
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
    */
        }break;

        // Changes blur tint level
    case SURFACE_BLUR_TINT:{

        /*
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
    */
        }break;

        // Remove blur
    case SURFACE_BLUR_REMOVE:{
    /*
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
    */
        }break;

    }

}






