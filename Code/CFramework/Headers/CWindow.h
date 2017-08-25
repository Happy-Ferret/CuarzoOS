#include "CCore.h"
#include <QWidget>

#ifndef CWINDOW
#define CWINDOW

/* ------------------ CWindow ------------------ */

class CWindow: public QWidget
{

    Q_OBJECT

public:
    CWindow(QWidget *parent = nullptr);
    void move(const QPoint &pos);
    void move(int x, int y);
    void setWindowTitle(const QString &title);
    void setMode(unsigned int mode = WINDOW_MODE);
    void setBlur(bool mode);
    void setWindowOpacity(uint opacity = 255);

    QString windowTitle();
    uint windowOpacity();
    uint mode();
    bool blurState();

    bool registeredSurface = false;

signals:
    void positionChanged(const QPoint &pos);
    void titleChanged(QString);
    void modeChanged(uint);
    void opacityChanged(uint);
    void blurStateChanged(bool);

private:
    QString localTitle = QString("");
    uint localMode = WINDOW_MODE;
    uint localOpacity = 255;
    bool localBlur = false;
};

#endif

