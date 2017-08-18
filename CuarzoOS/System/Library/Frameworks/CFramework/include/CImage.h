#ifndef CIMAGE_H
#define CIMAGE_H

#include <QWidget>
#include <QPainter>
#include <QBitmap>

class CImage : public QWidget
{
    Q_OBJECT

public:
    CImage(QPixmap image,QWidget *parent = nullptr);
    CImage(QPixmap image,QSize size,QWidget *parent = nullptr);
    CImage(QPixmap image,QColor color,QWidget *parent = nullptr);

    void setImage(QPixmap image);
    void setBorderRadius(uint radius);
    void setImageColor(QColor color);
    void setBorderColor(QColor color);
    void setBorderWidth(uint width);
    void enableColor(bool mode);
    bool colorEnabled(){return _colorEnabled;}

private:
    QPixmap _image;
    QColor _imageColor = QColor("#444444");
    QColor _borderColor = QColor("#444444");
    uint _borderRadius = 0;
    uint _borderWidth = 0;
    bool _colorEnabled = false;
    void paintEvent(QPaintEvent *event);

};

#endif // CIMAGE_H
