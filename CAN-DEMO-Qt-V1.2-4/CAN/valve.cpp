#include "valve.h"
#include "ui_valve.h"
#include <QTimer>
#include <QToolTip>
#include <QChartView>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QLineSeries>




valve::valve(CANThread *canthread,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::valve)
    ,canthread1(canthread)
{
    ui->setupUi(this);

    for (int i = 1; i <= 0x7F; ++i) {
        QString hexString = QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
        ui->comboBox_11->addItem(hexString);
    }

    ui->comboBox_11->setCurrentIndex(17);

    initChart1();
    initChart2();



    // connect(canthread, &CANThread::getProtocolData, this, &valve::onSpecificIdDataReceived);
    time1=new QTimer(this);
    // saveTimer=new QTimer(this);
    connect(time1,&QTimer::timeout,this,&valve::ReData_Slot);


    std::vector<std::function<void(const QPointF&, bool)>> slots1 = {
        [this](const QPointF& point, bool state) { this->showPointToolTip0(point, state); },
        [this](const QPointF& point, bool state) { this->showPointToolTip1(point, state); },
        [this](const QPointF& point, bool state) { this->showPointToolTip2(point, state); }
    };
    connectSeriesHoverSignals(ui->graphicsView, 3, slots1);

    std::vector<std::function<void(const QPointF&, bool)>> slots2 = {
        [this](const QPointF& point, bool state) { this->showPointToolTip3(point, state); },
        [this](const QPointF& point, bool state) { this->showPointToolTip4(point, state); }
    };
    connectSeriesHoverSignals(ui->graphicsView_2, 2, slots2);
    ui->lineEdit_13->setText("0");
    ui->lineEdit_14->setText("1000");
    ui->lineEdit->setText("200");
    ui->lineEdit_12->setText("3");

    // saveTimer->setInterval(ui->lineEdit->text().toInt());
    // connect(saveTimer, &QTimer::timeout, this, &valve::saveNewData);

    Apwmvalue = 0;
    Bpwmvalue = 0;
    er = 0;
    isLVDT = 0;

    inputvalue = 0;
    LVDTvalue = 0;
}

valve::~valve()
{

    delete ui;

    // 释放 QChart 对象
    QChart *qchart1 = ui->graphicsView->chart();
    if (qchart1) {
        delete qchart1;
    }
    QChart *qchart2 = ui->graphicsView_2->chart();
    if (qchart2) {
        delete qchart2;
    }
}

void valve::connectSeriesHoverSignals(QChartView* chartView, int seriesCount,
                                      const std::vector<std::function<void(const QPointF&, bool)>>& slotFunctions) {
    if (!chartView) {
        return;
    }

    QChart *qchart = chartView->chart();
    if (!qchart) {
        return;
    }

    QList<QAbstractSeries *> seriesList = qchart->series();
    if (seriesList.size() < seriesCount) {
        return;
    }

    for (int i = 0; i < seriesCount && i < slotFunctions.size(); ++i) {
        QLineSeries *series = qobject_cast<QLineSeries *>(seriesList.at(i));
        if (series) {
            connect(series, &QLineSeries::hovered, [this, slot = slotFunctions[i]](const QPointF& point, bool state) {
                slot(point, state);
            });
        }
    }
}

void valve::onSpecificIdDataReceived(VCI_CAN_OBJ *vci, unsigned int dwRel, unsigned int channel)
{
    if (vci) {
        // 假设 VCI_CAN_OBJ 结构体中有一个 Data 数组存储数据
        for(unsigned int i = 0; i < dwRel; i++) {
                if ( 0x180+ui->comboBox_11->currentText().toInt(nullptr,16)==vci[i].ID ) { // 检查帧 ID 是否匹配
                        faValue = static_cast<uint16_t>(vci[i].Data[0]) | (static_cast<uint16_t>(vci[i].Data[1]) << 8);
                        qDebug() << "Combined value: " << faValue;
                        Apwmvalue = static_cast<uint16_t>(vci[i].Data[2]) | (static_cast<uint16_t>(vci[i].Data[3]) << 8);
                        Bpwmvalue = static_cast<uint16_t>(vci[i].Data[4]) | (static_cast<uint16_t>(vci[i].Data[5]) << 8);
                        er = static_cast<uint16_t>(vci[i].Data[6]);
                        isLVDT = static_cast<uint16_t>(vci[i].Data[7]);
                }
                if(0x280+ui->comboBox_11->currentText().toInt(nullptr,16)==vci[i].ID){
                    inputvalue = static_cast<uint16_t>(vci[i].Data[0]) | (static_cast<uint16_t>(vci[i].Data[1]) << 8);
                    LVDTvalue = static_cast<uint16_t>(vci[i].Data[2]) | (static_cast<uint16_t>(vci[i].Data[3]) << 8);
                }
        }
    }
}

