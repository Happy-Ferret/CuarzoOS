#ifndef TOPBAR_H
#define TOPBAR_H

#include "headers.h"
#include "item.h"

class TopBar : public QWidget
{
    Q_OBJECT
public:
    TopBar();
    QHBoxLayout *layout = new QHBoxLayout(this);
    QVariantList launchItems;

signals:

public slots:
    void refreshSize();
    void readSettings();
    void openItem(QString path);
};

#endif // TOPBAR_H
