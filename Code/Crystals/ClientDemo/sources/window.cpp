#include "headers/window.h"
#include <QScreen>
#include "CCore.h"
#include <QMovie>
#include <random>
Window::Window()
{

  setCentralWidget(widget);
  move(0,0);
  resize(800,500);
  setMouseTracking(true);

  setWindowTitle("CuarzoOS");
  connect(cre,SIGNAL(pressed()),this,SLOT(createWindow()));
  connect(del,SIGNAL(pressed()),this,SLOT(deleteWindow()));
  connect(mod,SIGNAL(pressed()),this,SLOT(changeMode()));
  connect(blu,SIGNAL(pressed()),this,SLOT(activateBlur()));
  connect(opa,SIGNAL(pressed()),this,SLOT(changeOpacity()));
  connect(tit,SIGNAL(pressed()),this,SLOT(changeTitle()));
  connect(siz,SIGNAL(pressed()),this,SLOT(changeSize()));

  home->setFrameColor(GREEN);
  cre->setFrameColor(BLUE);
  del->setFrameColor(RED);
  siz->setFrameColor(ORANGE);
  tit->setFrameColor(DEEP_PURPLE);
  mod->setFrameColor(DEEP_ORANGE);
  blu->setFrameColor(TEAL);
  opa->setFrameColor(BROWN);
  a->setFrameColor(INDIGO);
  b->setFrameColor(PURPLE);
  c->setFrameColor(AMBER);
  d->setFrameColor(LIME);
  e->setFrameColor(PINK);


  QMovie *movie = new QMovie("/home/e/jobs.gif");
  movieFrame->setMovie(movie);

  layout->addWidget(a);
  layout->addWidget(b);
  layout->addWidget(c);
  layout->addWidget(d);
  layout->addWidget(e);

  layout->addWidget(wel);
  layout->addWidget(home);
  layout->addWidget(siz);
  layout->addWidget(cre);
  layout->addWidget(mod);
  layout->addWidget(blu);
  layout->addWidget(opa);
  layout->addWidget(tit);
  layout->addWidget(del);
  layout->addWidget(movieFrame);
  movie->start();
  movieFrame->hide();

}

void Window::mouseMoveEvent(QMouseEvent *e)
{
    setWindowTitle(
                QString::number( QApplication::primaryScreen()->size().width()) + " - " +
                QString::number( e->screenPos().x()) + " - " +
                 QString::number( e->localPos().x())
                );
}

void Window::createWindow()
{
    Window *w = new Window();
    w->show();
}

void Window::activateBlur()
{
    setBlur(true);
}

void Window::changeOpacity()
{
    setWindowOpacity(windowOpacity()-10);
}

void Window::changeMode()
{
    setMode(DOCK_MODE);
}

void Window::changeTitle()
{
    setWindowTitle("Sup bitches!");
}

void Window::changeSize()
{
    setFixedSize(width() + 10,height() + 10);
}

void Window::deleteWindow()
{
    close();
}

