#include "CCore.h"
#include "CLabel.h"
#include "CIconButton.h"
#include <QApplication>
#include <QWidget>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QLocalSocket>

#ifndef CWINDOW
#define CWINDOW

/* ------------------ CWindow ------------------ */

class CWindow: public QWidget
{

    Q_OBJECT

public:
    CWindow( uint mode = WINDOW_MODE);
    void move(const QPoint &pos);
    void move(int x, int y);
    void setWindowTitle(const QString &title);
    void setMode(unsigned int mode = WINDOW_MODE);
    void setWindowOpacity( float opacity = 1.0f );
    void setCentralWidget( QWidget *widget );

    QString windowTitle();
    uint windowOpacity();
    uint mode();

    bool registeredSurface = false;

    // Topbar items layout
    QHBoxLayout *firstTopLayout, seccondTopLayout;


private slots:
    void connected();
    void newMessage();

protected:
    void connectToCrystals();
private:
    void sendPosition(const QPoint &pos);
    void modeChanged(uint mode);
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


    uint localMode = WINDOW_MODE;
    uint localOpacity = 255;


    QLocalSocket *socket = new QLocalSocket(this);


};

#endif

