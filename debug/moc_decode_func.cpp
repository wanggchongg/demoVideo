/****************************************************************************
** Meta object code from reading C++ file 'decode_func.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../decode_func.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'decode_func.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Object_t {
    QByteArrayData data[7];
    char stringdata[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Object_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Object_t qt_meta_stringdata_Object = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 12),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 17),
QT_MOC_LITERAL(4, 39, 6),
QT_MOC_LITERAL(5, 46, 15),
QT_MOC_LITERAL(6, 62, 11)
    },
    "Object\0dataObjReady\0\0decodeRateChanged\0"
    "decode\0loseRateChanged\0dealTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Object[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   43,    2, 0x0a /* Public */,
       5,    0,   44,    2, 0x0a /* Public */,
       6,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Object::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Object *_t = static_cast<Object *>(_o);
        switch (_id) {
        case 0: _t->dataObjReady(); break;
        case 1: _t->decodeRateChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->decode(); break;
        case 3: _t->loseRateChanged(); break;
        case 4: _t->dealTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Object::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Object::dataObjReady)) {
                *result = 0;
            }
        }
        {
            typedef void (Object::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Object::decodeRateChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Object::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Object.data,
      qt_meta_data_Object,  qt_static_metacall, 0, 0}
};


const QMetaObject *Object::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Object::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Object.stringdata))
        return static_cast<void*>(const_cast< Object*>(this));
    return QObject::qt_metacast(_clname);
}

int Object::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Object::dataObjReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Object::decodeRateChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_DecodeThread_t {
    QByteArrayData data[6];
    char stringdata[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DecodeThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DecodeThread_t qt_meta_stringdata_DecodeThread = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 11),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 13),
QT_MOC_LITERAL(4, 40, 14),
QT_MOC_LITERAL(5, 55, 17)
    },
    "DecodeThread\0dataArrived\0\0dataDecoReady\0"
    "loseRateChange\0decodeRateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DecodeThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    2,

       0        // eod
};

void DecodeThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DecodeThread *_t = static_cast<DecodeThread *>(_o);
        switch (_id) {
        case 0: _t->dataArrived(); break;
        case 1: _t->dataDecoReady(); break;
        case 2: _t->loseRateChange(); break;
        case 3: _t->decodeRateChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DecodeThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DecodeThread::dataArrived)) {
                *result = 0;
            }
        }
        {
            typedef void (DecodeThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DecodeThread::dataDecoReady)) {
                *result = 1;
            }
        }
        {
            typedef void (DecodeThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DecodeThread::loseRateChange)) {
                *result = 2;
            }
        }
        {
            typedef void (DecodeThread::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DecodeThread::decodeRateChanged)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject DecodeThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DecodeThread.data,
      qt_meta_data_DecodeThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *DecodeThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DecodeThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DecodeThread.stringdata))
        return static_cast<void*>(const_cast< DecodeThread*>(this));
    return QThread::qt_metacast(_clname);
}

int DecodeThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DecodeThread::dataArrived()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DecodeThread::dataDecoReady()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void DecodeThread::loseRateChange()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void DecodeThread::decodeRateChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
