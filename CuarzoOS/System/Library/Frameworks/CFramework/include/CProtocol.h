#ifndef CPROTOCOL_H
#define CPROTOCOL_H

#include "CCore.h"
#include "CWindow.h"
#include "CBlurWidget.h"
#include <QApplication>
#include <QLocalSocket>
#include <QObject>
#include <QMap>

class CBlurWidget;

class CProtocol : public QObject
{
    Q_OBJECT

    friend class CBlurWidget;

public:
    CProtocol(QApplication *);

private slots:
    void connected();
    void messageIn();
    void sendPosition(const QPoint &pos);
    void modeChanged(uint mode);
    void opacityChanged(float opacity);
    void mouseGrab();

    void blurTint(float tint);
    void blurLevel(float level);
    void blurRect();
    void blurRemove(bool);
private:
    QLocalSocket *socket = new QLocalSocket(this);
    CWindow *findCWindowById(uint id);
    QMap <uint,CWindow*>windows;
    QMap <uint,CBlurWidget*>blurWidgets;
    void connectBlurWidget( CBlurWidget *widget );


};

#endif // CPROTOCOL_H
