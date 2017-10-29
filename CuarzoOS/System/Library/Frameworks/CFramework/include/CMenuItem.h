#ifndef CMENUITEM_H
#define CMENUITEM_H

#include <QFrame>
#include <QHBoxLayout>
#include "CMaterialIcon.h"
#include "CIcon.h"
#include "CLabel.h"

class CMenuItem : public QWidget
{
    Q_OBJECT

public:
    CMenuItem();
    CMenuItem( const QString &text );
    CMenuItem( const QString &text, const QPixmap &icon );
    CMenuItem( const QString &text, const QPixmap &icon, const QString &shortcut );

    void setIcon(  const QPixmap &icon );
    void setText( const QString &text );
    void setShortcut( const QString &shortcut );
    void setEnabled( bool mode );

    bool enabled() { return _enabled; }
    QString getShortcut(){ return shortcut; }

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    virtual void enterEvent(QEvent *e);
    virtual void leaveEvent(QEvent *);

private:

    QHBoxLayout *layout = new QHBoxLayout( this );
    CIcon *icon = new CIcon( this );
    CIcon *arrow = new CIcon( CMaterialIcon::pixmap("play_arrow") , QSize( 20, 20 ));
    CLabel *label = new CLabel();
    QSpacerItem *iconSpace = new QSpacerItem(24,24);

    QString shortcut = "";
    bool _enabled = true;

    void setActive( bool mode);


    void setup();

signals:
    void mouseOver();
    void selected();

};

#endif // CMENUITEM_H
