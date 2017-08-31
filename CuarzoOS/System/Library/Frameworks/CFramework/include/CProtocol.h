#ifndef CPROTOCOL_H
#define CPROTOCOL_H

#include "CCore.h"
#include "CWindow.h"
#include <QApplication>
#include <QLocalSocket>
#include <QObject>
#include <QMap>

class CProtocol : public QObject
{
    Q_OBJECT

public:
    CProtocol(QApplication *);
public slots:
    void connected();
    void messageIn();
    void sendPosition(const QPoint &pos);
    void modeChanged(uint mode);
    void opacityChanged(float opacity);
    void blurStateChanged(bool mode);
    void mouseGrab();

private:
    QLocalSocket *socket = new QLocalSocket(this);
    CWindow *findCWindowById(uint id);
    QMap <uint,CWindow*>windows;
};

#endif // CPROTOCOL_H
