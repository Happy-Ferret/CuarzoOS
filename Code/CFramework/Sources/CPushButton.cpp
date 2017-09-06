#include "CPushButton.h"

CPushButton::CPushButton(QWidget *parent)
{
    QFrame::setParent(parent);
    setup();
}

CPushButton::CPushButton(const QString &text, QWidget *parent)
{
    QFrame::setParent(parent);
    setup();
    setDisplayMode(CPushButton::textOnly);
    setText(text);
}

CPushButton::CPushButton(QPixmap icon, QWidget *parent)
{
    QFrame::setParent(parent);
    setup();
    setFixedSize(32,32);
    setDisplayMode(CPushButton::iconOnly);
    setIcon(icon);
    enableIconColor(true);
    setIconColor(_iconColor);
    layout->setStretch(0,0);
    layout->setStretch(1,0);
    _text->hide();
}

CPushButton::CPushButton(const QString &text, QPixmap icon, IconPosition position, QWidget *parent)
{
    setup();
    QFrame::setParent(parent);
    setDisplayMode(CPushButton::textAndIcon);
    setIcon(icon);
    enableIconColor(true);
    _icon->setFixedSize(22,22);
    _text->enableEllipsis(true);
    setIconColor(QColor("#FFFFFF"));
    setTextColor(QColor("#FFFFFF"));
    setFrameColor(QColor(BLUE));
    setText(text);
}

void CPushButton::setDisplayMode(CPushButton::DisplayMode mode)
{
    _displayMode = mode;

    switch (mode) {
    case CPushButton::textOnly:
        _text->setAlignment(Qt::AlignCenter);
        _icon->hide();
        _text->show();
        resetStyle();
        break;
    case CPushButton::textAndIcon:
        layout->setContentsMargins(10,4,10,4);
        layout->setSpacing(4);
        layout->setAlignment(Qt::AlignCenter);
        _icon->setAlignment(Qt::AlignLeft);
        _icon->show();
        _text->show();
        _text->setAlignment(Qt::AlignCenter);
        resetStyle();
        break;
    case CPushButton::iconOnly:
        layout->setMargin(4);
        layout->setSpacing(0);
        layout->setAlignment(Qt::AlignCenter);
        _icon->setAlignment(Qt::AlignCenter);
        _icon->show();
        _text->show();
        resetStyle();
        break;
    default:
        break;
    }
}

void CPushButton::setIconPosition(IconPosition position)
{

    layout->takeAt(0);
    layout->takeAt(1);

    if(position == CPushButton::left)
    {
        layout->addWidget(_icon);
        layout->addWidget(_text,1);
        _text->setAlignment(Qt::AlignLeft);
    }
    else
    {
        layout->addWidget(_text);
        layout->addWidget(_icon,1);
        _text->setAlignment(Qt::AlignRight);
    }
}


void CPushButton::setIcon(QPixmap icon)
{
    _pixmap = icon;
    _icon->setPixmap(icon);
}

void CPushButton::setIconColor(QColor color)
{
    _iconColor = color;

    if(_pixmap.isNull())
        return;

    if(_iconColorEnabled)
    {
        QImage tmp = _pixmap.toImage();

        for(int y = 0; y < tmp.height(); y++)
        {
            for(int x= 0; x < tmp.width(); x++)
            {
                _iconColor.setAlpha(tmp.pixelColor(x,y).alpha());
                tmp.setPixelColor(x,y,_iconColor);
            }
        }
        _icon->setPixmap(QPixmap::fromImage(tmp));
    }
    else
    {
        _icon->setPixmap(_pixmap);
    }
}

void CPushButton::setIconSize(const QSize &size)
{
    _icon->setFixedSize(size);
}

void CPushButton::enableIconColor(bool mode)
{
    _iconColorEnabled = mode;
    setIconColor(_iconColor);
}

void CPushButton::setFontFamily(const QString &family)
{
    _text->setFontFamily(family);
}


void CPushButton::setFontSize(uint size, const QString &units)
{
    _text->setFontSize(size,units);
}

void CPushButton::setFontWeight(const QString &weight)
{
    _text->setFontWeight(weight);
}

void CPushButton::setTextColor(QColor color)
{
    _text->setFontColor(color);
}

void CPushButton::setText(const QString &text)
{
    _text->setText(text);
}

void CPushButton::setBorderWidth(uint width)
{
    _borderWidth = width;
    resetStyle();
}

void CPushButton::setBorderRadius(uint radius)
{
    _borderRadius = radius;
    resetStyle();
}

void CPushButton::setFrameless(bool mode)
{
    _frameless = mode;
    resetStyle();
}

void CPushButton::setFrameColor(QColor color)
{
    _frameColor = color;
    resetStyle();
}

void CPushButton::enterEvent(QEvent *)
{
    _mouseOver = true;
    resetStyle();
    mouseEnter();
}

void CPushButton::leaveEvent(QEvent *)
{
    _mouseOver = false;
    resetStyle();
    mouseLeave();
}

void CPushButton::mousePressEvent(QMouseEvent *event)
{
    pressed();
    pressing = true;
    resetStyle();
}

void CPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    released();
    clicked(_mouseOver);
    pressing = false;
    resetStyle();
}



void CPushButton::setup()
{
    layout->setContentsMargins(12,8,12,8);
    layout->setSpacing(6);
    layout->addWidget(_icon);
    layout->addWidget(_text);

    _text->setFontColor(_textColor);
    _text->setFontFamily("Lucida");
    _text->setFontWeight("bold");
    _text->enableEllipsis(true);
    _text->setAlignment(Qt::AlignCenter);


    _icon->setScaledContents(true);

    _shadow->setOffset(0);
    _shadow->setBlurRadius(5);
    _shadow->setColor( QColor( GRAY ) );
    setFixedHeight(33);
    setGraphicsEffect(_shadow);

    _icon->setMouseTracking(true);
    _text->setMouseTracking(true);
    setMouseTracking(true);

    setDisplayMode(CPushButton::textOnly);
    setIconPosition(CPushButton::left);

}

void CPushButton::resetStyle()
{
    if( _frameless )
        setStyleSheet( NULL );
    else
    {
        if ( pressing )
            setStyleSheet("CPushButton{background-color:"+_frameColor.darker(110).name()+";border-radius:"+QString::number(_borderRadius)+"px;}");
        else if ( _mouseOver )
            setStyleSheet("CPushButton{background-color:"+_frameColor.lighter(110).name()+";border-radius:"+QString::number(_borderRadius)+"px;}");
        else
            setStyleSheet("CPushButton{background-color:"+_frameColor.name()+";border-radius:"+QString::number(_borderRadius)+"px;}");

    }

}


