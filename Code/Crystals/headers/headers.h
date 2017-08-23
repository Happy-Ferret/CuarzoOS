// QT
#include <QGuiApplication>
#include <QScreen>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QPointer>
#include <QtMath>
#include <QProcess>
#include <QDir>

#include <QLocalServer>
#include <QLocalSocket>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QTouchEvent>

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

#ifndef APPLICATION_TYPES
#define APPLICATION_TYPES

// The way Crystals recognize the application

#define CLIENT_TYPE 0
#define CRYSTALS_TYPE 1

#endif

#ifndef SURFACE_MODES
#define SURFACE_MODES

// The way Crystals recognize the surface role

    #define WINDOW_MODE 0
    #define FRAMELESS_MODE 1
    #define TOPBAR_MODE 2
    #define FILEMANAGER_MODE 3
    #define DOCK_MODE 4
    #define TITLEBAR_MODE 5
#endif

// System root path
#define SYSTEM_PATH QString("/home/e/Escritorio/CuarzoOS/CuarzoOS")

#ifndef MESSAGES
#define MESSAGES


/* ------------------ In Messages Types ------------------ */

// Register App
#define REGISTER_APP 0
typedef struct{
    unsigned int type; // Message type
    unsigned int pid; // App proccess Id
    unsigned int appType; // Application Type
}RegisterAppStruct;

// Configure Surface
#define SURFACE_CONFIG 1
typedef struct{
    unsigned int type = SURFACE_CONFIG; // Message type
    unsigned int id; // Surface Id
    unsigned int role; // Surface Role
    unsigned int x; // X pos
    unsigned int y; // Y pos
    unsigned int opacity; // Surface Opacity
    char title[128]; // Surface Title
}SurfaceConfigStruct;

// Send Surface Role
#define SURFACE_ROLE 2
typedef struct{
    unsigned int type = SURFACE_ROLE; // Message type
    unsigned int id; // Surface Id
    unsigned int role; // Surface Role
}SurfaceRoleStruct;

// Send Surface Position
#define SURFACE_POS 3
typedef struct{
    unsigned int type = SURFACE_POS; // Message type
    unsigned int id; // Surface Id
    int x; // X cords
    int y; // Y cords
}SurfacePosStruct;

// Send Surface Title
#define SURFACE_TITLE 4
typedef struct{
    unsigned int type = SURFACE_TITLE; // Message type
    unsigned int id; // Surface Id
    char title[128]; // Surface Title
}SurfaceTitleStruct;

// Send Surface Opacity
#define SURFACE_OPACITY 5
typedef struct{
    unsigned int type = SURFACE_OPACITY; // Message type
    unsigned int id; // Surface Id
    unsigned int opacity; // Surface Opacity
}SurfaceOpacityStruct;

// Send Surface blur Request
#define SURFACE_BLUR 6
typedef struct{
    unsigned int type = SURFACE_BLUR; // Message type
    unsigned int id; // Surface Id
    bool activate; // Turn ON/OFF blur
}SurfaceBlurStruct;

// Send Surface Minimize
#define SURFACE_MINIMIZE 7
typedef struct{
    unsigned int type = SURFACE_MINIMIZE; // Message type
    unsigned int id; // Surface Id
    bool minimize; // Turn ON/OFF minimize
}SurfaceMinimizeStruct;

// Send Surface Expand
#define SURFACE_EXPAND 8
typedef struct{
    unsigned int type = SURFACE_EXPAND; // Message type
    unsigned int id; // Surface Id
    bool expand; // Turn ON/OFF expand
    unsigned int expandMode;
}SurfaceExpandStruct;



/* ------------------ Out Messages Types ------------------ */

// Messages Out

// App Registered Event
#define REGISTERED_APP 0
typedef struct{
    unsigned int type = REGISTERED_APP; // Message type
}RegisteredAppStruct;

// Surface Id Registered
#define REGISTERED_SURFACE 1
typedef struct{
    unsigned int type = REGISTERED_SURFACE; // Message type
    unsigned int id; // Message type
}RegisteredSurfaceStruct;

// Surface Blur Image
#define SURFACE_BLUR_IMAGE 2
typedef struct{
    unsigned int type = SURFACE_BLUR_IMAGE; // Message type
    unsigned int id; // Surface desitnation
    unsigned int width; // Pixels
    unsigned int height; // Pixels
    unsigned char pixels[4*64*64]; // 64x64 Image (RGBA 255)
}SurfaceBlurImageStruct;


/* ------------------ Messages to GUI ------------------ */

// Titlebar request
#define TITLEBAR_REQUEST 20
typedef struct{
    unsigned int type = TITLEBAR_REQUEST; // Message type
    unsigned int forPid; // Process id of the surface
    unsigned int forId; // Surface which needs the titlebar
    unsigned int width; // Surface width
    char title[128]; // Surface Title
}TitlebarRequestStruct;

/* ------------------ Messages from GUI ------------------ */

// Titlebar Created
#define TITLEBAR_CREATED 20
typedef struct{
    unsigned int type; // Message type
    unsigned int id; // TitleBar id
    unsigned int forPid; // Process id of the surface
    unsigned int forId; // Surface which needs the titlebar
}TitlebarCreatedStruct;

#endif

#ifndef STRUCTURES
#define STRUCTURES

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

// IPC messages
enum MessageType{ Caca };

// View type
enum ViewType{ Paradiso, TitleBar, Roller };

// Selected Shader Mode
#define SHADER_NORMAL 0
#define SHADER_BACKGROUND 1
#define SHADER_HBLUR 2
#define SHADER_VBLUR 3
#define SHADER_FINAL 4
#define SHADER_BLUR_RECT 5
#define SHADER_DRAW_BLUR 6
#define SHADER_TITLEBAR 7
#define SHADER_BOTTOM_SHADOW 8
#define SHADER_TOP_SHADOW 9

#endif
