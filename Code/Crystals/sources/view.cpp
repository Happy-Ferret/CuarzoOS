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
    float h = size().height(); // View Height
    float w = size().width(); // View Width

    QColor surfaceColor = QColor(255,255,255,255);

    /* -------------- Surface -------------*/

    // Top Left
    setVertexPos(0,borderWidth,0);
    setVertexCol(0, surfaceColor);

    // Top Right
    setVertexPos(1,w - borderWidth,0);
    setVertexCol(1, surfaceColor);

    uint index = 2;

    // Right corner
    for(float x = radius - borderWidth; x >= 0.0f ; x -= (radius - borderWidth)/radius)
    {
        float y = qSqrt( qPow( radius - borderWidth , 2 ) - qPow( x  , 2 ));
        setVertexCol(index,surfaceColor);
        setVertexPos(index , w - radius + x , h - radius + y );
        index++;

    }

    // Left corner
    for(float x = 0.0f; x <= radius - borderWidth ; x += (radius - borderWidth)/radius)
    {
        float y = qSqrt( qPow( radius - borderWidth , 2 ) - qPow( x  , 2 ));
        setVertexCol(index,surfaceColor);
        setVertexPos(index , radius - x - borderWidth, h - radius + y );
        index++;

    }

    // Save surface vertex count
    surfaceCount = index;



    /* -------------- Border -------------*/


    // Top Right less border
    setVertexPos(index,w,0);
    setVertexCol(index,Qt::transparent);
    index++;

    // Top Right
    setVertexPos(index,w - borderWidth,0);
    setVertexCol(index,surfaceColor);
    index++;

    int X = radius;

    // Right corner
    for(float x = radius - borderWidth; x >= 0.0f ; x -= (radius - borderWidth)/radius)
    {
        // Out
        float y = qSqrt( qPow( radius , 2 ) - qPow( X  , 2 ));
        setVertexCol(index,Qt::transparent);
        setVertexPos(index , w - radius + X , h - radius + y );
        index++;
        X--;

        // In
        y = qSqrt( qPow( radius - borderWidth , 2 ) - qPow( x  , 2 ));
        setVertexCol(index,surfaceColor);
        setVertexPos(index , w - radius + x , h - radius + y );
        index++;

    }

    X = 0;
    // Left corner
    for(float x = 0.0f; x <= radius - borderWidth ; x += (radius - borderWidth)/radius)
    {
        // Out
        float y = qSqrt( qPow( radius , 2 ) - qPow( X  , 2 ));
        setVertexCol(index,Qt::transparent);
        setVertexPos(index , radius - X - borderWidth , h - radius + y );
        index++;
        X++;

        // In
        y = qSqrt( qPow( radius - borderWidth , 2 ) - qPow( x  , 2 ));
        setVertexCol(index,surfaceColor);
        setVertexPos(index , radius - x  - borderWidth, h - radius + y );
        index++;

    }

    // Top Right
    setVertexPos(index,0,0);
    setVertexCol(index,Qt::transparent);
    index++;

    // Top Left less border
    setVertexPos(index,borderWidth,0);
    setVertexCol(index,surfaceColor);
    index++;

    borderCount = index - surfaceCount;


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






