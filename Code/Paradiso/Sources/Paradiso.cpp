#include "Paradiso.h"

Paradiso::Paradiso() : CWindow( TopBar )
{
    // Configure Paradiso
    setCentralWidget( topBar );
    setFixedSize(QApplication::primaryScreen()->size().width(), 28);

    // Setup topbar
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(cuarzoMenu);
    layout->addWidget(textMenu);
    layout->addWidget(textMenuB);
    textMenu->text->setFontWeight("bold");
    cuarzoMenu->setFixedWidth(64);
    layout->setAlignment(Qt::AlignLeft);

    cuarzoMenu->installEventFilter(this);
    textMenu->installEventFilter(this);
    textMenuB->installEventFilter(this);

    // Display Top Bar
    show();
}

bool Paradiso::eventFilter(QObject *watched, QEvent *event)
{
    // Mouse enter
    if( event->type() == QEvent::Enter)
    {
        qDebug() << "ENTRO";

        if( activeMenu != nullptr)
        {
            if( PMenu *menu = qobject_cast<PMenu*>(watched) )
            {
                activeMenu->setActive( false );
                activeMenu = menu;
                menu->setActive(true);
                return true;
            }
        }
    }

    // Mouse press
    if( event->type() == QEvent::MouseButtonPress)
    {
        if( PMenu *menu = qobject_cast<PMenu*>(watched) )
        {
            activeMenu = menu;
            menu->setActive(true);
            return true;

        }
        else
        {
            if( activeMenu != nullptr)
            {
                activeMenu->setActive( false );
                activeMenu = nullptr;
            }
            return true;
        }
    }

    return false;
}


void Paradiso::messageFromCrystals()
{
        // Store the message
        //QByteArray message = crystalsSocket->readAll();

        // Message type
        //unsigned int type = *(unsigned int*)message.mid(0,sizeof(unsigned int)).data();

}

