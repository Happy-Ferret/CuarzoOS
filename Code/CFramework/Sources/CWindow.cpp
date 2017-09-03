#include "CWindow.h"
#include <QDebug>

CWindow::CWindow()
{
    // Wrongly used to identify a surface
    QWidget::setWindowTitle(QString::number(winId()));

    // Prevent app crash
    move(winId(),winId());

    // Deletes blue Qt frame
    setWindowFlags(Qt::FramelessWindowHint);

    // Asigns parent
    QWidget::setParent(nullptr);

    firstTopLayout = new QHBoxLayout(topBarItems);

    // Window icons
    QString path = SYSTEM_PATH + "/System/Library/Icons/Crystals/";

    // Buttons
    closeButton = new CIconButton(
                QPixmap( path + "Window_Close_Normal.png"),
                QPixmap( path + "Window_Close_Over.png"),
                QPixmap( path + "Window_Close_Press.png"),
                this
    );

    minimizeButton = new CIconButton(
                QPixmap( path + "Window_Minimize_Normal.png"),
                QPixmap( path + "Window_Minimize_Over.png"),
                QPixmap( path + "Window_Minimize_Press.png"),
                this
    );

    expandButton = new CIconButton(
                QPixmap( path + "Window_Expand_Normal.png"),
                QPixmap( path + "Window_Expand_Over.png"),
                QPixmap( path + "Window_Expand_Press.png"),
                this
    );

    int buttonSize = 16;
    closeButton->setFixedSize( buttonSize, buttonSize);
    minimizeButton->setFixedSize( buttonSize, buttonSize);
    expandButton->setFixedSize( buttonSize, buttonSize);

    horizontalLayout->setMargin(8);
    horizontalLayout->setSpacing(10);
    horizontalLayout->addWidget(closeButton);
    horizontalLayout->addWidget(minimizeButton);
    horizontalLayout->addWidget(expandButton);
    horizontalLayout->addWidget( topBarItems , 1);

    _title->setAlignment( Qt::AlignCenter );
    _title->enableEllipsis(true);
    _title->setFontColor( QColor(GRAY) );
    topBar->setObjectName("QZTP");
    topBar->setStyleSheet("#QZTP{background:qlineargradient( x1:0 y1:0, x2:0 y2:1, stop:0 #EEE , stop:1 #DDD);border-bottom:1px solid #CCC}");
    topBar->setAutoFillBackground(true);

    verticalLayout->addWidget(topBar,0,Qt::AlignTop);
    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(0);

    topBar->installEventFilter(this);
    installEventFilter(this);
    refreshtemsPositions();
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
    _title->setText(title);
}

// Gets local title
QString CWindow::windowTitle()
{
    return _title->text();
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
        setPalette(Qt::transparent);
    else
        setPalette(Qt::white);
}

// Gets blur state
bool CWindow::blurState()
{
    return localBlur;
}

void CWindow::refreshtemsPositions()
{
    _title->resize(topBar->width() - 300, topBar->height());
    _title->move( 150, 0 );
}

void CWindow::resizeEvent(QResizeEvent *)
{
    refreshtemsPositions();
}

bool CWindow::eventFilter(QObject *watched, QEvent *event)
{
    if ( event->type() == QEvent::MouseButtonPress && watched == topBar)
        mouseGrabEvent();
}



// Set surface Opacity
void CWindow::setWindowOpacity(float opacity)
{
    localOpacity = opacity;
    opacityChanged(opacity);
}

void CWindow::setCentralWidget(QWidget *widget)
{
    verticalLayout->insertWidget( 1, widget, 1 );
}

// Gets surface opacity
uint CWindow::windowOpacity()
{
    return localOpacity;
}
