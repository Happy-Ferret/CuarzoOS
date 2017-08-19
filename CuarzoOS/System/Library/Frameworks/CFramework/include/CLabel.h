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
    void setFontSize(uint size , const QString &units= "px");
    void setFontFamily(const QString &family);
    void setFontWeight(const QString &weight);
    void setFontStyle(const QString &style);
    void setFontColor(QColor color);
    void enableEllipsis( bool mode );
    bool ellipsisEnabled(){ return localEllipsis; }
private:


    bool localEllipsis = false;
    QString localText = "";

    QColor _fontColor = QColor("#444444");
    QString _fontFamily = "Coves";
    QString _fontWeight = "light";
    QString _fontSize = "16px";
    QString _fontStyle= "regular";

    void resetStyle();
    void resizeEvent(QResizeEvent *);
    void setup();
};
#endif // CLABEL_H
