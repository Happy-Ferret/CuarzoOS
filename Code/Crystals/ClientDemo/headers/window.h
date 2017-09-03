#ifndef WINDOW_H
#define WINDOW_H

#include "CApplication.h"
#include "CWindow.h"
#include "CLabel.h"
#include "CImage.h"
#include "CPushButton.h"

#include <QMouseEvent>
#include <QBoxLayout>
#include <QPushButton>
#include <QTimer>

class Window : public CWindow
{
    Q_OBJECT
public:
    Window();
    CPushButton *home = new CPushButton("Icon and Text",QPixmap("/home/e/icon.svg"));
    CPushButton *wel = new CPushButton(QPixmap("/home/e/icon.svg"),this);

    CPushButton *cre = new CPushButton("Crear",this);
    CPushButton *opa = new CPushButton("Opacidad",this);
    CPushButton *mod = new CPushButton("Modo",this);
    CPushButton *blu = new CPushButton("Blur",this);
    CPushButton *tit = new CPushButton("Title",this);
    CPushButton *siz = new CPushButton("Resize",this);
    CPushButton *del = new CPushButton("Delete",this);

    QLabel *movieFrame = new QLabel(this);

    QWidget *widget = new QWidget(this);

    QHBoxLayout *layout = new QHBoxLayout(widget);

private:
    virtual void mouseMoveEvent(QMouseEvent*e);

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
