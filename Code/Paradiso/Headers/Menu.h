#ifndef MENU_H
#define MENU_H

#include "Headers.h"

// A topbar menu (Text or Icon)

class Menu : public QWidget
{
    Q_OBJECT

public:

    Menu(const QString &title);
    Menu(QPixmap pix);

    void setup();

    QHBoxLayout *layout = new QHBoxLayout(this);
    CLabel *text = new CLabel(this);
    CIcon *icon = nullptr;
    QPixmap pixmap;

private:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif // TEXTMENU_H
