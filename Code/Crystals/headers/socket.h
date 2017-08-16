#ifndef SOCKET_H
#define SOCKET_H

#include "headers.h"
#include "view.h"

class Socket : public QObject
{
    Q_OBJECT
public:
    Socket(QLocalSocket *_socket);
    QLocalSocket *socket = nullptr;
    uint appType;
    uint processID;
    bool connected = false;

private slots:
    void newMessage();
    void disconn();
signals:
    void messageIn();
    void disconnected();
};

#endif // SOCKET_H
