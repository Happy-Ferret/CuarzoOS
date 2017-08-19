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

    setDisplayMode(CPushButton::iconOnly);
    setIcon(icon);
}

CPushButton::CPushButton(const QString &text, QPixmap icon, IconPosition position, QWidget *parent)
{
    setup();
    QFrame::setParent(parent);
    setTextColor(QColor("#444"));
    setFrameColor(QColor("#DDD"));
    setDisplayMode(CPushButton::textAndIcon);
    setText(text);
    setIcon(icon);
}

void CPushButton::setDisplayMode(CPushButton::DisplayMode mode)
{
    _displayMode = mode;

    switch (mode) {
    case CPushButton::textOnly:
        _icon->hide();
        _text->show();
        resetStyle();
        break;
    case CPushButton::textAndIcon:
        _icon->show();
        _text->show();
        resetStyle();
        break;
    case CPushButton::iconOnly:
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
    }
    else
    {
        layout->addWidget(_text);
        layout->addWidget(_icon,1);
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
    animState = 0;
    pressing = true;
    timer->start(1);
}

void CPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    released();
    clicked(_mouseOver);
    pressing = false;
    timer->start(1);
}

void CPushButton::animate()
{
     if(animState == 0)
    {
         if(_opacity->opacity()< 0.6)
         {
             animState = 1;
             _opacity->setOpacity(0.6);
         }
         else
         {
             _opacity->setOpacity(_opacity->opacity() - 0.005);
             timer->start(1);
         }
    }
    if(animState == 1 && !pressing)
    {
         if(_opacity->opacity()> 1.0)
         {
             _opacity->setOpacity(1.0);
         }
         else
         {
             _opacity->setOpacity(_opacity->opacity() + 0.005);
             timer->start(1);
         }
    }
}

void CPushButton::setup()
{
    layout->setContentsMargins(10,6,10,6);
    layout->setSpacing(6);
    layout->addWidget(_icon);
    layout->addWidget(_text);

    _text->setFontColor(_textColor);
    _text->setFontFamily("Coves");
    _text->setFontWeight("bold");
    _text->enableEllipsis(true);
    _text->setAlignment(Qt::AlignCenter);

    _icon->setScaledContents(true);
    _opacity->setOpacity(1.0);

    setGraphicsEffect(_opacity);
    setMouseTracking(true);
    setDisplayMode(CPushButton::textOnly);
    setIconPosition(CPushButton::left);

    connect(timer,SIGNAL(timeout()),this,SLOT(animate()));
}

void CPushButton::resetStyle()
{
    if(_frameless == false && (_displayMode == CPushButton::textOnly || _displayMode == CPushButton::textAndIcon))
    {
        QColor  color = _frameColor;
        QColor colorPlus = _frameColor;
        int variation = 10;
        int lessVariation = 20;

        if(_frameColor.red() + variation  > 255) { colorPlus.setRed(255);}
        else { colorPlus.setRed(_frameColor.red() + variation ); }
        if(_frameColor.green() + variation  > 255) { colorPlus.setGreen(255); }
        else { colorPlus.setGreen(_frameColor.green() + variation ); }
        if(_frameColor.blue() + variation  > 255) { colorPlus.setBlue(255); }
        else { colorPlus.setBlue(_frameColor.blue() + variation ); }

        if(_mouseOver)
            color = colorPlus;

        QColor colorLess = _frameColor;

        if(_frameColor.red() - lessVariation < 0) { colorLess.setRed(0); }
        else { colorLess.setRed(_frameColor.red() - lessVariation ); }
        if(_frameColor.green() - lessVariation  < 0) { colorLess.setGreen(255); }
        else { colorLess.setGreen(_frameColor.green() - lessVariation); }
        if(_frameColor.blue() - lessVariation  < 0) { colorLess.setBlue(0); }
        else { colorLess.setBlue(_frameColor.blue() - lessVariation ); }

        setStyleSheet(
            "CPushButton{border-color:"+colorLess.name()+
            ";background:qlineargradient( x1:0 y1:0, x2:0 y2:1, stop:0 "+colorPlus.name()+
            ", stop:1 "+color.name()+
            ");border-radius:"+QString::number(_borderRadius)+"px;border-width:1px;border-style:solid}"
        );
    }
    else
    {
        setStyleSheet("");
    }
}


