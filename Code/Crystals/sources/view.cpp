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
    SurfaceScaledStruct msg;
    msg.id = surfaceId;
    msg.height = size.height() / compositor->ratio;
    msg.width = size.width() / compositor->ratio;

    // Copy message to a char pointer
    char data[sizeof(SurfaceScaledStruct)];
    memcpy(data,&msg,sizeof(SurfaceScaledStruct));

    // Sends the message
    compositor->findSocketByPId(surface()->client()->processId())->socket->write(data,sizeof(SurfaceScaledStruct));
}


QOpenGLTexture *View::getTexture()
{
    if (advance())
        texture = currentBuffer().toOpenGLTexture();

    return texture;
}

void View::setPosition(const QPointF &pos)
{
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






