#include "CCore.h"
#include "CLabel.h"
#include "CIconButton.h"
#include <QApplication>
#include <QWidget>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QLocalSocket>
#include <QTimer>
#include <QScreen>
#include <QtMath>

#ifndef CWINDOW
#define CWINDOW

/* ------------------ CWindow ------------------ */

class CWindow: public QWidget
{

    Q_OBJECT

public:
    CWindow( WindowRole role = WindowRole::Frame);
    void move(const QPoint &pos);
    void move(int x, int y);
    void setWindowTitle(const QString &title);
    void setWindowRole(WindowRole role = Frame);
    void setWindowOpacity( float opacity = 1.0f );
    void setCentralWidget( QWidget *widget );

    bool beforeClose() { return true; }
    bool maximized(){ return localMaximized; }

    QLocalSocket *getSocket(){ return socket; }

    QString windowTitle();
    uint windowOpacity();
    WindowRole windowRole();

    bool registeredSurface = false;

    // Topbar items layout
    QHBoxLayout *firstTopLayout, seccondTopLayout;

    void close();
    void minimize( bool state = true );
    void maximize(MaximizeMode mode = CurrentWorkspace, bool state = true );

private slots:
    void connected();
    void newMessage();
    void maximizeAnimation();
protected:
    void connectToCrystals();
private:
    void sendPosition(const QPoint &pos);
    void windowRoleChanged(WindowRole role);
    void opacityChanged(float opacity);
    void mouseGrab();

    /*
    void blurTint(float tint);
    void blurLevel(float level);
    void blurRect();
    void blurRemove(bool);
    */

    void refreshtemsPositions();

    // Separate the Titlebar from the central widget
    QVBoxLayout *verticalLayout = new QVBoxLayout( this );

    // Topbar widget
    QWidget *topBar = new QWidget( this );

    // Topbar items widget
    QWidget *topBarItems = new QWidget( this );

    // Topbar layout
    QHBoxLayout *horizontalLayout= new QHBoxLayout(topBar);

    // Title label
    CLabel *_title = new CLabel( QApplication::applicationName(), topBar );

    // Window buttons
    CIconButton *closeButton, *minimizeButton, *expandButton;

    // Resize event
    void resizeEvent(QResizeEvent *);
    bool eventFilter(QObject *watched, QEvent *event);

    // Animation
    QTimer *animationTimer = new QTimer( this );
    bool localMaximized = false;
    QSize unmaximizedSize, maximizedSize;
    QPoint unmaximizedPos, maximizedPos;
    int currentMaximizeStep = 0;
    float maximizeSteps = 15.0f;
    float dxMaxim, dyMaxim, dwMaxim, dhMaxim;

    WindowRole localRole;
    uint localOpacity = 255;


    QLocalSocket *socket = new QLocalSocket(this);


};

#endif

