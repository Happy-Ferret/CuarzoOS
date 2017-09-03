#ifndef CICONBUTTON_H
#define CICONBUTTON_H

#include <QLabel>

class CIconButton : public QLabel
{
    Q_OBJECT

public:
    CIconButton( QWidget *parent = nullptr );
    CIconButton( QPixmap normal, QPixmap over, QPixmap pressed, QWidget *parent = nullptr );

    void setNormalPixmap( QPixmap normal );
    void setOverPixmap( QPixmap over );
    void setPressedPixmap( QPixmap pressed );

    QPixmap normalPixmap() { return _normalPixmap;}
    QPixmap overPixmap() { return _overPixmap;}
    QPixmap pressedPixmap() { return _pressedPixmap;}

private:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);

    bool over = false;
    bool pressing = false;

    QPixmap _normalPixmap, _overPixmap, _pressedPixmap;

signals:
    void mouseOver();
    void released();
    void pressed();
    void clicked();
};

#endif // CICONBUTTON_H
