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

    // Transparent background
    setPalette( Qt::transparent );

    firstTopLayout = new QHBoxLayout(topBarItems);

    // Window icons
    QString path = SYSTEM_PATH + "/System/Library/Icons/Crystals/";

    // Buttons
    closeButton = new CIconButton(
                QPixmap( path + "close_focus.png"),
                QPixmap( path + "close_focus.png"),
                QPixmap( path + "close_active.png"),
                this
    );

    minimizeButton = new CIconButton(
                QPixmap( path + "minimize_focus.png"),
                QPixmap( path + "minimize_focus.png"),
                QPixmap( path + "minimize_active.png"),
                this
    );

    expandButton = new CIconButton(
                QPixmap( path + "maximize_focus.png"),
                QPixmap( path + "maximize_focus.png"),
                QPixmap( path + "maximize_active.png"),
                this
    );

    int buttonSize = 16;
    closeButton->setFixedSize( buttonSize, buttonSize);
    minimizeButton->setFixedSize( buttonSize, buttonSize);
    expandButton->setFixedSize( buttonSize, buttonSize);

    horizontalLayout->setMargin(8);
    horizontalLayout->setSpacing(8);
    horizontalLayout->addWidget(closeButton);
    horizontalLayout->addWidget(minimizeButton);
    horizontalLayout->addWidget(expandButton);
    horizontalLayout->addWidget( topBarItems , 1);

    _title->setAlignment( Qt::AlignCenter );
    _title->enableEllipsis(true);
    _title->setFontColor( QColor(GRAY) );
    topBar->setObjectName("QZTP");
    topBar->setStyleSheet("#QZTP{background:qlineargradient( x1:0 y1:0, x2:0 y2:1, stop:0 #FFF , stop:1 #e8eaf6);border-bottom:1px solid #CCC}");
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
