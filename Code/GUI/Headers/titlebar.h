#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "CWindow.h"
#include <QHBoxLayout>
#include <QApplication>
#include "CLabel.h"


class TitleBar : public CLabel
{
    Q_OBJECT

public:
    TitleBar();
    uint surfaceID;
    uint processID;

    void setFixedWidth(int size);
};

#endif // TITLEBAR_H
