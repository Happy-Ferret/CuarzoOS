#include "Menu.h"

Menu::Menu(const QString &title)
{
    text->setText(title);
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
    setPalette( QColor(LIGHT_BLUE) );
    layout->addWidget(text);

    if( icon != nullptr)
        layout->addWidget(icon);

    layout->setMargin(0);
    layout->setSpacing(0);

    setMaximumWidth(200);
}

void Menu::mousePressEvent(QMouseEvent *)
{
    icon->enableColor(true);
    setAutoFillBackground(true);
}

void Menu::mouseReleaseEvent(QMouseEvent *)
{
    icon->enableColor(false);
    setAutoFillBackground(false);
}


