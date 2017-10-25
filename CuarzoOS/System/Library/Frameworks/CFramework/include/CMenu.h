#ifndef CMENU_H
#define CMENU_H

#include "CWindow.h"
#include <QBoxLayout>

class CMenu : public CWindow
{

    Q_OBJECT

public:
    CMenu();
    CMenu( const QString &title);

    void setTitle( const QString &title);
    void show( const QPoint &pos );

    void insertItem( QWidget*item );
    void insertItemAt( QWidget*item, uint index );
    void removeItem( QWidget*item );


    QString title() { return _title; }
private:
    void setup();
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout( widget );
    QString _title = "";
};

#endif // CMENU_H
