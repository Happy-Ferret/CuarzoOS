#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "CWindow.h"
#include "titlebarbutton.h"
#include <QHBoxLayout>
#include <QApplication>
#include "CLabel.h"


class TitleBar : public CWindow
{
    Q_OBJECT

public:
    TitleBar();
    TitleBarButton *close, *minimize, *expand;
    CLabel *title = new CLabel("Untitled");
    uint surfaceID;
    uint processID;


};

#endif // TITLEBAR_H
