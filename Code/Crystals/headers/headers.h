// QT
#include <QGuiApplication>
#include <QScreen>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QPointer>
#include <QtMath>
#include <QProcess>
#include <QDir>

#include <QLocalServer>
#include <QLocalSocket>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QTouchEvent>
#include <QWheelEvent>

// Wayland
#include <QtWaylandCompositor/QWaylandCompositor>
#include <QtWaylandCompositor/QWaylandSurface>
#include <QtWaylandCompositor/QWaylandView>
#include <QtWaylandCompositor/QWaylandWlShellSurface>
#include <QtWaylandCompositor/QWaylandXdgSurfaceV5>
#include <QtWaylandCompositor/QWaylandXdgShellV5>
#include <QtWaylandCompositor/QWaylandWlShellSurface>
#include <QtWaylandCompositor/qwaylandseat.h>
#include <QtWaylandCompositor/qwaylanddrag.h>

// Open GL
#include <QOpenGLWindow>
#include <QOpenGLContext>
#include <QOpenGLTextureBlitter>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLWindow>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>

// CuarzoOS
#include "CCore.h"

#ifndef DEFINITIONS
#define DEFINITIONS


// Vertex structure
struct Vertex
{
    float position[3];
    float color[4];
    float texture[2];
};

// Background View Mode
enum ViewMode { Image, Color, Gradient };

// Background image size mode
enum ImageMode { ResizeToFill, KeepRatioToFill };


// Shader Draw Mode
#define SHADER_DRAW_SURFACE 0
#define SHADER_DRAW_SHADOW 1
#define SHADER_DRAW_BLUR 2

// Shader Blur Modes
#define BLUR_RECT 0
#define BLUR_HORIZONTAL 1
#define BLUR_VERTICAL 2


#endif
