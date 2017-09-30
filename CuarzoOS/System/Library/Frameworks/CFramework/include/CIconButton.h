#ifndef CICONBUTTON_H
#define CICONBUTTON_H

#include <QLabel>
#include <QEvent>

class CIconButton : public QLabel
{
    Q_OBJECT

public:
    CIconButton( QWidget *parent = nullptr );
    CIconButton( QPixmap active, QPixmap focus, QPixmap unfocus, QPixmap hover, QWidget *parent = nullptr );

    void setActivePixmap( QPixmap active );
    void setFocusPixmap( QPixmap focus );
    void setUnfocusPixmap( QPixmap unfocus );
    void setHoverPixmap( QPixmap hover);

    void setWindowFocus( bool focus );

    QPixmap activePixmap() { return _active;}
    QPixmap focusPixmap() { return _focus;}
    QPixmap unfocusPixmap() { return _unfocus;}
    QPixmap hoverPixmap() { return _hover;}


private:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);

    bool over = false;
    bool pressing = false;
    bool focus = false;

    QPixmap _active, _focus, _hover,_unfocus;


signals:
    void mouseOver();
    void released();
    void pressed();
    void clicked();
};

#endif // CICONBUTTON_H
