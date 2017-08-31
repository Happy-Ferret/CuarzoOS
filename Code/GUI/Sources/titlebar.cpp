#include "titlebar.h"

TitleBar::TitleBar()
{
    setFontWeight("light");
    setFontSize(15);
    setFontColor(QColor("#666"));
    setAlignment(Qt::AlignCenter);
    enableEllipsis(true);
    setFixedHeight(32);

    show();
}



