#include "CImage.h"

CImage::CImage(QWidget *parent)
{
     setParent(parent);
}

CImage::CImage(QPixmap image, QWidget *parent)
{
    setParent(parent);
    setImage(image);
}

CImage::CImage(QPixmap image, QSize size, QWidget *parent)
{
    setParent(parent);
    setFixedSize(size);
    setImage(image);
}

CImage::CImage(QPixmap image, QColor color, QWidget *parent)
{
    setParent(parent);
    _image = image;
    setImageColor(color);
}

void CImage::setImage(QPixmap image)
{
    _image = image;
    repaint();
}

void CImage::setBorderRadius(uint radius)
{
    _borderRadius = radius;
    repaint();
}

void CImage::setImageColor(QColor color)
{
    _imageColor = color;
    repaint();
}

void CImage::setBorderColor(QColor color)
{
    _borderColor = color;
    repaint();
}

void CImage::setBorderWidth(uint width)
{
    _borderWidth = width;
    repaint();
}

void CImage::enableColor(bool mode)
{
    _colorEnabled = mode;
    repaint();
}

void CImage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    QBrush brush;
    QPen pen = QPen(_borderColor);
    pen.setWidth(_borderWidth);
    painter->setPen(pen);

    if(_colorEnabled)
    {
        QImage im = _image.scaled(size()).toImage();

        for(int y = 0; y < im.height(); y++)
        {
            for(int x= 0; x < im.width(); x++)
            {
                QColor color = _imageColor;
                color.setAlpha(im.pixelColor(x,y).alpha());
                im.setPixelColor(x,y,color);
            }
        }
        brush = QBrush(im);
    }
    else
    {
        brush = QBrush(_image.scaled(size()));
    }

    painter->setBrush(brush);
    painter->drawRoundedRect(QRect(0,0,width(),height()), _borderRadius, _borderRadius);
}
