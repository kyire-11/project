#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canthread.h"
#include <QTimer>
#include <QDateTime>
#include <QString>
#include <QThread>
#include "datasaver.h"
#include  "valve.h"
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QLineSeries>          //线条类
#include <QChartView>
#include <QLineSeries>          //线条类
#include <QtMath>
#include <QListWidget>
#include <QTimer>               //时间类
#include <QDateTime>
#include <QDateTimeAxis>        //时间坐标轴类
#include <QValueAxis>           //普通坐标轴类
#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>
#include <dbc.h>
#include <QToolTip>
#include <QGraphicsView>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QModbusDevice>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QQueue>
#include <QPair>
#include <QComboBox>
#include "modbusworker.h"

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void AddDataToList(QStringList strList);
    void setupChart();
    void setupChart1();
    void setupChart2();
    void setupChart3();
    bool loadDataFromExcel(const QString &filePath,QList<QLineSeries *> &seriesListn);
    void adjustChartAxes();

    void checkTimeoutDevices(QHash<quint32, QListWidgetItem*>& idToItems,
                                         const QHash<quint32, QDateTime>& lastSeen,
                                         const QSet<quint32>& updatedDevices);
    void updateDeviceStatus(quint32 deviceId, bool hasLvdt,
                            QHash<quint32, QListWidgetItem*>& idToItems);

    void markAllDevicesOffline(QHash<quint32, QListWidgetItem*>& idToItems);


    void onAdjustAxesClicked2();
    void adjustChartAxes2();

    void sendNextFlowDataBatch();
    void sendNextFlowDataBatch2();
    void sendNextFlowDataBatch3();

    void processCanResponse(const QByteArray& canData,int &wlwlReceived);
    void processCanResponse2(const QByteArray& canData,int &wlwlReceived);
    void processCanResponse3(const QByteArray& canData,int &dlReceived);

    bool loadDataFromExcel3(const QString &filePath,QList<QLineSeries *> &seriesListn);
    void adjustChartAxes3();
    void onAdjustAxesClicked3();


    void sendCurrentValue();


    void setupChart4();


    void closeSerialPort();
    bool isSerialPortOpen() const;

    // 通信功能
    bool writeSingleRegister(quint16 address, quint16 value);
    bool readHoldingRegisters(quint16 startAddress, quint16 quantity);

    // 设置参数
    // void setResponseTimeout(int timeoutMs);
    void setMaxRetries(int retries);

    QByteArray createWriteFrame(quint16 address, quint16 data);
    QByteArray createReadFrame(quint16 address);
    QByteArray calculateCRC(const QByteArray &data);
    bool eventFilter(QObject *watched, QEvent *event) override;
    QList<QChartView*> zoomableChartViews;



    void appendToFile(const QString& message);
    void clearCharts();
    bool xAxisRangeSet1 = false;
    bool xAxisRangeSet2 = false;


    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer4;

    int faCount;
    int nodeReceived=0;
    int cycleReceived=0;
    int baudReceived=0;
    int LVDTReceived=0;
    int LVDTReceived2=0;
    int recovReceived=0;
    int saveReceived=0;
    int saveReceived2=0;
    int wlReceived;
    int dlReceived;
    int wdReceived;
    int t1=0;
    int t2=0;
    int t3=0;
    int t4=0;
    int t5=0;
    int t6=0;
    int t7=0;
    int t8=0;
    int t9=0;
    int t10=0;
    int t11=0;
    void initializeAddressCombobox(QComboBox *combobox, int min, int max, bool special);
    void RS485sendCurrentValue();
    QPair<int, int> getAxisAndChartIndex(const QString& optionText);
    bool isClosing;



signals:
    void resized();
    void dataReceived(quint16 address, const QVector<quint16> &values);
    void writeCompleted(quint16 address, quint16 value, bool success);
    void errorOccurred(const QString &errorString);
    void exceptionReceived(quint8 exceptionCode);
    void setupModbusParams(const QString &portName,
                                QSerialPort::BaudRate baudRate,
                                QSerialPort::DataBits dataBits,
                                QSerialPort::StopBits stopBits,
                                QSerialPort::Parity parity);

