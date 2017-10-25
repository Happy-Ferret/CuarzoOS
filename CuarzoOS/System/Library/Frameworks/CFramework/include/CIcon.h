#ifndef CICON_H
#define CICON_H

#include <QLabel>

class CIcon : public QLabel
{
    Q_OBJECT

public:
    CIcon( QWidget *parent = nullptr);
    CIcon( const QPixmap &icon, QWidget *parent = nullptr);
    CIcon( const QPixmap &icon, const QSize &size, QWidget *parent = nullptr);

    void setPixmap(const QPixmap & icon);
    void setColor( const QColor &color);
    void enableColor( bool mode );

    QColor getColor(){ return _color; }
    bool colorEnabled(){ return _colorEnabled; }

private:

    void setup();

    QPixmap _pixmap = QPixmap();
    QPixmap _coloredPixmap;
    QColor _color = QColor(Qt::black);
    bool _colorEnabled = false;

};

#endif // CICON_H
