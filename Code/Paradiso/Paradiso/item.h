#ifndef ITEM_H
#define ITEM_H

#include "headers.h"

class Item : public QWidget
{
public:
    Item();

    QHBoxLayout *layout = new QHBoxLayout(this);
    QLabel *icon = new QLabel();
    QPixmap image;
    QString path = "";

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

public slots:
    void readSettings();
    void setIcon();
    void setActive(bool option);

};

#endif // ITEM_H
