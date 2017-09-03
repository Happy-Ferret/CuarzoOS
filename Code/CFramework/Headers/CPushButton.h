#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include "CLabel.h"
#include "CCore.h"
#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>
#include <QTimer>


class CPushButton : public QFrame
{
    Q_OBJECT
public:

    enum DisplayMode{textOnly,iconOnly,textAndIcon};
    enum IconPosition{left,right};

    CPushButton(QWidget *parent = nullptr);
    CPushButton(const QString &text, QWidget *parent = nullptr);
    CPushButton(QPixmap icon, QWidget *parent = nullptr);
    CPushButton(const QString &text, QPixmap icon, IconPosition position = CPushButton::left, QWidget *parent = nullptr);

    void setDisplayMode(DisplayMode mode);

    void setIconPosition(IconPosition  position);
    void setIcon(QPixmap icon);
    void setIconColor(QColor color);
    void setIconSize(const QSize &size);
    void enableIconColor(bool mode);

    void setFontFamily(const QString &family);
    void setFontSize(uint size,const QString &units = "px");
    void setFontWeight(const QString &weight);
    void setTextColor(QColor color);
    void setText(const QString &text);

    void setBorderWidth(uint width);
    void setBorderRadius(uint radius);
    void setFrameless(bool mode);

    void setFrameColor(QColor color);

    QHBoxLayout *buttonLayout(){return layout;}
    CLabel *label(){ return _text; }
    QLabel *icon(){ return _icon; }


signals:
    void mouseEnter();
    void mouseLeave();
    void pressed();
    void released();
    void doubleClicked();
    void clicked(bool);

private:
    void setup();
    void resetStyle();

    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent*);
    virtual void mouseDoubleClickEvent(QMouseEvent *){doubleClicked();}
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    QHBoxLayout *layout = new QHBoxLayout(this);
    CLabel *_text = new CLabel(this);
    QLabel *_icon = new QLabel(this);

    QGraphicsDropShadowEffect *_shadow = new QGraphicsDropShadowEffect( this );

    DisplayMode _displayMode = CPushButton::textOnly;
    IconPosition _iconPosition = CPushButton::left;

    uint animState = 0;
    bool pressing = false;

    bool _frameless = false;
    bool _mouseOver = false;
    bool _iconColorEnabled = false;

    uint _borderRadius = 6;
    uint _borderWidth = 1;

    QTimer *timer = new QTimer(this);

    QColor _textColor = Qt::white;
    QColor _frameColor = QColor(BLUE);
    QColor _iconColor = Qt::white;

    QPixmap _pixmap;
};

#endif // CPUSHBUTTON_H