private slots:
    void onGetProtocolData(VCI_CAN_OBJ *vci,unsigned int dwRel,unsigned int channel);

    void on_savetxtBt_clicked();

    void on_savetxtBt_2_clicked();


    void saveNewData();




    void onSaveFinished();
    void onErrorOccurred(const QString &errorMessage);
    void onAdjustAxesClicked();

    void updateTimeLabel();







    // void onBoardInfo(VCI_BOARD_INFO vbi);

    void on_pushButton_clicked();

    void on_sendBtn_clicked();

    void on_cleanListBtn_clicked();

    void on_pushButton_4_clicked();

    // void on_pushButton_2_clicked();

    // void on_pushButton_3_clicked();

    void onTimerTimeout();

    void onTimerTimeout1();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_cycleBt_clicked();

    void on_bautBt_clicked();

    void on_LVDTBt_clicked();

    void on_recovBt_clicked();

    void on_saveBt_clicked();

    void on_sendfaBt_clicked();

    void on_pushButton_13_clicked();




    // void on_savetxtBt_3_clicked();

    void on_pushButton_16_clicked();

    void on_tranBt_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();




    void parseTxtData(const QString &filePath);

    void drawChart();



    void updateChartVisibility();

    void on_checkBox_5_stateChanged(int arg1);

    void on_checkBox_6_stateChanged(int arg1);

    void on_checkBox_7_stateChanged(int arg1);

    void on_checkBox_8_stateChanged(int arg1);

    void on_checkBox_9_stateChanged(int arg1);

    // void checkDeviceOnlineStatus();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();


    void on_pushButton_15_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_69_clicked();

    void on_pushButton_70_clicked();

    void on_LVDTBt_2_clicked();

    void on_saveBt_2_clicked();

    void on_pushButton_71_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_openBt_clicked();


    // void handleStateChanged(QModbusDevice::State state);
    // void handleError(QModbusDevice::Error error);
    // void handleReplyFinished();
    // void handleTimeout();
    void onDataReceived(quint16 address,  QVector<quint16> values);
    void displayModbusRequest(quint16 startAddress, quint16 quantity,bool isRead);
    quint16 calculateModbusCRC(const QByteArray &data);
    // void displayModbusRequest2(quint16 startAddress, quint16 quantity);

    void updateSerialPortList();



    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_bautBt_2_clicked();

    void on_pushButton_24_clicked();

    void on_cycleBt_2_clicked();

    void on_cycleBt_3_clicked();

    void on_cycleBt_4_clicked();

    void on_cycleBt_5_clicked();

    // void on_pushButton_25_clicked();

    // void readAllRegisters();

    // void processNextRequest();

    // QString getModbusErrorMessage(quint8 exceptionCode);

    void on_pushButton_27_clicked();


    void initChart1();
    // void ReData_Slot();
    // void DisplayChart1();
    void saveDataToFile();
    void onWriteOperationCompleted(quint16 address, quint16 value, bool success);
    QString parseRegisterValue(quint16 address, quint16 value);
    void RS485onTimerTimeout();

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_sendfaBt_4_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void processChartData();

    void on_pushButton_26_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    CANThread *canthread;
    QTimer *timer;
    int remainingCount=0;
    QTimer *saveTimer;                  // 定时检查新数据的定时器
    QThread *saveThread;                // 保存数据的子线程
    datasaver *dataSaver;               // 数据保存对象
    int startSaveRow;                   // 点击保存按钮时的起始行数
    bool isSaving;                      // 保存状态标志
    QString savePath;

    valve *valveWindow;
    // QSet<quint32> receivedFrameIds;
    QString filePath;
    QString filePath1;

    QList<QLineSeries *> seriesList;
    QMap<QString, int> fieldIndexes;

    QList<QLineSeries *> seriesList1;
    QMap<QString, int> fieldIndexes1;

    QtCharts::QChart *chart;
    QtCharts::QChart *qchart1;
    QtCharts::QChartView *chartView;
    QtCharts::QChartView *chartView1;
    // CustomChartView *chartView;
    QtCharts::QDateTimeAxis *axisX;
    QtCharts::QValueAxis *axisY;

    QHash<quint32, QDateTime> m_idLastReceivedTime;  // 存储ID的最后接收时间
    QTimer *m_refreshTimer;

    QList<QValueAxis*> yAxes;
    QVector<double> flowDataBuffer;
    QVector<double> fyDataBuffer;
    unsigned char direct;
    int fcount=0;

    QtCharts::QChart *qchart2;
    QString filePath2;
    QList<QLineSeries *> seriesList2;
    QMap<QString, int> fieldIndexes2;
    QtCharts::QChartView *chartView2;
    QList<QValueAxis*> yAxes2;
    QVector<double> flowDataBuffer2;
    QVector<double> fyDataBuffer2;
    unsigned char direct2;
    int fcount2=0;


    DBC *dbc;
    QList<DBC*> dbcWindows;


    quint32 groupStatus = 0;  // 32位状态变量，每bit表示一组是否接收成功
    quint32 groupStatus2 = 0;
    quint32 groupStatus3 = 0;  // 32位状态变量，每bit表示一组是否接收成功
    quint32 groupStatus4 = 0;
    quint32 groupStatus5 = 0;
    bool allGroupsReceived = false;  // 标记是否所有组都已接收


    QtCharts::QChart *qchart3;
    QString filePath3;
    QList<QLineSeries *> seriesList3;
    QMap<QString, int> fieldIndexes3;
    QtCharts::QChartView *chartView3;
    QList<QValueAxis*> yAxes3;
    QVector<double> flowDataBuffer3;
    QVector<double> fyDataBuffer3;
    unsigned char direct3;
    int fcount3=0;


    QList<QList<QVariant>> dataTable;

    int currentValue;    // 当前发送的值
    int startValue;      // 起始值
    int endValue;        // 结束值
    int valueStep;       // 值的步长（间隔）
    int sendInterval;    // 发送间隔时间（毫秒）
    bool increasing;
    QTimer* cycleTimer;      // 控制200ms的发送间隔
    QTimer* stepTimer;       // 控制6秒的步长切换周期
    QList<int> stepValues;   // 存储不同阶段的步长值
    int currentStepIndex;    // 当前步长索引
    // int stepCycleCount;      // 步长周期计数
    // int totalStepCycles;     // 总步长周期数
    bool isSteppingMode;     // 是否处于步进模式



    QString filePath4;
    QMap<QString, QList<QStringList>> frameDataMap; // 存储解析后的数据
    QChart *chart4;
    QChartView *chartView4;
    QDateTimeAxis *axisX4;

