#ifndef CAPPLICATION
#define CAPPLICATION

#include "CCore.h"
#include "CWindow.h"
#include "CProtocol.h"
#include <QApplication>
#include <QLocalSocket>


/* ------------------ CApplication ------------------ */

class CProtocol;

class CApplication : public QApplication
{

    Q_OBJECT

public:
    CApplication(int &argc,char **argv);
    CProtocol *protocol;
};


#endif


