#ifndef WINDOWCOMPOSITOR_H
#define WINDOWCOMPOSITOR_H

#include "headers.h"
#include "window.h"
#include "view.h"
#include "socket.h"
#include "launchman.h"

class QOpenGLTexture;
class Compositor;
class View;
class Socket;

class Compositor : public QWaylandCompositor
{
    Q_OBJECT
public:

    // Setup compositor
    Compositor();

    // Unix sockets IPC for clients
    QLocalServer *server = new QLocalServer(this);

    // Compositor Window ( Screen )
    Window *window = new Window(this);

    // Set the Wayland output to the screen
    QWaylandOutput *output = new QWaylandOutput(this, window);

    // Wayland Shell to identify surfaces
    QWaylandWlShell *wlShell = new QWaylandWlShell(this);

    // Launchman
    LaunchMan man;

    // Stored surfaces
    QList<View*> views;

    // Stored client sockets
    QList<Socket*> sockets;

    // Special sockets
    Socket *crystalsGuiSocket = nullptr;

    // Wayland cursor surface
    QWaylandView cursor;

    // Cursor position
    int m_cursorHotspotX;
    int m_cursorHotspotY;

    // Manage render
    void startRender();
    void endRender();

    // Changes the screen resolution
    void setScreenResolution(QSize size);


    void handleMouseEvent(QWaylandView *target, QMouseEvent *me);
    void handleResize(View *target, const QSize &initialSize, const QPoint &delta, int edge);
    void handleDrag(View *target, QMouseEvent *me);

    // Raise the selected view
    void raise(View *view);

    // Find view by id
    View *findViewById(uint id);

    // Find view by id and pid
    View *findViewByIdAndPid(uint id,uint pid);

    // Find socket by pid
    Socket *findSocketByPId(uint id);

protected:
    void adjustCursorSurface(QWaylandSurface *surface, int hotspotX, int hotspotY);

signals:
    void startResize(int edge, bool anchored);
    void dragStarted(View *dragIcon);

public slots:
    void readyToLaunchApps();
    void triggerRender();
    void newClientConnected();
    void newClientMessage();

private slots:
    void socketDisconnected();
    void surfaceHasContentChanged();
    void surfaceDestroyed();
    void surfaceSizeChanged();
    void viewSurfaceDestroyed();

    void startDrag();

    void titleChanged();


    void onSurfaceCreated(QWaylandSurface *surface);
    void onWlShellCreated(QWaylandWlShellSurface *wlShellSurface);


    void onSubsurfaceChanged(QWaylandSurface *child, QWaylandSurface *parent);
    void onSubsurfacePositionChanged(const QPoint &position);

    void updateCursor();
private:
    View *findView(const QWaylandSurface *s) const;
};


#endif // WINDOWCOMPOSITOR_H
