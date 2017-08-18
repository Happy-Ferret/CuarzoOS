#include "CCore.h"
#include <QMainWindow>

#ifndef CWIDGET
#define CWIDGET

/* ------------------ CWidget ------------------ */

class CWidget : public QMainWindow
{

    Q_OBJECT

public:

    virtual ~CWidget() {}

    // Constructor
    CWidget(CWidget *parent = nullptr)
    {
        // Wrongly used to identify a surface
        QWidget::setWindowTitle(QString::number(winId()));

        // Deletes blue Qt frame
        setWindowFlags(Qt::FramelessWindowHint);

        // Asigns parent
        QWidget::setParent(parent);

    }

    // Assign and send position to Crystals
    void move(const QPoint &pos)
    {
        QWidget::move(pos);
        positionChanged(pos);
    }
    void move(int x, int y)
    {
        QWidget::move(x,y);
        positionChanged(QPoint(x,y));
    }

    // Sends title to Crystals
    void setWindowTitle(const QString &title)
    {
        localTitle = title;
        titleChanged(title);
    }

    // Gets local title
    QString windowTitle()
    {
        return localTitle;
    }

    // Resize
    void resize(const QSize &size)
    {
        QWidget::resize(size);
    }

    // Resize
    void resize(int x, int y)
    {
        QWidget::resize(x,y);
    }

    // Sends surface mode
    void setMode(unsigned int mode = WINDOW_MODE)
    {
        localMode = mode;
        modeChanged(mode);
    }

    // Gets surface mode
    unsigned int mode()
    {
        return localMode;
    }

    // Turn On/OFF blur
    void setBlur(bool mode)
    {
        localBlur = mode;
        blurStateChanged(mode);
        if(mode)
        {
            setPalette(Qt::transparent);
        }
        else
        {
            setPalette(Qt::white);
        }
    }

    // Gets blur state
    bool blurState()
    {
        return localBlur;
    }


    // Set surface Opacity
    void setWindowOpacity(uint opacity = 255)
    {
        localOpacity = opacity;
        opacityChanged(opacity);
    }

    // Gets surface opacity
    uint windowOpacity()
    {
        return localOpacity;
    }

    bool registeredSurface = false;

signals:
    void positionChanged(const QPoint &pos);
    void titleChanged(QString);
    void modeChanged(uint);
    void opacityChanged(uint);
    void blurStateChanged(bool);

private:
    QString localTitle = "";
    uint localMode = WINDOW_MODE;
    uint localOpacity = 255;
    bool localBlur = false;
};

#endif

