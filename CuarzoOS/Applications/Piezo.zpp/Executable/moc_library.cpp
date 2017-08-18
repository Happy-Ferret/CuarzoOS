/****************************************************************************
** Meta object code from reading C++ file 'library.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Code/Piezo/Headers/library.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'library.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Library_t {
    QByteArrayData data[22];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Library_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Library_t qt_meta_stringdata_Library = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Library"
QT_MOC_LITERAL(1, 8, 15), // "userInfoChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "songAddProgress"
QT_MOC_LITERAL(4, 41, 15), // "songAddCanceled"
QT_MOC_LITERAL(5, 57, 15), // "songAddComplete"
QT_MOC_LITERAL(6, 73, 15), // "songDeletionEnd"
QT_MOC_LITERAL(7, 89, 15), // "deleteFromCloud"
QT_MOC_LITERAL(8, 105, 15), // "deleteFromLocal"
QT_MOC_LITERAL(9, 121, 14), // "deleteFromBoth"
QT_MOC_LITERAL(10, 136, 11), // "setUserInfo"
QT_MOC_LITERAL(11, 148, 3), // "res"
QT_MOC_LITERAL(12, 152, 8), // "getCloud"
QT_MOC_LITERAL(13, 161, 12), // "cloudLibrary"
QT_MOC_LITERAL(14, 174, 12), // "songUploaded"
QT_MOC_LITERAL(15, 187, 8), // "songData"
QT_MOC_LITERAL(16, 196, 15), // "startMusicAdder"
QT_MOC_LITERAL(17, 212, 11), // "deleteSongs"
QT_MOC_LITERAL(18, 224, 13), // "songsToDelete"
QT_MOC_LITERAL(19, 238, 4), // "from"
QT_MOC_LITERAL(20, 243, 10), // "songAddEnd"
QT_MOC_LITERAL(21, 254, 6) // "newLib"

    },
    "Library\0userInfoChanged\0\0songAddProgress\0"
    "songAddCanceled\0songAddComplete\0"
    "songDeletionEnd\0deleteFromCloud\0"
    "deleteFromLocal\0deleteFromBoth\0"
    "setUserInfo\0res\0getCloud\0cloudLibrary\0"
    "songUploaded\0songData\0startMusicAdder\0"
    "deleteSongs\0songsToDelete\0from\0"
    "songAddEnd\0newLib"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Library[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    1,   85,    2, 0x06 /* Public */,
       4,    0,   88,    2, 0x06 /* Public */,
       5,    0,   89,    2, 0x06 /* Public */,
       6,    0,   90,    2, 0x06 /* Public */,
       7,    1,   91,    2, 0x06 /* Public */,
       8,    1,   94,    2, 0x06 /* Public */,
       9,    1,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  100,    2, 0x0a /* Public */,
      12,    1,  103,    2, 0x0a /* Public */,
      14,    1,  106,    2, 0x0a /* Public */,
      16,    0,  109,    2, 0x0a /* Public */,
      17,    2,  110,    2, 0x0a /* Public */,
      20,    1,  115,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QVariantMap,   11,
    QMetaType::Void, QMetaType::QVariantMap,   13,
    QMetaType::Void, QMetaType::QVariantMap,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantList, QMetaType::QString,   18,   19,
    QMetaType::Void, QMetaType::QVariantList,   21,

       0        // eod
};

void Library::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Library *_t = static_cast<Library *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->userInfoChanged(); break;
        case 1: _t->songAddProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->songAddCanceled(); break;
        case 3: _t->songAddComplete(); break;
        case 4: _t->songDeletionEnd(); break;
        case 5: _t->deleteFromCloud((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->deleteFromLocal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->deleteFromBoth((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setUserInfo((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 9: _t->getCloud((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 10: _t->songUploaded((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 11: _t->startMusicAdder(); break;
        case 12: _t->deleteSongs((*reinterpret_cast< QVariantList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->songAddEnd((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Library::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Library::userInfoChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Library::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Library::songAddProgress)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Library::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Library::songAddCanceled)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Library::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Library::songAddComplete)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Library::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Library::songDeletionEnd)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Library::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Library::deleteFromCloud)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Library::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Library::deleteFromLocal)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Library::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Library::deleteFromBoth)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject Library::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Library.data,
      qt_meta_data_Library,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Library::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Library::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Library.stringdata0))
        return static_cast<void*>(const_cast< Library*>(this));
    return QObject::qt_metacast(_clname);
}

int Library::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Library::userInfoChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Library::songAddProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Library::songAddCanceled()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Library::songAddComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Library::songDeletionEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Library::deleteFromCloud(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Library::deleteFromLocal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Library::deleteFromBoth(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