void valve::initChart1()
{

    // 创建通用字体设置
    QFont font;
    font.setFamily("SimHei");  // 中文字体支持
    font.setPointSize(10);     // 字体大小


        qchart = new QChart();
        ui->graphicsView->setChart(qchart);
        ui->graphicsView->setRenderHint(QPainter::Antialiasing); // 设置抗锯齿


        // 创建三条线
        QLineSeries *series0 = new QLineSeries;
        QLineSeries *series1 = new QLineSeries;
        QLineSeries *series2 = new QLineSeries;

        // 设置名字
        series0->setName("阀芯位移值");
        series1->setName("PWMA电流反馈值");
        series2->setName("PWMB电流反馈值");

        // 把线条放到chart里
        qchart->addSeries(series0);
        qchart->addSeries(series1);
        qchart->addSeries(series2);

        // 创建 X 轴
        QDateTimeAxis *axisX = new QDateTimeAxis;

        axisX->setFormat("hh:mm:ss");
        axisX->setTickCount(7);
        axisX->setTitleText("time(sec)");

        // 创建 Y 轴
        QValueAxis *axisY = new QValueAxis;
        axisY->setTitleText("阀芯值位移");//QObject::tr()
        axisY->setTitleBrush(QBrush(Qt::blue));
        // 设置 Y 轴轴线颜色
        axisY->setLinePen(QPen(Qt::blue));
        axisY->setRange(0, 1000);
        axisY->setTickCount(6);
        axisY->setLabelFormat("%d");
        axisY->setLabelsFont(font);

        QValueAxis *axisY2 = new QValueAxis;
        axisY2->setTitleText("PWMA电流值");//QObject::tr()
        axisY2->setTitleBrush(QBrush(Qt::green));
        // 设置 Y 轴轴线颜色
        axisY2->setLinePen(QPen(Qt::green));
        axisY2->setRange(0, 1000);
        axisY2->setTickCount(6);
        axisY2->setLabelFormat("%d");
        axisY2->setLabelsFont(font);

        QtCharts::QValueAxis *axisY3 = new QtCharts::QValueAxis();
        axisY3->setTitleText("PWMB电流值");//QObject::tr()
        axisY3->setTitleBrush(QBrush(QColorConstants::Svg::orange));

        // 设置 Y 轴轴线颜色
        axisY3->setLinePen(QPen(QColorConstants::Svg::orange));
        axisY3->setRange(0, 1000);
        axisY3->setTickCount(6);
        axisY3->setLabelFormat("%d");
       // axisY3->setTitlePosition(QValueAxis::AxisTitlePositionBegin);
       //  axisY3->setTickType(QValueAxis::);
        // 应用到标题
        // axisY3->setTitleFont(font);

        // 应用到标签
        axisY3->setLabelsFont(font);



        // 将坐标轴添加到图表
        qchart->addAxis(axisX, Qt::AlignBottom);
        qchart->addAxis(axisY, Qt::AlignLeft);
        qchart->addAxis(axisY2, Qt::AlignRight);
        qchart->addAxis(axisY3, Qt::AlignRight);

        //将系列绑定到坐标轴
        series0->attachAxis(axisX);
        series0->attachAxis(axisY);
        series1->attachAxis(axisX);
        series1->attachAxis(axisY2);
        series2->attachAxis(axisX);
        series2->attachAxis(axisY3);

        // 启用阴影效果
        qchart->setDropShadowEnabled(true);

        // 检查绑定情况
        qDebug() << "Series 0 attached axes count:" << series0->attachedAxes().count();
        qDebug() << "Series 1 attached axes count:" << series1->attachedAxes().count();
        qDebug() << "Series 2 attached axes count:" << series2->attachedAxes().count();

        qchart->setMargins(QMargins(5, 5, 5, 5));

        yAxes[0] = axisY;
        yAxes[1] = axisY2;
        yAxes[2] = axisY3;
}

void valve::initChart2(){
    QFont font;
    font.setFamily("SimHei");  // 中文字体支持
    font.setPointSize(10);     // 字体大小
    QChart *qchart = new QChart();
    ui->graphicsView_2->setChart(qchart);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing); // 设置抗锯齿

    // 创建三条线
    QLineSeries *series0 = new QLineSeries;
    QLineSeries *series1 = new QLineSeries;


    // 设置名字
    series0->setName("外部模拟量");
    series1->setName("LVDT反馈电压");


    // 把线条放到chart里
    qchart->addSeries(series0);
    qchart->addSeries(series1);


    // 创建 X 轴
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("hh:mm:ss");
    axisX->setTickCount(5);
    axisX->setTitleText("time(sec)");

    // 创建 Y 轴
    QValueAxis *axisY0 = new QValueAxis;
    axisY0->setTitleText("外部模拟量");//QObject::tr()
    axisY0->setTitleBrush(QBrush(Qt::blue));
    // 设置 Y 轴轴线颜色
    axisY0->setLinePen(QPen(Qt::blue));
    axisY0->setRange(0, 1000);
    axisY0->setTickCount(6);
    axisY0->setLabelFormat("%d");
    axisY0->setLabelsFont(font);

    QValueAxis *axisY1 = new QValueAxis;
    axisY1->setTitleText("LVDT反馈电压");//QObject::tr()
    axisY1->setTitleBrush(QBrush(Qt::green));
    // 设置 Y 轴轴线颜色
    axisY1->setLinePen(QPen(Qt::green));
    axisY1->setRange(0, 1000);
    axisY1->setTickCount(6);
    axisY1->setLabelFormat("%d");
    axisY1->setLabelsFont(font);

    // 将坐标轴添加到图表
    qchart->addAxis(axisX, Qt::AlignBottom);
    qchart->addAxis(axisY0, Qt::AlignLeft);
    qchart->addAxis(axisY1, Qt::AlignRight);

    // 将系列绑定到坐标轴
    series0->attachAxis(axisX);
    series0->attachAxis(axisY0);
    series1->attachAxis(axisX);
    series1->attachAxis(axisY1);


    // 启用阴影效果
    qchart->setDropShadowEnabled(true);
    qchart->setMargins(QMargins(5, 5, 5, 5));

    yAxes2[0] = axisY0;
    yAxes2[1] = axisY1;



}


