/****************************************************************************
** Meta object code from reading C++ file 'CApplication.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Code/Crystals/ClientDemo/CFramework/CApplication.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CApplication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CApplication_t {
    QByteArrayData data[14];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CApplication_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CApplication_t qt_meta_stringdata_CApplication = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CApplication"
QT_MOC_LITERAL(1, 13, 3), // "run"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 9), // "connected"
QT_MOC_LITERAL(4, 28, 9), // "messageIn"
QT_MOC_LITERAL(5, 38, 12), // "sendPosition"
QT_MOC_LITERAL(6, 51, 3), // "pos"
QT_MOC_LITERAL(7, 55, 12), // "titleChanged"
QT_MOC_LITERAL(8, 68, 5), // "title"
QT_MOC_LITERAL(9, 74, 11), // "modeChanged"
QT_MOC_LITERAL(10, 86, 4), // "mode"
QT_MOC_LITERAL(11, 91, 14), // "opacityChanged"
QT_MOC_LITERAL(12, 106, 7), // "opacity"
QT_MOC_LITERAL(13, 114, 16) // "blurStateChanged"

    },
    "CApplication\0run\0\0connected\0messageIn\0"
    "sendPosition\0pos\0titleChanged\0title\0"
    "modeChanged\0mode\0opacityChanged\0opacity\0"
    "blurStateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CApplication[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    1,   57,    2, 0x0a /* Public */,
       7,    1,   60,    2, 0x0a /* Public */,
       9,    1,   63,    2, 0x0a /* Public */,
      11,    1,   66,    2, 0x0a /* Public */,
      13,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::UInt,   10,
    QMetaType::Void, QMetaType::UInt,   12,
    QMetaType::Void, QMetaType::Bool,   10,

       0        // eod
};

void CApplication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CApplication *_t = static_cast<CApplication *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->run(); break;
        case 1: _t->connected(); break;
        case 2: _t->messageIn(); break;
        case 3: _t->sendPosition((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->titleChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->modeChanged((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 6: _t->opacityChanged((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 7: _t->blurStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CApplication::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CApplication::run)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CApplication::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_CApplication.data,
      qt_meta_data_CApplication,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CApplication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CApplication.stringdata0))
        return static_cast<void*>(const_cast< CApplication*>(this));
    return QApplication::qt_metacast(_clname);
}

int CApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CApplication::run()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
