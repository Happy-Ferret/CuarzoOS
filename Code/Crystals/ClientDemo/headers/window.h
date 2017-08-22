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

    CPushButton *mov = new CPushButton("Mover");
    CPushButton *home = new CPushButton("Pico");
    CPushButton *wel = new CPushButton("Welcome");

    QPushButton *cre = new QPushButton("Crear");
    QPushButton *opa = new QPushButton("Opacidad");
    QPushButton *mod = new QPushButton("Modo");
    QPushButton *blu = new QPushButton("Blur");
    QPushButton *tit = new QPushButton("Change the beautiful Title");
    QPushButton *siz = new QPushButton("Resize");
    QPushButton *del = new QPushButton("Delete");

    CLabel *label = new CLabel("CuarzoOS is cool!");
    //CImage *image = new CImage(QPixmap("/home/e/icon.svg"),QSize(100,100));

    QHBoxLayout *layout = new QHBoxLayout(this);
    QTimer *time = new QTimer(this);
    bool movee = false;
    void mouseMoveEvent(QMouseEvent *)
    {
        if(movee) move(QCursor::pos()+QPoint(-100,-100));
    }

public slots:
    void moveWindow();
    void deleteWindow();
    void createWindow();
    void activateBlur();
    void changeOpacity();
    void changeMode();
    void changeTitle();
    void changeSize();
    void timeStopped();
};

#endif // WINDOW_H