bool validateLineEditInput(QLineEdit *lineEdit,  const QString &errorTitle = "输入错误") {//int minValue, int maxValue,
    QString input = lineEdit->text();
    if (input.isEmpty()) {
        QMessageBox::warning(lineEdit->parentWidget(), errorTitle, "请输入内容。");
        return false;
    }

    bool ok;
    int value = input.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(lineEdit->parentWidget(), errorTitle, "输入内容不是有效的整数，请重新输入。");
        return false;
    }



    return true;
}







void valve::on_pushButton_14_clicked()
{


    // 如果有活动会话且处于暂停状态，则继续绘图
    if (hasActiveSession && isPaused) {
        // 计算本次暂停的时长并累加到总暂停时间
        pauseDuration += pauseStartTime.msecsTo(QDateTime::currentDateTime());

        // 恢复图表数据
        QChart *chart1 = ui->graphicsView->chart();
        if (chart1 && chart1->series().size() >= 3) {
            qobject_cast<QLineSeries*>(chart1->series().at(0))->replace(savedSeries0Data);
            qobject_cast<QLineSeries*>(chart1->series().at(1))->replace(savedSeries1Data);
            qobject_cast<QLineSeries*>(chart1->series().at(2))->replace(savedSeries2Data);
        }

        QChart *chart2 = ui->graphicsView_2->chart();
        if (chart2 && chart2->series().size() >= 2) {
            qobject_cast<QLineSeries*>(chart2->series().at(0))->replace(savedSeries3Data);
            qobject_cast<QLineSeries*>(chart2->series().at(1))->replace(savedSeries4Data);
        }

        // 恢复定时器


        connect(canthread1, &CANThread::getProtocolData, this, &valve::onSpecificIdDataReceived);
        time1->start();
        // saveTimer->setInterval(ui->lineEdit->text().toInt());
        // saveTimer->start();
        isPaused = false;
        isDrawing = true;
        appendToFile("System resumed!");
        return;
    }

    // 如果没有活动会话或会话已结束，则开始新绘图
    if (!hasActiveSession || (!isDrawing && !isPaused)) {
        // 检查是否需要继续之前的会话
        if (!fileName.isEmpty() && QFile::exists(fileName)) {
            // 恢复之前的会话
            activeSessionFileName = fileName;
            fileName = activeSessionFileName;

            // 恢复图表数据
            QChart *chart1 = ui->graphicsView->chart();
            if (chart1 && chart1->series().size() >= 3) {
                qobject_cast<QLineSeries*>(chart1->series().at(0))->replace(savedSeries0Data);
                qobject_cast<QLineSeries*>(chart1->series().at(1))->replace(savedSeries1Data);
                qobject_cast<QLineSeries*>(chart1->series().at(2))->replace(savedSeries2Data);
            }

            QChart *chart2 = ui->graphicsView_2->chart();
            if (chart2 && chart2->series().size() >= 2) {
                qobject_cast<QLineSeries*>(chart2->series().at(0))->replace(savedSeries3Data);
                qobject_cast<QLineSeries*>(chart2->series().at(1))->replace(savedSeries4Data);
            }
        } else {
            // 创建全新会话
            QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
            QDir currentDir(QCoreApplication::applicationDirPath());
            // currentDir.cdUp();
            QString saveFolder = currentDir.path() + "/cantex/can解析数据";
            fileName = saveFolder + "/" + timestamp + ".txt";
            activeSessionFileName = fileName;

            QDir dir(saveFolder);
            if (!dir.exists() && !dir.mkpath(".")) {
                QMessageBox::critical(this, "错误", "无法创建保存文件夹！");
                return;
            }

            // 写入文件头
            appendToFile("----------------------------------------------------------");
            appendToFile("> System started!");
            appendToFile("----------------------------------------------------------");
            appendToFile(QString("阀设备：%1").arg(ui->comboBox_11->currentText().toInt()));

            // 记录会话开始时间
            sessionStartTime = QDateTime::currentDateTime();
            pauseDuration = 0;

            // 清除图表（全新会话）
            clearCharts();
        }

        // 连接信号并开始定时器
        connect(canthread1, &CANThread::getProtocolData, this, &valve::onSpecificIdDataReceived);
        // saveTimer->setInterval(ui->lineEdit->text().toInt());
        // saveTimer->start();

        // 重置图表状态
        xAxisRangeSet1 = false;
        xAxisRangeSet2 = false;

        // 验证输入
        if (!(validateLineEditInput(ui->lineEdit_12) && validateLineEditInput(ui->lineEdit_13) &&
              validateLineEditInput(ui->lineEdit_14) && validateLineEditInput(ui->lineEdit))) {
            time1->stop();
            // saveTimer->stop();
            disconnect(canthread1, &CANThread::getProtocolData, this, &valve::onSpecificIdDataReceived);
            return;
        }

        if (ui->lineEdit_13->text().toInt() >= ui->lineEdit_14->text().toInt()) {
            QMessageBox::warning(this, "输入错误", "起始量程应该小于结束量程。");
            time1->stop();
            // saveTimer->stop();
            disconnect(canthread1, &CANThread::getProtocolData, this, &valve::onSpecificIdDataReceived);
            return;
        }

        // 开始绘图
        isDrawing = true;
        isPaused = false;
        hasActiveSession = true;

        time1->setInterval(ui->lineEdit->text().toInt());
        time1->start();
        appendToFile("System started!");
    }
}

