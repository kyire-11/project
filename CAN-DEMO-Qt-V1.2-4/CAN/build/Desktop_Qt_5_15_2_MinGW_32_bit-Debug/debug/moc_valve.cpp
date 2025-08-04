/****************************************************************************
** Meta object code from reading C++ file 'valve.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../valve.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'valve.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_valve_t {
    QByteArrayData data[21];
    char stringdata0[301];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_valve_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_valve_t qt_meta_stringdata_valve = {
    {
QT_MOC_LITERAL(0, 0, 5), // "valve"
QT_MOC_LITERAL(1, 6, 24), // "onSpecificIdDataReceived"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 12), // "VCI_CAN_OBJ*"
QT_MOC_LITERAL(4, 45, 3), // "vci"
QT_MOC_LITERAL(5, 49, 5), // "dwRel"
QT_MOC_LITERAL(6, 55, 7), // "channel"
QT_MOC_LITERAL(7, 63, 24), // "on_pushButton_14_clicked"
QT_MOC_LITERAL(8, 88, 13), // "DisplayChart1"
QT_MOC_LITERAL(9, 102, 13), // "DisplayChart2"
QT_MOC_LITERAL(10, 116, 11), // "ReData_Slot"
QT_MOC_LITERAL(11, 128, 24), // "on_pushButton_17_clicked"
QT_MOC_LITERAL(12, 153, 17), // "showPointToolTip0"
QT_MOC_LITERAL(13, 171, 5), // "point"
QT_MOC_LITERAL(14, 177, 5), // "state"
QT_MOC_LITERAL(15, 183, 17), // "showPointToolTip1"
QT_MOC_LITERAL(16, 201, 17), // "showPointToolTip2"
QT_MOC_LITERAL(17, 219, 17), // "showPointToolTip3"
QT_MOC_LITERAL(18, 237, 17), // "showPointToolTip4"
QT_MOC_LITERAL(19, 255, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(20, 277, 23) // "on_pushButton_2_clicked"

    },
    "valve\0onSpecificIdDataReceived\0\0"
    "VCI_CAN_OBJ*\0vci\0dwRel\0channel\0"
    "on_pushButton_14_clicked\0DisplayChart1\0"
    "DisplayChart2\0ReData_Slot\0"
    "on_pushButton_17_clicked\0showPointToolTip0\0"
    "point\0state\0showPointToolTip1\0"
    "showPointToolTip2\0showPointToolTip3\0"
    "showPointToolTip4\0on_pushButton_clicked\0"
    "on_pushButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_valve[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   79,    2, 0x08 /* Private */,
       7,    0,   86,    2, 0x08 /* Private */,
       8,    0,   87,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    0,   89,    2, 0x08 /* Private */,
      11,    0,   90,    2, 0x08 /* Private */,
      12,    2,   91,    2, 0x08 /* Private */,
      15,    2,   96,    2, 0x08 /* Private */,
      16,    2,  101,    2, 0x08 /* Private */,
      17,    2,  106,    2, 0x08 /* Private */,
      18,    2,  111,    2, 0x08 /* Private */,
      19,    0,  116,    2, 0x08 /* Private */,
      20,    0,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt, QMetaType::UInt,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,   13,   14,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,   13,   14,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,   13,   14,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,   13,   14,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,   13,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void valve::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<valve *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSpecificIdDataReceived((*reinterpret_cast< VCI_CAN_OBJ*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 1: _t->on_pushButton_14_clicked(); break;
        case 2: _t->DisplayChart1(); break;
        case 3: _t->DisplayChart2(); break;
        case 4: _t->ReData_Slot(); break;
        case 5: _t->on_pushButton_17_clicked(); break;
        case 6: _t->showPointToolTip0((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->showPointToolTip1((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->showPointToolTip2((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: _t->showPointToolTip3((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 10: _t->showPointToolTip4((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 11: _t->on_pushButton_clicked(); break;
        case 12: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject valve::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_valve.data,
    qt_meta_data_valve,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *valve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *valve::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_valve.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int valve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
