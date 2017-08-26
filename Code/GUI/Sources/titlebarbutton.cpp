#include "titlebarbutton.h"


TitleBarButton::TitleBarButton(const QString &path, QWidget *parent)
{
    setParent(parent);
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(animate()));
    connect(opacityTimer,SIGNAL(timeout()),this,SLOT(animateOpacity()));
    setGraphicsEffect(opacity);
    opacity->setOpacity(1.0);
    setPixmap(QPixmap(path));
    setScaledContents(true);
    resize(22,22);
    show();
}

void TitleBarButton::enterEvent(QEvent *)
{
    scale = 1;
    initialPosition = pos();
    animationTimer->start(5);
    mouseOver = true;
}

void TitleBarButton::leaveEvent(QEvent *)
{
    scale = -1;
    animationTimer->start(5);
    mouseOver = false;
}

void TitleBarButton::mousePressEvent(QMouseEvent *)
{
    pressing = true;
    opacityScale = -0.01;
    opacityTimer->start(1);
}

void TitleBarButton::mouseReleaseEvent(QMouseEvent *)
{
    pressing = false;
    opacityScale = 0.01;
    opacityTimer->start(1);
}

void TitleBarButton::animate()
{
    if(scale > 0)
    {
        if(width() >= big)
        {
            resize(QSize(big,big));
            move(initialPosition - QPoint((big-small)/2,(big-small)/2));
        }
        else
        {
            resize(size() + QSize(2,2));
            move(pos() - QPoint(1,1));
            animationTimer->start(5);
        }
    }
    else
    {
        if(width() <= small)
        {
            resize(QSize(small,small));
            move(initialPosition);
        }
        else
        {
            resize(size() - QSize(2,2));
            move(pos() + QPoint(1,1));
            animationTimer->start(5);
        }
    }
}

void TitleBarButton::animateOpacity()
{
    if(opacityScale < 0)
    {
        if(opacity->opacity() < 0.6)
        {
            opacityScale = 0.6;
        }
        else
        {
            opacity->setOpacity(opacity->opacity() + opacityScale);
            opacityTimer->start(1);
        }
    }
    else
    {
        if(opacity->opacity() > 1.0)
        {
            opacity->setOpacity(1.0);
        }
        else
        {
            if(!pressing)
            {
                opacity->setOpacity(opacity->opacity() + opacityScale);
                opacityTimer->start(1);
            }
        }
    }
}
