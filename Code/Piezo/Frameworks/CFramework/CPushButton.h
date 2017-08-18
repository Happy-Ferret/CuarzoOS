#ifndef CPUSHBUTTON
#define CPUSHBUTTON

// Button display modes
#define TEXT_ONLY 0
#define ICON_ONLY 1
#define TEXT_AND_ICON 2

// Button pressed animation modes
#define OPACITY 0
#define SCALED 1
#define COLOR 2
#define ICON 3

#include "CLabel.h"
#include <QFrame>
#include <QHBoxLayout>

/* ------------------ CPushButton------------------ */

class CPushButton : public QFrame
{

    Q_OBJECT

public:

private:
    QHBoxLayout *layout = new QHBoxLayout(this);
    CLabel *label = new CLabel();

    void setup()
    {

    }
};
#endif
