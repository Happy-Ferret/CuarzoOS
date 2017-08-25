#include "view.h"

View::View(Compositor *compositor)
    : compositor(compositor)
    , m_parentView(nullptr)
{
}

void View::setRole(uint newRole)
{
    role = newRole;
    roleChanged(newRole);

    // Creates a title bar
    if( role == WINDOW_MODE || role == FRAMELESS_MODE)
    {
        if(titleBar == nullptr)
        {
            TitlebarRequestStruct msg;
            msg.forPid = surface()->client()->processId();
            msg.forId = surfaceId;
            msg.width = size().width();
            strcpy(msg.title,title.toUtf8());

            // Copy message to a char pointer
            char data[sizeof(TitlebarRequestStruct )];
            memcpy(data,&msg,sizeof(TitlebarRequestStruct));

            // Send message
            compositor->crystalsGuiSocket->socket->write(data,sizeof(TitlebarRequestStruct));

            // Print event
            qDebug() << "TitleBar request sent";
        }
    }
}

void View::setTitle(const QString &newTitle)
{
    title = newTitle;
    titleChanged(newTitle);

    TitlebarTitleStruct msg;
    msg.forPid = surface()->client()->processId();
    msg.forId = surfaceId;
    strcpy(msg.title,title.toUtf8());

    // Copy message to a char pointer
    char data[sizeof(TitlebarTitleStruct )];
    memcpy(data,&msg,sizeof(TitlebarTitleStruct));

    // Send message
    compositor->crystalsGuiSocket->socket->write(data,sizeof(TitlebarTitleStruct));

    // Print event
    qDebug() << "TitleBar title sent";
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
    msg.height = size.height();
    msg.width = size.width();

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


QSize View::size() const
{
    return surface()->size();
}

bool View::isCursor() const
{
    return surface() && surface()->isCursorSurface();
}






