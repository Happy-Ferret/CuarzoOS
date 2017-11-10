#ifndef VIEW_H
#define VIEW_H

#include "headers.h"
#include "compositor.h"
#include "socket.h"

class Compositor;
class View;

class View : public QWaylandView
{
    Q_OBJECT
public:

    View(Compositor *_compositor);

    // Surface configuration
    uint role = WINDOW_MODE;
    uint opacity = 255;
    int surfaceId = -1;
    int appId = -1;
    bool blur = false;
    bool configured = false;

    // Configuration methods
    void setRole(uint newRole);
    void setOpacity(uint newOpacity);
    void setSize(const QSize &size);
    void setSocket( Socket *_socket );

    Socket *socket = nullptr;
    QMap<uint, SurfaceBlurCreateStruct*> blurWidgets;

    QOpenGLTexture *getTexture();

    QPointF position() const { return m_position; }
    void setPosition(const QPointF &pos);

    QSize size() const;
    bool isCursor() const;

    Compositor *compositor = nullptr;
    QOpenGLTexture *texture = nullptr;
    QPointF m_position, previusPosition;
    QSize previusSize;

private slots:
    void newMessage();

signals:
    void roleChanged(uint newRole);
    void opacityChanged(uint newOpacity);

};

#endif
