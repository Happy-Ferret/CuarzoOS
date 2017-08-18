#include "menu.h"
Menu::Menu()
{
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setParent(0);
    layout->addWidget(frame);
    layout->setMargin(0);
    menuLayout->setContentsMargins(0,5,0,5);
    menuLayout->setSpacing(0);
    frame->setObjectName("fram");
    frame->setStyleSheet("#fram{border-radius:5px;background:#FFF;border-color:#CCC}");
}