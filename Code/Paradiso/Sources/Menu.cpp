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
    icon = new CImage(pixmap,QSize(22,22),this);
    setup();
}

void Menu::setup()
{
    layout->addWidget(text);
    if( icon != nullptr)
        layout->addWidget(icon);
    layout->setMargin(0);
    layout->setSpacing(0);

    setMaximumWidth(200);
}


