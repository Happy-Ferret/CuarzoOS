#include "CIconButton.h"

CIconButton::CIconButton(QWidget *parent)
{
    setParent( parent );
    setScaledContents( true );
    setMouseTracking(true);
}

CIconButton::CIconButton(QPixmap active, QPixmap focus, QPixmap unfocus, QPixmap hover, QWidget *parent)
{
    setActivePixmap( active );
    setFocusPixmap( focus );
    setUnfocusPixmap( unfocus );
    setHoverPixmap( hover );

    setScaledContents(true);
    setMouseTracking(true);

    setPixmap( unfocus );
}

void CIconButton::setActivePixmap(QPixmap active)
{
    _active = active;
    setPixmap( _active);
}

void CIconButton::setFocusPixmap(QPixmap focus)
{
    _focus = focus;
}

void CIconButton::setUnfocusPixmap(QPixmap unfocus)
{
    _unfocus = unfocus;
}

void CIconButton::setHoverPixmap(QPixmap hover)
{
    _hover= hover;
}

void CIconButton::setWindowFocus(bool state)
{
    focus = state;

    if ( focus )
    {
        if ( !_focus.isNull() )
            setPixmap( _focus);
    }
    else
    {
        if ( !_unfocus.isNull() )
            setPixmap( _unfocus);
    }

}

void CIconButton::mousePressEvent(QMouseEvent *)
{
    pressing = true;

    if ( !_active.isNull() )
        setPixmap( _active);

    pressed();
}

void CIconButton::mouseReleaseEvent(QMouseEvent *)
{
    pressing = false;

    if( over )
    {
        if ( !_hover.isNull()  )
            setPixmap( _hover);
        clicked();
    }

    if( !over )
    {
        if( focus )
        {
            if( !_focus.isNull()  )
                setPixmap( _focus);
        }
        else
        {
            if( !_unfocus.isNull()  )
                setPixmap( _unfocus );
        }

    }


    released();
}

void CIconButton::enterEvent(QEvent *)
{
    over = true;

    if( !_hover.isNull()  )
        setPixmap( _hover);

    mouseOver();
}

void CIconButton::leaveEvent(QEvent *)
{
    if( !pressing && !_focus.isNull() )
    {
        if( focus )
        {
            if( !_focus.isNull()  )
                setPixmap( _focus );
        }
        else
        {
            if( !_unfocus.isNull()  )
                setPixmap( _unfocus );
        }
    }

}




