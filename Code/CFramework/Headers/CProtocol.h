#ifndef CPROTOCOL_H
#define CPROTOCOL_H

#include "CCore.h"
#include "CWindow.h"
#include <QApplication>
#include <QLocalSocket>
#include <QObject>

class CProtocol : public QObject
{
    Q_OBJECT

public:
    CProtocol(QApplication *);
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
};

#endif // CPROTOCOL_H
