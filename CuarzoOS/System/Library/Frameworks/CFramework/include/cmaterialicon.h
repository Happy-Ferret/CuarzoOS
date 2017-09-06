#ifndef CMATERIALICON_H
#define CMATERIALICON_H

#include "CCore.h"
#include <QPixmap>
#include <QImage>
#include <QPicture>
#include <QIcon>

class CMaterialIcon
{
public:
    QPixmap pixmap( const QString iconName)
    {
        return QPixmap( SYSTEM_PATH + "/System/Library/Icons/Materialize/ic_" + iconName + "_48.svg");
    }
    QImage image( const QString iconName)
    {
        return QImage( SYSTEM_PATH + "/System/Library/Icons/Materialize/ic_" + iconName + "_48.svg");
    }
    QPicture picture( const QString iconName)
    {
        return QPicture( SYSTEM_PATH + "/System/Library/Icons/Materialize/ic_" + iconName + "_48.svg");
    }
    QIcon icon( const QString iconName)
    {
        return QIcon( SYSTEM_PATH + "/System/Library/Icons/Materialize/ic_" + iconName + "_48.svg");
    }
};

#endif // CMATERIALICON_H
