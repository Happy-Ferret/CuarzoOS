#ifndef CCORE
#define CCORE

/* ------------------ CCore ------------------ */

// The way Crystals recognize the application

#define CLIENT_TYPE 0
#define CRYSTALS_TYPE 1

// Way Crystals identify a surface

#define WINDOW_MODE 0
#define FRAMELESS_MODE 1
#define TOPBAR_MODE 2
#define FILEMANAGER_MODE 3
#define DOCK_MODE 4

// Cuarzo Colors
#define BLUE QString("#009DDC")
#define VIOLET QString("#963D96")
#define RED QString("#E03A3E")
#define GREEN QString("#61BE4B")

// System root path ( For developing propouse )

#define SYSTEM_PATH QString("/home/e/Escritorio/CuarzoOS/CuarzoOS")

/* ------------------------------------------------------------------
                       Messages to Crystals
 ------------------------------------------------------------------ */

// Register App
#define REGISTER_APP 0
typedef struct{
    unsigned int type = REGISTER_APP; // Message type
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
    unsigned int opacity; // Opacity
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

/* ------------------------------------------------------------------
                       Messages from Crystals
 ------------------------------------------------------------------ */


// App Registered Event
#define REGISTERED_APP 0
typedef struct{
    unsigned int type; // Message type
}RegisteredAppStruct;

// Surface Id Registered
#define REGISTERED_SURFACE 1
typedef struct{
    unsigned int type; // Message type
    unsigned int id; // Message type
}RegisteredSurfaceStruct;

// Surface Moved
#define SURFACE_MOVED 2
typedef struct{
    unsigned int type; // Message type
    unsigned int id; // Surface id
    int x; // X position
    int y; // Y position
}SurfaceMovedStruct;

// Surface Escaled
#define SURFACE_SCALED 3
typedef struct{
    unsigned int type; // Message type
    unsigned int id; // Surface id
    unsigned int width; // X position
   unsigned  int height; // Y position
}SurfaceScaledStruct;

// Surface Closed
#define SURFACE_CLOSED 4
typedef struct{
    unsigned int type; // Message type
    unsigned int id; // Surface id
}SurfaceClosedStruct;

// Surface Minimized
#define SURFACE_MINIMIZED 5
typedef struct{
    unsigned int type; // Message type
    unsigned int id; // Surface id
    bool state; // Minimize Option
}SurfaceMinimizedStruct;

// Surface Expanded
#define SURFACE_EXPANDED 6
typedef struct{
    unsigned int type; // Message type
    unsigned int id; // Surface id
    unsigned int mode; // Expand mode
}SurfaceExpandedStruct;

#endif


