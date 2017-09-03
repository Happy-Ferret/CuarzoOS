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
    msg.id = surfaceId;
    msg.height = size.height();
    msg.width = size.width();

    // Copy message to a char pointer
    char data[sizeof(SurfaceScaledStruct)];
    memcpy(data,&msg,sizeof(SurfaceScaledStruct));

    // Sends the message
    socket->socket->write(data,sizeof(SurfaceScaledStruct));
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
    SurfaceMovedStruct msg;
    msg.id = surfaceId;
    msg.x = pos.x();
    msg.y = pos.y();

    // Copy message to a char pointer
    char data[sizeof(SurfaceMovedStruct)];
    memcpy(data,&msg,sizeof(SurfaceMovedStruct));

    // Sends the message
    socket->socket->write(data,sizeof(SurfaceMovedStruct));

    m_position = pos;
}


QSize View::size() const
{
    return surface()->size();
}

bool View::isCursor() const
{
    return surface() && surface()->isCursorSurface();
}






