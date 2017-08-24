#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include "CLabel.h"
#include "CCore.h"
#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QGraphicsOpacityEffect>
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

    void enterEvent(QEvent *);
    void leaveEvent(QEvent*);
    void mouseDoubleClickEvent(QMouseEvent *){doubleClicked();}
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    QHBoxLayout *layout = new QHBoxLayout(this);
    CLabel *_text = new CLabel(this);
    QLabel *_icon = new QLabel(this);

signals:
    void mouseEnter();
    void mouseLeave();
    void pressed();
    void released();
    void doubleClicked();
    void clicked(bool);
public slots:
    void animate();
private:
    void setup();
    void resetStyle();


    QGraphicsOpacityEffect *_opacity = new QGraphicsOpacityEffect(this);

    DisplayMode _displayMode = CPushButton::textOnly;
    IconPosition _iconPosition = CPushButton::left;

    uint animState = 0;
    bool pressing = false;

    bool _frameless = false;
    bool _mouseOver = false;
    bool _iconColorEnabled = false;

    uint _borderRadius = 8;
    uint _borderWidth = 1;

    QTimer *timer = new QTimer(this);

    QColor _textColor = Qt::white;
    QColor _frameColor = QColor(BLUE);
    QColor _iconColor = QColor("#444444");

    QPixmap _pixmap;
};

#endif // CPUSHBUTTON_H
