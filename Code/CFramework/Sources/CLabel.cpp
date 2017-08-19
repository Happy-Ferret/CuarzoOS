#include "CLabel.h"

// Constructor 1
CLabel::CLabel(QWidget *parent)
{
    setParent(parent);
    setup();
}

// Constructor 2
CLabel::CLabel(const QString &text,QWidget *parent)
{
    setParent(parent);
    setText(text);
    setup();
}

// Set label text
void CLabel::setText(const QString &text)
{
    localText = text;

    if(localEllipsis)
    {
        QFontMetrics metrics(font());
        QString elidedText = metrics.elidedText(text, Qt::ElideRight, width());
        QLabel::setText(elidedText);
    }
    else
    {
        QLabel::setText(text);
    }
}

void CLabel::setFontSize(uint size, const QString &units)
{
    _fontSize = QString::number(size) + units;
    resetStyle();
}

void CLabel::setFontFamily(const QString &family)
{
    _fontFamily = family;
    resetStyle();
}

void CLabel::setFontWeight(const QString &weight)
{
    _fontWeight = weight;
    resetStyle();
}

void CLabel::setFontStyle(const QString &style)
{
    _fontStyle = style;
    resetStyle();
}

void CLabel::setFontColor(QColor color)
{
    _fontColor = color;
    resetStyle();
}

// Set label text
void CLabel::enableEllipsis( bool mode )
{
    localEllipsis = mode;
    setText(localText);
}


void CLabel::resetStyle()
{
    setStyleSheet(
        "font-size:"+_fontSize +
        ";font-family:" + _fontFamily +
        ";font-weight:" + _fontWeight +
        ";font-style:" + _fontStyle +
        ";color:" + _fontColor.name()
   );
}

// Resize event
void CLabel::resizeEvent(QResizeEvent *)
{
    if(localEllipsis)
        setText(localText);
}

void CLabel::setup()
{
    resetStyle();
}
