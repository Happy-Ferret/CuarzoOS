#ifndef TEXTMENU_H
#define TEXTMENU_H

#include "Headers.h"

class TextMenu : public QWidget
{
    Q_OBJECT
public:
    TextMenu(const QString &title);
    CLabel *text = new CLabel(this);
};

#endif // TEXTMENU_H
