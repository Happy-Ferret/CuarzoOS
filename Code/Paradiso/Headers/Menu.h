#ifndef MENU_H
#define MENU_H

#include "Headers.h"

class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(const QString &title);
    Menu(QPixmap icon);
    CLabel *text = new CLabel(this);
    QPixmap icon;

};

#endif // TEXTMENU_H
