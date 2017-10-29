/****************************************************************************
** Meta object code from reading C++ file 'CProtocol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Headers/CProtocol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CProtocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CProtocol_t {
    QByteArrayData data[17];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CProtocol_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CProtocol_t qt_meta_stringdata_CProtocol = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CProtocol"
QT_MOC_LITERAL(1, 10, 9), // "connected"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 9), // "messageIn"
QT_MOC_LITERAL(4, 31, 12), // "sendPosition"
QT_MOC_LITERAL(5, 44, 3), // "pos"
QT_MOC_LITERAL(6, 48, 11), // "modeChanged"
QT_MOC_LITERAL(7, 60, 4), // "mode"
QT_MOC_LITERAL(8, 65, 14), // "opacityChanged"
QT_MOC_LITERAL(9, 80, 7), // "opacity"
QT_MOC_LITERAL(10, 88, 9), // "mouseGrab"
QT_MOC_LITERAL(11, 98, 8), // "blurTint"
QT_MOC_LITERAL(12, 107, 4), // "tint"
QT_MOC_LITERAL(13, 112, 9), // "blurLevel"
QT_MOC_LITERAL(14, 122, 5), // "level"
QT_MOC_LITERAL(15, 128, 8), // "blurRect"
QT_MOC_LITERAL(16, 137, 10) // "blurRemove"

    },
    "CProtocol\0connected\0\0messageIn\0"
    "sendPosition\0pos\0modeChanged\0mode\0"
    "opacityChanged\0opacity\0mouseGrab\0"
    "blurTint\0tint\0blurLevel\0level\0blurRect\0"
    "blurRemove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CProtocol[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    1,   66,    2, 0x08 /* Private */,
       6,    1,   69,    2, 0x08 /* Private */,
       8,    1,   72,    2, 0x08 /* Private */,
      10,    0,   75,    2, 0x08 /* Private */,
      11,    1,   76,    2, 0x08 /* Private */,
      13,    1,   79,    2, 0x08 /* Private */,
      15,    0,   82,    2, 0x08 /* Private */,
      16,    1,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    5,
    QMetaType::Void, QMetaType::UInt,    7,
    QMetaType::Void, QMetaType::Float,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,   12,
    QMetaType::Void, QMetaType::Float,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void CProtocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CProtocol *_t = static_cast<CProtocol *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->messageIn(); break;
        case 2: _t->sendPosition((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _t->modeChanged((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 4: _t->opacityChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->mouseGrab(); break;
        case 6: _t->blurTint((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->blurLevel((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->blurRect(); break;
        case 9: _t->blurRemove((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CProtocol::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CProtocol.data,
      qt_meta_data_CProtocol,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CProtocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CProtocol::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CProtocol.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CProtocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
