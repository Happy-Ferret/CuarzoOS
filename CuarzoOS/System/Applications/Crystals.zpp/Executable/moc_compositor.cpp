/****************************************************************************
** Meta object code from reading C++ file 'compositor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../Code/Crystals/headers/compositor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'compositor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Compositor_t {
    QByteArrayData data[26];
    char stringdata0[368];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Compositor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Compositor_t qt_meta_stringdata_Compositor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Compositor"
QT_MOC_LITERAL(1, 11, 11), // "startResize"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "edge"
QT_MOC_LITERAL(4, 29, 8), // "anchored"
QT_MOC_LITERAL(5, 38, 11), // "dragStarted"
QT_MOC_LITERAL(6, 50, 5), // "View*"
QT_MOC_LITERAL(7, 56, 8), // "dragIcon"
QT_MOC_LITERAL(8, 65, 17), // "readyToLaunchApps"
QT_MOC_LITERAL(9, 83, 13), // "triggerRender"
QT_MOC_LITERAL(10, 97, 18), // "newClientConnected"
QT_MOC_LITERAL(11, 116, 16), // "newClientMessage"
QT_MOC_LITERAL(12, 133, 12), // "updateCursor"
QT_MOC_LITERAL(13, 146, 18), // "socketDisconnected"
QT_MOC_LITERAL(14, 165, 24), // "surfaceHasContentChanged"
QT_MOC_LITERAL(15, 190, 16), // "surfaceDestroyed"
QT_MOC_LITERAL(16, 207, 18), // "surfaceSizeChanged"
QT_MOC_LITERAL(17, 226, 20), // "viewSurfaceDestroyed"
QT_MOC_LITERAL(18, 247, 9), // "startDrag"
QT_MOC_LITERAL(19, 257, 12), // "titleChanged"
QT_MOC_LITERAL(20, 270, 16), // "onSurfaceCreated"
QT_MOC_LITERAL(21, 287, 16), // "QWaylandSurface*"
QT_MOC_LITERAL(22, 304, 7), // "surface"
QT_MOC_LITERAL(23, 312, 16), // "onWlShellCreated"
QT_MOC_LITERAL(24, 329, 23), // "QWaylandWlShellSurface*"
QT_MOC_LITERAL(25, 353, 14) // "wlShellSurface"

    },
    "Compositor\0startResize\0\0edge\0anchored\0"
    "dragStarted\0View*\0dragIcon\0readyToLaunchApps\0"
    "triggerRender\0newClientConnected\0"
    "newClientMessage\0updateCursor\0"
    "socketDisconnected\0surfaceHasContentChanged\0"
    "surfaceDestroyed\0surfaceSizeChanged\0"
    "viewSurfaceDestroyed\0startDrag\0"
    "titleChanged\0onSurfaceCreated\0"
    "QWaylandSurface*\0surface\0onWlShellCreated\0"
    "QWaylandWlShellSurface*\0wlShellSurface"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Compositor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x06 /* Public */,
       5,    1,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  102,    2, 0x0a /* Public */,
       9,    0,  103,    2, 0x0a /* Public */,
      10,    0,  104,    2, 0x0a /* Public */,
      11,    0,  105,    2, 0x0a /* Public */,
      12,    0,  106,    2, 0x0a /* Public */,
      13,    0,  107,    2, 0x08 /* Private */,
      14,    0,  108,    2, 0x08 /* Private */,
      15,    0,  109,    2, 0x08 /* Private */,
      16,    0,  110,    2, 0x08 /* Private */,
      17,    0,  111,    2, 0x08 /* Private */,
      18,    0,  112,    2, 0x08 /* Private */,
      19,    0,  113,    2, 0x08 /* Private */,
      20,    1,  114,    2, 0x08 /* Private */,
      23,    1,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 24,   25,

       0        // eod
};

void Compositor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Compositor *_t = static_cast<Compositor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startResize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->dragStarted((*reinterpret_cast< View*(*)>(_a[1]))); break;
        case 2: _t->readyToLaunchApps(); break;
        case 3: _t->triggerRender(); break;
        case 4: _t->newClientConnected(); break;
        case 5: _t->newClientMessage(); break;
        case 6: _t->updateCursor(); break;
        case 7: _t->socketDisconnected(); break;
        case 8: _t->surfaceHasContentChanged(); break;
        case 9: _t->surfaceDestroyed(); break;
        case 10: _t->surfaceSizeChanged(); break;
        case 11: _t->viewSurfaceDestroyed(); break;
        case 12: _t->startDrag(); break;
        case 13: _t->titleChanged(); break;
        case 14: _t->onSurfaceCreated((*reinterpret_cast< QWaylandSurface*(*)>(_a[1]))); break;
        case 15: _t->onWlShellCreated((*reinterpret_cast< QWaylandWlShellSurface*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< View* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWaylandSurface* >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWaylandWlShellSurface* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Compositor::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Compositor::startResize)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Compositor::*_t)(View * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Compositor::dragStarted)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Compositor::staticMetaObject = {
    { &QWaylandCompositor::staticMetaObject, qt_meta_stringdata_Compositor.data,
      qt_meta_data_Compositor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Compositor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Compositor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Compositor.stringdata0))
        return static_cast<void*>(this);
    return QWaylandCompositor::qt_metacast(_clname);
}

int Compositor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWaylandCompositor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Compositor::startResize(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Compositor::dragStarted(View * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
