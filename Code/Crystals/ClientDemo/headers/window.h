#ifndef WINDOW_H
#define WINDOW_H

#include "CApplication.h"
#include "CWindow.h"
#include "CLabel.h"
#include "CImage.h"
#include "CPushButton.h"


#include <QBoxLayout>
#include <QPushButton>
#include <QTimer>

class Window : public CWindow
{
    Q_OBJECT
public:
    Window();

    CPushButton *home = new CPushButton("Pico",this);
    CPushButton *wel = new CPushButton("Welcome",this);

    CPushButton *cre = new CPushButton("Crear",this);
    CPushButton *opa = new CPushButton("Opacidad",this);
    CPushButton *mod = new CPushButton("Modo",this);
    CPushButton *blu = new CPushButton("Blur",this);
    CPushButton *tit = new CPushButton("Title",this);
    CPushButton *siz = new CPushButton("Resize",this);
    CPushButton *del = new CPushButton("Delete",this);

    QHBoxLayout *layout = new QHBoxLayout(this);


public slots:
    void deleteWindow();
    void createWindow();
    void activateBlur();
    void changeOpacity();
    void changeMode();
    void changeTitle();
    void changeSize();
};

#endif // WINDOW_H
