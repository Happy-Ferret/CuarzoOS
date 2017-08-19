#include "titlebar.h"

TitleBar::TitleBar()
{
    setPalette(Qt::white);
    close = new TitleBarButton(QApplication::applicationDirPath() + "/../Resources/Images/window_close.png",this);
    minimize = new TitleBarButton(QApplication::applicationDirPath() + "/../Resources/Images/window_minimize.png",this);
    expand = new TitleBarButton(QApplication::applicationDirPath() + "/../Resources/Images/window_expand.png",this);

    close->setParent(this);
    minimize->setParent(this);
    expand->setParent(this);

    close->move(10,6);
    minimize->move(50,6);
    expand->move(90,6);

    setFixedHeight(40);

    close->show();

    show();
}


