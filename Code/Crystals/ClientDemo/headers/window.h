#ifndef WINDOW_H
#define WINDOW_H

#include "CApplication.h"
#include "CWindow.h"
#include "CLabel.h"
#include "CIcon.h"
#include "CPushButton.h"
#include "CMaterialIcon.h"
#include "CMenu.h"
#include "CMenuItem.h"
#include "CBlurWidget.h"

#include <QMouseEvent>
#include <QBoxLayout>
#include <QPushButton>
#include <QTimer>

class Window : public CWindow
{
    Q_OBJECT
public:
    Window();
    CPushButton *home = new CPushButton("Icon and Text",CMaterialIcon::pixmap("palette"));
    CPushButton *wel = new CPushButton(CMaterialIcon::pixmap("place"),this);

    CPushButton *a = new CPushButton(CMaterialIcon::pixmap("headset"),this);
    CPushButton *b = new CPushButton(CMaterialIcon::pixmap("time_to_leave"),this);
    CPushButton *c = new CPushButton(CMaterialIcon::pixmap("wifi"),this);
    CPushButton *d = new CPushButton(CMaterialIcon::pixmap("restaurant"),this);
    CPushButton *e = new CPushButton(CMaterialIcon::pixmap("power_settings_new"),this);

    CPushButton *cre = new CPushButton("Crear",CMaterialIcon::pixmap("add_circle_outline"));
    CPushButton *opa = new CPushButton("Opacidad",CMaterialIcon::pixmap("format_shapes"));
    CPushButton *mod = new CPushButton("Modo",CMaterialIcon::pixmap("swap_horiz"));
    CPushButton *blu = new CPushButton("Blur",CMaterialIcon::pixmap("blur_on"));
    CPushButton *tit = new CPushButton("Title",CMaterialIcon::pixmap("text_fields"));
    CPushButton *siz = new CPushButton("Resize",this);
    CPushButton *del = new CPushButton("Delete",CMaterialIcon::pixmap("delete"));

    QLabel *movieFrame = new QLabel(this);
    CIcon *logo = new CIcon(QPixmap("/home/e/inst.png"),QSize(200,200),this);
    //CMenu *menu = new CMenu();
    CMenuItem *item = new CMenuItem( "Options for a Better World, and a better Life, and Shut Up my friends you need to be quiet pleaseeeee!", CMaterialIcon::pixmap("format_shapes") );

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
