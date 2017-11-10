#include "PMenu.h"

PMenu::PMenu(const QString &title)
{
    text->setText(title);
    text->setFontSize(18);
    text->enableEllipsis(true);
    setup();
}

PMenu::PMenu(QPixmap pix)
{
    text->hide();
    pixmap = pix;
    icon = new CIcon(pixmap,QSize(22,22),this);
    icon->setColor(Qt::white);
    icon->enableColor(false);
    setup();
}



void PMenu::setup()
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

void PMenu::setActive(bool mode)
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



