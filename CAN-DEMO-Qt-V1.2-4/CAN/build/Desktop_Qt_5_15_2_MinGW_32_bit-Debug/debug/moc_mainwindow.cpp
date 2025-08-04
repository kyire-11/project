/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[115];
    char stringdata0[2108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "resized"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "dataReceived"
QT_MOC_LITERAL(4, 33, 7), // "address"
QT_MOC_LITERAL(5, 41, 16), // "QVector<quint16>"
QT_MOC_LITERAL(6, 58, 6), // "values"
QT_MOC_LITERAL(7, 65, 14), // "writeCompleted"
QT_MOC_LITERAL(8, 80, 5), // "value"
QT_MOC_LITERAL(9, 86, 7), // "success"
QT_MOC_LITERAL(10, 94, 13), // "errorOccurred"
QT_MOC_LITERAL(11, 108, 11), // "errorString"
QT_MOC_LITERAL(12, 120, 17), // "exceptionReceived"
QT_MOC_LITERAL(13, 138, 13), // "exceptionCode"
QT_MOC_LITERAL(14, 152, 17), // "setupModbusParams"
QT_MOC_LITERAL(15, 170, 8), // "portName"
QT_MOC_LITERAL(16, 179, 21), // "QSerialPort::BaudRate"
QT_MOC_LITERAL(17, 201, 8), // "baudRate"
QT_MOC_LITERAL(18, 210, 21), // "QSerialPort::DataBits"
QT_MOC_LITERAL(19, 232, 8), // "dataBits"
QT_MOC_LITERAL(20, 241, 21), // "QSerialPort::StopBits"
QT_MOC_LITERAL(21, 263, 8), // "stopBits"
QT_MOC_LITERAL(22, 272, 19), // "QSerialPort::Parity"
QT_MOC_LITERAL(23, 292, 6), // "parity"
QT_MOC_LITERAL(24, 299, 17), // "onGetProtocolData"
QT_MOC_LITERAL(25, 317, 12), // "VCI_CAN_OBJ*"
QT_MOC_LITERAL(26, 330, 3), // "vci"
QT_MOC_LITERAL(27, 334, 5), // "dwRel"
QT_MOC_LITERAL(28, 340, 7), // "channel"
QT_MOC_LITERAL(29, 348, 20), // "on_savetxtBt_clicked"
QT_MOC_LITERAL(30, 369, 22), // "on_savetxtBt_2_clicked"
QT_MOC_LITERAL(31, 392, 11), // "saveNewData"
QT_MOC_LITERAL(32, 404, 14), // "onSaveFinished"
QT_MOC_LITERAL(33, 419, 15), // "onErrorOccurred"
QT_MOC_LITERAL(34, 435, 12), // "errorMessage"
QT_MOC_LITERAL(35, 448, 19), // "onAdjustAxesClicked"
QT_MOC_LITERAL(36, 468, 15), // "updateTimeLabel"
QT_MOC_LITERAL(37, 484, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(38, 506, 18), // "on_sendBtn_clicked"
QT_MOC_LITERAL(39, 525, 23), // "on_cleanListBtn_clicked"
QT_MOC_LITERAL(40, 549, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(41, 573, 14), // "onTimerTimeout"
QT_MOC_LITERAL(42, 588, 15), // "onTimerTimeout1"
QT_MOC_LITERAL(43, 604, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(44, 628, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(45, 652, 18), // "on_cycleBt_clicked"
QT_MOC_LITERAL(46, 671, 17), // "on_bautBt_clicked"
QT_MOC_LITERAL(47, 689, 17), // "on_LVDTBt_clicked"
QT_MOC_LITERAL(48, 707, 18), // "on_recovBt_clicked"
QT_MOC_LITERAL(49, 726, 17), // "on_saveBt_clicked"
QT_MOC_LITERAL(50, 744, 19), // "on_sendfaBt_clicked"
QT_MOC_LITERAL(51, 764, 24), // "on_pushButton_13_clicked"
QT_MOC_LITERAL(52, 789, 24), // "on_pushButton_16_clicked"
QT_MOC_LITERAL(53, 814, 17), // "on_tranBt_clicked"
QT_MOC_LITERAL(54, 832, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(55, 856, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(56, 880, 12), // "parseTxtData"
QT_MOC_LITERAL(57, 893, 8), // "filePath"
QT_MOC_LITERAL(58, 902, 9), // "drawChart"
QT_MOC_LITERAL(59, 912, 21), // "updateChartVisibility"
QT_MOC_LITERAL(60, 934, 26), // "on_checkBox_5_stateChanged"
QT_MOC_LITERAL(61, 961, 4), // "arg1"
QT_MOC_LITERAL(62, 966, 26), // "on_checkBox_6_stateChanged"
QT_MOC_LITERAL(63, 993, 26), // "on_checkBox_7_stateChanged"
QT_MOC_LITERAL(64, 1020, 26), // "on_checkBox_8_stateChanged"
QT_MOC_LITERAL(65, 1047, 26), // "on_checkBox_9_stateChanged"
QT_MOC_LITERAL(66, 1074, 24), // "on_pushButton_10_clicked"
QT_MOC_LITERAL(67, 1099, 24), // "on_pushButton_11_clicked"
QT_MOC_LITERAL(68, 1124, 24), // "on_pushButton_12_clicked"
QT_MOC_LITERAL(69, 1149, 24), // "on_pushButton_14_clicked"
QT_MOC_LITERAL(70, 1174, 24), // "on_pushButton_17_clicked"
QT_MOC_LITERAL(71, 1199, 24), // "on_pushButton_18_clicked"
QT_MOC_LITERAL(72, 1224, 24), // "on_pushButton_15_clicked"
QT_MOC_LITERAL(73, 1249, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(74, 1273, 24), // "on_pushButton_69_clicked"
QT_MOC_LITERAL(75, 1298, 24), // "on_pushButton_70_clicked"
QT_MOC_LITERAL(76, 1323, 19), // "on_LVDTBt_2_clicked"
QT_MOC_LITERAL(77, 1343, 19), // "on_saveBt_2_clicked"
QT_MOC_LITERAL(78, 1363, 24), // "on_pushButton_71_clicked"
QT_MOC_LITERAL(79, 1388, 24), // "on_pushButton_19_clicked"
QT_MOC_LITERAL(80, 1413, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(81, 1437, 24), // "on_pushButton_20_clicked"
QT_MOC_LITERAL(82, 1462, 24), // "on_pushButton_21_clicked"
QT_MOC_LITERAL(83, 1487, 17), // "on_openBt_clicked"
QT_MOC_LITERAL(84, 1505, 14), // "onDataReceived"
QT_MOC_LITERAL(85, 1520, 20), // "displayModbusRequest"
QT_MOC_LITERAL(86, 1541, 12), // "startAddress"
QT_MOC_LITERAL(87, 1554, 8), // "quantity"
QT_MOC_LITERAL(88, 1563, 6), // "isRead"
QT_MOC_LITERAL(89, 1570, 18), // "calculateModbusCRC"
QT_MOC_LITERAL(90, 1589, 4), // "data"
QT_MOC_LITERAL(91, 1594, 20), // "updateSerialPortList"
QT_MOC_LITERAL(92, 1615, 24), // "on_pushButton_22_clicked"
QT_MOC_LITERAL(93, 1640, 24), // "on_pushButton_23_clicked"
QT_MOC_LITERAL(94, 1665, 19), // "on_bautBt_2_clicked"
QT_MOC_LITERAL(95, 1685, 24), // "on_pushButton_24_clicked"
QT_MOC_LITERAL(96, 1710, 20), // "on_cycleBt_2_clicked"
QT_MOC_LITERAL(97, 1731, 20), // "on_cycleBt_3_clicked"
QT_MOC_LITERAL(98, 1752, 20), // "on_cycleBt_4_clicked"
QT_MOC_LITERAL(99, 1773, 20), // "on_cycleBt_5_clicked"
QT_MOC_LITERAL(100, 1794, 24), // "on_pushButton_27_clicked"
QT_MOC_LITERAL(101, 1819, 10), // "initChart1"
QT_MOC_LITERAL(102, 1830, 14), // "saveDataToFile"
QT_MOC_LITERAL(103, 1845, 25), // "onWriteOperationCompleted"
QT_MOC_LITERAL(104, 1871, 18), // "parseRegisterValue"
QT_MOC_LITERAL(105, 1890, 19), // "RS485onTimerTimeout"
QT_MOC_LITERAL(106, 1910, 24), // "on_pushButton_28_clicked"
QT_MOC_LITERAL(107, 1935, 24), // "on_pushButton_29_clicked"
QT_MOC_LITERAL(108, 1960, 21), // "on_sendfaBt_4_clicked"
QT_MOC_LITERAL(109, 1982, 24), // "on_pushButton_32_clicked"
QT_MOC_LITERAL(110, 2007, 24), // "on_pushButton_33_clicked"
QT_MOC_LITERAL(111, 2032, 16), // "processChartData"
QT_MOC_LITERAL(112, 2049, 24), // "on_pushButton_26_clicked"
QT_MOC_LITERAL(113, 2074, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(114, 2102, 5) // "index"

    },
    "MainWindow\0resized\0\0dataReceived\0"
    "address\0QVector<quint16>\0values\0"
    "writeCompleted\0value\0success\0errorOccurred\0"
    "errorString\0exceptionReceived\0"
    "exceptionCode\0setupModbusParams\0"
    "portName\0QSerialPort::BaudRate\0baudRate\0"
    "QSerialPort::DataBits\0dataBits\0"
    "QSerialPort::StopBits\0stopBits\0"
    "QSerialPort::Parity\0parity\0onGetProtocolData\0"
    "VCI_CAN_OBJ*\0vci\0dwRel\0channel\0"
    "on_savetxtBt_clicked\0on_savetxtBt_2_clicked\0"
    "saveNewData\0onSaveFinished\0onErrorOccurred\0"
    "errorMessage\0onAdjustAxesClicked\0"
    "updateTimeLabel\0on_pushButton_clicked\0"
    "on_sendBtn_clicked\0on_cleanListBtn_clicked\0"
    "on_pushButton_4_clicked\0onTimerTimeout\0"
    "onTimerTimeout1\0on_pushButton_5_clicked\0"
    "on_pushButton_8_clicked\0on_cycleBt_clicked\0"
    "on_bautBt_clicked\0on_LVDTBt_clicked\0"
    "on_recovBt_clicked\0on_saveBt_clicked\0"
    "on_sendfaBt_clicked\0on_pushButton_13_clicked\0"
    "on_pushButton_16_clicked\0on_tranBt_clicked\0"
    "on_pushButton_6_clicked\0on_pushButton_7_clicked\0"
    "parseTxtData\0filePath\0drawChart\0"
    "updateChartVisibility\0on_checkBox_5_stateChanged\0"
    "arg1\0on_checkBox_6_stateChanged\0"
    "on_checkBox_7_stateChanged\0"
    "on_checkBox_8_stateChanged\0"
    "on_checkBox_9_stateChanged\0"
    "on_pushButton_10_clicked\0"
    "on_pushButton_11_clicked\0"
    "on_pushButton_12_clicked\0"
    "on_pushButton_14_clicked\0"
    "on_pushButton_17_clicked\0"
    "on_pushButton_18_clicked\0"
    "on_pushButton_15_clicked\0"
    "on_pushButton_2_clicked\0"
    "on_pushButton_69_clicked\0"
    "on_pushButton_70_clicked\0on_LVDTBt_2_clicked\0"
    "on_saveBt_2_clicked\0on_pushButton_71_clicked\0"
    "on_pushButton_19_clicked\0"
    "on_pushButton_3_clicked\0"
    "on_pushButton_20_clicked\0"
    "on_pushButton_21_clicked\0on_openBt_clicked\0"
    "onDataReceived\0displayModbusRequest\0"
    "startAddress\0quantity\0isRead\0"
    "calculateModbusCRC\0data\0updateSerialPortList\0"
    "on_pushButton_22_clicked\0"
    "on_pushButton_23_clicked\0on_bautBt_2_clicked\0"
    "on_pushButton_24_clicked\0on_cycleBt_2_clicked\0"
    "on_cycleBt_3_clicked\0on_cycleBt_4_clicked\0"
    "on_cycleBt_5_clicked\0on_pushButton_27_clicked\0"
    "initChart1\0saveDataToFile\0"
    "onWriteOperationCompleted\0parseRegisterValue\0"
    "RS485onTimerTimeout\0on_pushButton_28_clicked\0"
    "on_pushButton_29_clicked\0on_sendfaBt_4_clicked\0"
    "on_pushButton_32_clicked\0"
    "on_pushButton_33_clicked\0processChartData\0"
    "on_pushButton_26_clicked\0"
    "on_tabWidget_currentChanged\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      85,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  439,    2, 0x06 /* Public */,
       3,    2,  440,    2, 0x06 /* Public */,
       7,    3,  445,    2, 0x06 /* Public */,
      10,    1,  452,    2, 0x06 /* Public */,
      12,    1,  455,    2, 0x06 /* Public */,
      14,    5,  458,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      24,    3,  469,    2, 0x08 /* Private */,
      29,    0,  476,    2, 0x08 /* Private */,
      30,    0,  477,    2, 0x08 /* Private */,
      31,    0,  478,    2, 0x08 /* Private */,
      32,    0,  479,    2, 0x08 /* Private */,
      33,    1,  480,    2, 0x08 /* Private */,
      35,    0,  483,    2, 0x08 /* Private */,
      36,    0,  484,    2, 0x08 /* Private */,
      37,    0,  485,    2, 0x08 /* Private */,
      38,    0,  486,    2, 0x08 /* Private */,
      39,    0,  487,    2, 0x08 /* Private */,
      40,    0,  488,    2, 0x08 /* Private */,
      41,    0,  489,    2, 0x08 /* Private */,
      42,    0,  490,    2, 0x08 /* Private */,
      43,    0,  491,    2, 0x08 /* Private */,
      44,    0,  492,    2, 0x08 /* Private */,
      45,    0,  493,    2, 0x08 /* Private */,
      46,    0,  494,    2, 0x08 /* Private */,
      47,    0,  495,    2, 0x08 /* Private */,
      48,    0,  496,    2, 0x08 /* Private */,
      49,    0,  497,    2, 0x08 /* Private */,
      50,    0,  498,    2, 0x08 /* Private */,
      51,    0,  499,    2, 0x08 /* Private */,
      52,    0,  500,    2, 0x08 /* Private */,
      53,    0,  501,    2, 0x08 /* Private */,
      54,    0,  502,    2, 0x08 /* Private */,
      55,    0,  503,    2, 0x08 /* Private */,
      56,    1,  504,    2, 0x08 /* Private */,
      58,    0,  507,    2, 0x08 /* Private */,
      59,    0,  508,    2, 0x08 /* Private */,
      60,    1,  509,    2, 0x08 /* Private */,
      62,    1,  512,    2, 0x08 /* Private */,
      63,    1,  515,    2, 0x08 /* Private */,
      64,    1,  518,    2, 0x08 /* Private */,
      65,    1,  521,    2, 0x08 /* Private */,
      66,    0,  524,    2, 0x08 /* Private */,
      67,    0,  525,    2, 0x08 /* Private */,
      68,    0,  526,    2, 0x08 /* Private */,
      69,    0,  527,    2, 0x08 /* Private */,
      70,    0,  528,    2, 0x08 /* Private */,
      71,    0,  529,    2, 0x08 /* Private */,
      72,    0,  530,    2, 0x08 /* Private */,
      73,    0,  531,    2, 0x08 /* Private */,
      74,    0,  532,    2, 0x08 /* Private */,
      75,    0,  533,    2, 0x08 /* Private */,
      76,    0,  534,    2, 0x08 /* Private */,
      77,    0,  535,    2, 0x08 /* Private */,
      78,    0,  536,    2, 0x08 /* Private */,
      79,    0,  537,    2, 0x08 /* Private */,
      80,    0,  538,    2, 0x08 /* Private */,
      81,    0,  539,    2, 0x08 /* Private */,
      82,    0,  540,    2, 0x08 /* Private */,
      83,    0,  541,    2, 0x08 /* Private */,
      84,    2,  542,    2, 0x08 /* Private */,
      85,    3,  547,    2, 0x08 /* Private */,
      89,    1,  554,    2, 0x08 /* Private */,
      91,    0,  557,    2, 0x08 /* Private */,
      92,    0,  558,    2, 0x08 /* Private */,
      93,    0,  559,    2, 0x08 /* Private */,
      94,    0,  560,    2, 0x08 /* Private */,
      95,    0,  561,    2, 0x08 /* Private */,
      96,    0,  562,    2, 0x08 /* Private */,
      97,    0,  563,    2, 0x08 /* Private */,
      98,    0,  564,    2, 0x08 /* Private */,
      99,    0,  565,    2, 0x08 /* Private */,
     100,    0,  566,    2, 0x08 /* Private */,
     101,    0,  567,    2, 0x08 /* Private */,
     102,    0,  568,    2, 0x08 /* Private */,
     103,    3,  569,    2, 0x08 /* Private */,
     104,    2,  576,    2, 0x08 /* Private */,
     105,    0,  581,    2, 0x08 /* Private */,
     106,    0,  582,    2, 0x08 /* Private */,
     107,    0,  583,    2, 0x08 /* Private */,
     108,    0,  584,    2, 0x08 /* Private */,
     109,    0,  585,    2, 0x08 /* Private */,
     110,    0,  586,    2, 0x08 /* Private */,
     111,    0,  587,    2, 0x08 /* Private */,
     112,    0,  588,    2, 0x08 /* Private */,
     113,    1,  589,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::Bool,    4,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::UChar,   13,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 16, 0x80000000 | 18, 0x80000000 | 20, 0x80000000 | 22,   15,   17,   19,   21,   23,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 25, QMetaType::UInt, QMetaType::UInt,   26,   27,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   57,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   61,
    QMetaType::Void, QMetaType::Int,   61,
    QMetaType::Void, QMetaType::Int,   61,
    QMetaType::Void, QMetaType::Int,   61,
    QMetaType::Void, QMetaType::Int,   61,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::Bool,   86,   87,   88,
    QMetaType::UShort, QMetaType::QByteArray,   90,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::Bool,    4,    8,    9,
    QMetaType::QString, QMetaType::UShort, QMetaType::UShort,    4,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  114,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resized(); break;
        case 1: _t->dataReceived((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< const QVector<quint16>(*)>(_a[2]))); break;
        case 2: _t->writeCompleted((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->exceptionReceived((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: _t->setupModbusParams((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QSerialPort::BaudRate(*)>(_a[2])),(*reinterpret_cast< QSerialPort::DataBits(*)>(_a[3])),(*reinterpret_cast< QSerialPort::StopBits(*)>(_a[4])),(*reinterpret_cast< QSerialPort::Parity(*)>(_a[5]))); break;
        case 6: _t->onGetProtocolData((*reinterpret_cast< VCI_CAN_OBJ*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 7: _t->on_savetxtBt_clicked(); break;
        case 8: _t->on_savetxtBt_2_clicked(); break;
        case 9: _t->saveNewData(); break;
        case 10: _t->onSaveFinished(); break;
        case 11: _t->onErrorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->onAdjustAxesClicked(); break;
        case 13: _t->updateTimeLabel(); break;
        case 14: _t->on_pushButton_clicked(); break;
        case 15: _t->on_sendBtn_clicked(); break;
        case 16: _t->on_cleanListBtn_clicked(); break;
        case 17: _t->on_pushButton_4_clicked(); break;
        case 18: _t->onTimerTimeout(); break;
        case 19: _t->onTimerTimeout1(); break;
        case 20: _t->on_pushButton_5_clicked(); break;
        case 21: _t->on_pushButton_8_clicked(); break;
        case 22: _t->on_cycleBt_clicked(); break;
        case 23: _t->on_bautBt_clicked(); break;
        case 24: _t->on_LVDTBt_clicked(); break;
        case 25: _t->on_recovBt_clicked(); break;
        case 26: _t->on_saveBt_clicked(); break;
        case 27: _t->on_sendfaBt_clicked(); break;
        case 28: _t->on_pushButton_13_clicked(); break;
        case 29: _t->on_pushButton_16_clicked(); break;
        case 30: _t->on_tranBt_clicked(); break;
        case 31: _t->on_pushButton_6_clicked(); break;
        case 32: _t->on_pushButton_7_clicked(); break;
        case 33: _t->parseTxtData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 34: _t->drawChart(); break;
        case 35: _t->updateChartVisibility(); break;
        case 36: _t->on_checkBox_5_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->on_checkBox_6_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->on_checkBox_7_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->on_checkBox_8_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->on_checkBox_9_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->on_pushButton_10_clicked(); break;
        case 42: _t->on_pushButton_11_clicked(); break;
        case 43: _t->on_pushButton_12_clicked(); break;
        case 44: _t->on_pushButton_14_clicked(); break;
        case 45: _t->on_pushButton_17_clicked(); break;
        case 46: _t->on_pushButton_18_clicked(); break;
        case 47: _t->on_pushButton_15_clicked(); break;
        case 48: _t->on_pushButton_2_clicked(); break;
        case 49: _t->on_pushButton_69_clicked(); break;
        case 50: _t->on_pushButton_70_clicked(); break;
        case 51: _t->on_LVDTBt_2_clicked(); break;
        case 52: _t->on_saveBt_2_clicked(); break;
        case 53: _t->on_pushButton_71_clicked(); break;
        case 54: _t->on_pushButton_19_clicked(); break;
        case 55: _t->on_pushButton_3_clicked(); break;
        case 56: _t->on_pushButton_20_clicked(); break;
        case 57: _t->on_pushButton_21_clicked(); break;
        case 58: _t->on_openBt_clicked(); break;
        case 59: _t->onDataReceived((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< QVector<quint16>(*)>(_a[2]))); break;
        case 60: _t->displayModbusRequest((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 61: { quint16 _r = _t->calculateModbusCRC((*reinterpret_cast< const QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 62: _t->updateSerialPortList(); break;
        case 63: _t->on_pushButton_22_clicked(); break;
        case 64: _t->on_pushButton_23_clicked(); break;
        case 65: _t->on_bautBt_2_clicked(); break;
        case 66: _t->on_pushButton_24_clicked(); break;
        case 67: _t->on_cycleBt_2_clicked(); break;
        case 68: _t->on_cycleBt_3_clicked(); break;
        case 69: _t->on_cycleBt_4_clicked(); break;
        case 70: _t->on_cycleBt_5_clicked(); break;
        case 71: _t->on_pushButton_27_clicked(); break;
        case 72: _t->initChart1(); break;
        case 73: _t->saveDataToFile(); break;
        case 74: _t->onWriteOperationCompleted((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 75: { QString _r = _t->parseRegisterValue((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 76: _t->RS485onTimerTimeout(); break;
        case 77: _t->on_pushButton_28_clicked(); break;
        case 78: _t->on_pushButton_29_clicked(); break;
        case 79: _t->on_sendfaBt_4_clicked(); break;
        case 80: _t->on_pushButton_32_clicked(); break;
        case 81: _t->on_pushButton_33_clicked(); break;
        case 82: _t->processChartData(); break;
        case 83: _t->on_pushButton_26_clicked(); break;
        case 84: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<quint16> >(); break;
            }
            break;
        case 59:
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
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::resized)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(quint16 , const QVector<quint16> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::dataReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(quint16 , quint16 , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::writeCompleted)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::errorOccurred)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::exceptionReceived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QString & , QSerialPort::BaudRate , QSerialPort::DataBits , QSerialPort::StopBits , QSerialPort::Parity );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::setupModbusParams)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 85)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 85;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 85)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 85;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::resized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::dataReceived(quint16 _t1, const QVector<quint16> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::writeCompleted(quint16 _t1, quint16 _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::exceptionReceived(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::setupModbusParams(const QString & _t1, QSerialPort::BaudRate _t2, QSerialPort::DataBits _t3, QSerialPort::StopBits _t4, QSerialPort::Parity _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
