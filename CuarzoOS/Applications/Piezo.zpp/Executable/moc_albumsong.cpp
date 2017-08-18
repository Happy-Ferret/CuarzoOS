/****************************************************************************
** Meta object code from reading C++ file 'albumsong.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Code/Piezo/Headers/albumsong.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'albumsong.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AlbumSong_t {
    QByteArrayData data[15];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AlbumSong_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AlbumSong_t qt_meta_stringdata_AlbumSong = {
    {
QT_MOC_LITERAL(0, 0, 9), // "AlbumSong"
QT_MOC_LITERAL(1, 10, 12), // "songSelected"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "songPlayed"
QT_MOC_LITERAL(4, 35, 16), // "songRightClicked"
QT_MOC_LITERAL(5, 52, 12), // "showSongMenu"
QT_MOC_LITERAL(6, 65, 8), // "syncSong"
QT_MOC_LITERAL(7, 74, 14), // "cancelDownload"
QT_MOC_LITERAL(8, 89, 11), // "setSelected"
QT_MOC_LITERAL(9, 101, 10), // "setPlaying"
QT_MOC_LITERAL(10, 112, 7), // "setData"
QT_MOC_LITERAL(11, 120, 11), // "setLocation"
QT_MOC_LITERAL(12, 132, 11), // "syncClicked"
QT_MOC_LITERAL(13, 144, 10), // "piePressed"
QT_MOC_LITERAL(14, 155, 11) // "morePressed"

    },
    "AlbumSong\0songSelected\0\0songPlayed\0"
    "songRightClicked\0showSongMenu\0syncSong\0"
    "cancelDownload\0setSelected\0setPlaying\0"
    "setData\0setLocation\0syncClicked\0"
    "piePressed\0morePressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AlbumSong[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       3,    1,   82,    2, 0x06 /* Public */,
       4,    1,   85,    2, 0x06 /* Public */,
       5,    1,   88,    2, 0x06 /* Public */,
       6,    1,   91,    2, 0x06 /* Public */,
       7,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   97,    2, 0x0a /* Public */,
       9,    1,  100,    2, 0x0a /* Public */,
      10,    1,  103,    2, 0x0a /* Public */,
      11,    1,  106,    2, 0x0a /* Public */,
      12,    0,  109,    2, 0x0a /* Public */,
      13,    0,  110,    2, 0x0a /* Public */,
      14,    0,  111,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QVariantMap,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AlbumSong::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AlbumSong *_t = static_cast<AlbumSong *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->songSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->songPlayed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->songRightClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->showSongMenu((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->syncSong((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->cancelDownload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setPlaying((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setData((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 9: _t->setLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->syncClicked(); break;
        case 11: _t->piePressed(); break;
        case 12: _t->morePressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AlbumSong::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AlbumSong::songSelected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AlbumSong::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AlbumSong::songPlayed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AlbumSong::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AlbumSong::songRightClicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AlbumSong::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AlbumSong::showSongMenu)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (AlbumSong::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AlbumSong::syncSong)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (AlbumSong::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AlbumSong::cancelDownload)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject AlbumSong::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_AlbumSong.data,
      qt_meta_data_AlbumSong,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AlbumSong::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AlbumSong::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AlbumSong.stringdata0))
        return static_cast<void*>(const_cast< AlbumSong*>(this));
    return QFrame::qt_metacast(_clname);
}

int AlbumSong::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void AlbumSong::songSelected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AlbumSong::songPlayed(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AlbumSong::songRightClicked(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AlbumSong::showSongMenu(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AlbumSong::syncSong(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AlbumSong::cancelDownload(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
