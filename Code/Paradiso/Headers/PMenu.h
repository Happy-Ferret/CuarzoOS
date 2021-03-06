#ifndef MENU_H
#define MENU_H

#include "Headers.h"

// A topbar menu (Text or Icon)

class PMenu : public QWidget
{
    Q_OBJECT

public:

    PMenu(const QString &title);
    PMenu(QPixmap pix);

    void setup();
    void setActive( bool mode );

    QHBoxLayout *layout = new QHBoxLayout(this);
    CLabel *text = new CLabel(this);
    CIcon *icon = nullptr;
    QPixmap pixmap;

};

#endif // TEXTMENU_H
