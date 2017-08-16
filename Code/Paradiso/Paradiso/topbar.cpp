#include "topbar.h"


//Setup topbar

TopBar::TopBar()
{
    setWindowFlag(Qt::FramelessWindowHint);
    QPalette backgroundColor(QColor(255,255,255,230));
    setPalette(backgroundColor);
    layout->setSpacing(10);
    layout->setMargin(0);
    refreshSize();
    readSettings();
    show();
}

//Refresh size when resolution changes

void TopBar::refreshSize()
{
    resize(QApplication::desktop()->width(),24);
}

//Read settings

void TopBar::readSettings()
{
    QFile settings(QApplication::applicationDirPath() + "/settings.info");
    settings.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(settings.readAll());
    launchItems = doc.toVariant().toMap()["launchItems"].toList();

    foreach (QVariant item, launchItems) {
       openItem(item.toString());
    }

}

//Open a .paraditem file

void TopBar::openItem(QString path)
{
    Item *newItem = new Item();
    newItem->path = path;
    newItem->readSettings();
    layout->addWidget(newItem);
    newItem->setIcon();
    newItem->show();
}
