#ifndef TITLEBARBUTTON_H
#define TITLEBARBUTTON_H

#include <QTimer>
#include <QGraphicsOpacityEffect>
#include "QLabel"

class TitleBarButton : public QLabel{
    Q_OBJECT

public:
    TitleBarButton(const QString &path, QWidget *parent = nullptr);
    QTimer *animationTimer = new QTimer(this);
    QTimer *opacityTimer = new QTimer(this);
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    float opacityScale = 0.01;
    int scale = 1;
    int big = 24;
    int small = 22;
    bool mouseOver =  false;
    bool pressing = false;
    QPoint initialPosition;
public slots:
    void animate();
    void animateOpacity();
};

#endif // TITLEBARBUTTON_H
