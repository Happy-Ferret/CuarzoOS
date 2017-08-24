#include "titlebar.h"

TitleBar::TitleBar()
{
    // Titlebar  background color
    setPalette(Qt::white);

    // Create the buttons
    close = new TitleBarButton(QApplication::applicationDirPath() + "/../Resources/Images/window_close.png",this);
    minimize = new TitleBarButton(QApplication::applicationDirPath() + "/../Resources/Images/window_minimize.png",this);
    expand = new TitleBarButton(QApplication::applicationDirPath() + "/../Resources/Images/window_expand.png",this);

    // Asign parents
    close->setParent(this);
    minimize->setParent(this);
    expand->setParent(this);

    title->setFontWeight("bold");
    title->setFontColor(QColor("#666"));
    title->setAlignment(Qt::AlignCenter);
    title->enableEllipsis(true);
    title->setParent(this);
    title->show();

    // Set buttons positions
    close->move(10,6);
    minimize->move(50,6);
    expand->move(90,6);

    // Set titlebar size
    setFixedHeight(40);

    show();
}

void TitleBar::setFixedWidth(int size)
{
    QWidget::setFixedWidth(size);
    title->move(150,13);
    title->setFixedWidth(width() - 300);
}


