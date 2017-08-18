#ifndef CLABEL_H
#define CLABEL_H

#include <QLabel>
#include <QFontMetrics>

/* ------------------ CLabel ------------------ */

class CLabel : public QLabel
{

    Q_OBJECT

public:

    CLabel(QWidget *parent = nullptr);
    CLabel(const QString &text,QWidget *parent = nullptr);
    void setText(const QString &text);
    void enableEllipsis( bool mode );

    bool ellipsisEnabled(){ return localEllipsis; }

private:

    bool localEllipsis = false;
    QString localText = "";

    void resizeEvent(QResizeEvent *);
    void setup();
};
#endif // CLABEL_H