void valve::on_pushButton_17_clicked()
{
    if (isDrawing && !isPaused) {
        // 保存当前图表数据
        QChart *chart1 = ui->graphicsView->chart();
        if (chart1 && chart1->series().size() >= 3) {
            savedSeries0Data = qobject_cast<QLineSeries*>(chart1->series().at(0))->points();
            savedSeries1Data = qobject_cast<QLineSeries*>(chart1->series().at(1))->points();
            savedSeries2Data = qobject_cast<QLineSeries*>(chart1->series().at(2))->points();
        }

        QChart *chart2 = ui->graphicsView_2->chart();
        if (chart2 && chart2->series().size() >= 2) {
            savedSeries3Data = qobject_cast<QLineSeries*>(chart2->series().at(0))->points();
            savedSeries4Data = qobject_cast<QLineSeries*>(chart2->series().at(1))->points();
        }

        // 记录暂停开始时间
        pauseStartTime = QDateTime::currentDateTime();

        // 暂停定时器
        time1->stop();
        // saveTimer->stop();

        isPaused = true;
        isDrawing = false;
        appendToFile("System paused!");
    }
}

// 修改数据显示函数，使用绝对时间轴
void valve::DisplayChart1()
{
    if (!isDrawing || isPaused) return;

    QDateTime currentTime = QDateTime::currentDateTime();

    // 获取图表
    QChart *qchart = ui->graphicsView->chart();
    if (!qchart) return;

    // 获取系列列表
    QList<QAbstractSeries *> seriesList = qchart->series();
    if (seriesList.size() < 3) return;

    // 安全地进行类型转换
    QLineSeries *series0 = qobject_cast<QLineSeries *>(seriesList.at(0));
    QLineSeries *series1 = qobject_cast<QLineSeries *>(seriesList.at(1));
    QLineSeries *series2 = qobject_cast<QLineSeries *>(seriesList.at(2));

    // 添加数据点
    if(ui->checkBox_4->isChecked() && series0) {
        series0->append(currentTime.toMSecsSinceEpoch(), faValue);
        ui->label_12->setText(QString::number(faValue));
    }
    if(ui->checkBox_5->isChecked() && series1) {
        series1->append(currentTime.toMSecsSinceEpoch(), Apwmvalue);
        ui->label_13->setText(QString::number(Apwmvalue));
    }
    if(ui->checkBox_6->isChecked() && series2) {
        series2->append(currentTime.toMSecsSinceEpoch(), Bpwmvalue);
        ui->label_14->setText(QString::number(Bpwmvalue));
    }

    // 设置X轴范围
    if (!xAxisRangeSet1) {
        xAxisRangeSet1 = true;
        QList<QAbstractAxis *> axes = series0->attachedAxes();
        for (QAbstractAxis *axis : axes) {
            if (axis->orientation() == Qt::Horizontal) {
                QDateTimeAxis *xAxis = qobject_cast<QDateTimeAxis *>(axis);
                if (xAxis) {
                    xAxis->setMin(sessionStartTime);
                    xAxis->setMax(sessionStartTime.addSecs(ui->lineEdit_12->text().toUInt()*60));
                }
                break;
            }
        }
    }
}

