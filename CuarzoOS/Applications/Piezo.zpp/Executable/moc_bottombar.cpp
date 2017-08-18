/****************************************************************************
** Meta object code from reading C++ file 'bottombar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Code/Piezo/Headers/bottombar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bottombar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BottomBar_t {
    QByteArrayData data[8];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BottomBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BottomBar_t qt_meta_stringdata_BottomBar = {
    {
QT_MOC_LITERAL(0, 0, 9), // "BottomBar"
QT_MOC_LITERAL(1, 10, 12), // "sendLoopMode"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 15), // "sendShuffleMode"
QT_MOC_LITERAL(4, 40, 10), // "toggleLoop"
QT_MOC_LITERAL(5, 51, 13), // "toggleShuffle"
QT_MOC_LITERAL(6, 65, 14), // "setShuffleMode"
QT_MOC_LITERAL(7, 80, 11) // "setLoopMode"

    },
    "BottomBar\0sendLoopMode\0\0sendShuffleMode\0"
    "toggleLoop\0toggleShuffle\0setShuffleMode\0"
    "setLoopMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BottomBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   50,    2, 0x0a /* Public */,
       5,    0,   51,    2, 0x0a /* Public */,
       6,    1,   52,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void BottomBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BottomBar *_t = static_cast<BottomBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendLoopMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sendShuffleMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->toggleLoop(); break;
        case 3: _t->toggleShuffle(); break;
        case 4: _t->setShuffleMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setLoopMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BottomBar::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BottomBar::sendLoopMode)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BottomBar::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BottomBar::sendShuffleMode)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject BottomBar::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_BottomBar.data,
      qt_meta_data_BottomBar,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BottomBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BottomBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BottomBar.stringdata0))
        return static_cast<void*>(const_cast< BottomBar*>(this));
    return QFrame::qt_metacast(_clname);
}

int BottomBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void BottomBar::sendLoopMode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BottomBar::sendShuffleMode(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
