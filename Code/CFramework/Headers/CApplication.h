#include "CCore.h"
#include "CWindow.h"
#include <QApplication>
#include <QLocalSocket>
#include <QWindow>
#include <QStyleFactory>

#ifndef CAPPLICATION
#define CAPPLICATION

/* ------------------ CApplication ------------------ */

class CApplication : public QApplication
{
    Q_OBJECT

public:
    CApplication(int &argc,char **argv);

public slots:
    void connected();
    void messageIn();
    void sendPosition(const QPoint &pos);
    void titleChanged(QString title);
    void modeChanged(uint mode);
    void opacityChanged(uint opacity);
    void blurStateChanged(bool mode);

private:
    QLocalSocket *socket = new QLocalSocket(this);
    CWindow *findCWindowById(uint id);

signals:
    void run();
};

#endif


