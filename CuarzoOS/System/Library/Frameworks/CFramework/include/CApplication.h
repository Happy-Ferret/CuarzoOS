#include "CCore.h"
#include "CProtocol.h"
#include "CWindow.h"
#include <QApplication>
#include <QLocalSocket>

#ifndef CAPPLICATION
#define CAPPLICATION

/* ------------------ CApplication ------------------ */

class CApplication : public QApplication
{
    Q_OBJECT

public:
    CApplication(int &argc,char **argv);
    CProtocol *protocol = new CProtocol(this);
};

#endif


