#include "CBlurWidget.h"


CBlurWidget::CBlurWidget(QWidget *parent)
{
    setParent( parent );
    setPalette(Qt::transparent);
    CApplication *app = qobject_cast<CApplication*>(QApplication::instance());
    app->protocol->connectBlurWidget( this );
}

void CBlurWidget::enableBlur(bool state)
{
    _state = false;
    stateChanged( _state );
}

void CBlurWidget::setBlurLevel(float level)
{
    _level = level;
    levelChanged( _level );
}

void CBlurWidget::setBlurTint(float tint)
{
    _tint = tint;
    tintChanged( _tint );
}

void CBlurWidget::resizeEvent(QResizeEvent *)
{
    geometryChanged();
}

void CBlurWidget::moveEvent(QMoveEvent *)
{
    geometryChanged();
}
