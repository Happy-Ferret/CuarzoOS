#include "CMenu.h"
#include <QDebug>

CMenu::CMenu()
{
    setup();
}

CMenu::CMenu(const QString &title)
{
    setTitle( title );
    setup();
}

void CMenu::setTitle(const QString &title)
{
    _title = title;
}

void CMenu::show(const QPoint &pos)
{
    move( pos );
    CWindow::show();
}

void CMenu::insertItem(QWidget *item)
{
    layout->addWidget(item);

}

void CMenu::insertItemAt(QWidget *item, uint index)
{
    layout->insertWidget( index, item );
}

void CMenu::removeItem(QWidget *item)
{
    layout->removeWidget( item );
}

void CMenu::setup()
{
    setParent( nullptr );
    setCentralWidget(widget);
    CWindow::hide();
    layout->setSpacing( 0 );
    layout->setContentsMargins( 0, 10, 0, 10);
    setMinimumWidth(  200 );
    setMaximumWidth( 500 );
    setMode( MENU_MODE );
}


