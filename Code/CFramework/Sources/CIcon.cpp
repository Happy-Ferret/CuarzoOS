#include "CIcon.h"


CIcon::CIcon(QWidget *parent)
{
    setParent(parent);
}

CIcon::CIcon(const QPixmap &icon, QWidget *parent)
{
    setParent(parent);
    setPixmap(icon);
    setup();
}

CIcon::CIcon(const QPixmap &icon, const QSize &size, QWidget *parent)
{
    setParent(parent);
    setFixedSize(size);
    setPixmap(icon);
    setup();

}

void CIcon::setPixmap(const QPixmap &icon)
{
    _pixmap = icon;

    if( colorEnabled() )
    {
        setColor(_color);
    }
    else
    {
        QLabel::setPixmap(_pixmap);
    }

}

void CIcon::setColor(const QColor &color)
{
    QImage newPix = _pixmap.toImage();
    _colorEnabled = true;
    _color = color;

    for (int x = 0; x < newPix.width(); x++)
    {
        for (int y = 0; y < newPix.height(); y++)
        {
            _color.setAlpha(newPix.pixelColor( x, y ).alpha() );
            newPix.setPixelColor( x, y, _color);
        }
    }

    _coloredPixmap = QPixmap::fromImage(newPix);

    QLabel::setPixmap(_coloredPixmap);
}

void CIcon::enableColor(bool mode)
{
    _colorEnabled = mode;

    if( mode )
    {
         QLabel::setPixmap(_coloredPixmap);
    }
    else
    {
        QLabel::setPixmap(_pixmap);
    }
}

void CIcon::setup()
{
    setScaledContents(true);
    _coloredPixmap = _pixmap;
}


