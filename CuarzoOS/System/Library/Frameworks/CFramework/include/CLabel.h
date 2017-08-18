#ifndef CLABEL_H
#define CLABEL_H

#include <QLabel>
#include <QFontMetrics>

/* ------------------ CLabel ------------------ */

class CLabel : public QLabel
{

    Q_OBJECT

public:

    // Constructor 1
    CLabel(QWidget *parent = nullptr)
    {
        setParent(parent);
        setup();
    }

    // Constructor 2
    CLabel(const QString &text,QWidget *parent = nullptr)
    {
        setParent(parent);
        setText(text);
        setup();
    }

    // Set label text
    void setText(const QString &text)
    {
            localText = text;

            if(localEllipsis)
            {
                QFontMetrics metrics(font());
                QString elidedText = metrics.elidedText(text, Qt::ElideRight, width());
                QLabel::setText(elidedText);
            }
            else
            {
                QLabel::setText(text);
            }
    }

    // Set label text
    void enableEllipsis( bool mode )
    {
        localEllipsis = mode;
        setText(localText);
    }

    // Getters
    bool ellipsisEnabled(){ return localEllipsis; }

private:

    bool localEllipsis = false;
    QString localText = "";

    // Resize event
    void resizeEvent(QResizeEvent *)
    {
        if(localEllipsis)
            setText(localText);
    }

    void setup()
    {
        setStyleSheet("font-size:19px;color:#444");
    }
};
#endif // CLABEL_H
