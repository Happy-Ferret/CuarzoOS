#include "Menu.h"

Menu::Menu(const QString &title)
{
    text->setText(title);
    text->setFontSize(18);
    text->enableEllipsis(true);
    setup();
}

Menu::Menu(QPixmap pix)
{
    text->hide();
    pixmap = pix;
    icon = new CIcon(pixmap,QSize(22,22),this);
    icon->setColor(Qt::white);
    icon->enableColor(false);
    setup();
}



void Menu::setup()
{
    setMouseTracking(true);
    setPalette( QColor(LIGHT_BLUE) );
    layout->addWidget(text);

    if( icon != nullptr)
        layout->addWidget(icon);

    layout->setContentsMargins(10,0,10,0);
    layout->setSpacing(0);

    setMaximumWidth(200);
}

void Menu::setActive(bool mode)
{
    if( mode )
    {
        if( icon == nullptr )
        {
            text->setFontColor( Qt::white );
        }
        else
        {
            icon->enableColor(true);
        }
        setAutoFillBackground(true);
    }
    else
    {
        if( icon == nullptr )
        {
            text->setFontColor( QColor(DEEP_GRAY) );
        }
        else
        {
            icon->enableColor(false);
        }
        setAutoFillBackground(false);
    }
}



