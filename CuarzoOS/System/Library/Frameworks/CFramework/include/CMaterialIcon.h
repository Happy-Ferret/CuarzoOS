#ifndef CMATERIALICON_H
#define CMATERIALICON_H

#include "CCore.h"
#include <QPixmap>
#include <QImage>
#include <QIcon>

class CMaterialIcon
{
public:
    static QPixmap pixmap( const QString iconName)
    {
        return QPixmap( SYSTEM_PATH + "/System/Library/Icons/Materialize/ic_" + iconName + "_48px.svg");
    }
    static QImage image( const QString iconName)
    {
        return QImage( SYSTEM_PATH + "/System/Library/Icons/Materialize/ic_" + iconName + "_48px.svg");
    }
    static QIcon icon( const QString iconName)
    {
        return QIcon( SYSTEM_PATH + "/System/Library/Icons/Materialize/ic_" + iconName + "_48px.svg");
    }
};

#endif // CMATERIALICON_H
