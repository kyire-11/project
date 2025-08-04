/****************************************************************************
** Meta object code from reading C++ file 'modbusworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../modbusworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modbusworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModbusWorker_t {
    QByteArrayData data[36];
    char stringdata0[491];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModbusWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModbusWorker_t qt_meta_stringdata_ModbusWorker = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ModbusWorker"
QT_MOC_LITERAL(1, 13, 11), // "initialized"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "success"
QT_MOC_LITERAL(4, 34, 13), // "parametersSet"
QT_MOC_LITERAL(5, 48, 22), // "connectionStateChanged"
QT_MOC_LITERAL(6, 71, 9), // "connected"
QT_MOC_LITERAL(7, 81, 12), // "dataReceived"
QT_MOC_LITERAL(8, 94, 12), // "startAddress"
QT_MOC_LITERAL(9, 107, 16), // "QVector<quint16>"
QT_MOC_LITERAL(10, 124, 6), // "values"
QT_MOC_LITERAL(11, 131, 14), // "writeCompleted"
QT_MOC_LITERAL(12, 146, 7), // "address"
QT_MOC_LITERAL(13, 154, 5), // "value"
QT_MOC_LITERAL(14, 160, 13), // "errorOccurred"
QT_MOC_LITERAL(15, 174, 5), // "error"
QT_MOC_LITERAL(16, 180, 16), // "initModbusDevice"
QT_MOC_LITERAL(17, 197, 21), // "setupModbusParameters"
QT_MOC_LITERAL(18, 219, 8), // "portName"
QT_MOC_LITERAL(19, 228, 21), // "QSerialPort::BaudRate"
QT_MOC_LITERAL(20, 250, 8), // "baudRate"
QT_MOC_LITERAL(21, 259, 21), // "QSerialPort::DataBits"
QT_MOC_LITERAL(22, 281, 8), // "dataBits"
QT_MOC_LITERAL(23, 290, 21), // "QSerialPort::StopBits"
QT_MOC_LITERAL(24, 312, 8), // "stopBits"
QT_MOC_LITERAL(25, 321, 19), // "QSerialPort::Parity"
QT_MOC_LITERAL(26, 341, 6), // "parity"
QT_MOC_LITERAL(27, 348, 14), // "openSerialPort"
QT_MOC_LITERAL(28, 363, 15), // "closeSerialPort"
QT_MOC_LITERAL(29, 379, 20), // "requestReadRegisters"
QT_MOC_LITERAL(30, 400, 8), // "quantity"
QT_MOC_LITERAL(31, 409, 7), // "slaveId"
QT_MOC_LITERAL(32, 417, 20), // "requestWriteRegister"
QT_MOC_LITERAL(33, 438, 18), // "processNextRequest"
QT_MOC_LITERAL(34, 457, 19), // "handleReplyFinished"
QT_MOC_LITERAL(35, 477, 13) // "handleTimeout"

    },
    "ModbusWorker\0initialized\0\0success\0"
    "parametersSet\0connectionStateChanged\0"
    "connected\0dataReceived\0startAddress\0"
    "QVector<quint16>\0values\0writeCompleted\0"
    "address\0value\0errorOccurred\0error\0"
    "initModbusDevice\0setupModbusParameters\0"
    "portName\0QSerialPort::BaudRate\0baudRate\0"
    "QSerialPort::DataBits\0dataBits\0"
    "QSerialPort::StopBits\0stopBits\0"
    "QSerialPort::Parity\0parity\0openSerialPort\0"
    "closeSerialPort\0requestReadRegisters\0"
    "quantity\0slaveId\0requestWriteRegister\0"
    "processNextRequest\0handleReplyFinished\0"
    "handleTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModbusWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    1,   92,    2, 0x06 /* Public */,
       5,    1,   95,    2, 0x06 /* Public */,
       7,    2,   98,    2, 0x06 /* Public */,
      11,    3,  103,    2, 0x06 /* Public */,
      14,    1,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  113,    2, 0x0a /* Public */,
      17,    5,  114,    2, 0x0a /* Public */,
      27,    0,  125,    2, 0x0a /* Public */,
      28,    0,  126,    2, 0x0a /* Public */,
      29,    3,  127,    2, 0x0a /* Public */,
      32,    3,  134,    2, 0x0a /* Public */,
      33,    0,  141,    2, 0x08 /* Private */,
      34,    0,  142,    2, 0x08 /* Private */,
      35,    0,  143,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::UShort, 0x80000000 | 9,    8,   10,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::Bool,   12,   13,    3,
    QMetaType::Void, QMetaType::QString,   15,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 19, 0x80000000 | 21, 0x80000000 | 23, 0x80000000 | 25,   18,   20,   22,   24,   26,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::UChar,    8,   30,   31,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::UChar,   12,   13,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ModbusWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModbusWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initialized((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->parametersSet((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->connectionStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->dataReceived((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< QVector<quint16>(*)>(_a[2]))); break;
        case 4: _t->writeCompleted((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 5: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->initModbusDevice(); break;
        case 7: _t->setupModbusParameters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QSerialPort::BaudRate(*)>(_a[2])),(*reinterpret_cast< QSerialPort::DataBits(*)>(_a[3])),(*reinterpret_cast< QSerialPort::StopBits(*)>(_a[4])),(*reinterpret_cast< QSerialPort::Parity(*)>(_a[5]))); break;
        case 8: { bool _r = _t->openSerialPort();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->closeSerialPort(); break;
        case 10: _t->requestReadRegisters((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 11: _t->requestWriteRegister((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 12: _t->processNextRequest(); break;
        case 13: _t->handleReplyFinished(); break;
        case 14: _t->handleTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<quint16> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ModbusWorker::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModbusWorker::initialized)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ModbusWorker::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModbusWorker::parametersSet)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ModbusWorker::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModbusWorker::connectionStateChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ModbusWorker::*)(quint16 , QVector<quint16> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModbusWorker::dataReceived)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ModbusWorker::*)(quint16 , quint16 , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModbusWorker::writeCompleted)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ModbusWorker::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModbusWorker::errorOccurred)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ModbusWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ModbusWorker.data,
    qt_meta_data_ModbusWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ModbusWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModbusWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ModbusWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ModbusWorker::initialized(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModbusWorker::parametersSet(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ModbusWorker::connectionStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ModbusWorker::dataReceived(quint16 _t1, QVector<quint16> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ModbusWorker::writeCompleted(quint16 _t1, quint16 _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ModbusWorker::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
