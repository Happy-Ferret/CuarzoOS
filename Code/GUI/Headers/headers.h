#ifndef HEADERS_H
#define HEADERS_H

// QT
#include <QApplication>
#include <QWidget>
#include <QLocalSocket>


/* ------------------ Messages from Crystals ------------------ */

// Titlebar request
#define TITLEBAR_REQUEST 20
typedef struct{
    unsigned int type; // Message type
    unsigned int forPid; // Process id of the surface
    unsigned int forId; // Surface which needs the titlebar
    unsigned int width; // Surface width
    char title[128]; // Surface Title
}TitlebarRequestStruct;

/* ------------------ Messages to Crystals ------------------ */

// Titlebar Created
#define TITLEBAR_CREATED 20
typedef struct{
    unsigned int type = TITLEBAR_CREATED ; // Message type
    unsigned int id; // TitleBar id
    unsigned int forPid; // Process id of the surface
    unsigned int forId; // Surface which needs the titlebar
}TitlebarCreatedStruct;

#endif // HEADERS_H