// 同样修改DisplayChart2函数
void valve::DisplayChart2()
{
    if (!isDrawing || isPaused) return;

    QDateTime currentTime = QDateTime::currentDateTime();

    // 获取图表
    QChart *qchart = ui->graphicsView_2->chart();
    if (!qchart) return;

    // 获取系列列表
    QList<QAbstractSeries *> seriesList = qchart->series();
    if (seriesList.size() < 2) return;

    // 安全地进行类型转换
    QLineSeries *series0 = qobject_cast<QLineSeries *>(seriesList.at(0));
    QLineSeries *series1 = qobject_cast<QLineSeries *>(seriesList.at(1));

    // 添加数据点
    if(ui->checkBox_9->isChecked() && series0) {
        series0->append(currentTime.toMSecsSinceEpoch(), inputvalue);
        ui->label_15->setText(QString::number(inputvalue));
    }
    if(ui->checkBox_7->isChecked() && series1) {
        series1->append(currentTime.toMSecsSinceEpoch(), LVDTvalue);
        ui->label_16->setText(QString::number(LVDTvalue));
    }

    // 设置X轴范围
    if (!xAxisRangeSet2) {
        xAxisRangeSet2 = true;
        QList<QAbstractAxis *> axes = series0->attachedAxes();
        for (QAbstractAxis *axis : axes) {
            if (axis->orientation() == Qt::Horizontal) {
                QDateTimeAxis *xAxis = qobject_cast<QDateTimeAxis *>(axis);
                if (xAxis) {
                    xAxis->setMin(sessionStartTime);
                    xAxis->setMax(sessionStartTime.addSecs(ui->lineEdit_12->text().toUInt()*60));
                }
                break;
            }
        }
    }
}










void valve::clearCharts()
{
    QChart *qchart = ui->graphicsView->chart();
    if (qchart) {
        QList<QAbstractSeries *> seriesList = qchart->series();
        for (QAbstractSeries *series : seriesList) {
            QLineSeries *lineSeries = qobject_cast<QLineSeries *>(series);
            if (lineSeries) {
                lineSeries->clear();
            }
        }
    }
    qchart = ui->graphicsView_2->chart();
    if (qchart) {
        QList<QAbstractSeries *> seriesList = qchart->series();
        for (QAbstractSeries *series : seriesList) {
            QLineSeries *lineSeries = qobject_cast<QLineSeries *>(series);
            if (lineSeries) {
                lineSeries->clear();
            }
        }
    }
}




void valve::updateChartRange(QChartView* chartView, int seriesIndex, int min, int max)
{
    if (!chartView) return;

    QChart* chart = chartView->chart();
    if (!chart) return;

    QList<QAbstractSeries *> seriesList = chart->series();
    if (seriesIndex >= seriesList.size()) return;

    QLineSeries *series = qobject_cast<QLineSeries*>(seriesList.at(seriesIndex));
    if (!series) return;

    QList<QAbstractAxis*> axes = series->attachedAxes();
    for (QAbstractAxis* axis : axes) {
        if (QValueAxis* valueAxis = qobject_cast<QValueAxis*>(axis)) {
            valueAxis->setRange(min, max);
        }
    }
}





QPair<int, int> valve::getAxisAndChartIndex(const QString& optionText)
{
    // 图表索引：0 表示第一个图表，1 表示第二个图表
    // Y轴索引：根据不同图表和线条对应
    if (optionText == "阀芯位移值") {
        return QPair<int, int>(0, 0);
    } else if (optionText == "PWMA电流反馈值") {
        return QPair<int, int>(0, 1);
    } else if (optionText == "PWMB电流反馈值") {
        return QPair<int, int>(0, 2);
    } else if (optionText == "外部模拟量") {
        return QPair<int, int>(1, 0);
    } else if (optionText == "LVDT反馈电压") {
        return QPair<int, int>(1, 1);
    }
    return QPair<int, int>(-1, -1); // 表示未找到对应的选项
}


void valve::on_pushButton_clicked()
{
    QString selectedText = ui->comboBox->currentText();

    // 获取对应的图表和轴索引
    QPair<int, int> chartAxis = getAxisAndChartIndex(selectedText);
    int chartIndex = chartAxis.first;
    int axisIndex = chartAxis.second;

    // 验证选项有效性
    if (chartIndex == -1 || axisIndex == -1) {
        QMessageBox::warning(this, "错误", "无效的线段选择");
        return;
    }

    // 获取输入的量程值
    int min = ui->lineEdit_13->text().toInt();
    int max = ui->lineEdit_14->text().toInt();

    if (min >= max) {
        QMessageBox::warning(this, "输入错误", "最小值必须小于最大值");
        return;
    }

    // 更新对应的Y轴
    QValueAxis* targetAxis = nullptr;

    if (chartIndex == 0) {
        if (axisIndex < 3) targetAxis = yAxes[axisIndex];
    } else if (chartIndex == 1) {
        if (axisIndex < 2) targetAxis = yAxes2[axisIndex];
    }

    if (targetAxis) {
        targetAxis->setRange(min, max);
        // appendToFile(QString("调整 %1 量程为: %2 - %3").arg(selectedText).arg(min).arg(max));
    }
}




void valve::ReData_Slot()
{

    if (!isDrawing) {
        return; // 如果没有在绘图，直接返回
    }



    QDateTime currentTime = QDateTime::currentDateTime();
    uint duration = ui->lineEdit_12->text().toUInt() * 60;
    if (startTime.secsTo(currentTime) >= duration) {
        isDrawing = false; // 达到绘图时长，标记停止绘图
        time1->stop(); // 停止定时器
        return;
    }
    DisplayChart1();
    DisplayChart2();
    saveDataToFile();

    if(er==0){
        ui->label_3->setText("LDVT异常");
    }else if(er==1){
        ui->label_3->setText("PWMA异常");
    }else if(er==2){
        ui->label_3->setText("PWMB异常");
    }
    if(isLVDT==0){
        ui->label_5->setText("有LVDT");
    }else if(isLVDT==1){
        ui->label_5->setText("无LVDT");
    }

    faValue = 0;

    Apwmvalue = 0;
    Bpwmvalue = 0;
    er = 0;
    isLVDT = 0;

    inputvalue = 0;
    LVDTvalue = 0;
}