// QMap<quint8, QList<QStringList>> frameDataMap;





    int stepCycleCount;      // 当前步长阶段已持续的200ms周期数（6秒=30个周期）
    int totalStepCycles = 0;  // 6秒固定周期数（可改为动态配置）
    bool isStepChanging;     // 防止步长切换时重复计算

    // QModbusRtuSerialMaster *m_modbusDevice ;
    ModbusWorker *m_modbusWorker; // 工作者对象
    QThread *m_modbusThread = nullptr;      // 工作线程
    QTimer *m_readTimer=new QTimer();




    QTimer *serialPortTimer;
    QStringList currentPorts;



    QChart *qchart5;
    QList<QValueAxis*> yAxes5;



    // 在valve类中添加新的成员变量
    bool isDrawing = false;      // 是否正在绘图
    bool isPaused = false;       // 是否处于暂停状态
    bool hasActiveSession = false; // 是否有活动会话
    QString activeSessionFileName; // 当前会话文件名
    QDateTime sessionStartTime;  // 会话开始时间
    QDateTime pauseStartTime;    // 暂停开始时间
    qint64 pauseDuration = 0;    // 累计暂停时间
    QList<QPointF> savedSeries0Data, savedSeries1Data, savedSeries2Data;
    qint16 position=0;
    qint16 currentA=0;
    qint16 currentB=0;
    int er=0;
    bool hasLVDT=0;
    QTimer *time1;
    QString fileName;
    QDateTime startTime;


    int currentValue1;    // 当前发送的值
    int startValue1;      // 起始值
    int endValue1;        // 结束值
    int valueStep1;       // 值的步长（间隔）
    int sendInterval1;    // 发送间隔时间（毫秒）
    bool increasing1;
    int stepCycleCount1;      // 当前步长阶段已持续的200ms周期数（6秒=30个周期）
    int totalStepCycles1 = 0;  // 6秒固定周期数（可改为动态配置）
    bool isStepChanging1;     // 防止步长切换时重复计算


    QTimer *modbusRequestTimer;  // Modbus请求定时器
    QTimer *drawTimer;           // 严格绘图定时器
    QMutex dataMutex;
    struct ModbusData {
        double position = 0.0;
        double currentA = 0.0;
        double currentB = 0.0;
        QDateTime timestamp;
        double er=0;
        double lvdt=0;
    };
    ModbusData latestData;
    bool dataReady = false;
    bool ondata=false;


    QLineSeries *seriesDisp;
    QLineSeries *seriesCurrA;
    QLineSeries *seriesCurrB;
    QLineSeries *seriesHVol;
    QLineSeries *seriesLVolt;
    QValueAxis *axisYLeft;
    QValueAxis *axisYRight;

    bool issend;

    QHash<quint32, QListWidgetItem*> deviceIdToListItems;
    // 存储设备最后更新时间
    QHash<quint32, QDateTime> deviceLastSeen;


















};

#endif // MAINWINDOW_H
