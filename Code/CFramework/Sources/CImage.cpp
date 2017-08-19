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
    update();
}

void CImage::setBorderRadius(uint radius)
{
    _borderRadius = radius;
    update();
}

void CImage::setImageColor(QColor color)
{
    _imageColor = color;
    update();
}

void CImage::setBorderColor(QColor color)
{
    _borderColor = color;
    update();
}

void CImage::setBorderWidth(uint width)
{
    _borderWidth = width;
    update();
}

void CImage::enableColor(bool mode)
{
    _colorEnabled = mode;
    update();
}

void CImage::setOpacity(float opacity)
{
    if(opacity > 1.0)
        opacity = 1.0;
    if(opacity < 0.0)
        opacity = 0.0;

    _opacity = opacity;
    update();
}

void CImage::paintEvent(QPaintEvent *)
{

    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    QBrush brush;
    _borderColor.setAlphaF(_opacity);
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
                color.setAlpha(im.pixelColor(x,y).alpha()*_opacity);
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


