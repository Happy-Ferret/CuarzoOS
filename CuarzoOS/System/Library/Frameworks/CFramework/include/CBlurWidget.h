#ifndef CBLURWIDGET_H
#define CBLURWIDGET_H

#include <QWidget>
//#include "CApplication.h"

class CBlurWidget : public QWidget
{

Q_OBJECT

public:
    CBlurWidget( QWidget *parent = nullptr );
    void enableBlur( bool state );
    void setBlurLevel( float level = 1.0f );
    void setBlurTint( float tint = 0.5f );

    bool enabled() { return _state; }
    float blurLevel() { return _level; }
    float blurTint() { return _tint; }

private:
    bool _state = true;
    float _level = 1.6f;
    float _tint = 0.5f;

    virtual void resizeEvent(QResizeEvent*);
    virtual void moveEvent(QMoveEvent*);

signals:
    void stateChanged( bool );
    void levelChanged( float );
    void tintChanged( float );
    void geometryChanged();
};

#endif // CBLURWIDGET_H
