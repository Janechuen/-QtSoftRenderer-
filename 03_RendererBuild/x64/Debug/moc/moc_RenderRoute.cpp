/****************************************************************************
** Meta object code from reading C++ file 'RenderRoute.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Src/Render/RenderRoute.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RenderRoute.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RenderRoute_t {
    QByteArrayData data[14];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RenderRoute_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RenderRoute_t qt_meta_stringdata_RenderRoute = {
    {
QT_MOC_LITERAL(0, 0, 11), // "RenderRoute"
QT_MOC_LITERAL(1, 12, 8), // "frameOut"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 14), // "unsigned char*"
QT_MOC_LITERAL(4, 37, 5), // "image"
QT_MOC_LITERAL(5, 43, 4), // "loop"
QT_MOC_LITERAL(6, 48, 21), // "BindRenderingGeometry"
QT_MOC_LITERAL(7, 70, 7), // "Appdata"
QT_MOC_LITERAL(8, 78, 5), // "Mesh*"
QT_MOC_LITERAL(9, 84, 4), // "mesh"
QT_MOC_LITERAL(10, 89, 11), // "std::string"
QT_MOC_LITERAL(11, 101, 1), // "f"
QT_MOC_LITERAL(12, 103, 9), // "Pipeline*"
QT_MOC_LITERAL(13, 113, 8) // "pipeline"

    },
    "RenderRoute\0frameOut\0\0unsigned char*\0"
    "image\0loop\0BindRenderingGeometry\0"
    "Appdata\0Mesh*\0mesh\0std::string\0f\0"
    "Pipeline*\0pipeline"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RenderRoute[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   32,    2, 0x0a /* Public */,
       6,    3,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    0x80000000 | 7, 0x80000000 | 8, 0x80000000 | 10, 0x80000000 | 12,    9,   11,   13,

       0        // eod
};

void RenderRoute::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RenderRoute *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->frameOut((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 1: _t->loop(); break;
        case 2: { Appdata _r = _t->BindRenderingGeometry((*reinterpret_cast< Mesh*(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< Pipeline*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< Appdata*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RenderRoute::*)(unsigned char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RenderRoute::frameOut)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RenderRoute::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_RenderRoute.data,
    qt_meta_data_RenderRoute,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RenderRoute::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderRoute::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RenderRoute.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RenderRoute::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void RenderRoute::frameOut(unsigned char * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