void valve::appendToFile(const QString& message)
{
    QFile file(fileName);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << "]"
            << " " << message << "\n";
        file.close();
    }
}

void valve::showPointToolTip0(const QPointF &point, bool state)
{
    if (state) {
        // 获取系列
        QChart *qchart = ui->graphicsView->chart();
        if (!qchart) {
            return;
        }
        QList<QAbstractSeries *> seriesList = qchart->series();
        if (seriesList.size() < 3) {
            return;
        }
        QLineSeries *series0 = qobject_cast<QLineSeries *>(seriesList.at(0));
        if (!series0 || series0->count() == 0) {
            return;
        }

        // 二分查找最接近的点
        qreal targetX = point.x();
        int left = 0;
        int right = series0->count() - 1;
        int closestIndex = 0;
        qreal minDistance = std::numeric_limits<qreal>::max();

        while (left <= right) {
            int mid = left + (right - left) / 2;
            QPointF midPoint = series0->at(mid);
            qreal distance = qAbs(midPoint.x() - targetX);

            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = mid;
            }

            if (midPoint.x() < targetX) {
                left = mid + 1;
            } else if (midPoint.x() > targetX) {
                right = mid - 1;
            } else {
                // 精确匹配，退出循环
                break;
            }
        }

        // 检查最接近点的左右邻居，确保找到全局最接近点
        if (closestIndex > 0) {
            QPointF leftPoint = series0->at(closestIndex - 1);
            qreal leftDistance = qAbs(leftPoint.x() - targetX);
            if (leftDistance < minDistance) {
                minDistance = leftDistance;
                closestIndex = closestIndex - 1;
            }
        }

        if (closestIndex < series0->count() - 1) {
            QPointF rightPoint = series0->at(closestIndex + 1);
            qreal rightDistance = qAbs(rightPoint.x() - targetX);
            if (rightDistance < minDistance) {
                closestIndex = closestIndex + 1;
            }
        }

        // 获取最接近点并显示工具提示
        QPointF closestPoint = series0->at(closestIndex);
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(closestPoint.x()));
        QString timeStr = dateTime.toString("hh:mm:ss");
        QToolTip::showText(QCursor::pos(), QString("时间: %1, 数值: %2").arg(timeStr).arg(closestPoint.y()));
    } else {
        QToolTip::hideText();
    }
}


void valve::showPointToolTip1(const QPointF &point, bool state)
{
    if (state) {
        // 获取系列
        QChart *qchart = ui->graphicsView->chart();
        if (!qchart) {
            return;
        }
        QList<QAbstractSeries *> seriesList = qchart->series();
        if (seriesList.size() < 3) {
            return;
        }
        QLineSeries *series0 = qobject_cast<QLineSeries *>(seriesList.at(1));
        if (!series0 || series0->count() == 0) {
            return;
        }

        // 二分查找最接近的点
        qreal targetX = point.x();
        int left = 0;
        int right = series0->count() - 1;
        int closestIndex = 0;
        qreal minDistance = std::numeric_limits<qreal>::max();

        while (left <= right) {
            int mid = left + (right - left) / 2;
            QPointF midPoint = series0->at(mid);
            qreal distance = qAbs(midPoint.x() - targetX);

            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = mid;
            }

            if (midPoint.x() < targetX) {
                left = mid + 1;
            } else if (midPoint.x() > targetX) {
                right = mid - 1;
            } else {
                // 精确匹配，退出循环
                break;
            }
        }

        // 检查最接近点的左右邻居，确保找到全局最接近点
        if (closestIndex > 0) {
            QPointF leftPoint = series0->at(closestIndex - 1);
            qreal leftDistance = qAbs(leftPoint.x() - targetX);
            if (leftDistance < minDistance) {
                minDistance = leftDistance;
                closestIndex = closestIndex - 1;
            }
        }

        if (closestIndex < series0->count() - 1) {
            QPointF rightPoint = series0->at(closestIndex + 1);
            qreal rightDistance = qAbs(rightPoint.x() - targetX);
            if (rightDistance < minDistance) {
                closestIndex = closestIndex + 1;
            }
        }

        // 获取最接近点并显示工具提示
        QPointF closestPoint = series0->at(closestIndex);
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(closestPoint.x()));
        QString timeStr = dateTime.toString("hh:mm:ss");
        QToolTip::showText(QCursor::pos(), QString("时间: %1, 数值: %2").arg(timeStr).arg(closestPoint.y()));
    } else {
        QToolTip::hideText();
    }
}


