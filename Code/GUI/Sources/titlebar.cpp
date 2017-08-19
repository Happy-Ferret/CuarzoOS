#include "titlebar.h"

TitleBar::TitleBar()
{
    close = new TitleBarButton(QApplication::applicationDirPath() + "/../Resources/Images/window_close.png",this);
    minimize = new TitleBarButton(QApplication::applicationDirPath() + "/../Resources/Images/window_minimize.png",this);
    expand = new TitleBarButton(QApplication::applicationDirPath() + "/../Resources/Images/window_expand.png",this);

    close->setParent(this);
    minimize->setParent(this);
    expand->setParent(this);

    close->move(10,10);
    minimize->move(50,10);
    expand->move(90,10);

    close->show();

    show();
}


