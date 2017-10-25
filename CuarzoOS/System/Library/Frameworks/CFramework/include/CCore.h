#ifndef CCORE
#define CCORE

/* ------------------ CCore ------------------ */

// The way Crystals recognize the application

#define CLIENT_TYPE 0
#define CRYSTALS_TYPE 1
#define PARADISO_TYPE 2


// Way Crystals identify a surface

#define WINDOW_MODE 0
#define FRAMELESS_MODE 1
#define DOCK_MODE 2
#define PARADISO_MODE 3
#define MENU_MODE 4


// Materialize Colors
#define RED QString("#f44336")
#define PINK QString("#e91e63")
#define PURPLE QString("#9c27b0")
#define DEEP_PURPLE QString("#673ab7")
#define INDIGO QString("#3f51b5")
#define BLUE QString("#2196f3")
#define LIGHT_BLUE QString("#03a9f4")
#define CYAN QString("#00bcd4")
#define TEAL QString("#009688")
#define GREEN QString("#4caf50")
#define LIGHT_GREEN QString("#8bc34a")
#define LIME QString("#cddc39")
#define YELLOW QString("#ffeb3b")
#define AMBER QString("#ffc107")
#define ORANGE QString("#ff9800")
#define DEEP_ORANGE QString("#ff5722")
#define BROWN QString("#795548")
#define GRAY QString("#9e9e9e")
#define DEEP_GRAY QString("#424242")
#define BLUE_GRAY QString("#607d8b")


// System root path ( For developing propouse )

#define SYSTEM_PATH QString("/home/e/Escritorio/CuarzoOS/CuarzoOS")


/* ------------------ Messages From Clients ------------------ */

#define REGISTER_APP 0
#define SURFACE_CONFIG 1
#define SURFACE_ROLE 2
#define SURFACE_POS 3
#define SURFACE_GRAB 4
#define SURFACE_OPACITY 5
#define SURFACE_MINIMIZE 6
#define SURFACE_EXPAND 7
#define SURFACE_BLUR_CREATE 8
#define SURFACE_BLUR_TINT 9
#define SURFACE_BLUR_LEVEL 10
#define SURFACE_BLUR_RECT 11
#define SURFACE_BLUR_REMOVE 12

typedef struct
{
    unsigned int type = REGISTER_APP;
    unsigned int pid;
    unsigned int appType;
}
RegisterAppStruct;

typedef struct
{
    unsigned int type = SURFACE_CONFIG;
    unsigned int id;
    unsigned int role;
    int x;
    int y;
    unsigned int opacity;
}
SurfaceConfigStruct;

typedef struct
{
    unsigned int type = SURFACE_ROLE;
    unsigned int id;
    unsigned int role;
}
SurfaceRoleStruct;

typedef struct
{
    unsigned int type = SURFACE_POS;
    unsigned int id;
    int x;
    int y;
}
SurfacePosStruct;

typedef struct
{
    unsigned int type = SURFACE_GRAB;
    unsigned int id;
}
SurfaceGrabStruct;

typedef struct
{
    unsigned int type = SURFACE_OPACITY;
    unsigned int id;
    unsigned int opacity;
}
SurfaceOpacityStruct;

typedef struct
{
    unsigned int type = SURFACE_MINIMIZE;
    unsigned int id;
    bool minimize;
}
SurfaceMinimizeStruct;

typedef struct
{
    unsigned int type = SURFACE_EXPAND;
    unsigned int id;
    bool expand;
    unsigned int expandMode;
}
SurfaceExpandStruct;

typedef struct
{
    unsigned int type = SURFACE_BLUR_CREATE;
    unsigned int surfaceId;
    unsigned int blurId;
    int x;
    int y;
    unsigned int w;
    unsigned int h;
    float tint;
    float level;
}
SurfaceBlurCreateStruct;

typedef struct
{
    unsigned int type = SURFACE_BLUR_TINT;
    unsigned int surfaceId;
    unsigned int blurId;
    float tint;
}
SurfaceBlurTintStruct;

typedef struct
{
    unsigned int type = SURFACE_BLUR_LEVEL;
    unsigned int surfaceId;
    unsigned int blurId;
    float level;
}
SurfaceBlurLevelStruct;

typedef struct
{
    unsigned int type = SURFACE_BLUR_RECT;
    unsigned int surfaceId;
    unsigned int blurId;
    int x;
    int y;
    unsigned int w;
    unsigned int h;
}
SurfaceBlurRectStruct;

typedef struct
{
    unsigned int type = SURFACE_BLUR_REMOVE;
    unsigned int surfaceId;
    unsigned int blurId;
}
SurfaceBlurRemoveStruct;



/* ------------------ Messages to Clients ------------------ */

#define REGISTERED_APP 0
#define REGISTERED_SURFACE 1
#define SURFACE_SCALED 2
#define SURFACE_MOVED 3


typedef struct
{
    unsigned int type = REGISTERED_APP;
}
RegisteredAppStruct;

typedef struct
{
    unsigned int type = REGISTERED_SURFACE;
    unsigned int id;
}
RegisteredSurfaceStruct;

typedef struct
{
    unsigned int type = SURFACE_SCALED;
    unsigned int id;
    unsigned int width;
    unsigned  int height;
}
SurfaceScaledStruct;

typedef struct
{
    unsigned int type = SURFACE_MOVED;
    unsigned int id;
    int x;
    int y;
}
SurfaceMovedStruct;

#endif