void valve::showPointToolTip2(const QPointF &point, bool state)
{
    if (state) {
        // 获取系列
        QChart *qchart = ui->graphicsView->chart();
        if (!qchart) {
            return;
        }
        QList<QAbstractSeries *> seriesList = qchart->series();
        if (seriesList.size() < 3) {
            return;
        }
        QLineSeries *series0 = qobject_cast<QLineSeries *>(seriesList.at(2));
        if (!series0 || series0->count() == 0) {
            return;
        }

        // 二分查找最接近的点
        qreal targetX = point.x();
        int left = 0;
        int right = series0->count() - 1;
        int closestIndex = 0;
        qreal minDistance = std::numeric_limits<qreal>::max();

        while (left <= right) {
            int mid = left + (right - left) / 2;
            QPointF midPoint = series0->at(mid);
            qreal distance = qAbs(midPoint.x() - targetX);

            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = mid;
            }

            if (midPoint.x() < targetX) {
                left = mid + 1;
            } else if (midPoint.x() > targetX) {
                right = mid - 1;
            } else {
                // 精确匹配，退出循环
                break;
            }
        }

        // 检查最接近点的左右邻居，确保找到全局最接近点
        if (closestIndex > 0) {
            QPointF leftPoint = series0->at(closestIndex - 1);
            qreal leftDistance = qAbs(leftPoint.x() - targetX);
            if (leftDistance < minDistance) {
                minDistance = leftDistance;
                closestIndex = closestIndex - 1;
            }
        }

        if (closestIndex < series0->count() - 1) {
            QPointF rightPoint = series0->at(closestIndex + 1);
            qreal rightDistance = qAbs(rightPoint.x() - targetX);
            if (rightDistance < minDistance) {
                closestIndex = closestIndex + 1;
            }
        }

        // 获取最接近点并显示工具提示
        QPointF closestPoint = series0->at(closestIndex);
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(closestPoint.x()));
        QString timeStr = dateTime.toString("hh:mm:ss");
        QToolTip::showText(QCursor::pos(), QString("时间: %1, 数值: %2").arg(timeStr).arg(closestPoint.y()));
    } else {
        QToolTip::hideText();
    }
}

void valve::showPointToolTip3(const QPointF &point, bool state)
{
    if (state) {
        // 获取系列
        QChart *qchart = ui->graphicsView_2->chart();
        if (!qchart) {
            return;
        }
        QList<QAbstractSeries *> seriesList = qchart->series();
        if (seriesList.size() < 2) {
            return;
        }
        QLineSeries *series0 = qobject_cast<QLineSeries *>(seriesList.at(0));
        if (!series0 || series0->count() == 0) {
            return;
        }

        // 二分查找最接近的点
        qreal targetX = point.x();
        int left = 0;
        int right = series0->count() - 1;
        int closestIndex = 0;
        qreal minDistance = std::numeric_limits<qreal>::max();

        while (left <= right) {
            int mid = left + (right - left) / 2;
            QPointF midPoint = series0->at(mid);
            qreal distance = qAbs(midPoint.x() - targetX);

            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = mid;
            }

            if (midPoint.x() < targetX) {
                left = mid + 1;
            } else if (midPoint.x() > targetX) {
                right = mid - 1;
            } else {
                // 精确匹配，退出循环
                break;
            }
        }

        // 检查最接近点的左右邻居，确保找到全局最接近点
        if (closestIndex > 0) {
            QPointF leftPoint = series0->at(closestIndex - 1);
            qreal leftDistance = qAbs(leftPoint.x() - targetX);
            if (leftDistance < minDistance) {
                minDistance = leftDistance;
                closestIndex = closestIndex - 1;
            }
        }

        if (closestIndex < series0->count() - 1) {
            QPointF rightPoint = series0->at(closestIndex + 1);
            qreal rightDistance = qAbs(rightPoint.x() - targetX);
            if (rightDistance < minDistance) {
                closestIndex = closestIndex + 1;
            }
        }

        // 获取最接近点并显示工具提示
        QPointF closestPoint = series0->at(closestIndex);
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(closestPoint.x()));
        QString timeStr = dateTime.toString("hh:mm:ss");
        QToolTip::showText(QCursor::pos(), QString("时间: %1, 数值: %2").arg(timeStr).arg(closestPoint.y()));
    } else {
        QToolTip::hideText();
    }
}

