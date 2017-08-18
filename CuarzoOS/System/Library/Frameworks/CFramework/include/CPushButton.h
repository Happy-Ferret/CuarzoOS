#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include "CLabel.h"
#include <QFrame>
#include <QHBoxLayout>

class CPushButton : public QFrame
{
    Q_OBJECT
public:

    enum DisplayMode{textOnly,iconOnly,textAndIcon};
    enum AnimationMode{opacityAnimation,sizeAnimation,colorAnimation};
    enum IconPosition{left,right};


    CPushButton(QWidget *parent = nullptr);
    CPushButton(const QString &text, QWidget *parent = nullptr);
    CPushButton(QPixmap icon, QWidget *parent = nullptr);
    CPushButton(const QString &text, QPixmap icon, QWidget *parent = nullptr);

    void setDisplayMode(DisplayMode mode);
    void setPressAnimation(AnimationMode mode);

    void setIconPosition(uint  position);
    void setPressIcon(QPixmap icon);
    void setIcon(QPixmap icon);

    void setFontFamily(QString family);
    void setFontSize(uint size);
    void setFontWeight(QString weight);
    void setTextColor(QColor color);
    void setText(const QString &text);

    void showBackground(bool mode);
    void setBorderRadius(uint radius);

    void setPressBackgroundColor(QColor color);
    void setPressBorderColor(QColor color);
    void setPressTextColor(QColor color);


signals:

public slots:

private:
    void setup();

    DisplayMode _displayMode;
    AnimationMode _pressAnimationMode;
    IconPosition _iconPosition;

    bool _background;

    QColor _textColor;
    QColor _pressedTextColor;
    QColor _backgroundColor;

    QPixmap _normalIcon;
    QPixmap _pressedIcon;

    CLabel *_text = new CLabel(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
};

#endif // CPUSHBUTTON_H
