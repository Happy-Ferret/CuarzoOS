/****************************************************************************
** Meta object code from reading C++ file 'CPushButton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CFramework/Headers/CPushButton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CPushButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CPushButton_t {
    QByteArrayData data[8];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPushButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPushButton_t qt_meta_stringdata_CPushButton = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CPushButton"
QT_MOC_LITERAL(1, 12, 10), // "mouseEnter"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "mouseLeave"
QT_MOC_LITERAL(4, 35, 7), // "pressed"
QT_MOC_LITERAL(5, 43, 8), // "released"
QT_MOC_LITERAL(6, 52, 13), // "doubleClicked"
QT_MOC_LITERAL(7, 66, 7) // "clicked"

    },
    "CPushButton\0mouseEnter\0\0mouseLeave\0"
    "pressed\0released\0doubleClicked\0clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPushButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,
       6,    0,   48,    2, 0x06 /* Public */,
       7,    1,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void CPushButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CPushButton *_t = static_cast<CPushButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseEnter(); break;
        case 1: _t->mouseLeave(); break;
        case 2: _t->pressed(); break;
        case 3: _t->released(); break;
        case 4: _t->doubleClicked(); break;
        case 5: _t->clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CPushButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPushButton::mouseEnter)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CPushButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPushButton::mouseLeave)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CPushButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPushButton::pressed)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CPushButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPushButton::released)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CPushButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPushButton::doubleClicked)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (CPushButton::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPushButton::clicked)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject CPushButton::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CPushButton.data,
      qt_meta_data_CPushButton,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CPushButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPushButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CPushButton.stringdata0))
        return static_cast<void*>(const_cast< CPushButton*>(this));
    return QFrame::qt_metacast(_clname);
}

int CPushButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CPushButton::mouseEnter()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CPushButton::mouseLeave()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CPushButton::pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CPushButton::released()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CPushButton::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CPushButton::clicked(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