void valve::showPointToolTip4(const QPointF &point, bool state)
{
    if (state) {
        // 获取系列
        QChart *qchart = ui->graphicsView_2->chart();
        if (!qchart) {
            return;
        }
        QList<QAbstractSeries *> seriesList = qchart->series();
        if (seriesList.size() < 2) {
            return;
        }
        QLineSeries *series0 = qobject_cast<QLineSeries *>(seriesList.at(1));
        if (!series0 || series0->count() == 0) {
            return;
        }

        // 二分查找最接近的点
        qreal targetX = point.x();
        int left = 0;
        int right = series0->count() - 1;
        int closestIndex = 0;
        qreal minDistance = std::numeric_limits<qreal>::max();

        while (left <= right) {
            int mid = left + (right - left) / 2;
            QPointF midPoint = series0->at(mid);
            qreal distance = qAbs(midPoint.x() - targetX);

            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = mid;
            }

            if (midPoint.x() < targetX) {
                left = mid + 1;
            } else if (midPoint.x() > targetX) {
                right = mid - 1;
            } else {
                // 精确匹配，退出循环
                break;
            }
        }

        // 检查最接近点的左右邻居，确保找到全局最接近点
        if (closestIndex > 0) {
            QPointF leftPoint = series0->at(closestIndex - 1);
            qreal leftDistance = qAbs(leftPoint.x() - targetX);
            if (leftDistance < minDistance) {
                minDistance = leftDistance;
                closestIndex = closestIndex - 1;
            }
        }

        if (closestIndex < series0->count() - 1) {
            QPointF rightPoint = series0->at(closestIndex + 1);
            qreal rightDistance = qAbs(rightPoint.x() - targetX);
            if (rightDistance < minDistance) {
                closestIndex = closestIndex + 1;
            }
        }

        // 获取最接近点并显示工具提示
        QPointF closestPoint = series0->at(closestIndex);
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(closestPoint.x()));
        QString timeStr = dateTime.toString("hh:mm:ss");
        QToolTip::showText(QCursor::pos(), QString("时间: %1, 数值: %2").arg(timeStr).arg(closestPoint.y()));
    } else {
        QToolTip::hideText();
    }
}



void valve::saveDataToFile()
{
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);

            // out.setCodec("UTF-8");
            QDateTime now = QDateTime::currentDateTime();
            out << now.toString("yyyy-MM-dd hh:mm:ss.zzz") << "  "
                << QString("阀芯位移值: %1").arg(faValue)
                <<QString(", PWMA: %1").arg(Apwmvalue)
                <<QString(", PWMB: %1").arg(Bpwmvalue)
                <<QString(", er: %1").arg(er)
                <<QString(", isLVDT: %1").arg(isLVDT)
                <<QString(", 外部模拟量: %1").arg(inputvalue)
                <<QString(", LVDT反馈电压: %1").arg(LVDTvalue)
                << "\n";
            file.close();
        }
    }
}




// void valve::saveNewData()
// {


//     saveDataToFile();

// }




void valve::on_pushButton_2_clicked()
{


    // 停止当前会话
    if (isDrawing || isPaused) {
        time1->stop();
        // saveTimer->stop();
        disconnect(canthread1, &CANThread::getProtocolData, this, &valve::onSpecificIdDataReceived);

        // 保存最后数据
        if (isDrawing) {
            saveDataToFile();
            appendToFile("System restarted!");
        }

        isDrawing = false;
        isPaused = false;
        hasActiveSession = false;
    }

    // 创建全新会话
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    QDir currentDir(QCoreApplication::applicationDirPath());
    // currentDir.cdUp();
    QString saveFolder = currentDir.path() + "/cantex/can解析数据";
    fileName = saveFolder + "/" + timestamp + ".txt";
    qDebug()<<saveFolder;
    activeSessionFileName = fileName;

    QDir dir(saveFolder);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            QMessageBox::critical(this, "错误", "无法创建保存文件夹！");
            return;
        }
    }

    // QDir dir(saveFolder);
    // if (!dir.exists() && !dir.mkpath(".")) {
    //     QMessageBox::critical(this, "错误", "无法创建保存文件夹！");
    //     return;
    // }

    // 写入文件头
    appendToFile("----------------------------------------------------------");
    appendToFile("> System restarted!");
    appendToFile("----------------------------------------------------------");
    appendToFile(QString("阀设备：%1").arg(ui->comboBox_11->currentText().toInt()));

    // 记录会话开始时间
    sessionStartTime = QDateTime::currentDateTime();
    pauseDuration = 0;

    // 清除图表
    clearCharts();

    // 连接信号并开始定时器
    connect(canthread1, &CANThread::getProtocolData, this, &valve::onSpecificIdDataReceived);
    // saveTimer->setInterval(ui->lineEdit->text().toInt());
    // saveTimer->start();

    // 重置图表状态
    xAxisRangeSet1 = false;
    xAxisRangeSet2 = false;

    // 验证输入
    if (!(validateLineEditInput(ui->lineEdit_12) && validateLineEditInput(ui->lineEdit_13) &&
          validateLineEditInput(ui->lineEdit_14) && validateLineEditInput(ui->lineEdit))) {
        time1->stop();
        // saveTimer->stop();
        disconnect(canthread1, &CANThread::getProtocolData, this, &valve::onSpecificIdDataReceived);
        return;
    }

    if (ui->lineEdit_13->text().toInt() >= ui->lineEdit_14->text().toInt()) {
        QMessageBox::warning(this, "输入错误", "起始量程应该小于结束量程。");
        time1->stop();
        // saveTimer->stop();
        disconnect(canthread1, &CANThread::getProtocolData, this, &valve::onSpecificIdDataReceived);
        return;
    }

    // 开始绘图
    isDrawing = true;
    isPaused = false;
    hasActiveSession = true;

    time1->setInterval(ui->lineEdit->text().toInt());
    time1->start();
}

