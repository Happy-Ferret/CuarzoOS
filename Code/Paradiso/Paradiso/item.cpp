#include "item.h"

extern QString blue;

Item::Item()
{
    setMouseTracking(true);
    layout->addWidget(icon);
    layout->setMargin(0);
    layout->setAlignment(Qt::AlignCenter);
    icon->setScaledContents(true);
    setFixedSize(30,24);
}

void Item::readSettings()
{
    if(path == "")
        return;

    QFile settings(path + "/settings.info");
    settings.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(settings.readAll());
    image = QPixmap(path + "/" + doc.toVariant().toMap()["icon"].toString());
}

void Item::setIcon()
{
    float width = ((float)image.width() / (float)image.height()) * 16.0f;
    icon->setFixedSize(width,16);
    icon->setPixmap(image);
}

void Item::setActive(bool option)
{
    if(option)
    {
        QPixmap activeImage( image.size() );
        activeImage.fill( Qt::white );
        activeImage.setMask( image.createMaskFromColor( Qt::transparent ) );
        icon->setPixmap(activeImage);
        setStyleSheet("background:"+blue);
    }
    else{
        icon->setPixmap(image);
        setStyleSheet("background:transparent");
    }

}

void Item::mousePressEvent(QMouseEvent *)
{
    setActive(true);
}

void Item::mouseReleaseEvent(QMouseEvent *)
{
    setActive(false);
}
