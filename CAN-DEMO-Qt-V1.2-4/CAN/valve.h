#ifndef VALVE_H
#define VALVE_H

#include <QWidget>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QLineSeries>          //线条类
#include <QChartView>
#include <QLineSeries>          //线条类
#include <QtMath>

#include <QTimer>               //时间类
#include <QDateTime>
#include <QDateTimeAxis>        //时间坐标轴类
#include <QValueAxis>           //普通坐标轴类
#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>
#include "canthread.h"

QT_CHARTS_USE_NAMESPACE

class CANThread;

namespace Ui {
class valve;
}

class valve : public QWidget
{
    Q_OBJECT

public:
    explicit valve(CANThread *canthread,QWidget *parent = nullptr);
    ~valve();



    void clearCharts();
    void connectSeriesHoverSignals(QChartView* chartView, int seriesCount,
                                   const std::vector<std::function<void(const QPointF&, bool)>>& slotFunctions);
    void saveDataToFile();

    // void updateChartRange(QChartView* chartView, int min, int max);
    void updateChartRange(QChartView* chartView, int seriesIndex, int min, int max);
    void appendToFile(const QString& message);





private slots:
    // 定义槽函数，用于接收特定 ID 帧数据
    void onSpecificIdDataReceived(VCI_CAN_OBJ *vci,unsigned int dwRel,unsigned int channel);


    void on_pushButton_14_clicked();

    void DisplayChart1();

    void DisplayChart2();

    void ReData_Slot();



    void on_pushButton_17_clicked();
    void showPointToolTip0(const QPointF &point, bool state);
    void showPointToolTip1(const QPointF &point, bool state);
    void showPointToolTip2(const QPointF &point, bool state);
    void showPointToolTip3(const QPointF &point, bool state);
    void showPointToolTip4(const QPointF &point, bool state);

    // void saveNewData();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::valve *ui;
    QTimer *time1;

    void initChart1();
    void initChart2();

    QChart *qchart;

    const int maxHistorySeconds = 30;
    uint16_t faValue;
    uint16_t Apwmvalue;
    uint16_t Bpwmvalue;
    uint16_t er;
    uint16_t isLVDT;
    uint16_t inputvalue;
    uint16_t LVDTvalue;
    bool xAxisRangeSet1 = false;
    bool xAxisRangeSet2 = false;
    bool yAxisRangeSet1 = false;
    bool yAxisRangeSet2 = false;

    QDateTime startTime;
    bool isSaving=false;
    QTimer *saveTimer;
    QString fileName;

    CANThread *canthread1;

    QValueAxis* yAxes[3];  // 第一个图表的3个Y轴
    QValueAxis* yAxes2[2]; // 第二个图表的2个Y轴

    // 新增一个函数用于根据选项文字获取对应的轴和图表索引
    QPair<int, int> getAxisAndChartIndex(const QString& optionText);

    // 在valve类中添加新的成员变量
    bool isDrawing = false;      // 是否正在绘图
    bool isPaused = false;       // 是否处于暂停状态
    bool hasActiveSession = false; // 是否有活动会话
    QString activeSessionFileName; // 当前会话文件名
    QDateTime sessionStartTime;  // 会话开始时间
    QDateTime pauseStartTime;    // 暂停开始时间
    qint64 pauseDuration = 0;    // 累计暂停时间
    QList<QPointF> savedSeries0Data, savedSeries1Data, savedSeries2Data;
    QList<QPointF> savedSeries3Data, savedSeries4Data;
};

#endif // VALVE_H
