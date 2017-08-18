#include "CPushButton.h"

CPushButton::CPushButton(QWidget *parent)
{
    QFrame::setParent(parent);
    setDisplayMode(CPushButton::textOnly);
    setPressAnimation(CPushButton::opacityAnimation);
    setIconPosition(CPushButton::left);
}

CPushButton::CPushButton(const QString &text, QWidget *parent)
{
    QFrame::setParent(parent);
    setDisplayMode(CPushButton::textOnly);
    setPressAnimation(CPushButton::opacityAnimation);
    setIconPosition(CPushButton::left);
    setText(text);

}

CPushButton::CPushButton(QPixmap icon, QWidget *parent)
{
    setup();
    QFrame::setParent(parent);

    setDisplayMode(CPushButton::iconOnly);
    setIcon(icon);
}

CPushButton::CPushButton(const QString &text, QPixmap icon, IconPosition position, QWidget *parent)
{
    setup();
    QFrame::setParent(parent);

    setDisplayMode(CPushButton::textAndIcon);
    setText(text);
    setIcon(icon);
}

void CPushButton::setDisplayMode(CPushButton::DisplayMode mode)
{
    _displayMode = mode;

    switch (mode) {
    case CPushButton::textOnly:

        break;
    default:
        break;
    }
}

void CPushButton::setPressAnimation(CPushButton::AnimationMode mode)
{

}

void CPushButton::setIconPosition(IconPosition position)
{

}

void CPushButton::setPressIcon(QPixmap icon)
{

}

void CPushButton::setIcon(QPixmap icon)
{

}

void CPushButton::setFontFamily(QString family)
{

}

void CPushButton::setFontSize(uint size)
{

}

void CPushButton::setFontWeight(QString weight)
{

}

void CPushButton::setTextColor(QColor color)
{

}

void CPushButton::setText(const QString &text)
{

}

void CPushButton::showBackground(bool mode)
{

}

void CPushButton::setBorderRadius(uint radius)
{

}

void CPushButton::setPressBackgroundColor(QColor color)
{

}

void CPushButton::setPressBorderColor(QColor color)
{

}

void CPushButton::setPressTextColor(QColor color)
{

}

void CPushButton::setup()
{

}

