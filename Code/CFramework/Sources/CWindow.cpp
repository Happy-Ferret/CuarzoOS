#include "CWindow.h"


CWindow::CWindow(QWidget *parent)
{
    // Wrongly used to identify a surface
    QWidget::setWindowTitle(QString::number(winId()));

    // Deletes blue Qt frame
    setWindowFlags(Qt::FramelessWindowHint);

    // Asigns parent
    QWidget::setParent(parent);

}

// Assign and send position to Crystals
void CWindow::move(const QPoint &pos)
{
    QWidget::move(pos);
    positionChanged(pos);
}
void CWindow::move(int x, int y)
{
    QWidget::move(x,y);
    positionChanged(QPoint(x,y));
}

// Sends title to Crystals
void CWindow::setWindowTitle(const QString &title)
{
    localTitle = title;
    titleChanged(title);
}

// Gets local title
QString CWindow::windowTitle()
{
    return localTitle;
}

// Resize
void CWindow::resize(const QSize &size)
{
    QWidget::resize(size);
}

// Resize
void CWindow::resize(int x, int y)
{
    QWidget::resize(x,y);
}

// Sends surface mode
void CWindow::setMode(unsigned int mode)
{
    localMode = mode;
    modeChanged(mode);
}

// Gets surface mode
uint CWindow::mode()
{
    return localMode;
}

// Turn On/OFF blur
void CWindow::setBlur(bool mode)
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
bool CWindow::blurState()
{
    return localBlur;
}


// Set surface Opacity
void CWindow::setWindowOpacity(uint opacity)
{
    localOpacity = opacity;
    opacityChanged(opacity);
}

// Gets surface opacity
uint CWindow::windowOpacity()
{
    return localOpacity;
}
