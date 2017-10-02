#ifndef MENU_H
#define MENU_H

#include "Headers.h"

class Menu : public QWidget
{
    Q_OBJECT

public:

    Menu(const QString &title);
    Menu(QPixmap pix);

    void setup();

    QHBoxLayout *layout = new QHBoxLayout(this);
    CLabel *text = new CLabel(this);
    CImage *icon = nullptr;
    QPixmap pixmap;

};

#endif // TEXTMENU_H
