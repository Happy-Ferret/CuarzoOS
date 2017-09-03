#include "CIconButton.h"

CIconButton::CIconButton(QWidget *parent)
{
    setParent( parent );
    setScaledContents( true );
    setMouseTracking(true);
}

CIconButton::CIconButton(QPixmap normal, QPixmap over, QPixmap pressed, QWidget *parent)
{
    setNormalPixmap( normal );
    setOverPixmap( over );
    setPressedPixmap( pressed );
    setScaledContents(true);
    setPixmap( _normalPixmap );
    setMouseTracking(true);
}

void CIconButton::setNormalPixmap(QPixmap normal)
{
    _normalPixmap = normal;
    setPixmap( _normalPixmap );
}

void CIconButton::setOverPixmap(QPixmap over)
{
    _overPixmap = over;
}

void CIconButton::setPressedPixmap(QPixmap pressed)
{
    _pressedPixmap = pressed;
}

void CIconButton::mousePressEvent(QMouseEvent *)
{
    pressing = true;

    if ( !_pressedPixmap.isNull() )
        setPixmap( _pressedPixmap );

    pressed();
}

void CIconButton::mouseReleaseEvent(QMouseEvent *)
{
    pressing = false;

    if( over )
    {
        if ( !_overPixmap.isNull()  )
            setPixmap( _overPixmap );
        clicked();
    }

    if( !over )
        if( !_normalPixmap.isNull()  )
            setPixmap( _normalPixmap );

    released();
}

void CIconButton::enterEvent(QEvent *)
{
    over = true;

    if( !_overPixmap.isNull()  )
        setPixmap( _overPixmap );

    mouseOver();
}

void CIconButton::leaveEvent(QEvent *)
{
    if( !pressing && !_normalPixmap.isNull() )
        setPixmap( _normalPixmap );
}
