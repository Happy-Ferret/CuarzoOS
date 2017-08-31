#include "headers/window.h"
#include <QScreen>
#include "CCore.h"
#include <QMovie>
#include <random>
Window::Window()
{

  setCentralWidget(widget);
  move(200,200);
  resize(800,500);

  setWindowTitle("Hello World Application");
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
  siz->setFrameColor(YELLOW);


  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0,255);

  uint r = distribution(generator);
  uint g = distribution(generator);
  uint b = distribution(generator);

  setPalette( QColor( r, g, b ) );

  QMovie *movie = new QMovie("/home/e/jobs.gif");
  movieFrame->setMovie(movie);

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

  wel->hide();
  home->hide();
  siz->hide();
  mod->hide();
  blu->hide();
  opa->hide();
  tit->hide();
  del->hide();
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

