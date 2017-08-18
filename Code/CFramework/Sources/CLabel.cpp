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

// Set label text
void CLabel::enableEllipsis( bool mode )
{
    localEllipsis = mode;
    setText(localText);
}

// Resize event
void CLabel::resizeEvent(QResizeEvent *)
{
    if(localEllipsis)
        setText(localText);
}

void CLabel::setup()
{
    setStyleSheet("font-size:19px;color:#444");
}
