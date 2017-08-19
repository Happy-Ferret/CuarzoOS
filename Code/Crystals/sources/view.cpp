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
}

void View::setOpacity(uint newOpacity)
{
    opacity = newOpacity;
    opacityChanged(newOpacity);
}

void View::calcVertexPos()
{
    float x = position().x(); // View X
    float y = position().y(); // View Y
    float h = size().height(); // View Height
    float w = size().width(); // View Width

    QColor surfaceColor = QColor(255,255,255,255);
    setVertexPos(0, 0, 0);
    setVertexPos(1, w, 0);
    setVertexPos(2, w, h);
    setVertexPos(3, 0,  h);

    setVertexCol(0,surfaceColor);
    setVertexCol(1,surfaceColor);
    setVertexCol(2,surfaceColor);
    setVertexCol(3,surfaceColor);

    setTextureCord(0,0,0);
    setTextureCord(1,1,0);
    setTextureCord(2,1,1);
    setTextureCord(3,0,1);
}

void View::calcBlurRect()
{
    // Surface position
    float x = position().x();
    float y =position().y();

    // Surface size
    float w = size().width();
    float h = size().height();

    // Window height
    float winH = compositor->window->height();

    int margin = (6.0f*5.0f);

    // Top left
    blurRectVertices[0].position[0] = -1.0f;
    blurRectVertices[0].position[1] = -1.0f;
    blurRectVertices[0].position[2] = 0.0f;

    blurRectVertices[0].texture[0] = x - margin;
    blurRectVertices[0].texture[1] = winH - y +margin;

    // Bottom left
    blurRectVertices[1].position[0] = -1.0f;
    blurRectVertices[1].position[1] =  1.0f;
    blurRectVertices[1].position[2] = 0.0f;

    blurRectVertices[1].texture[0] = x - margin;
    blurRectVertices[1].texture[1] = winH - y - h - margin ;

    // Bottom right
    blurRectVertices[2].position[0] =  1.0f;
    blurRectVertices[2].position[1] =  1.0f;
    blurRectVertices[2].position[2] = 0.0f;

    blurRectVertices[2].texture[0] = x + w +margin;
    blurRectVertices[2].texture[1] = winH - y - h -margin;

    // Top right
    blurRectVertices[3].position[0] = 1.0f;
    blurRectVertices[3].position[1] =-1.0f ;
    blurRectVertices[3].position[2] = 0.0f;

    blurRectVertices[3].texture[0] = x + w + margin;
    blurRectVertices[3].texture[1] = winH - y + margin;
}

void View::calcTopBarRect()
{
    float x = position().x(); // View X
    float y = position().y(); // View Y
    float w = size().width(); // View Height

    // Top left
    topBarVertices[0].position[0] = 0;
    topBarVertices[0].position[1] = 0;
    topBarVertices[0].position[2] = zIndex;

    topBarVertices[0].texture[0] = 0;
    topBarVertices[0].texture[1] = 0;

    // Top Right
    topBarVertices[1].position[0] = w;
    topBarVertices[1].position[1] = 0;
    topBarVertices[1].position[2] = zIndex;

    topBarVertices[1].texture[0] = 1;
    topBarVertices[1].texture[1] = 0;

    // Bottom right
    topBarVertices[2].position[0] = w;
    topBarVertices[2].position[1] = topBarHeight;
    topBarVertices[2].position[2] = zIndex;

    topBarVertices[2].texture[0] = 1;
    topBarVertices[2].texture[1] = 1;

    // Bottom left
    topBarVertices[3].position[0] = 0;
    topBarVertices[3].position[1] = topBarHeight ;
    topBarVertices[3].position[2] = zIndex;

    topBarVertices[3].texture[0] = 0;
    topBarVertices[3].texture[1] = 1;

    titleBar->setPosition(QPointF(x, y-topBarHeight));
}

void View::setVertexCol(int index, QColor color)
{
    vertices[index].color[0] = color.redF();
    vertices[index].color[1] = color.greenF();
    vertices[index].color[2] = color.blueF();
    vertices[index].color[3] = color.alphaF();
}

void View::setVertexPos(int index, float x, float y)
{
    vertices[index].position[0] = x;
    vertices[index].position[1] = y;
    vertices[index].position[2] = zIndex;
}

void View::setTextureCord(int index, float x, float y)
{
    vertices[index].texture[0] = x;
    vertices[index].texture[1] = y;
}

QOpenGLTexture *View::getTexture()
{
    if (advance()) {
        QWaylandBufferRef buf = currentBuffer();
        texture = buf.toOpenGLTexture();
    }

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






