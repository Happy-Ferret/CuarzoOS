#include "CMenuItem.h"
#include "QDebug"

CMenuItem::CMenuItem()
{
    setMouseTracking(true);
    setup();
}

CMenuItem::CMenuItem(const QString &text)
{
    setMouseTracking(true);
    setup();
    setText( text );
}

CMenuItem::CMenuItem(const QString &text, const QPixmap &icon)
{
    setMouseTracking(true);
    setup();
    setText( text );
    setIcon( icon );
}

CMenuItem::CMenuItem(const QString &text, const QPixmap &icon, const QString &shortcut)
{
    setMouseTracking(true);
    setup();
    setText( text );
    setIcon( icon );
    setShortcut( shortcut );
}

void CMenuItem::setIcon(const QPixmap &ico)
{
    iconSpace->changeSize( 0, 0 );
    icon->setPixmap( ico );
    icon ->show();
}

void CMenuItem::setText(const QString &text)
{
    label->setText( text );
    label->show();
}

void CMenuItem::setShortcut(const QString &shortcu)
{
    shortcut = shortcu;
}

void CMenuItem::setEnabled(bool mode)
{
    _enabled = mode;

    if( mode )
    {
        icon->setColor( QColor(DEEP_GRAY) );
        arrow->setColor( QColor(DEEP_GRAY) );
        label->setFontColor( QColor(DEEP_GRAY) );
    }
    else
    {
        icon->setColor( QColor(GRAY) );
        arrow->setColor( QColor(GRAY) );
        label->setFontColor( QColor(GRAY) );
    }
}

void CMenuItem::setActive(bool mode)
{
    if( mode )
    {
        if( enabled() )
        {
            setAutoFillBackground(true);
            icon->setColor( Qt::white );
            arrow->setColor( Qt::white );
            label->setFontColor( Qt::white );
        }
    }
    else
    {
        if( enabled() )
        {
            setAutoFillBackground(false);
            icon->setColor( QColor(DEEP_GRAY) );
            arrow->setColor( QColor(DEEP_GRAY) );
            label->setFontColor( QColor(DEEP_GRAY) );
        }
    }
}

void CMenuItem::mousePressEvent(QMouseEvent *)
{

}

void CMenuItem::mouseReleaseEvent(QMouseEvent *)
{

}


void CMenuItem::enterEvent(QEvent *e)
{
    setActive(true);
}

void CMenuItem::leaveEvent(QEvent *)
{
    setActive(false);
}

void CMenuItem::setup()
{

    setPalette( QColor( LIGHT_BLUE ) );

    layout->setMargin(6);
    layout->setSpacing(6);
    layout->setAlignment( icon, Qt::AlignCenter );
    layout->setAlignment( label, Qt::AlignLeft );
    layout->setAlignment( arrow, Qt::AlignRight );
    layout->addSpacerItem( iconSpace );

    icon->setColor( QColor(GRAY) );
    arrow->setColor( QColor(DEEP_GRAY) );
    label->setFontColor( QColor(DEEP_GRAY) );
    icon->setFixedSize( 24, 24 );
    label->enableEllipsis( true );
    label->setFontSize( 18 );

    layout->addWidget( icon );
    layout->addWidget( label );
    layout->addWidget( arrow );

    icon->hide();
    label->hide();
    arrow->hide();

}
















