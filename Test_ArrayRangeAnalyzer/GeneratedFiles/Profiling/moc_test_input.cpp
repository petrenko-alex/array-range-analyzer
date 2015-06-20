/****************************************************************************
** Meta object code from reading C++ file 'test_input.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../test_input.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_input.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Test_input_t {
    QByteArrayData data[10];
    char stringdata[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Test_input_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Test_input_t qt_meta_stringdata_Test_input = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Test_input"
QT_MOC_LITERAL(1, 11, 16), // "readVarInfo_data"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "readArrInfo_data"
QT_MOC_LITERAL(4, 46, 19), // "readExpression_data"
QT_MOC_LITERAL(5, 66, 13), // "readData_data"
QT_MOC_LITERAL(6, 80, 11), // "readVarInfo"
QT_MOC_LITERAL(7, 92, 11), // "readArrInfo"
QT_MOC_LITERAL(8, 104, 14), // "readExpression"
QT_MOC_LITERAL(9, 119, 8) // "readData"

    },
    "Test_input\0readVarInfo_data\0\0"
    "readArrInfo_data\0readExpression_data\0"
    "readData_data\0readVarInfo\0readArrInfo\0"
    "readExpression\0readData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Test_input[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Test_input::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Test_input *_t = static_cast<Test_input *>(_o);
        switch (_id) {
        case 0: _t->readVarInfo_data(); break;
        case 1: _t->readArrInfo_data(); break;
        case 2: _t->readExpression_data(); break;
        case 3: _t->readData_data(); break;
        case 4: _t->readVarInfo(); break;
        case 5: _t->readArrInfo(); break;
        case 6: _t->readExpression(); break;
        case 7: _t->readData(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Test_input::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Test_input.data,
      qt_meta_data_Test_input,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Test_input::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Test_input::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Test_input.stringdata))
        return static_cast<void*>(const_cast< Test_input*>(this));
    return QObject::qt_metacast(_clname);
}

int Test_input::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
