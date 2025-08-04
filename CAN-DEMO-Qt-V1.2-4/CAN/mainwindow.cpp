#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QButtonGroup>
#include <cfloat>
#include <QtWidgets/QGraphicsProxyWidget>
#include "xlsxdocument.h"
#include <QPdfWriter>
#include <QDesktopServices>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    , saveTimer(new QTimer(this))
    , saveThread(new QThread(this))
    , dataSaver(new datasaver())
    , startSaveRow(0)
    , isSaving(false)
{
    ui->setupUi(this);

    resize(1800, 1000);

    QStringList listHeader;
    listHeader << "系统时间" <<  "方向" << "ID号" <<  "数据";//"CAN通道" <<"帧类型" << "帧格式" << "长度" <<
    //"时间标识" << "时间标识(s)" <<传输
    ui->comboBox_3->setCurrentIndex(3);

    ui->tableWidget->setColumnCount(listHeader.count());
    ui->tableWidget->setHorizontalHeaderLabels(listHeader);

    ui->tableWidget->setColumnWidth(0,180);
    ui->tableWidget->setColumnWidth(1,110);
    ui->tableWidget->setColumnWidth(2,160);
    ui->tableWidget->setColumnWidth(3,210);


    ui->pushButton_8->setEnabled(false);
    ui->sendfaBt->setEnabled(false);
    ui->cycleBt->setEnabled(false);
    ui->bautBt->setEnabled(false);
    ui->LVDTBt->setEnabled(false);
    ui->recovBt->setEnabled(false);
    ui->saveBt->setEnabled(false);
    ui->savetxtBt->setEnabled(false);
    ui->savetxtBt_3->setEnabled(false);

    // for (int i = 1; i <= 0x7F; ++i) {
    //     QString hexString = QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
    //     ui->comboBox_12->addItem(hexString);
    // }

    for (int i = 1; i <= 0x7E; ++i) {
        QString hexString = QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
        QString displayText = hexString; // 默认显示两位十六进制

        // 如果是最后一个元素（0x7F），修改显示文本
        // if (i == 0x7F) {
        //     displayText = "7F全局配置";
        // }

        // 添加项：显示文本为 displayText，用户数据为 i 的实际值
        ui->comboBox_12->addItem(displayText, i);
    }

    ui->comboBox_12->setCurrentIndex(17);

    // for (int i = 1; i <= 0x7F; ++i) {
    //     QString hexString = QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
    //     ui->comboBox_10->addItem(hexString);
    // }

    for (int i = 1; i <= 0x7F; ++i) {
        QString hexString = QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
        QString displayText = hexString; // 默认显示两位十六进制

        // 如果是最后一个元素（0x7F），修改显示文本
        if (i == 0x7F) {
            displayText = "7F(全局配置)";
        }

        // 添加项：显示文本为 displayText，用户数据为 i 的实际值
        ui->comboBox_10->addItem(displayText, i);
    }

    ui->comboBox_10->setCurrentIndex(17);

    for (int i = 1; i <= 0x7E; ++i) {
        QString hexString = QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
        QString displayText = hexString; // 默认显示两位十六进制

        // 如果是最后一个元素（0x7F），修改显示文本
        // if (i == 0x7F) {
        //     displayText = "7F全局配置";
        // }

        // 添加项：显示文本为 displayText，用户数据为 i 的实际值
        ui->comboBox_11->addItem(displayText, i);
    }

    ui->comboBox_11->setCurrentIndex(17);


    for (int i = 1; i <= 0x7E; ++i) {
        QString hexString = QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
        QString displayText = hexString; // 默认显示两位十六进制

        // 如果是最后一个元素（0x7F），修改显示文本
        // if (i == 0x7F) {
        //     displayText = "7F全局配置";
        // }

        // 添加项：显示文本为 displayText，用户数据为 i 的实际值
        ui->comboBox_26->addItem(displayText, i);
    }

    ui->comboBox_26->setCurrentIndex(17);

    for (int i = 1; i <= 0x7E; ++i) {
        QString hexString = QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
        QString displayText = hexString; // 默认显示两位十六进制

        // 如果是最后一个元素（0x7F），修改显示文本
        // if (i == 0x7F) {
        //     displayText = "7F全局配置";
        // }

        // 添加项：显示文本为 displayText，用户数据为 i 的实际值
        ui->comboBox_26->addItem(displayText, i);
    }

    ui->comboBox_26->setCurrentIndex(17);


    for (int i = 1; i <= 0x7E; ++i) {
        QString hexString = QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
        QString displayText = hexString; // 默认显示两位十六进制

        // 如果是最后一个元素（0x7F），修改显示文本
        // if (i == 0x7F) {
        //     displayText = "7F全局配置";
        // }

        // 添加项：显示文本为 displayText，用户数据为 i 的实际值
        ui->comboBox_61->addItem(displayText, i);
    }

    ui->comboBox_61->setCurrentIndex(17);

    for (int i = 10; i <= 1000; i+=10) {
        QString String = QString("%1").arg(i);
        ui->comboBox_13->addItem(String);
    }

    ui->comboBox_13->setCurrentIndex(0);



    QButtonGroup *buttonGroup = new QButtonGroup(this);

    // 将三个QCheckBox添加到QButtonGroup中
    buttonGroup->addButton(ui->checkBox, 1);
    buttonGroup->addButton(ui->checkBox_2, 2);
    buttonGroup->addButton(ui->checkBox_3, 3);

    // 设置Exclusive属性为true，确保同一组中只能有一个按钮被选中
    buttonGroup->setExclusive(true);

    QButtonGroup *buttonGroup1 = new QButtonGroup(this);

    // 将三个QCheckBox添加到QButtonGroup中
    buttonGroup1->addButton(ui->checkBox_19, 1);
    buttonGroup1->addButton(ui->checkBox_20, 2);
    buttonGroup1->addButton(ui->checkBox_21, 3);

    // 设置Exclusive属性为true，确保同一组中只能有一个按钮被选中
    buttonGroup1->setExclusive(true);

    QDoubleValidator *validator = new QDoubleValidator(0, 100, 2, this);
    ui->lineEdit_15->setValidator(validator);
    ui->lineEdit_16->setValidator(validator);

    QDoubleValidator *yAxisValidator = new QDoubleValidator(-DBL_MAX, DBL_MAX, 2, this);
    ui->lineEdit_16->setValidator(yAxisValidator);
    ui->lineEdit_17->setValidator(yAxisValidator);



    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // faCount=0;


    QTimer *timer3 = new QTimer(this);
    connect(timer3, &QTimer::timeout, this, &MainWindow::updateTimeLabel);
    timer3->start(1000);

    canthread = new CANThread();



    timer = new QTimer(this);
    timer1 = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
    connect(canthread,&CANThread::getProtocolData,this,&MainWindow::onGetProtocolData);

    connect(timer1, &QTimer::timeout, this, &MainWindow::onTimerTimeout1);

    dataSaver->moveToThread(saveThread);
    saveTimer->setInterval(1000);
    saveThread->start();
    connect(saveTimer, &QTimer::timeout, this, &MainWindow::saveNewData);
    connect(dataSaver, &datasaver::saveFinished, this, &MainWindow::onSaveFinished);
    connect(dataSaver, &datasaver::errorOccurred, this, &MainWindow::onErrorOccurred);



    valveWindow=new valve(canthread);


    ui->frame->setFrameShape(QFrame::Box);  // 设置边框样式
    QVBoxLayout *layout = new QVBoxLayout(ui->frame);
    layout->addWidget(valveWindow);

    ui->lineEdit_15->setText("0");
    ui->lineEdit_16->setText("100");






    setupChart();
    setupChart1();
    setupChart2();
    setupChart3();
    setupChart4();
    initChart1();

    // m_modbusMaster = new QModbusRtuSerialMaster(this);

    // connect(serialPort,SIGNAL(readyRead()),this,SLOT(serialPort_receivedata()));

    serialPortTimer = new QTimer(this);
    connect(serialPortTimer, SIGNAL(timeout()), this, SLOT(updateSerialPortList()));
    serialPortTimer->start(2000); // 2000毫秒

    // 初始扫描
    updateSerialPortList();

    // QStringList serialname;
    // for(const QSerialPortInfo &info:QSerialPortInfo::availablePorts()){
    //     serialname+=info.portName();
    // }
    // ui->serialCb->addItems(serialname);
    ui->baundrateCb->setCurrentIndex(2);



    // QIntValidator *intValidator = new QIntValidator(1, 100,this);  // 范围1-100
    // ui->lineEdit_51->setValidator(intValidator);

    // qDebug() << "Validator Range:" << validator->bottom() << "-" << validator->top();
    // connect(ui->lineEdit_51, &QLineEdit::editingFinished, [this]() {
    //             QString text = ui->lineEdit_51->text();
    //             bool ok;
    //             int value = text.toInt(&ok);

    //             if (ok && value >= 1 && value <= 100) {
    //                 qDebug() << "输入有效:" << value;
    //             } else {
    //                 qDebug() << "输入无效:" << text;
    //                 ui->lineEdit_51->clear(); // 清除无效输入
    //             }
    //         }


    ui->lineEdit_52->setRange(0,2000);
    ui->lineEdit_57->setRange(0,2000);

    ui->lineEdit_50->setRange(0,1000);
    ui->lineEdit_55->setRange(0,1000);

    ui->lineEdit_51->setRange(0,1000);
    ui->lineEdit_56->setRange(0,1000);

    ui->lineEdit_6->setRange(0,1000);
    ui->lineEdit_19->setRange(0,1000);

    ui->lineEdit_7->setRange(0,1000);
    ui->lineEdit_20->setRange(0,1000);

    ui->lineEdit_8->setRange(0,2000);
    ui->lineEdit_21->setRange(0,2000);

    ui->lineEdit_54->setRange(0,1000000);

    // connect(ui->lineEdit_51, &QLineEdit::textChanged, [this](const QString &text){
    //     if(text.isEmpty()) return;

    //     bool ok;
    //     int value = text.toInt(&ok);

    //     if(!ok || value < 1 || value > 100) {
    //         ui->lineEdit_51->clear();
    //     }
    // });

    zoomableChartViews.append(ui->graphicsView);
    zoomableChartViews.append(ui->graphicsView_2);
    zoomableChartViews.append(ui->graphicsView_3);
    zoomableChartViews.append(ui->graphicsView_4);
    zoomableChartViews.append(ui->graphicsView_5);
    zoomableChartViews.append(ui->graphicsView_6);

    foreach (QChartView* view, zoomableChartViews) {
        view->viewport()->installEventFilter(this);
    }







}

MainWindow::~MainWindow()
{


        // 停止所有定时器
        if (timer) {
            timer->stop();
            delete timer;
            timer = nullptr;
        }

        if (timer1) {
            timer1->stop();
            delete timer1;
            timer1 = nullptr;
        }

        if (saveTimer) {
            saveTimer->stop();
            delete saveTimer;
            saveTimer = nullptr;
        }

        // 停止并等待数据保存线程完成
        if (dataSaver) {
            // 发出停止信号


            // 停止定时器
            if (saveTimer) {
                saveTimer->stop();
            }

            // 停止线程
            if (saveThread && saveThread->isRunning()) {
                saveThread->quit();
                saveThread->wait();
            }

            delete dataSaver;
            dataSaver = nullptr;
        }

        // 停止并等待CAN线程完成
        if (canthread) {
            // 发出停止信号
            canthread->stop();

            // 停止线程
            if (canthread->isRunning()) {
                canthread->quit();
                canthread->wait();
            }

            delete canthread;
            canthread = nullptr;
        }

        // 清理DBC窗口
        qDeleteAll(dbcWindows);
        dbcWindows.clear();

        // 清理阀门窗口
        if (valveWindow) {
            delete valveWindow;
            valveWindow = nullptr;
        }

        if (m_modbusThread) {
                m_modbusWorker->closeSerialPort();
                m_modbusThread->quit();
                m_modbusThread->wait();
                delete m_modbusThread;
            }

        // 最后删除UI
        delete ui;



}

void MainWindow::updateTimeLabel(){
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeString = currentTime.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_8->setText(timeString);
}

// 实现串口列表更新槽函数
void MainWindow::updateSerialPortList()
{
    QStringList newPorts;
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        newPorts.append(info.portName());
    }

    // 找出新增和移除的端口
    QStringList addedPorts;
    QStringList removedPorts;

    for (const QString &port : newPorts) {
        if (!currentPorts.contains(port)) {
            addedPorts.append(port);
        }
    }

    for (const QString &port : currentPorts) {
        if (!newPorts.contains(port)) {
            removedPorts.append(port);
        }
    }

    // 如果有变化，触发信号
    if (!addedPorts.isEmpty() || !removedPorts.isEmpty()) {
        currentPorts = newPorts;
        ui->serialCb->clear();
        ui->serialCb->addItems(currentPorts);
    }


    // 或者更新下拉列表

}



void MainWindow::AddDataToList(QStringList strList)
{

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    for (int i = 0; i < strList.count(); ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(strList.at(i));
        ui->tableWidget->setItem(row, i, item);
    }



    // 批量设置对齐方式
    for (int i = 0; i < ui->tableWidget->columnCount(); ++i) {
        QTableWidgetItem *item = ui->tableWidget->item(row, i);
        if (item) {
            item->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->tableWidget->scrollToBottom();
}

void MainWindow::onGetProtocolData(VCI_CAN_OBJ *vci,unsigned int dwRel,unsigned int channel)
{




// 存储设备ID到列表项的映射
// static QHash<quint32, QListWidgetItem*> deviceIdToListItems;
// // 存储设备最后更新时间
// static QHash<quint32, QDateTime> deviceLastSeen;
static int emptyFrameCount = 0;
// 如果没有数据帧，将所有设备标记为离线
if (dwRel == 0) {

    emptyFrameCount++;

    if (emptyFrameCount >= 25) {
        markAllDevicesOffline(deviceIdToListItems);
        emptyFrameCount = 0;
        // ui->label_5->setText("LVDT状态：无数据");
        // ui->label_5->setStyleSheet("color: gray;");
    }
    return;
}

// 重置计数器并更新全局状态
// static int emptyFrameCount = 0;
emptyFrameCount = 0;
// ui->label_5->setText("LVDT状态：检测中");
// ui->label_5->setStyleSheet("color: blue;");

// 清空临时状态集合
QSet<quint32> updatedDevices;

    for (unsigned int i = 0; i < dwRel; i++) {
        QStringList messageList;
        messageList << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        messageList << "接收";
        messageList << "0x" + QString("%1").arg(vci[i].ID, 8, 16, QChar('0')).toUpper();

        quint32 originalId = vci[i].ID;
        bool isValveDevice = (originalId >= 0x180 && originalId <= 0x1FF);
        bool hasLvdt = false;

        // 处理阀设备的LVDT状态
        if (isValveDevice) {
            quint32 deviceId = originalId - 0x180;
            updatedDevices.insert(deviceId);
            deviceLastSeen[deviceId] = QDateTime::currentDateTime();

            // 解析LVDT状态
            if (vci[i].RemoteFlag == 0 && vci[i].DataLen >= 1) {
                hasLvdt = ((vci[i].Data[vci[i].DataLen - 1] & 0x01) == 0);
            }

            // 更新或创建设备状态项
            updateDeviceStatus(deviceId, hasLvdt, deviceIdToListItems);
        }

        // 构建完整消息并添加到列表
        QString dataStr;
        if (vci[i].RemoteFlag == 0) {
            for (int j = 0; j < vci[i].DataLen; j++)
                dataStr += QString("%1 ").arg(vci[i].Data[j], 2, 16, QChar('0')).toUpper();
        } else {
            dataStr = "[远程帧]";
        }
        messageList << dataStr;

        // 根据复选框状态添加消息
        if (ui->checkBox_4->isChecked()) {
            AddDataToList(messageList);
        }










        if(nodeReceived==1){
            if (vci[i].ID == 0x7e4 && vci[i].DataLen == 8 && vci[i].Data[1] == 0x00 && vci[i].Data[0] == 0x11) {
                ui->plainTextEdit->appendPlainText(QString("0x%1节点号配置回令接收成功！\n").arg(ui->comboBox_11->currentData().toInt()));
                nodeReceived = 0;
                t1=0;
            }
            else{
                t1++;
                ui->plainTextEdit->appendPlainText("节点号正在配置中！");
            }
            if(t1>10){
                ui->plainTextEdit->appendPlainText(QString("0x%1节点号配置失败！\n").arg(ui->comboBox_11->currentData().toInt()));
                t1=0;
                nodeReceived = 0;
            }
        }

        if(cycleReceived==1){
            if (vci[i].ID == 0x7e4 && vci[i].DataLen == 8 && vci[i].Data[1] == 0x00 && vci[i].Data[0] == 0x12) {
                ui->plainTextEdit->appendPlainText(QString("配置周期为%1ms成功！\n").arg(ui->comboBox_13->currentText()));
                cycleReceived = 0;
                t2=0;
            }
            else{
                t2++;
                ui->plainTextEdit->appendPlainText("周期正在配置中！");
            }
            if(t2>10){
                ui->plainTextEdit->appendPlainText(QString("配置周期为%1ms失败！\n").arg(ui->comboBox_13->currentText()));
                t2=0;
                cycleReceived = 0;
            }
        }

        if(baudReceived==1){
            if (vci[i].ID == 0x7e4 && vci[i].DataLen == 8 && vci[i].Data[1] == 0x00 && vci[i].Data[0] == 0x13) {
                ui->plainTextEdit->appendPlainText(QString("配置波特率为%1kb成功！\n").arg(ui->comboBox_7->currentText()));
                baudReceived = 0;
                t3=0;
            }
            else{
                t3++;
                ui->plainTextEdit->appendPlainText("正在配置波特率中！");
            }
            if(t3>10){
                ui->plainTextEdit->appendPlainText(QString("配置波特率为%1kb失败！\n").arg(ui->comboBox_7->currentText()));
                t3=0;
                baudReceived = 0;
            }
        }

        if(LVDTReceived==1){
            if (vci[i].ID == 0x7e4 && vci[i].DataLen == 8 && vci[i].Data[1] == 0x00 && vci[i].Data[0] == 0x16) {
                switch (vci[i].Data[2]) {
                case 0x00:
                    ui->plainTextEdit->appendPlainText("阀芯中位配置成功\n");
                    break;
                case 0x10:
                    ui->plainTextEdit->appendPlainText("PWMA流量起点配置成功\n");
                    break;
                case 0x11:
                    ui->plainTextEdit->appendPlainText("PWMA流量终点配置成功\n");
                    break;
                case 0x20:
                    ui->plainTextEdit->appendPlainText("PWMB流量起点配置成功\n");
                    break;
                case 0x21:
                    ui->plainTextEdit->appendPlainText("PWMB流量终点配置成功\n");
                    break;
                default:
                    return;
                    break;
                }
                LVDTReceived = 0;
                t4=0;
            }
            else{
                t4++;
                ui->plainTextEdit->appendPlainText("正在配置LVDT");
            }
            if(t4>10){
                ui->plainTextEdit->appendPlainText("LVDT配置失败！\n");
                t4=0;
                LVDTReceived = 0;
            }
        }


        if(LVDTReceived2==1){
            if (vci[i].ID == 0x7e4 && vci[i].DataLen == 8 && vci[i].Data[1] == 0x00 && vci[i].Data[0] == 0x16) {
                switch (vci[i].Data[2]) {
                case 0x00:
                    ui->plainTextEdit_2->appendPlainText("阀芯中位配置成功\n");
                    break;
                case 0x10:
                    ui->plainTextEdit_2->appendPlainText("PWMA流量起点配置成功\n");
                    break;
                case 0x11:
                    ui->plainTextEdit_2->appendPlainText("PWMA流量终点配置成功\n");
                    break;
                case 0x20:
                    ui->plainTextEdit_2->appendPlainText("PWMB流量起点配置成功\n");
                    break;
                case 0x21:
                    ui->plainTextEdit_2->appendPlainText("PWMB流量终点配置成功\n");
                    break;
                default:
                    return;
                    break;
                }
                LVDTReceived2 = 0;
                t4=0;
            }
            else{
                t9++;
                ui->plainTextEdit_2->appendPlainText("正在配置LVDT");
            }
            if(t9>10){
                ui->plainTextEdit_2->appendPlainText("LVDT配置失败！\n");
                t9=0;
                LVDTReceived2 = 0;
            }
        }

        if(recovReceived==1){
            if (vci[i].ID == 0x7e4 && vci[i].DataLen == 8 && vci[i].Data[1] == 0x00 && vci[i].Data[0] == 0xAA) {
                ui->plainTextEdit->appendPlainText("恢复出厂设置成功！\n");
                recovReceived = 0;
            }
            else{
                t5++;
                ui->plainTextEdit->appendPlainText("正在恢复出厂设置！");
            }
            if(t5>10){
                ui->plainTextEdit->appendPlainText("恢复出厂设置失败！\n");
                t5=0;
                recovReceived = 0;
            }
        }



        if(saveReceived==1){
            if (vci[i].ID == 0x7e4 && vci[i].DataLen == 8 && vci[i].Data[1] == 0x00 && vci[i].Data[0] == 0x17) {
                ui->plainTextEdit->appendPlainText("保存设置成功！\n");
                saveReceived = 0;
                t6=0;
            }
            else{
                t6++;
                ui->plainTextEdit->appendPlainText("正在保存设置！");
            }
            if(t6>10){
                ui->plainTextEdit->appendPlainText("保存设置失败！\n");
                t6=0;
                saveReceived = 0;
            }
        }

        if(saveReceived2==1){
            if (vci[i].ID == 0x7e4 && vci[i].DataLen == 8 && vci[i].Data[1] == 0x00 && vci[i].Data[0] == 0x17) {
                ui->plainTextEdit_2->appendPlainText("保存设置成功！\n");
                saveReceived2 = 0;
                t10=0;
            }
            else{
                t10++;
                ui->plainTextEdit_2->appendPlainText("正在保存设置！");
            }
            if(t10>10){
                ui->plainTextEdit_2->appendPlainText("保存设置失败！\n");
                t10=0;
                saveReceived2 = 0;
            }
        }

        if(wlReceived==1){
            if(originalId==0x380+ui->comboBox_14->currentData().toInt()){
                QByteArray byteArray(reinterpret_cast<const char*>(vci[i].Data), 8);
                t7=0;
                processCanResponse(byteArray,wlReceived);

            }else{
                t7++;
            }
            if(t7>1000){
                ui->plainTextEdit_2->appendPlainText("位移/流量标定设置失败！\n");
                t7=0;
                wlReceived = 0;
            }
        }

        if(dlReceived==1){
            if(originalId==0x480+ui->comboBox_14->currentData().toInt()){
                QByteArray byteArray(reinterpret_cast<const char*>(vci[i].Data), 8);
                t8=0;
                processCanResponse2(byteArray,dlReceived);

            }else{
                t8++;
            }
            if(t8>1000){
                ui->plainTextEdit_2->appendPlainText("电流/流量标定设置失败！\n");
                t8=0;
                dlReceived = 0;
            }
        }

        if(wdReceived==1){
            if(originalId==0x580+ui->comboBox_14->currentData().toInt()){
                QByteArray byteArray(reinterpret_cast<const char*>(vci[i].Data), 8);
                t11=0;
                processCanResponse3(byteArray,wdReceived);

            }else{
                t11++;
            }
            if(t11>1000){
                ui->plainTextEdit_2->appendPlainText("位移/电压标定设置失败！\n");
                t11=0;
                wdReceived = 0;
            }
        }


    }

    // 检查超时的设备并标记为离线
    checkTimeoutDevices(deviceIdToListItems, deviceLastSeen, updatedDevices);

}


// 在类中添加成员变量
// quint32 groupStatus = 0;  // 32位状态变量，每bit表示一组是否接收成功
// bool allGroupsReceived = false;  // 标记是否所有组都已接收

int countBitsSet(quint32 value) {
    int count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

// 处理接收到的CAN数据
void MainWindow::processCanResponse(const QByteArray& canData,int &wlReceived) {

    // 检查数据长度是否符合预期
    if (canData.size() < 8) return;

    // 提取接收标记字节（假设B0~B3位于索引4~7）
    quint8 b0 = static_cast<quint8>(canData.at(0));
    quint8 b1 = static_cast<quint8>(canData.at(1));
    quint8 b2 = static_cast<quint8>(canData.at(2));
    quint8 b3 = static_cast<quint8>(canData.at(3));

    quint8 b4 = static_cast<quint8>(canData.at(4));
    quint8 b5 = static_cast<quint8>(canData.at(5));
    quint8 b6 = static_cast<quint8>(canData.at(6));
    quint8 b7 = static_cast<quint8>(canData.at(7));

    // 组合4个字节为32位状态变量
    quint32 receivedGroups = (static_cast<quint32>(b0) << 0) |
                             (static_cast<quint32>(b1) << 8) |
                             (static_cast<quint32>(b2) << 16) |
                             (static_cast<quint32>(b3) << 24);



    quint32 receivedGroups2 = (static_cast<quint32>(b4) << 0) |
                             (static_cast<quint32>(b5) << 8) |
                             (static_cast<quint32>(b6) << 16) |
                             (static_cast<quint32>(b7) << 24);



    // 更新状态（使用OR操作确保已接收的组不会被清除）
    // groupStatus |= receivedGroups;
    // groupStatus2 |= receivedGroups2;

    // int receivedCount = countBitsSet(groupStatus);
    int receivedCount = countBitsSet(receivedGroups);

    // 可选：显示当前接收进度
    // if(receivedCount!=0){
    //     ui->plainTextEdit_2->appendPlainText(
    //         QString("%1组流量/位移标定数据已标定成功").arg(receivedCount)
    //         );
    // }

    // int receivedCount2 = countBitsSet(groupStatus2);
    int receivedCount2 = countBitsSet(receivedGroups2);
    // // 可选：显示当前接收进度
    // if(receivedCount2!=0){
    //     ui->plainTextEdit_2->appendPlainText(
    //         QString("%1组流量/位移标定数据已标定成功").arg(receivedCount2)
    //         );
    // }
    qDebug()<<receivedCount+receivedCount2<<(flowDataBuffer.size()+2)/3;

    // 检查是否所有32组都已接收成功
    if (receivedCount+receivedCount2 == (flowDataBuffer.size()+2)/3 ) {
        QByteArray canData;
        int groupNumber = 0xAA;
        canData.clear();

        // 填充全零数据
        for (int i = 0; i < 6; ++i) {
            canData.append('\x00');
        }

        // 添加分组序号(0xAA)
        canData.append(groupNumber);

        // 添加固定值 0x52
        canData.append(direct);

        // 发送保存指令
        if (!canData.isEmpty()) {
            int frameId = 0x300 + ui->comboBox_14->currentData().toInt();
            unsigned char data[8];
            for (int i = 0; i < canData.size(); ++i) {
                data[i] = static_cast<unsigned char>(canData.at(i));
            }

            if (canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                                    frameId,
                                    0,
                                    0,
                                    data,
                                    8)) {
                ui->plainTextEdit_2->appendPlainText(
                    QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") +
                    " 已发送标定保存指令"
                    );
            }
        }


        fcount=0;


        // 显示发送成功信息（带时间戳）
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        ui->plainTextEdit_2->appendPlainText(
            timestamp + QString("%1组标定数据已标定成功!").arg(receivedCount+receivedCount2)
            );
        wlReceived=0;
        // groupStatus=0;
        // groupStatus2=0;
    }
}

// 辅助函数：计算整数中被置位的位数


void MainWindow::processCanResponse2(const QByteArray& canData,int &dlReceived) {

    // 检查数据长度是否符合预期
    if (canData.size() < 8) return;

    // 提取接收标记字节（假设B0~B3位于索引4~7）
    quint8 b0 = static_cast<quint8>(canData.at(0));
    quint8 b1 = static_cast<quint8>(canData.at(1));
    quint8 b2 = static_cast<quint8>(canData.at(2));
    quint8 b3 = static_cast<quint8>(canData.at(3));

    quint8 b4 = static_cast<quint8>(canData.at(4));
    quint8 b5 = static_cast<quint8>(canData.at(5));
    quint8 b6 = static_cast<quint8>(canData.at(6));
    quint8 b7 = static_cast<quint8>(canData.at(7));

    // 组合4个字节为32位状态变量
    quint32 receivedGroups = (static_cast<quint32>(b0) << 0) |
                             (static_cast<quint32>(b1) << 8) |
                             (static_cast<quint32>(b2) << 16) |
                             (static_cast<quint32>(b3) << 24);



    quint32 receivedGroups2 = (static_cast<quint32>(b4) << 0) |
                              (static_cast<quint32>(b5) << 8) |
                              (static_cast<quint32>(b6) << 16) |
                              (static_cast<quint32>(b7) << 24);



    // 更新状态（使用OR操作确保已接收的组不会被清除）
    // groupStatus3 |= receivedGroups;
    // groupStatus4 |= receivedGroups2;

    // int receivedCount = countBitsSet(groupStatus3);
    int receivedCount = countBitsSet(receivedGroups);

    // // 可选：显示当前接收进度
    // if(receivedCount!=0){
    //     ui->plainTextEdit_2->appendPlainText(
    //         QString("%1组电流/流量标定数据已标定成功").arg(receivedCount)
    //         );
    // }

    // int receivedCount2 = countBitsSet(groupStatus4);
        int receivedCount2 = countBitsSet(receivedGroups2);
    // // 可选：显示当前接收进度
    // if(receivedCount2!=0){
    //     ui->plainTextEdit_2->appendPlainText(
    //         QString("%1组电流/流量标定数据已标定成功").arg(receivedCount2)
    //         );
    // }

    // 检查是否所有32组都已接收成功
    if (receivedCount+receivedCount2 == (flowDataBuffer2.size()+2)/3 ) {
        QByteArray canData;
        int groupNumber = 0xAA;
        canData.clear();

        // 填充全零数据
        for (int i = 0; i < 6; ++i) {
            canData.append('\x00');
        }

        // 添加分组序号(0xAA)
        canData.append(groupNumber);

        // 添加固定值 0x52
        canData.append(direct2);

        // 发送保存指令
        if (!canData.isEmpty()) {
            int frameId = 0x400 + ui->comboBox_14->currentData().toInt();
            unsigned char data[8];
            for (int i = 0; i < canData.size(); ++i) {
                data[i] = static_cast<unsigned char>(canData.at(i));
            }

            if (canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                                    frameId,
                                    0,
                                    0,
                                    data,
                                    8)) {
                ui->plainTextEdit_2->appendPlainText(
                    QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") +
                    " 已发送标定保存指令"
                    );
            }
        }
        fcount2=0;
        // 显示发送成功信息（带时间戳）
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        ui->plainTextEdit_2->appendPlainText(
            timestamp + QString("%1组电流/流量标定数据已标定成功!").arg(receivedCount+receivedCount2)
            );
        dlReceived=0;
        // groupStatus3=0;
        // groupStatus4=0;
    }
}




void MainWindow::processCanResponse3(const QByteArray& canData,int &dlReceived) {

    // 检查数据长度是否符合预期
    if (canData.size() < 8) return;

    // 提取接收标记字节（假设B0~B3位于索引4~7）
    quint8 b0 = static_cast<quint8>(canData.at(0));
    quint8 b1 = static_cast<quint8>(canData.at(1));
    quint8 b2 = static_cast<quint8>(canData.at(2));
    quint8 b3 = static_cast<quint8>(canData.at(3));


    // 组合4个字节为32位状态变量
    quint32 receivedGroups = (static_cast<quint32>(b0) << 0) |
                             (static_cast<quint32>(b1) << 8) |
                             (static_cast<quint32>(b2) << 16) |
                             (static_cast<quint32>(b3) << 24);







    // 更新状态（使用OR操作确保已接收的组不会被清除）
    // groupStatus5 |= receivedGroups;


    // int receivedCount = countBitsSet(groupStatus5);
    int receivedCount = countBitsSet(receivedGroups);

    // // 可选：显示当前接收进度
    // if(receivedCount!=0){
    //     ui->plainTextEdit_2->appendPlainText(
    //         QString("%1组电流/流量标定数据已标定成功").arg(receivedCount)
    //         );
    // }



    // 检查是否所有32组都已接收成功
    if (receivedCount == (static_cast<int>((flowDataBuffer3.size() + 1) / 2) )) {
        QByteArray canData;

        // 所有数据发送完成，发送保存指令(分组序号=0xAA)
        int groupNumber = 0xAA;
        canData.clear();

        // 填充全零数据
        for (int i = 0; i < 6; ++i) {
            canData.append('\x00');
        }

        // 添加分组序号(0xAA)
        canData.append(groupNumber);

        // 添加固定值 0x52
        canData.append(static_cast<char>(0x52));

        // 发送保存指令
        if (!canData.isEmpty()) {
            int frameId = 0x500 + ui->comboBox_14->currentData().toInt();
            unsigned char data[8];
            for (int i = 0; i < canData.size(); ++i) {
                data[i] = static_cast<unsigned char>(canData.at(i));
            }

            if (canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                                    frameId,
                                    0,
                                    0,
                                    data,
                                    8)) {
                ui->plainTextEdit_2->appendPlainText(
                    QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") +
                    " 已发送标定保存指令"
                    );
            }
        }


        // 显示发送成功信息（带时间戳）
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        ui->plainTextEdit_2->appendPlainText(
            timestamp + QString("%1组电流/流量标定数据已标定成功!").arg(receivedCount)
            );
        wdReceived=0;
        // groupStatus5=0;

    }
}






void MainWindow::updateDeviceStatus(quint32 deviceId, bool hasLvdt,
                                    QHash<quint32, QListWidgetItem*>& idToItems)
{
    QString statusText = hasLvdt ? "有LVDT" : "无LVDT";
    QString color = hasLvdt ? "green" : "red";
    QString itemText = QString("阀设备ID：0x%1  %2").arg(deviceId, 2, 16, QChar('0')).toUpper().arg(statusText);

    // 如果已存在该项，更新它
    if (idToItems.contains(deviceId)) {
        QListWidgetItem *item = idToItems[deviceId];
        item->setText(itemText);
        item->setForeground(QColor(color));
    }
    // 否则创建新项
    else {
        QListWidgetItem *item = new QListWidgetItem(itemText);
        item->setForeground(QColor(color));

        // 查找插入位置，保持ID升序排列
        int insertPos = 0;
        while (insertPos < ui->listWidget->count()) {
            QString currentText = ui->listWidget->item(insertPos)->text();
            if (currentText.startsWith("阀设备ID：")) {
                QString currentIdStr = currentText.mid(9, 2);
                bool ok;
                int currentId = currentIdStr.toInt(&ok, 16);
                if (ok && currentId > deviceId) {
                    break;
                }
            }
            insertPos++;
        }

        ui->listWidget->insertItem(insertPos, item);
        idToItems[deviceId] = item;
    }
}

void MainWindow::markAllDevicesOffline(QHash<quint32, QListWidgetItem*>& idToItems)
{
    QHashIterator<quint32, QListWidgetItem*> it(idToItems);

    while (it.hasNext()) {
        it.next();
        QListWidgetItem *item = it.value();
        item->setText(QString("阀设备ID：0x%1  离线").arg(it.key(), 2, 16, QChar('0')).toUpper());
        item->setForeground(QColor("gray"));
    }
}

// 检查超时的设备并标记为离线
void MainWindow::checkTimeoutDevices(QHash<quint32, QListWidgetItem*>& idToItems,
                                     const QHash<quint32, QDateTime>& lastSeen,
                                     const QSet<quint32>& updatedDevices)
{
    QDateTime now = QDateTime::currentDateTime();
    QMutableHashIterator<quint32, QListWidgetItem*> it(idToItems);

    while (it.hasNext()) {
        it.next();
        quint32 deviceId = it.key();

        // 如果设备超过2秒未更新，标记为离线
        if (!updatedDevices.contains(deviceId) &&
            lastSeen.value(deviceId).msecsTo(now) > 2000) {

            QListWidgetItem *item = it.value();
            item->setText(QString("阀设备ID：0x%1  离线").arg(deviceId, 2, 16, QChar('0')).toUpper());
            item->setForeground(QColor("gray"));
        }
    }
}



QString versionStr(USHORT ver)
{
    return "V" + QString::number((ver & 0x0FFF) /0x100,16).toUpper() + "." + QString("%1 ").arg((ver & 0x0FFF) % 0x100,2,16,QChar('0')).toUpper();
}



void MainWindow::on_pushButton_clicked()//打开
{
    if(ui->pushButton->text() == tr("打开设备"))
    {
        UINT baundRate = 0;
        if(ui->comboBox_3->currentText().indexOf("Kbps") != -1)
            baundRate = ui->comboBox_3->currentText().remove("Kbps").toUInt();
        else
            baundRate = QVariant(ui->comboBox_3->currentText().remove("Mbps").toFloat()).toUInt();
        UINT channel = (ui->comboBox->currentIndex() == 1) ? PCAN_USBBUS1 : 0;
        bool dev = canthread->openDevice(static_cast<CAN_Device_Type>(ui->comboBox->currentIndex()),
                                      QVariant(ui->comboBox_2->currentIndex()).toUInt(),
                                      channel,baundRate);
        if(dev == true)
        {
            ui->comboBox->setEnabled(false);
            ui->comboBox_2->setEnabled(false);
            ui->comboBox_3->setEnabled(false);
            // ui->pushButton_2->setEnabled(true);
            ui->pushButton->setText(tr("关闭设备"));
            ui->plainTextEdit->appendPlainText("打开设备成功!\n");
            // QMessageBox::information(this,"成功","打开设备成功！");
        }
        else{
        QMessageBox::warning(this,"警告","打开设备失败！");
        return;
        }



        if(canthread->initCAN())
        {
            // ui->pushButton_3->setEnabled(true);
            // ui->pushButton_2->setEnabled(false);
            ui->plainTextEdit->appendPlainText("CAN初始化成功!\n");
        }
        else{
        QMessageBox::warning(this,"警告","CAN初始化失败！");
        return;
        }





        if(canthread->startCAN())
        {
            // ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(true);
            ui->sendBtn->setEnabled(true);

            ui->pushButton_8->setEnabled(true);
            ui->sendfaBt->setEnabled(true);
            ui->cycleBt->setEnabled(true);
            ui->bautBt->setEnabled(true);
            ui->LVDTBt->setEnabled(true);
            ui->recovBt->setEnabled(true);
            ui->saveBt->setEnabled(true);
            ui->savetxtBt->setEnabled(true);
            ui->savetxtBt_3->setEnabled(true);
            canthread->start();
            QMessageBox::information(this,"成功","打开设备成功！");
            ui->plainTextEdit->appendPlainText("CAN启动成功!\n");
        }
        else{
        QMessageBox::warning(this,"警告","CAN启动失败！");
        return;
        }

    }
    else if(ui->pushButton->text() == tr("关闭设备"))
    {
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->sendBtn->setEnabled(false);
        // ui->pushButton_2->setEnabled(false);
        // ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);

        ui->pushButton_8->setEnabled(false);
        ui->sendfaBt->setEnabled(false);
        ui->cycleBt->setEnabled(false);
        ui->bautBt->setEnabled(false);
        ui->LVDTBt->setEnabled(false);
        ui->recovBt->setEnabled(false);
        ui->saveBt->setEnabled(false);
        ui->savetxtBt->setEnabled(false);
        ui->savetxtBt_3->setEnabled(false);

        ui->pushButton->setText(tr("打开设备"));
        canthread->stop();
        canthread->closeDevice();
        // deviceIdToListItems.clear();
        // deviceLastSeen.clear();
        // for (int i = 0; i < ui->listWidget->count(); ++i) {
        //     QListWidgetItem *item = ui->listWidget->item(i);
        //     ui->listWidget->removeItemWidget(item);
        // }
        qDeleteAll(deviceIdToListItems);  // 删除所有列表项对象
        deviceIdToListItems.clear();      // 清空哈希表
        ui->listWidget->clear();
        ui->plainTextEdit->appendPlainText("关闭设备成功!\n");
    }
}

void MainWindow::on_sendBtn_clicked()
{
    int count = ui->sendIDEdit_2->text().toInt();
    if (count <= 0) {
        QMessageBox::warning(this, "警告", "发送次数必须大于 0！");
        return;
    }
    // 设置剩余发送次数
    remainingCount = count;
    // 设置定时器的时间间隔（单位：毫秒），这里设置为 1000 毫秒即 1 秒
    int interval = ui->sendIDEdit_3->text().toInt();
    timer->start(interval);
}

void MainWindow::on_cleanListBtn_clicked()
{
    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_pushButton_4_clicked()//复位
{
    if(canthread->reSetCAN())
    {
        ui->pushButton_4->setEnabled(false);
        ui->sendBtn->setEnabled(false);
        // ui->pushButton_3->setEnabled(true);
        ui->plainTextEdit->appendPlainText("CAN复位成功!\n");
    }
    else
        QMessageBox::warning(this,"警告","CAN复位失败！");
}

// void MainWindow::on_pushButton_2_clicked()//初始化
// {
//     if(canthread->initCAN())
//     {
//         ui->pushButton_3->setEnabled(true);
//         ui->pushButton_2->setEnabled(false);
//         ui->plainTextEdit->appendPlainText("CAN初始化成功!\n");
//     }
//     else
//         QMessageBox::warning(this,"警告","CAN初始化失败！");
// }

// void MainWindow::on_pushButton_3_clicked()//启动
// {
//     if(canthread->startCAN())
//     {
//         ui->pushButton_3->setEnabled(false);
//         ui->pushButton_4->setEnabled(true);
//         ui->sendBtn->setEnabled(true);

//         ui->pushButton_8->setEnabled(true);
//         ui->sendfaBt->setEnabled(true);
//         ui->cycleBt->setEnabled(true);
//         ui->bautBt->setEnabled(true);
//         ui->LVDTBt->setEnabled(true);
//         ui->recovBt->setEnabled(true);
//         ui->saveBt->setEnabled(true);
//         ui->savetxtBt->setEnabled(true);
//         ui->savetxtBt_3->setEnabled(true);
//         canthread->start();

//         ui->plainTextEdit->appendPlainText("CAN启动成功!\n");
//     }
//     else
//         QMessageBox::warning(this,"警告","CAN启动失败！");
// }


// 封装函数，将 unsigned char 数组转换为十六进制字符串
QString arrayToHexString(const unsigned char* data, size_t size) {
    QString dataString;
    for (size_t i = 0; i < size; ++i) {
        dataString += QString("%1 ").arg(static_cast<int>(data[i]), 2, 16, QChar('0'));
    }
    return dataString;
}

// 封装构建 QStringList 消息的函数
QStringList buildMessageList(QComboBox* comboBox_4, unsigned short NID, QComboBox* comboBox_5,  const unsigned char* data, int dlc) {
    QStringList messageList;
    messageList.clear();

    // 时间
    messageList << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");



    // 收发
    messageList << "发送";

    // ID
    messageList << "0x" + QString("%1").arg(NID, 3, 16, QChar('0')).toUpper();



    QString str = "";
    if (comboBox_5->currentIndex() == 0) { // 数据帧显示数据

        for (int j = 0; j < dlc; ++j) {
            str += QString("%1 ").arg((unsigned char)data[j], 2, 16, QChar('0')).toUpper();
        }
    } else {
        messageList << "0x0"; // 长度
    }
    messageList << str;

    return messageList;
}

void MainWindow::onTimerTimeout()
{
    if (remainingCount <= 0) {
        // 发送次数已用完，停止定时器
        timer->stop();
        return;
    }

    if(ui->comboBox_6->currentIndex() == 0)//标准帧，ID 范围0-0x7FF
    {
        if(ui->sendIDEdit->text().toInt(Q_NULLPTR,16) > 0x7FF)
        {
            QMessageBox::warning(this,"警告","发送失败，标准帧ID范围为0~0x7FF！");
            timer->stop();
            remainingCount=0;
            return;
        }
    }
    else
    {
        if(ui->sendIDEdit->text().toInt(Q_NULLPTR,16) > 0x1FFFFFFF)
        {
            QMessageBox::warning(this,"警告","发送失败，扩展帧ID范围为0~0x1FFFFFFF！");
            timer->stop();
            remainingCount=0;
            return;
        }
    }
    QStringList strList = ui->sendDataEdit->text().split(" ");
    unsigned char data[8];
    memset(data,0,8);
    int dlc = 0;
    dlc = strList.count() > 8 ? 8 : strList.count();
    for(int i = 0;i < dlc;i ++)
        data[i] = strList.at(i).toInt(Q_NULLPTR,16);
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                            QVariant(ui->sendIDEdit->text().toInt(Q_NULLPTR,16)).toUInt(),
                            ui->comboBox_5->currentIndex(),
                            ui->comboBox_6->currentIndex(),
                            data,dlc))
    {//发送成功，打印数据
        QStringList messageList;

        messageList.clear();
        messageList << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");//时间

        messageList << "发送";//收发
        messageList << "0x" + ui->sendIDEdit->text().toUpper();//ID

        QString str = "";
        if(ui->comboBox_5->currentIndex() == 0)//数据帧显示数据
        {

            for(int j = 0;j < dlc;j ++)
                str += QString("%1 ").arg((unsigned char)data[j],2,16,QChar('0')).toUpper();//QString::number((unsigned char)data[j],16) + " ";
        }
        else
            messageList << "0x0";//长度
        messageList << str;//数据
        if(ui->checkBox_4->checkState())
        AddDataToList(messageList);
    }
    else
    {
        QMessageBox::warning(this,"警告","数据发送失败！");
        timer->stop();
    }

    // 减少剩余发送次数
    remainingCount--;
}

void MainWindow::on_pushButton_5_clicked()
{
    // timer->stop();
    remainingCount=0;
}
// int count = ui->lineEdit_4->text().toInt();
// if (count <= 0) {
//     QMessageBox::warning(this, "警告", "发送间隔必须大于 0！");
//     return;
// }
// // 设置剩余发送间隔
// faCount = count;
// // // 设置定时器的时间间隔（单位：毫秒），这里设置为 1000 毫秒即 1 秒
// int interval = ui->lineEdit_5->text().toInt();
// timer1->start(interval);
void MainWindow::on_sendfaBt_clicked()
{

    bool ok;
    if(ui->checkBox->isChecked()){
        startValue = ui->lineEdit_6->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "起始值必须是整数！");
            return;
        }

        // 获取结束值
        endValue = ui->lineEdit_19->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "结束值必须是整数！");
            return;
        }
    }else if(ui->checkBox_2->isChecked()){
        startValue = ui->lineEdit_7->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "起始值必须是整数！");
            return;
        }

        // 获取结束值
        endValue = ui->lineEdit_20->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "结束值必须是整数！");
            return;
        }
    }else if(ui->checkBox_3->isChecked()){
        startValue = ui->lineEdit_8->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "起始值必须是整数！");
            return;
        }

        // 获取结束值
        endValue = ui->lineEdit_21->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "结束值必须是整数！");
            return;
        }
    }
    // 检查起始值是否小于结束值
    increasing = (startValue <= endValue);
    qDebug()<<increasing;
    if (!increasing && valueStep > 0) {
        valueStep = -valueStep;  // 如果是递减，步长应为负数
    }

    // 获取发送间隔（毫秒）
    sendInterval = ui->lineEdit_5->text().toInt(&ok);
    if (!ok || sendInterval <= 0) {
        QMessageBox::warning(this, "警告", "发送间隔必须是大于0的整数！");
        return;
    }

    totalStepCycles=sendInterval/200;

    // 获取步长
    int step = ui->lineEdit_4->text().toInt(&ok);
    if (!ok || step == 0) {
        QMessageBox::warning(this, "警告", "步长必须是非零整数！");
        return;
    }

    // 设置步长，确保方向正确
    if ((increasing && step < 0) || (!increasing && step > 0)) {
        valueStep = -step;
    } else {
        valueStep = step;
    }

    // 重置当前值
    // currentValue = startValue;

    currentValue = startValue;
    stepCycleCount = 0;
    isStepChanging = true;

    ui->sendfaBt->setStyleSheet(
            "QPushButton {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #1cbf5e, stop:0.5 #0caa49, stop:1 #089c40);"
            "   color: white;"
            "   border: 1px solid #066f2d;"
            "   border-radius: 5px;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #1fd36a, stop:0.5 #0fc252, stop:1 #0ab144);"
            "}"
            "QPushButton:pressed {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #0a8a3a, stop:0.5 #097d33, stop:1 #066f2d);"
            "   padding-top: 11px;"
            "   padding-bottom: 9px;"
            "}"
        );


    // 启动定时器
    timer1->start(200);
    ui->plainTextEdit->appendPlainText(
        QString("开始发送：从%1到%2，初始步长%3，每200ms发送，6秒后切换步长")
            .arg(startValue).arg(endValue).arg(valueStep));


}

QString arrayToHexString(const unsigned char* data,int size) {
    QString dataString;
    for (int i = 0; i < size; i++) {
        dataString += QString("%1 ").arg(static_cast<int>(data[i]), 2, 16, QChar('0'));
    }
    return dataString;
}

bool validateLineEditInput1(QLineEdit *lineEdit, int minValue, int maxValue, const QString &errorTitle = "输入错误") {
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

    if (value < minValue || value > maxValue) {
        QMessageBox::warning(lineEdit->parentWidget(), errorTitle, QString("输入的整数必须在 %1 - %2 范围内，请重新输入。").arg(minValue).arg(maxValue));
        return false;
    }

    return true;
}


void MainWindow::sendCurrentValue()
{
    quint16 flow = static_cast<quint16>(currentValue);
    unsigned char highByte = (flow >> 8) & 0xFF;
    unsigned char lowByte = flow & 0xFF;
    unsigned short NID = ui->comboBox_12->currentData().toInt() + 0x100;
    unsigned char data[8];

    // 根据选中的CheckBox设置数据（保持原有逻辑）
    if (ui->checkBox->isChecked()) {
        data[5] = 0x0;
    } else if (ui->checkBox_2->isChecked()) {
        data[5] = 0x1;
    } else if (ui->checkBox_3->isChecked()) {
        data[5] = 0x2;
    } else {
        return;
    }

    // 填充数据
    data[0] = lowByte;
    data[1] = highByte;
    data[2] = 0x0;
    data[3] = 0x0;
    data[4] = 0x0;
    data[6] = 0x58;
    data[7] = 0x52;

    // 发送数据
    if (canthread->sendData(ui->comboBox_4->currentIndex(), NID, 0, 0, data, 8)) {
        ui->plainTextEdit->appendPlainText(
            QString("发送值：%1 数据：%2")
                .arg(currentValue).arg(arrayToHexString(data, 8)));

        if (ui->checkBox_4->checkState())
            AddDataToList(buildMessageList(ui->comboBox_4, NID, ui->comboBox_5, data, 8));
    }

    // 更新当前值（仅在非切换阶段更新，避免重复计算）
    if (!isStepChanging) {
        currentValue += valueStep;
        isStepChanging=true;
    }
}




void MainWindow::onTimerTimeout1()
{

    // if (isStepChanging) return;  // 防止切换时重复处理

    // 发送当前值
    sendCurrentValue();
    stepCycleCount++;  // 记录已发送的200ms周期数

    // 检查是否达到6秒（30个周期），切换步长
    if (stepCycleCount >= totalStepCycles) {
        // isStepChanging = true;  // 锁定切换过程

        // 示例：步长值翻倍（可自定义为固定列表或其他逻辑）
        // valueStep *= 2;
        stepCycleCount = 0;  // 重置周期计数器
        // ui->plainTextEdit->appendPlainText(
        //     QString("步长切换：新步长%1，继续发送")
        //         .arg(valueStep));

        isStepChanging = false;  // 解锁
    }

    // 边界检查：到达结束值时停止
    if ((increasing && currentValue > endValue) ||
        (!increasing && currentValue < endValue)) {
        timer1->stop();
        ui->sendfaBt->setStyleSheet("QPushButton { font-size: 24px; }");
        ui->plainTextEdit->appendPlainText("发送完成：已达到目标范围");
    }














    // if ((increasing && currentValue > endValue) ||
    //     (!increasing && currentValue < endValue)) {
    //     // 已达到结束值，停止发送
    //     timer1->stop();
    //     ui->plainTextEdit->appendPlainText("发送完成：已达到结束值");
    //     currentValue = startValue;  // 重置为起始值
    //     return;
    // }

    // quint16 flow = static_cast<quint16>(currentValue);
    // unsigned char highByte = static_cast<unsigned char>((flow >> 8) & 0xFF);
    // unsigned char lowByte = static_cast<unsigned char>(flow & 0xFF);

    // unsigned short NID = ui->comboBox_12->currentData().toInt() + 0x100;

    // if (ui->checkBox->isChecked()) {
    //     unsigned char data[] = {lowByte, highByte, 0x0, 0x0, 0x0, 0x0, 0x58, 0x52};

    //     if (canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
    //                             NID,
    //                             0,
    //                             0,
    //                             data, 8)) {
    //         ui->plainTextEdit->appendPlainText(
    //             QString("发送值：%1 数据：%2").arg(currentValue).arg(arrayToHexString(data, 8)));

    //         if (ui->checkBox_4->checkState())
    //             AddDataToList(buildMessageList(ui->comboBox_4, NID, ui->comboBox_5, data, 8));
    //     }
    // }else  if (ui->checkBox_2->isChecked()) {
    //     unsigned char data[] = {lowByte, highByte, 0x0, 0x0, 0x0, 0x1, 0x58, 0x52};

    //     if (canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
    //                             NID,
    //                             0,
    //                             0,
    //                             data, 8)) {
    //         ui->plainTextEdit->appendPlainText(
    //             QString("发送值：%1 数据：%2").arg(currentValue).arg(arrayToHexString(data, 8)));

    //         if (ui->checkBox_4->checkState())
    //             AddDataToList(buildMessageList(ui->comboBox_4, NID, ui->comboBox_5, data, 8));
    //     }
    // }else  if (ui->checkBox_3->isChecked()) {
    //     unsigned char data[] = {lowByte, highByte, 0x0, 0x0, 0x0, 0x2, 0x58, 0x52};

    //     if (canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
    //                             NID,
    //                             0,
    //                             0,
    //                             data, 8)) {
    //         ui->plainTextEdit->appendPlainText(
    //             QString("发送值：%1 数据：%2").arg(currentValue).arg(arrayToHexString(data, 8)));

    //         if (ui->checkBox_4->checkState())
    //             AddDataToList(buildMessageList(ui->comboBox_4, NID, ui->comboBox_5, data, 8));
    //     }
    // }

    // // 更新当前值
    // currentValue += (increasing ? valueStep : -valueStep);






    // if (faCount <= 0) {
    //     // 发送次数已用完，停止定时器
    //     timer1->stop();
    //     return;
    // }
    // quint16  flow;
    // unsigned char highByte;
    // unsigned char lowByte;
    // unsigned short NID =ui->comboBox_12->currentData().toInt()+0x100;
    // if(ui->checkBox->isChecked()&&validateLineEditInput1(ui->lineEdit_6,-1000,1000)){

    //     flow=static_cast<quint16>(ui->lineEdit_6->text().toInt());
    //     highByte = static_cast<unsigned char>((flow >> 8) & 0xFF);
    //     // 提取低 2 位（即低字节）
    //     lowByte = static_cast<unsigned char>(flow & 0xFF);
    //     unsigned char data[]={lowByte,highByte,0x0,0x0,0x0,0x0,0x58,0x52};
    //     if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
    //                             NID,
    //                             0,
    //                             0,
    //                             data,8)){
    //         ui->plainTextEdit->appendPlainText(QString("流量配置成功 数据：%1").arg(arrayToHexString(data,8)));
    //         if(ui->checkBox_4->checkState())
    //         AddDataToList(buildMessageList(ui->comboBox_4, NID, ui->comboBox_5,  data, 8));
    //     }
    // }

    // if(ui->checkBox_2->isChecked()&&validateLineEditInput1(ui->lineEdit_7,-1000,1000)){

    //     flow=static_cast<quint16>(ui->lineEdit_7->text().toInt());
    //     highByte = static_cast<unsigned char>((flow >> 8) & 0xFF);
    //     // 提取低 2 位（即低字节）
    //     lowByte = static_cast<unsigned char>(flow & 0xFF);
    //     unsigned char data[]={lowByte,highByte,0x0,0x0,0x0,0x1,0x58,0x52};
    //     if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
    //                             NID,
    //                             0,
    //                             0,
    //                             data,8)){
    //         ui->plainTextEdit->appendPlainText(QString("位移配置成功 数据：%1").arg(arrayToHexString(data,8)));
    //         if(ui->checkBox_4->checkState())
    //         AddDataToList(buildMessageList(ui->comboBox_4, NID, ui->comboBox_5,  data, 8));
    //     }
    // }

    // if(ui->checkBox_3->isChecked()&&validateLineEditInput1(ui->lineEdit_8,-2000,2000)){

    //     flow=static_cast<quint16>(ui->lineEdit_8->text().toInt());
    //     highByte = static_cast<unsigned char>((flow >> 8) & 0xFF);
    //     // 提取低 2 位（即低字节）
    //     lowByte = static_cast<unsigned char>(flow & 0xFF);
    //     unsigned char data[]={lowByte,highByte,0x0,0x0,0x0,0x2,0x58,0x52};
    //     if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
    //                             NID,
    //                             0,
    //                             0,
    //                             data,8)){
    //         ui->plainTextEdit->appendPlainText(QString("电流配置成功 数据：%1").arg(arrayToHexString(data,8)));
    //         if(ui->checkBox_4->checkState())
    //         AddDataToList(buildMessageList(ui->comboBox_4, NID, ui->comboBox_5,  data, 8));
    //     }
    // }

    // faCount--;

}




void MainWindow::on_pushButton_13_clicked()
{
    timer1->stop();
    // faCount=0;
}







void MainWindow::on_pushButton_8_clicked()  //阀节点配置
{
    unsigned char NID=ui->comboBox_10->currentData().toInt();
    unsigned char newNID=ui->comboBox_11->currentData().toInt();
    unsigned char data[]={0x11,NID,newNID,0x0,0x0,0x0,0x00,0x00};
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                        0x7e5,
                        0,
                        0,
                        data,8))
    {
        ui->plainTextEdit->appendPlainText("正在配置节点号！");
        AddDataToList(buildMessageList(ui->comboBox_4, 0x7e5, ui->comboBox_5,  data, 8));
        nodeReceived=1;
    }
}


void MainWindow::on_cycleBt_clicked()  // 周期节点配置
{
    unsigned char NID=ui->comboBox_10->currentData().toInt();
    unsigned char cycle=ui->comboBox_13->currentIndex()+1;    //是否需要转16进制
    unsigned char data[]={0x12,NID,cycle,0x0,0x0,0x0,0x00,0x00};
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                            0x7e5,
                            0,
                            0,
                            data,8))
    {
        ui->plainTextEdit->appendPlainText("正在配置周期！");
        AddDataToList(buildMessageList(ui->comboBox_4, 0x7e5, ui->comboBox_5,  data, 8));
        cycleReceived=1;
    }
}




void MainWindow::on_bautBt_clicked()   //波特率配置
{
    unsigned char NID=ui->comboBox_10->currentData().toInt();
    unsigned char baut=ui->comboBox_7->currentIndex();
    unsigned char data[]={0x13,NID,baut,0x0,0x0,0x0,0x00,0x00};
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                            0x7e5,
                            0,
                            0,
                            data,8))
    {
        ui->plainTextEdit->appendPlainText(QString("正在配置波特率为%1k！").arg(ui->comboBox_7->currentText()));
        AddDataToList(buildMessageList(ui->comboBox_4, 0x7e5, ui->comboBox_5,  data, 8));
        baudReceived=1;
    }
}


void MainWindow::on_LVDTBt_clicked()  //LVDT配置
{
    unsigned char NID=ui->comboBox_10->currentData().toInt();
    unsigned char lvdt=ui->comboBox_8->currentIndex();
    unsigned char lvdt1;
    switch (lvdt) {
    case 0:
        lvdt1=0x00;
        ui->plainTextEdit->appendPlainText("阀芯位移配置发送成功");
        break;
    case 1:
        lvdt1=0x10;
        ui->plainTextEdit->appendPlainText("PWMA流量起点配置发送成功");
        break;
    case 2:
        lvdt1=0x11;
        ui->plainTextEdit->appendPlainText("PWMA流量终点配置发送成功");
        break;
    case 3:
        lvdt1=0x20;
        ui->plainTextEdit->appendPlainText("PWMB流量起点配置发送成功");
        break;
    case 4:
        lvdt1=0x21;
        ui->plainTextEdit->appendPlainText("PWMB流量终点配置发送成功");
        break;
    default:
        return;
        break;
    }
    unsigned char data[]={0x16,NID,lvdt1,0x0,0x0,0x0,0x00,0x00};
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                            0x7e5,
                            0,
                            0,
                            data,8))
    {
        LVDTReceived=1;
        AddDataToList(buildMessageList(ui->comboBox_4, 0x7e5, ui->comboBox_5,  data, 8));
    }
}


void MainWindow::on_recovBt_clicked()
{
    QMessageBox msgBox;
        msgBox.setWindowTitle("确认恢复出厂设置");
        msgBox.setText("是否确认执行恢复出厂设置？此操作不可撤销！");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setIcon(QMessageBox::Warning); // 设置警告图标

        // 显示弹窗并获取用户选择
        int ret = msgBox.exec();
        if (ret != QMessageBox::Yes) { // 用户点击取消
            return; // 直接退出，不执行后续操作
        }
    ui->plainTextEdit->appendPlainText("正在恢复出厂设置中");
    unsigned char NID=ui->comboBox_10->currentData().toInt();
    unsigned char data[]={0xAA,NID,0x0,0x0,0x0,0x0,0x00,0x00};
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                            0x7e5,
                            0,
                            0,
                            data,8))
    {
        recovReceived=1;
        AddDataToList(buildMessageList(ui->comboBox_4, 0x7e5, ui->comboBox_5,  data, 8));
    }
}


void MainWindow::on_saveBt_clicked()
{
    ui->plainTextEdit->appendPlainText("正在保存设置中");
    unsigned char NID=ui->comboBox_10->currentData().toInt();
    unsigned char data[]={0x17,NID,0x0,0x0,0x0,0x0,0x00,0x00};
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                            0x7e5,
                            0,
                            0,
                            data,8))
    {
        saveReceived=1;
        AddDataToList(buildMessageList(ui->comboBox_4, 0x7e5, ui->comboBox_5,  data, 8));
    }
}




void MainWindow::on_savetxtBt_clicked()
{
    if (isSaving) return;

    isSaving = true;
    startSaveRow = ui->tableWidget->rowCount();

    // 动态生成文件名

    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    QDateTime currentDateTime1 = QDateTime::currentDateTime();

    // 获取当前程序运行的目录
    QDir currentDir(QCoreApplication::applicationDirPath());

    // 获取上一级目录
    QString parentFolder = currentDir.path();
    qDebug()<<parentFolder;
    // currentDir.cdUp();
    // if (currentDir.exists()) {
    //     parentFolder = currentDir.path();
    // }

    // 假设在上级目录下创建一个名为 "cantex" 的子文件夹用于保存文件
    QString subFolderName = "cantex";
    QString saveFolder = parentFolder + "/" + subFolderName+"/can原始数据";

    // 构建完整的文件名
    savePath = saveFolder + "/" + timestamp + ".txt";




    // 检查保存文件夹是否存在，若不存在则创建
    QDir dir(saveFolder);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            QMessageBox::critical(this, "错误", "无法创建保存文件夹！");
            isSaving = false;
            return;
        }
    }

    qDebug()<<savePath;
    QFile file(savePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        // 写入分隔线
        out << "[" << currentDateTime1.toString("yyyy-MM-dd hh:mm:ss.zzz") << "]" << " ----------------------------------------------------------" << "\n";
        // 写入系统启动信息
        out << "[" << currentDateTime1.toString("yyyy-MM-dd hh:mm:ss.zzz") << "]" << " > System start!" << "\n";
        // 写入分隔线
        out << "[" << currentDateTime1.toString("yyyy-MM-dd hh:mm:ss.zzz") << "]" << " ---------------------------------------------------------" << "\n";
        file.close();
    }

    dataSaver->setSavePath(savePath);
    saveTimer->start();
}

void MainWindow::on_savetxtBt_2_clicked()
{
    if (!isSaving) return;

    isSaving = false;
    saveTimer->stop();
}

void MainWindow::saveNewData()
{
    if (!isSaving) return;

    int currentRow = ui->tableWidget->rowCount();
    if (currentRow > startSaveRow) {
        QList<QStringList> dataToSave;
        for (int row = startSaveRow; row < currentRow; ++row) {
            QStringList rowData;
            for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                QTableWidgetItem *item = ui->tableWidget->item(row, col);
                if (item) {
                    rowData << item->text();
                }
            }
            dataToSave << rowData;
        }
        QMetaObject::invokeMethod(dataSaver, [this, dataToSave]() {
            dataSaver->saveData(dataToSave);
        }, Qt::QueuedConnection);
        startSaveRow = currentRow;
    }
}

void MainWindow::onSaveFinished()
{
    // 保存完成后的处理，可根据需要添加代码
}

void MainWindow::onErrorOccurred(const QString &errorMessage)
{
    QMessageBox::critical(this, "错误", errorMessage);
}








// void MainWindow::on_savetxtBt_3_clicked()
// {
//     // if (!v) {
//     //     v = new valve(this, canthread);
//     // }
//     v->show();
// }


// void MainWindow::on_savetxtBt_3_clicked()
// {
//         if (!valveWindow) {
//             valveWindow = new valve();//, canthread
//         }
//         valveWindow->show();
// }


void MainWindow::on_pushButton_16_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_tranBt_clicked()
{
    int fromBase = 2;
    QString result1,result2,result3,result4;
    QString input = ui->lineEdit->text();
    int fromBaseIndex = ui->comboBox_9->currentIndex();
    switch (fromBaseIndex) {
    case 0: fromBase = 2; break;
    case 1: fromBase = 8; break;
    case 2: fromBase = 10; break;
    case 3: fromBase = 16; break;
    }
    bool ok;
    int decimal = input.toInt(&ok, fromBase);
    if (!ok) {
        QMessageBox::warning(this, "错误", "输入无效");
        return;
    }


    result1 = QString::number(decimal, 2);
    result2 = QString::number(decimal, 8);
    result3 = QString::number(decimal, 10);
    result4 = QString::number(decimal, 16).toUpper();

    ui->lineEdit_2->setText(result1);
    ui->lineEdit_3->setText(result2);
    ui->lineEdit_9->setText(result3);
    ui->lineEdit_10->setText(result4);


}










void MainWindow::on_pushButton_6_clicked()
{
     filePath = QFileDialog::getOpenFileName(
        this,
        "选择数据文件",
        "./cantex/can解析数据",
        "文本文件 (*.txt);;所有文件 (*)"
        );

    if (filePath.isEmpty()) {
        return;
    }

    // 在lineEdit中显示文件路径
    ui->lineEdit_11->setText(filePath);
}


void MainWindow::on_pushButton_7_clicked()
{
    if (!filePath.isEmpty()) {
        parseTxtData(filePath);
        drawChart();
    }
}


// bool MainWindow::eventFilter(QObject *watched, QEvent *event)
// {
//     // 检查是否是支持的图表视口且事件为滚轮事件
//     QChartView* targetView = nullptr;
//     for (QChartView* view : zoomableChartViews) {
//         if (watched == view->viewport()) {
//             targetView = view;
//             break;
//         }
//     }

//     if (!targetView)
//         return QMainWindow::eventFilter(watched, event);

//     if (event->type() == QEvent::Wheel)
//     {
//         QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
//         if (wheelEvent->modifiers() & Qt::ControlModifier)
//         {
//             QChart *chart = targetView->chart();
//             QPointF mousePos = wheelEvent->position();
//             QPointF scenePos = targetView->mapToScene(mousePos.toPoint());
//             QPointF chartValue = chart->mapToValue(scenePos);

//             // 动态获取坐标轴类型（支持多种轴类型）
//             QAbstractAxis* axisX = chart->axisX();
//             QAbstractAxis* axisY = chart->axisY();

//             // 获取当前范围（支持QDateTimeAxis和QValueAxis）
//             double xMin = 0, xMax = 0, yMin = 0, yMax = 0;
//             QDateTime xDateTimeMin, xDateTimeMax;

//             if (auto dateAxis = qobject_cast<QDateTimeAxis*>(axisX)) {
//                 xDateTimeMin = dateAxis->min();
//                 xDateTimeMax = dateAxis->max();
//                 xMin = xDateTimeMin.toMSecsSinceEpoch();
//                 xMax = xDateTimeMax.toMSecsSinceEpoch();
//             }
//             else if (auto valueAxis = qobject_cast<QValueAxis*>(axisX)) {
//                 xMin = valueAxis->min();
//                 xMax = valueAxis->max();
//             }

//             if (auto valueAxis = qobject_cast<QValueAxis*>(axisY)) {
//                 yMin = valueAxis->min();
//                 yMax = valueAxis->max();
//             }

//             // 计算缩放因子
//             qreal scaleFactor = (wheelEvent->angleDelta().y() > 0) ? 0.9 : 1.1;

//             // 计算范围
//             qreal xRange = xMax - xMin;
//             qreal yRange = yMax - yMin;

//             qreal newXRange = xRange * scaleFactor;
//             qreal newYRange = yRange * scaleFactor;

//             // 计算鼠标位置在坐标轴上的相对位置
//             qreal xFraction = (chartValue.x() - xMin) / xRange;
//             qreal yFraction = (chartValue.y() - yMin) / yRange;

//             // 计算新范围
//             qreal newXMin = chartValue.x() - xFraction * newXRange;
//             qreal newXMax = newXMin + newXRange;
//             qreal newYMin = chartValue.y() - yFraction * newYRange;
//             qreal newYMax = newYMin + newYRange;

//             // 设置新范围（根据轴类型）
//             if (auto dateAxis = qobject_cast<QDateTimeAxis*>(axisX)) {
//                 dateAxis->setRange(
//                     QDateTime::fromMSecsSinceEpoch(newXMin),
//                     QDateTime::fromMSecsSinceEpoch(newXMax)
//                 );
//             }
//             else if (auto valueAxis = qobject_cast<QValueAxis*>(axisX)) {
//                 valueAxis->setRange(newXMin, newXMax);
//             }

//             if (auto valueAxis = qobject_cast<QValueAxis*>(axisY)) {
//                 valueAxis->setRange(newYMin, newYMax);
//             }

//             return true;
//         }
//     }

//     return QMainWindow::eventFilter(watched, event);
// }




bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    // 查找目标图表视图
    QChartView* targetView = nullptr;
    for (QChartView* view : zoomableChartViews) {
        if (watched == view->viewport()) {
            targetView = view;
            break;
        }
    }

    if (!targetView)
        return QMainWindow::eventFilter(watched, event);

    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        if (wheelEvent->modifiers() & Qt::ControlModifier)
        {
            QChart *chart = targetView->chart();
            QPointF mousePos = wheelEvent->position();
            QPointF scenePos = targetView->mapToScene(mousePos.toPoint());
            QPointF chartValue = chart->mapToValue(scenePos);

            // 获取所有坐标轴
            QList<QAbstractAxis*> allXAxes = chart->axes(Qt::Horizontal);
            QList<QAbstractAxis*> allYAxes = chart->axes(Qt::Vertical);

            // 如果没有坐标轴，直接返回
            if (allXAxes.isEmpty() || allYAxes.isEmpty())
                return false;

            // 计算缩放因子
            qreal scaleFactor = (wheelEvent->angleDelta().y() > 0) ? 0.9 : 1.1;

            // 存储所有Y轴的原始范围
            QVector<QPair<double, double>> yRanges;
            for (QAbstractAxis* axis : allYAxes) {
                double min = 0, max = 0;
                if (auto dateAxis = qobject_cast<QDateTimeAxis*>(axis)) {
                    min = dateAxis->min().toMSecsSinceEpoch();
                    max = dateAxis->max().toMSecsSinceEpoch();
                }
                else if (auto valueAxis = qobject_cast<QValueAxis*>(axis)) {
                    min = valueAxis->min();
                    max = valueAxis->max();
                }
                // 移除了QLogValueAxis支持
                yRanges.append(qMakePair(min, max));
            }

            // 处理所有X轴（通常只有一个）
            for (QAbstractAxis* axisX : allXAxes) {
                double xMin = 0, xMax = 0;

                if (auto dateAxis = qobject_cast<QDateTimeAxis*>(axisX)) {
                    xMin = dateAxis->min().toMSecsSinceEpoch();
                    xMax = dateAxis->max().toMSecsSinceEpoch();
                }
                else if (auto valueAxis = qobject_cast<QValueAxis*>(axisX)) {
                    xMin = valueAxis->min();
                    xMax = valueAxis->max();
                }

                // 计算X轴新范围
                double xRange = xMax - xMin;
                double newXRange = xRange * scaleFactor;
                double xFraction = (chartValue.x() - xMin) / xRange;
                double newXMin = chartValue.x() - xFraction * newXRange;
                double newXMax = newXMin + newXRange;

                // 设置X轴新范围
                if (auto dateAxis = qobject_cast<QDateTimeAxis*>(axisX)) {
                    dateAxis->setRange(
                        QDateTime::fromMSecsSinceEpoch(newXMin),
                        QDateTime::fromMSecsSinceEpoch(newXMax)
                    );
                }
                else if (auto valueAxis = qobject_cast<QValueAxis*>(axisX)) {
                    valueAxis->setRange(newXMin, newXMax);
                }
            }

            // 处理所有Y轴（同步缩放）
            for (int i = 0; i < allYAxes.size(); i++) {
                QAbstractAxis* axisY = allYAxes[i];
                double yMin = yRanges[i].first;
                double yMax = yRanges[i].second;

                // 计算Y轴新范围
                double yRange = yMax - yMin;
                double newYRange = yRange * scaleFactor;
                double yFraction = (chartValue.y() - yMin) / yRange;
                double newYMin = chartValue.y() - yFraction * newYRange;
                double newYMax = newYMin + newYRange;

                // 设置Y轴新范围
                if (auto dateAxis = qobject_cast<QDateTimeAxis*>(axisY)) {
                    dateAxis->setRange(
                        QDateTime::fromMSecsSinceEpoch(newYMin),
                        QDateTime::fromMSecsSinceEpoch(newYMax)
                    );
                }
                else if (auto valueAxis = qobject_cast<QValueAxis*>(axisY)) {
                    valueAxis->setRange(newYMin, newYMax);
                }
                // 移除了QLogValueAxis支持
            }

            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}




void MainWindow::setupChart()
{
    chart = new QChart();
    chart->setTitle("数据图表");
    chart->setAnimationOptions(QChart::AllAnimations);

    // 创建数据系列
    QStringList fields = {"阀芯位移值", "PWMA", "PWMB",  "外部模拟量", "LVDT反馈电压"};
    for (const QString& field : fields) {
        QLineSeries* series0 = new QLineSeries();
        series0->setName(field);
        seriesList.append(series0);
        chart->addSeries(series0);
        fieldIndexes[field] = seriesList.size() - 1;

        connect(series0, &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
            if (state) {
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
                        break; // 精确匹配
                    }
                }

                // 检查左右邻居点
                if (closestIndex > 0) {
                    QPointF leftPoint = series0->at(closestIndex - 1);
                    qreal leftDistance = qAbs(leftPoint.x() - targetX);
                    if (leftDistance < minDistance) {
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

                QString tooltip = QString("%1\n时间: %2\n值: %3")
                                      .arg(field)
                                      .arg(dateTime.toString("HH:mm:ss"))
                                      .arg(closestPoint.y());

                QToolTip::showText(QCursor::pos(), tooltip,ui->graphicsView );//chartView
            } else {
                QToolTip::hideText();
            }
        });
    }


    // 设置坐标轴
    axisX = new QDateTimeAxis();
    axisX->setTitleText("时间");
    axisX->setFormat("HH:mm:ss");
    chart->addAxis(axisX, Qt::AlignBottom);

    axisY = new QValueAxis();
    axisY->setTitleText("数值");
    chart->addAxis(axisY, Qt::AlignLeft);

    // 将所有系列附加到坐标轴
    for (QLineSeries* series : seriesList) {
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

ui->graphicsView->setRubberBand(QChartView::RectangleRubberBand);
// ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setChart(chart);







    // chartView = new QChartView(chart);
    // chartView->setRenderHint(QPainter::Antialiasing);

    // ui->graphicsView->setChart(chart);

}

void MainWindow::parseTxtData(const QString &filePath)
{
    // 从UI获取百分比值并验证
    bool startOk, endOk;
    double startPercent = ui->lineEdit_15->text().trimmed().toDouble(&startOk);
    double endPercent = ui->lineEdit_16->text().trimmed().toDouble(&endOk);

    if (!startOk || !endOk ||
        startPercent < 0 || startPercent > 100 ||
        endPercent < 0 || endPercent > 100 ||
        startPercent >= endPercent) {

        QMessageBox::critical(this, "输入错误",
                              "请输入有效的百分比范围 (0-100)，且起始百分比必须小于结束百分比");
        return;
    }

    // 清空现有数据
    for (QLineSeries* series : seriesList) {
        series->clear();
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "警告", "无法打开文件");
        return;
    }

    QTextStream in(&file);

    // 计算总行数
    int totalLines = 0;
    while (!in.atEnd()) {
        in.readLine();
        totalLines++;
    }

    // 重置文件指针
    file.reset();
    in.reset();

    // 计算起始行和结束行
    int startLine = qRound(totalLines * startPercent / 100.0);
    int endLine = qRound(totalLines * endPercent / 100.0);

    // 确保计算的行数在有效范围内
    startLine = qMax(1, startLine);
    endLine = qMin(totalLines, endLine);

    qDebug() << "总行数:" << totalLines << " 起始行:" << startLine << " 结束行:" << endLine;

    // 处理指定范围的行
    int currentLine = 0;
    int validDataCount = 0;

    // 添加变量保存第一个isLVDT值
    bool firstIsLVDTFound = false;
    double firstIsLVDTValue = 0.0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        currentLine++;

        // 跳过范围外的行
        if (currentLine < startLine) continue;
        if (currentLine > endLine) break;

        if (line.contains("阀设备：")) {
            // 提取阀设备信息
            int pos = line.indexOf("阀设备：") + 4;
            QString valveDevice = line.mid(pos).trimmed();
            ui->label_10->setText("阀设备："+valveDevice);
            continue; // 处理完阀设备行后跳过后续处理
        }

        // 提取时间戳
        int dataStartPos = line.indexOf("  "); // 查找两个空格的位置
        if (dataStartPos == -1 || dataStartPos < 23) {
            qDebug() << "无效行格式:" << line;
            continue;
        }

        QString timestampStr = line.left(dataStartPos);
        QDateTime timestamp = QDateTime::fromString(timestampStr, "yyyy-MM-dd hh:mm:ss.zzz");

        if (!timestamp.isValid()) {
            qDebug() << "无效时间戳:" << timestampStr;
            continue;
        }

        // 提取数据部分
        QString dataStr = line.mid(dataStartPos + 2).trimmed(); // +2 跳过两个空格
        QStringList pairs = dataStr.split(", ");

        bool lineHasValidData = false;

        for (const QString& pair : pairs) {
            QStringList keyValue = pair.split(": ");
            if (keyValue.size() == 2) {
                QString key = keyValue[0].trimmed();
                bool ok;
                double value = keyValue[1].toDouble(&ok);
                if (key == "isLVDT" && !firstIsLVDTFound) {
                    firstIsLVDTValue = value;
                    firstIsLVDTFound = true;
                }
                if (ok && fieldIndexes.contains(key)) {
                    seriesList[fieldIndexes[key]]->append(timestamp.toMSecsSinceEpoch(), value);
                    lineHasValidData = true;

                    // 保存第一个isLVDT值

                }
            }
        }

        if (lineHasValidData)
            validDataCount++;
    }

    file.close();

    ui->label_9->setText(firstIsLVDTValue == 0? "LVDT:有" : "LVDT:无");

    // 调试输出各系列的数据点数量
    qDebug() << "数据解析完成，有效数据行数:" << validDataCount;
    for (const QString& field : fieldIndexes.keys()) {
        qDebug() << field << "点数:" << seriesList[fieldIndexes[field]]->count();
    }

    // 输出第一个isLVDT值
    if (firstIsLVDTFound) {
        qDebug() << "第一个isLVDT值:" << firstIsLVDTValue;
        // 可以在这里使用firstIsLVDTValue，例如更新UI

    } else {
        qDebug() << "未找到isLVDT值";
    }

    // 通知数据已更新

}











void MainWindow::drawChart()
{
    // 调整坐标轴范围以适应数据
    QDateTime minTime = QDateTime::currentDateTime();
    QDateTime maxTime = QDateTime::fromMSecsSinceEpoch(0);
    double minValue = DBL_MAX;
    double maxValue = -DBL_MAX;

    for (QLineSeries* series : seriesList) {
        if (series->count() > 0) {
            for (int i = 0; i < series->count(); ++i) {
                QPointF point = series->at(i);
                QDateTime time = QDateTime::fromMSecsSinceEpoch(point.x());

                if (time < minTime) minTime = time;
                if (time > maxTime) maxTime = time;
                if (point.y() < minValue) minValue = point.y();
                if (point.y() > maxValue) maxValue = point.y();
            }
        }
    }

    // 设置坐标轴范围
    axisX->setRange(minTime, maxTime);
    axisY->setRange(minValue * 0.95, maxValue * 1.05);
}


void MainWindow::updateChartVisibility()
{

    seriesList[fieldIndexes["阀芯位移值"]]->setVisible(ui->checkBox_5->isChecked());
    seriesList[fieldIndexes["PWMA"]]->setVisible(ui->checkBox_6->isChecked());
    seriesList[fieldIndexes["PWMB"]]->setVisible(ui->checkBox_7->isChecked());
    seriesList[fieldIndexes["外部模拟量"]]->setVisible(ui->checkBox_8->isChecked());
    seriesList[fieldIndexes["LVDT反馈电压"]]->setVisible(ui->checkBox_9->isChecked());
}


void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    updateChartVisibility();
}


void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    updateChartVisibility();
}


void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
    updateChartVisibility();
}


void MainWindow::on_checkBox_8_stateChanged(int arg1)
{
    updateChartVisibility();
}


void MainWindow::on_checkBox_9_stateChanged(int arg1)
{
    updateChartVisibility();
}


void MainWindow::on_pushButton_10_clicked()
{
    QString yMinText = ui->lineEdit_17->text().trimmed();
    QString yMaxText = ui->lineEdit_18->text().trimmed();

    bool yMinOk, yMaxOk;
    double userMinValue = yMinText.toDouble(&yMinOk);
    double userMaxValue = yMaxText.toDouble(&yMaxOk);

    // 检查用户输入的有效性
    if (yMinOk && yMaxOk && userMinValue < userMaxValue) {
        // 如果用户输入有效，使用用户输入的范围
        axisY->setRange(userMinValue, userMaxValue);
        return;
    }

    // 调整坐标轴范围以适应数据（如果用户输入无效）
    QDateTime minTime = QDateTime::currentDateTime();
    QDateTime maxTime = QDateTime::fromMSecsSinceEpoch(0);
    double minValue = DBL_MAX;
    double maxValue = -DBL_MAX;

    for (QLineSeries* series : seriesList1) {
        if (series->count() > 0) {
            for (int i = 0; i < series->count(); ++i) {
                QPointF point = series->at(i);
                QDateTime time = QDateTime::fromMSecsSinceEpoch(point.x());

                if (time < minTime) minTime = time;
                if (time > maxTime) maxTime = time;
                if (point.y() < minValue) minValue = point.y();
                if (point.y() > maxValue) maxValue = point.y();
            }
        }
    }

    // 设置坐标轴范围
    axisX->setRange(minTime, maxTime);
    axisY->setRange(minValue * 0.95, maxValue * 1.05);
}






void MainWindow::setupChart1()
{
    qchart1 = new QChart();
    qchart1->setTitle("数据图表");
    qchart1->setAnimationOptions(QChart::AllAnimations);

    QValueAxis* axisX = new QValueAxis;
    axisX->setTitleText(QObject::tr("阀芯开度"));
    axisX->setRange(0, 1800);
    axisX->setLabelFormat("%.0f");
    axisX->setGridLineColor(Qt::lightGray);
    qchart1->addAxis(axisX, Qt::AlignBottom);

    QValueAxis* axisY = new QValueAxis;
    axisY->setTitleText(QObject::tr("位移"));
    axisY->setRange(0, 50);
    axisY->setLabelFormat("%.1f");
    axisY->setTitleBrush(QBrush(Qt::blue));
    // 设置 Y 轴轴线颜色
    axisY->setLinePen(QPen(Qt::blue));
    axisY->setGridLineColor(Qt::lightGray);
    qchart1->addAxis(axisY, Qt::AlignLeft);

    QValueAxis* axisY1 = new QValueAxis;
    axisY1->setTitleText(QObject::tr("流量"));
    axisY1->setRange(0, 50);
    axisY1->setLabelFormat("%.1f");
    axisY1->setTitleBrush(QBrush(Qt::red));
    // 设置 Y 轴轴线颜色
    axisY1->setLinePen(QPen(Qt::red));
    axisY1->setGridLineColor(Qt::lightGray);
    qchart1->addAxis(axisY1, Qt::AlignRight);

    QValueAxis* axisY2 = new QValueAxis;
    axisY2->setTitleText(QObject::tr("油温 (°C)"));
    axisY2->setRange(0, 80);
    axisY2->setLabelFormat("%.1f");

    axisY2->setGridLineVisible(false);
    qchart1->addAxis(axisY2, Qt::AlignRight);
    axisY2->setTitleBrush(QBrush(Qt::green));
    // 设置 Y 轴轴线颜色
    axisY2->setLinePen(QPen(Qt::green));
    yAxes = {axisY, axisY1, axisY2};

    // 创建数据系列
    QStringList fields = {"反馈位移 (mm)", "流量 (L/min)", "油温 (°C)"};
    seriesList1.clear();

    for (int i = 0; i < fields.size(); ++i) {
        QLineSeries* series0 = new QLineSeries();
        series0->setName(fields[i]);
        seriesList1.append(series0);

        // 将系列添加到图表
        qchart1->addSeries(series0);

        // 绑定X轴（所有系列共用）
        series0->attachAxis(axisX);

        // 绑定对应Y轴
        series0->attachAxis(yAxes[i]);

        // 设置不同颜色以便区分
        QPen pen = series0->pen();
        switch(i) {
        case 0: pen.setColor(Qt::blue); break;
        case 1: pen.setColor(Qt::red); break;
        case 2: pen.setColor(Qt::green); break;
        default: pen.setColor(Qt::black);
        }
        series0->setPen(pen);

        connect(series0, &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
            if (state) {
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
                        break; // 精确匹配
                    }
                }

                // 检查左右邻居点
                if (closestIndex > 0) {
                    QPointF leftPoint = series0->at(closestIndex - 1);
                    qreal leftDistance = qAbs(leftPoint.x() - targetX);
                    if (leftDistance < minDistance) {
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
                QString tooltip = QString("%1\n开度: %2\n值: %3")
                                      .arg(fields[i])
                                      .arg(closestPoint.x())
                                      .arg(closestPoint.y());

                QToolTip::showText(QCursor::pos(), tooltip, ui->graphicsView_2);
            } else {
                QToolTip::hideText();
            }
        });
    }

    // // 创建自定义图表视图
    // chartView1 = new QChartView(qchart1);
    // chartView1->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->setRubberBand(QChartView::RectangleRubberBand);

    ui->graphicsView_2->setChart(qchart1);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
}






void MainWindow::on_pushButton_11_clicked()
{
    filePath1 = QFileDialog::getOpenFileName(
        this,
        "选择数据文件",
        "./",
        "所有文件 (*.xlsx)"
        );

    if (filePath1.isEmpty()) {
        return;
    }

    // 在lineEdit中显示文件路径
    ui->lineEdit_12->setText(filePath1);
}


void MainWindow::on_pushButton_12_clicked()
{
    if (filePath1.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择数据文件！");
        return;
    }

    bool success = false;

    if (filePath1.endsWith(".xlsx", Qt::CaseInsensitive)) {
        success = loadDataFromExcel(filePath1,seriesList1);
    } else if (filePath1.endsWith(".txt", Qt::CaseInsensitive)) {
        // success = loadDataFromText(filePath1);
    } else {
        QMessageBox::warning(this, "警告", "不支持的文件类型！");
        return;
    }

    if (success) {
        adjustChartAxes();
        QMessageBox::information(this, "成功", "数据加载成功！");
    }
    connect(ui->pushButtonAdjust, &QPushButton::clicked, this, &MainWindow::onAdjustAxesClicked);
}




bool MainWindow::loadDataFromExcel(const QString &filePath,QList<QLineSeries *> &seriesListn)
{
    // 对于旧版QtXlsx，直接通过构造函数加载文件
    QXlsx::Document xlsx(filePath);

    // // 检查是否成功加载了文件
    // if (xlsx.dimension()) {
    //     QMessageBox::critical(this, "错误", "无法加载Excel文件！");
    //     return false;
    // }

    // 清空现有数据
    for (auto series : seriesListn) {
        series->clear();
    }

    // 获取当前工作表
    QXlsx::Worksheet *sheet = xlsx.currentWorksheet();
    if (!sheet) {
        QMessageBox::critical(this, "错误", "无法获取工作表！");
        return false;
    }

    // 获取数据范围
    QXlsx::CellRange range = sheet->dimension();
    if (range.rowCount() <= 1) {
        QMessageBox::information(this, "提示", "Excel文件中没有数据！");
        return true; // 没有数据但加载成功
    }

    // 读取数据（跳过标题行）
    for (int row = 2; row <= range.rowCount(); ++row) {
        // 获取X轴数据（第二列）
        QVariant xValue = sheet->read(row, 2);
        if (xValue.isNull()) continue;

        bool ok;
        qreal x = xValue.toDouble(&ok);
        if (!ok) continue;

        // 获取Y轴数据（3、4、5列）
        for (int col = 0; col < qMin(3, seriesListn.size()); ++col) {
            QVariant yValue = sheet->read(row, col + 3);
            if (!yValue.isNull()) {
                qreal y = yValue.toDouble(&ok);
                if (ok) {
                    seriesListn[col]->append(x, y);
                }
            }
        }
    }

    return true;
}




void MainWindow::adjustChartAxes()
{
    // 自动调整Y轴范围
    for (auto series : seriesList1) {
        QList<QPointF> points = series->points();
        if (points.isEmpty()) continue;

        qreal minY = points[0].y();
        qreal maxY = points[0].y();

        for (const auto& point : points) {
            minY = qMin(minY, point.y());
            maxY = qMax(maxY, point.y());
        }

        // 稍微扩展一下范围
        minY = qMax(0.0, minY * 0.9);
        maxY = maxY * 1.1;

        // 获取关联的Y轴
        QList<QAbstractAxis*> axes = series->attachedAxes();
        for (auto axis : axes) {
            if (axis->orientation() == Qt::Vertical) {
                QValueAxis* yAxis = qobject_cast<QValueAxis*>(axis);
                if (yAxis) {
                    yAxis->setRange(minY, maxY);
                }
            }
        }
    }
}







void MainWindow::onAdjustAxesClicked()
{
    // 获取用户选择的轴类型
    int axisType = ui->comboBoxAxisType->currentIndex();

    // 解析最小值和最大值
    bool minOk, maxOk;
    qreal minVal = ui->lineEditMin->text().toInt(&minOk);
    qreal maxVal = ui->lineEditMax->text().toInt(&maxOk);

    if (!minOk || !maxOk || minVal >= maxVal) {
        QMessageBox::warning(this, "警告", "范围值无效！请确保输入有效的数值且最小值小于最大值");
        return;
    }

     QValueAxis* xAxis = qobject_cast<QValueAxis*>(qchart1->axisX());

    // 根据选择的轴类型调整相应的坐标轴
     if (axisType == 0) { // X轴
         xAxis->setRange(minVal, maxVal);
     } else if (axisType >= 1 && axisType <= 3) { // Y轴
         int yAxisIndex = axisType - 1;
         if (yAxisIndex < yAxes.size()) {
             yAxes[yAxisIndex]->setRange(minVal, maxVal);
         }
     } else {
         QMessageBox::warning(this, "警告", "未知的轴类型！");

}
}


void MainWindow::on_pushButton_14_clicked()
{
    if (seriesList1.size() < 2) {  // 假设流量数据在第二个系列中
        QMessageBox::warning(this, "警告", "没有足够的数据系列！");
        return;
    }

    // 获取流量系列数据
    QLineSeries* flowSeries = seriesList1[1];  // 假设索引1是流量系列




    // 清空缓冲区并填充数据
    flowDataBuffer.clear();
    for (int i = 0; i < flowSeries->count(); ++i) {
        flowDataBuffer.append(flowSeries->at(i).y());
        fyDataBuffer.append(flowSeries->at(i).x());
    }
    qDebug()<<flowDataBuffer.size();

    ui->pushButton_14->setStyleSheet(
            "QPushButton {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #1cbf5e, stop:0.5 #0caa49, stop:1 #089c40);"
            "   color: white;"
            "   border: 1px solid #066f2d;"
            "   border-radius: 5px;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #1fd36a, stop:0.5 #0fc252, stop:1 #0ab144);"
            "}"
            "QPushButton:pressed {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #0a8a3a, stop:0.5 #097d33, stop:1 #066f2d);"
            "   padding-top: 11px;"
            "   padding-bottom: 9px;"
            "}"
        );

    sendNextFlowDataBatch();

}


void MainWindow::sendNextFlowDataBatch()
{
    // 每次发送3组数据
    QByteArray canData;
    static unsigned char k=1;


    if(fyDataBuffer[fcount]>=1000){
        direct=0x81;
        k=(fyDataBuffer[fcount]-1000)/60+1;
    }else{
        direct=0x82;
        k=(900-fyDataBuffer[fcount])/60+1;
    }

    for (int j = 0; j < 3; ++j) {
        if (fcount < flowDataBuffer.size()) {
            // 有数据：转换并添加
            quint16 value = static_cast<quint16>(std::round(flowDataBuffer[fcount++] * 10));
            canData.append(static_cast<char>(value & 0xFF));        // 低字节
            canData.append(static_cast<char>((value >> 8) & 0xFF)); // 高字节
        } else {
            // 无数据：补零
            canData.append('\x00');  // 低字节补0
            canData.append('\x00');  // 高字节补0
        }
    }


    // 发送CAN数据
    if (!canData.isEmpty()) {
        int NID=ui->comboBox_14->currentData().toInt()+0x300;
        unsigned char data[]={static_cast<unsigned char>(canData.at(0)),static_cast<unsigned char>(canData.at(1)),
                                static_cast<unsigned char>(canData.at(2)),static_cast<unsigned char>(canData.at(3)),
                                static_cast<unsigned char>(canData.at(4)),static_cast<unsigned char>(canData.at(5)),k,direct};
        if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                                NID,
                                0,
                                0,
                                data,8)){
            wlReceived=1;

            QString dataStr;
            // 每两个字节组合成一个16位数值
            for (int i = 0; i < 8; ++i) {
                dataStr += QString("%1 ").arg(static_cast<quint8>(data[i]), 2, 16, QChar('0')).toUpper();
            }

            ui->plainTextEdit_2->appendPlainText(
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") +
                QString(" 已经成功发送位移流量标定: %1").arg(dataStr.trimmed())
                );
        }
    }



    // 检查是否还有数据需要发送
    if (fcount < flowDataBuffer.size()) {
        // 延迟一段时间后发送下一批数据
        QTimer::singleShot(100, this, &MainWindow::sendNextFlowDataBatch);
    } else {
        // int groupNumber = 0xAA;
        // canData.clear();

        // // 填充全零数据
        // for (int i = 0; i < 6; ++i) {
        //     canData.append('\x00');
        // }

        // // 添加分组序号(0xAA)
        // canData.append(groupNumber);

        // // 添加固定值 0x52
        // canData.append(direct);

        // // 发送保存指令
        // if (!canData.isEmpty()) {
        //     int frameId = 0x300 + ui->comboBox_14->currentData().toInt();
        //     unsigned char data[8];
        //     for (int i = 0; i < canData.size(); ++i) {
        //         data[i] = static_cast<unsigned char>(canData.at(i));
        //     }

        //     if (canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
        //                             frameId,
        //                             0,
        //                             0,
        //                             data,
        //                             8)) {
        //         ui->plainTextEdit_2->appendPlainText(
        //             QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") +
        //             " 已发送标定保存指令"
        //             );
        //     }
        // }


        fcount=0;
        k=1;
        ui->pushButton_14->setStyleSheet("QPushButton { font-size: 24px; }");
        QMessageBox::information(this, "信息", "流量数据发送完成！");
    }
}







void MainWindow::setupChart2()
{
    qchart2 = new QChart();
    qchart2->setTitle("数据图表");
    qchart2->setAnimationOptions(QChart::AllAnimations);

    QValueAxis* axisX = new QValueAxis;
    axisX->setTitleText(QObject::tr("给定电流"));
    axisX->setRange(0, 1800);
    axisX->setLabelFormat("%.0f");
    axisX->setGridLineColor(Qt::lightGray);
    qchart2->addAxis(axisX, Qt::AlignBottom);

    QValueAxis* axisY = new QValueAxis;
    axisY->setTitleText(QObject::tr("位移"));
    axisY->setRange(0, 50);
    axisY->setLabelFormat("%.1f");
    axisY->setGridLineColor(Qt::lightGray);
    axisY->setTitleBrush(QBrush(Qt::blue));
    // 设置 Y 轴轴线颜色
    axisY->setLinePen(QPen(Qt::blue));
    qchart2->addAxis(axisY, Qt::AlignLeft);

    QValueAxis* axisY1 = new QValueAxis;
    axisY1->setTitleText(QObject::tr("流量"));
    axisY1->setRange(0, 50);
    axisY1->setLabelFormat("%.1f");
    axisY1->setGridLineColor(Qt::lightGray);
    axisY1->setTitleBrush(QBrush(Qt::red));
    // 设置 Y 轴轴线颜色
    axisY1->setLinePen(QPen(Qt::red));
    qchart2->addAxis(axisY1, Qt::AlignRight);

    QValueAxis* axisY2 = new QValueAxis;
    axisY2->setTitleText(QObject::tr("油温 (°C)"));
    axisY2->setRange(0, 80);
    axisY2->setLabelFormat("%.1f");
    axisY2->setTitleBrush(QBrush(Qt::green));
    // 设置 Y 轴轴线颜色
    axisY2->setLinePen(QPen(Qt::green));
    axisY2->setGridLineVisible(false);
    qchart2->addAxis(axisY2, Qt::AlignRight);

    yAxes2 = {axisY, axisY1, axisY2};

    // 创建数据系列
    QStringList fields = {"反馈位移 (mm)", "流量 (L/min)", "油温 (°C)"};
    seriesList2.clear();

    for (int i = 0; i < fields.size(); ++i) {
        QLineSeries* series0 = new QLineSeries();
        series0->setName(fields[i]);
        seriesList2.append(series0);

        // 将系列添加到图表
        qchart2->addSeries(series0);

        // 绑定X轴（所有系列共用）
        series0->attachAxis(axisX);

        // 绑定对应Y轴
        series0->attachAxis(yAxes2[i]);

        // 设置不同颜色以便区分
        QPen pen = series0->pen();
        switch(i) {
        case 0: pen.setColor(Qt::blue); break;
        case 1: pen.setColor(Qt::red); break;
        case 2: pen.setColor(Qt::green); break;
        default: pen.setColor(Qt::black);
        }
        series0->setPen(pen);

        connect(series0, &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
            if (state) {
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
                        break; // 精确匹配
                    }
                }

                // 检查左右邻居点
                if (closestIndex > 0) {
                    QPointF leftPoint = series0->at(closestIndex - 1);
                    qreal leftDistance = qAbs(leftPoint.x() - targetX);
                    if (leftDistance < minDistance) {
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
                QString tooltip = QString("%1\n开度: %2\n值: %3")
                                      .arg(fields[i])
                                      .arg(closestPoint.x())
                                      .arg(closestPoint.y());

                QToolTip::showText(QCursor::pos(), tooltip, ui->graphicsView_3);
            } else {
                QToolTip::hideText();
            }
        });
    }

    // 创建自定义图表视图
    chartView2 = new QChartView(qchart2);
    chartView2->setRenderHint(QPainter::Antialiasing);


    ui->graphicsView_3->setChart(qchart2);
    ui->graphicsView_3->setRenderHint(QPainter::Antialiasing);
}


void MainWindow::on_pushButton_17_clicked()
{
    filePath2 = QFileDialog::getOpenFileName(
        this,
        "选择数据文件",
        "./",
        "所有文件 (*.xlsx)"
        );

    if (filePath2.isEmpty()) {
        return;
    }

    // 在lineEdit中显示文件路径
    ui->lineEdit_13->setText(filePath2);
}


void MainWindow::on_pushButton_18_clicked()
{
    if (filePath2.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择数据文件！");
        return;
    }

    bool success = false;

    if (filePath2.endsWith(".xlsx", Qt::CaseInsensitive)) {
        success = loadDataFromExcel(filePath2,seriesList2);
    } else {
        QMessageBox::warning(this, "警告", "不支持的文件类型！");
        return;
    }

    if (success) {
        adjustChartAxes2();
        QMessageBox::information(this, "成功", "数据加载成功！");
    }
    connect(ui->pushButtonAdjust_2, &QPushButton::clicked, this, &MainWindow::onAdjustAxesClicked2);
}


void MainWindow::onAdjustAxesClicked2()
{
    // 获取用户选择的轴类型
    int axisType = ui->comboBoxAxisType_2->currentIndex();

    // 解析最小值和最大值
    bool minOk, maxOk;
    qreal minVal = ui->lineEditMin_4->text().toInt(&minOk);
    qreal maxVal = ui->lineEditMax_4->text().toInt(&maxOk);

    if (!minOk || !maxOk || minVal >= maxVal) {
        QMessageBox::warning(this, "警告", "范围值无效！请确保输入有效的数值且最小值小于最大值");
        return;
    }

    QValueAxis* xAxis = qobject_cast<QValueAxis*>(qchart2->axisX());

    // 根据选择的轴类型调整相应的坐标轴
    if (axisType == 0) { // X轴
        xAxis->setRange(minVal, maxVal);
    } else if (axisType >= 1 && axisType <= 3) { // Y轴
        int yAxisIndex = axisType - 1;
        if (yAxisIndex < yAxes2.size()) {
            yAxes2[yAxisIndex]->setRange(minVal, maxVal);
        }
    } else {
        QMessageBox::warning(this, "警告", "未知的轴类型！");
    }
}




void MainWindow::adjustChartAxes2()
{
    // 初始化X轴的全局最小值和最大值
    qreal minX = std::numeric_limits<qreal>::max();
    qreal maxX = std::numeric_limits<qreal>::lowest();

    // 自动调整Y轴范围
    for (auto series : seriesList2) {
        QList<QPointF> points = series->points();
        if (points.isEmpty()) continue;

        // 计算当前系列的Y轴范围
        qreal minY = points[0].y();
        qreal maxY = points[0].y();

        // 同时更新X轴的全局范围
        for (const auto& point : points) {
            minY = qMin(minY, point.y());
            maxY = qMax(maxY, point.y());
            minX = qMin(minX, point.x());
            maxX = qMax(maxX, point.x());
        }

        // 稍微扩展一下Y轴范围
        minY = qMax(0.0, minY * 0.9);
        maxY = maxY * 1.1;

        // 获取关联的Y轴并设置范围
        QList<QAbstractAxis*> axes = series->attachedAxes();
        for (auto axis : axes) {
            if (axis->orientation() == Qt::Vertical) {
                QValueAxis* yAxis = qobject_cast<QValueAxis*>(axis);
                if (yAxis) {
                    yAxis->setRange(minY, maxY);
                }
            }
        }
    }

    // 如果有数据点，设置X轴范围
    if (minX <= maxX) {
        // 稍微扩展X轴范围
        qreal padding = (maxX - minX) * 0.05; // 5%的边距
        minX -= padding;
        maxX += padding;

        // 为所有系列关联的X轴设置范围
        for (auto series : seriesList2) {
            QList<QAbstractAxis*> axes = series->attachedAxes();
            for (auto axis : axes) {
                if (axis->orientation() == Qt::Horizontal) {
                    QValueAxis* xAxis = qobject_cast<QValueAxis*>(axis);
                    if (xAxis) {
                        xAxis->setRange(minX, maxX);
                    }
                }
            }
        }
    }
}



void MainWindow::on_pushButton_15_clicked()
{
    if (seriesList2.size() < 2) {  // 假设流量数据在第二个系列中
        QMessageBox::warning(this, "警告", "没有足够的数据系列！");
        return;
    }

    // 获取流量系列数据
    QLineSeries* flowSeries = seriesList2[1];  // 假设索引1是流量系列




    // 清空缓冲区并填充数据
    flowDataBuffer2.clear();
    for (int i = 0; i < flowSeries->count(); ++i) {
        flowDataBuffer2.append(flowSeries->at(i).y());
        fyDataBuffer2.append(flowSeries->at(i).x());
    }

    ui->pushButton_15->setStyleSheet(
            "QPushButton {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #1cbf5e, stop:0.5 #0caa49, stop:1 #089c40);"
            "   color: white;"
            "   border: 1px solid #066f2d;"
            "   border-radius: 5px;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #1fd36a, stop:0.5 #0fc252, stop:1 #0ab144);"
            "}"
            "QPushButton:pressed {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #0a8a3a, stop:0.5 #097d33, stop:1 #066f2d);"
            "   padding-top: 11px;"
            "   padding-bottom: 9px;"
            "}"
        );

    sendNextFlowDataBatch2();
}




void MainWindow::sendNextFlowDataBatch2()
{
    // 每次发送3组数据
    QByteArray canData;
    static unsigned char k1=1;

if(fyDataBuffer2[fcount2]==0){
    if(fyDataBuffer2[fcount2+1]>0){
        direct2=0x91;
        k1=(fyDataBuffer2[fcount2]-0)/60+1;
    }else{
        direct2=0x92;
        k1=(0-fyDataBuffer2[fcount2])/60+1;
    }
}else if(fyDataBuffer2[fcount2]>0){
        direct2=0x91;
        k1=(fyDataBuffer2[fcount2]-0)/60+1;
}else if(fyDataBuffer2[fcount2]<0){
        direct2=0x92;
        k1=(0-fyDataBuffer2[fcount2])/60+1;
    }

    for (int j = 0; j < 3; ++j) {
        if (fcount < flowDataBuffer2.size()) {
            // 有数据：转换并添加
            quint16 value = static_cast<quint16>(std::round(flowDataBuffer2[fcount2++] * 10));
            canData.append(static_cast<char>(value & 0xFF));        // 低字节
            canData.append(static_cast<char>((value >> 8) & 0xFF)); // 高字节
        } else {
            // 无数据：补零
            canData.append('\x00');  // 低字节补0
            canData.append('\x00');  // 高字节补0
        }
    }


    // 发送CAN数据
    if (!canData.isEmpty()) {
        int NID=ui->comboBox_26->currentData().toInt()+0x400;
        unsigned char data[]={static_cast<unsigned char>(canData.at(0)),static_cast<unsigned char>(canData.at(1)),
                                static_cast<unsigned char>(canData.at(2)),static_cast<unsigned char>(canData.at(3)),
                                static_cast<unsigned char>(canData.at(4)),static_cast<unsigned char>(canData.at(5)),k1,direct2};
        if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                                NID,
                                0,
                                0,
                                data,8)){
            dlReceived=1;

            QString dataStr;
            for (int i = 0; i < 8; ++i) {
                dataStr += QString("%1 ").arg(static_cast<quint8>(data[i]), 2, 16, QChar('0')).toUpper();
            }

            ui->plainTextEdit_2->appendPlainText(
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") +
                QString(" 已经成功发送电流/流量标定: 0x%1").arg(dataStr.trimmed())
                );
        }
    }



    // 检查是否还有数据需要发送
    if (fcount2 < flowDataBuffer2.size()) {
        // 延迟一段时间后发送下一批数据
        QTimer::singleShot(100, this, &MainWindow::sendNextFlowDataBatch2);
    } else {
        // int groupNumber = 0xAA;
        // canData.clear();

        // // 填充全零数据
        // for (int i = 0; i < 6; ++i) {
        //     canData.append('\x00');
        // }

        // // 添加分组序号(0xAA)
        // canData.append(groupNumber);

        // // 添加固定值 0x52
        // canData.append(direct2);

        // // 发送保存指令
        // if (!canData.isEmpty()) {
        //     int frameId = 0x400 + ui->comboBox_14->currentData().toInt();
        //     unsigned char data[8];
        //     for (int i = 0; i < canData.size(); ++i) {
        //         data[i] = static_cast<unsigned char>(canData.at(i));
        //     }

        //     if (canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
        //                             frameId,
        //                             0,
        //                             0,
        //                             data,
        //                             8)) {
        //         ui->plainTextEdit_2->appendPlainText(
        //             QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") +
        //             " 已发送标定保存指令"
        //             );
        //     }
        // }
        fcount2=0;
        k1=1;
        ui->pushButton_15->setStyleSheet("QPushButton { font-size: 24px; }");
        QMessageBox::information(this, "信息", "流量数据发送完成！");
    }
}





void MainWindow::on_pushButton_2_clicked()
{
    if (dbcWindows.isEmpty()) {
        DBC* newDbcWindow = new DBC(canthread);
        dbcWindows.append(newDbcWindow);

        // 窗口关闭时从列表中移除
        connect(newDbcWindow, &DBC::destroyed, [this, newDbcWindow]() {
            dbcWindows.removeOne(newDbcWindow);
        });

        newDbcWindow->show();
    } else {
        // 如果已经有DBC窗口，则直接显示已有的DBC窗口
        dbcWindows.first()->show();
    }
}






void MainWindow::setupChart3()
{
    qchart3 = new QChart();
    qchart3->setTitle("数据图表");
    qchart3->setAnimationOptions(QChart::AllAnimations);

    QValueAxis* axisX = new QValueAxis;
    axisX->setTitleText(QObject::tr("位移值"));
    axisX->setRange(0, 50);
    axisX->setLabelFormat("%.4f");
    axisX->setGridLineColor(Qt::lightGray);
    qchart3->addAxis(axisX, Qt::AlignBottom);

    QValueAxis* axisY = new QValueAxis;
    axisY->setTitleText(QObject::tr("测量值"));
    axisY->setRange(0, 50);
    axisY->setLabelFormat("%.4f");
    axisY->setGridLineColor(Qt::lightGray);
    axisY->setTitleBrush(QBrush(Qt::blue));
    // 设置 Y 轴轴线颜色
    axisY->setLinePen(QPen(Qt::blue));
    qchart3->addAxis(axisY, Qt::AlignLeft);

    QValueAxis* axisY1 = new QValueAxis;
    axisY1->setTitleText(QObject::tr("理论值"));
    axisY1->setRange(0, 50);
    axisY1->setLabelFormat("%.4f");
    axisY1->setGridLineColor(Qt::lightGray);
    axisY1->setTitleBrush(QBrush(Qt::red));
    // 设置 Y 轴轴线颜色
    axisY1->setLinePen(QPen(Qt::red));
    qchart3->addAxis(axisY1, Qt::AlignRight);


    yAxes3 = {axisY, axisY1};

    // 创建数据系列
    QStringList fields = {"测量值", "理论值"};
    seriesList3.clear();

    for (int i = 0; i < fields.size(); ++i) {
        QLineSeries* series0 = new QLineSeries();
        series0->setName(fields[i]);
        seriesList3.append(series0);

        // 将系列添加到图表
        qchart3->addSeries(series0);

        // 绑定X轴（所有系列共用）
        series0->attachAxis(axisX);

        // 绑定对应Y轴
        series0->attachAxis(yAxes3[i]);

        // 设置不同颜色以便区分
        QPen pen = series0->pen();
        switch(i) {
        case 0: pen.setColor(Qt::blue); break;
        case 1: pen.setColor(Qt::red); break;
        default: pen.setColor(Qt::black);
        }
        series0->setPen(pen);



    }

    // 创建自定义图表视图
    chartView3 = new QChartView(qchart3);
    chartView3->setRenderHint(QPainter::Antialiasing);


    connect(seriesList3[1], &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
        if (state) {
            int closestIndex = 0;
            qreal minDistance = std::numeric_limits<qreal>::max();
            QLineSeries* measureSeries = seriesList3[0];
            QLineSeries* theorySeries = seriesList3[1];
            for (int i = 0; i < theorySeries->count(); ++i) {
                qreal distance = qAbs(theorySeries->at(i).x() - point.x());
                if (distance < minDistance) {
                    minDistance = distance;
                    closestIndex = i;
                }
            }

            qreal displacement = theorySeries->at(closestIndex).x();
            qreal measureValue = measureSeries->at(closestIndex).y();
            qreal theoryValue = theorySeries->at(closestIndex).y();

            QString tooltip = QString("位移量: %1 mm\n测量值: %2 V\n理论值: %3 V")
                                  .arg(displacement, 0, 'f', 2)
                                  .arg(measureValue, 0, 'f', 4)
                                  .arg(theoryValue, 0, 'f', 4);

            // 获取视图的几何信息
            QRect viewRect = ui->graphicsView_5->geometry();
            QPoint pos = point.toPoint();
            // 确保鼠标坐标在视图内
            if (pos.x() >= 0 && pos.x() <= viewRect.width() && pos.y() >= 0 && pos.y() <= viewRect.height()) {
                // QPoint screenPos = ui->graphicsView_5->mapToGlobal(pos);
                QToolTip::showText(QCursor::pos(), tooltip, ui->graphicsView_5);
            }
        } else {
            QToolTip::hideText();
        }
    });

    connect(seriesList3[0], &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
        if (state) {
            int closestIndex = 0;
            qreal minDistance = std::numeric_limits<qreal>::max();
            QLineSeries* measureSeries = seriesList3[0];
            QLineSeries* theorySeries = seriesList3[1];
            for (int i = 0; i < measureSeries->count(); ++i) {
                qreal distance = qAbs(measureSeries->at(i).x() - point.x());
                if (distance < minDistance) {
                    minDistance = distance;
                    closestIndex = i;
                }
            }

            qreal displacement = measureSeries->at(closestIndex).x();
            qreal measureValue = measureSeries->at(closestIndex).y();
            qreal theoryValue = theorySeries->at(closestIndex).y();

            QString tooltip = QString("位移量: %1 mm\n测量值: %2 V\n理论值: %3 V")
                                  .arg(displacement, 0, 'f', 2)
                                  .arg(measureValue, 0, 'f', 4)
                                  .arg(theoryValue, 0, 'f', 4);

            // 获取视图的几何信息
            QRect viewRect = ui->graphicsView_5->geometry();
            QPoint pos = point.toPoint();
            // 确保鼠标坐标在视图内
            if (pos.x() >= 0 && pos.x() <= viewRect.width() && pos.y() >= 0 && pos.y() <= viewRect.height()) {
                // QPoint screenPos = ui->graphicsView_5->mapToGlobal(pos);
                QToolTip::showText(QCursor::pos(), tooltip, ui->graphicsView_5);
            }
        } else {
            QToolTip::hideText();
        }
    });




    // connect(seriesList3[1], &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
    //     if (state) {
    //         int closestIndex = 0;
    //         qreal minDistance = std::numeric_limits<qreal>::max();
    //         QLineSeries* measureSeries = seriesList3[0];
    //         QLineSeries* theorySeries = seriesList3[1];
    //         for (int i = 0; i < theorySeries->count(); ++i) {
    //             qreal distance = qAbs(theorySeries->at(i).x() - point.x());
    //             if (distance < minDistance) {
    //                 minDistance = distance;
    //                 closestIndex = i;
    //             }
    //         }

    //         qreal displacement = theorySeries->at(closestIndex).x();
    //         qreal measureValue = measureSeries->at(closestIndex).y();
    //         qreal theoryValue = theorySeries->at(closestIndex).y();

    //         QString tooltip = QString("位移量: %1 mm\n测量值: %2 V\n理论值: %3 V")
    //                               .arg(displacement, 0, 'f', 2)
    //                               .arg(measureValue, 0, 'f', 4)
    //                               .arg(theoryValue, 0, 'f', 4);

    //         QPointF scenePos = chartView3->chart()->mapToScene(point);
    //         QPoint screenPos = chartView3->mapToGlobal(scenePos.toPoint());
    //         QToolTip::showText(screenPos, tooltip, ui->graphicsView_5);
    //     } else {
    //         QToolTip::hideText();
    //     }
    // });

    // connect(seriesList3[0], &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
    //     if (state) {
    //         int closestIndex = 0;
    //         qreal minDistance = std::numeric_limits<qreal>::max();
    //         QLineSeries* measureSeries = seriesList3[0];
    //         QLineSeries* theorySeries = seriesList3[1];
    //         for (int i = 0; i < measureSeries->count(); ++i) {
    //             qreal distance = qAbs(measureSeries->at(i).x() - point.x());
    //             if (distance < minDistance) {
    //                 minDistance = distance;
    //                 closestIndex = i;
    //             }
    //         }

    //         qreal displacement = measureSeries->at(closestIndex).x();
    //         qreal measureValue = measureSeries->at(closestIndex).y();
    //         qreal theoryValue = theorySeries->at(closestIndex).y();

    //         QString tooltip = QString("位移量: %1 mm\n测量值: %2 V\n理论值: %3 V")
    //                               .arg(displacement, 0, 'f', 2)
    //                               .arg(measureValue, 0, 'f', 4)
    //                               .arg(theoryValue, 0, 'f', 4);

    //         QPointF scenePos = chartView3->chart()->mapToScene(point);
    //         QPoint screenPos = chartView3->mapToGlobal(scenePos.toPoint());
    //         QToolTip::showText(screenPos, tooltip, ui->graphicsView_5);
    //     } else {
    //         QToolTip::hideText();
    //     }
    // });




    ui->graphicsView_5->setChart(qchart3);
    ui->graphicsView_5->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::on_pushButton_69_clicked()
{
    filePath3 = QFileDialog::getOpenFileName(
        this,
        "选择数据文件",
        "./",
        "所有文件 (*.xlsx)"
        );

    if (filePath3.isEmpty()) {
        return;
    }

    // 在lineEdit中显示文件路径
    ui->lineEdit_69->setText(filePath3);
}


void MainWindow::on_pushButton_70_clicked()
{
    if (filePath3.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择数据文件！");
        return;
    }

    bool success = false;

    if (filePath3.endsWith(".xlsx", Qt::CaseInsensitive)) {
        success = loadDataFromExcel3(filePath3,seriesList3);
    } else {
        QMessageBox::warning(this, "警告", "不支持的文件类型！");
        return;
    }

    if (success) {
        adjustChartAxes3();
        QMessageBox::information(this, "成功", "数据加载成功！");
    }
    connect(ui->pushButtonAdjust_3, &QPushButton::clicked, this, &MainWindow::onAdjustAxesClicked3);
}



void MainWindow::onAdjustAxesClicked3()
{
    // 获取用户选择的轴类型
    int axisType = ui->comboBoxAxisType_3->currentIndex();

    // 解析最小值和最大值
    bool minOk, maxOk;
    qreal minVal = ui->lineEditMin_5->text().toInt(&minOk);
    qreal maxVal = ui->lineEditMax_5->text().toInt(&maxOk);

    if (!minOk || !maxOk || minVal >= maxVal) {
        QMessageBox::warning(this, "警告", "范围值无效！请确保输入有效的数值且最小值小于最大值");
        return;
    }

    QValueAxis* xAxis = qobject_cast<QValueAxis*>(qchart3->axisX());

    // 根据选择的轴类型调整相应的坐标轴
    if (axisType == 0) { // X轴
        xAxis->setRange(minVal, maxVal);
    } else if (axisType >= 1 && axisType <= 3) { // Y轴
        int yAxisIndex = axisType - 1;
        if (yAxisIndex < yAxes3.size()) {
            yAxes3[yAxisIndex]->setRange(minVal, maxVal);
        }
    } else {
        QMessageBox::warning(this, "警告", "未知的轴类型！");
    }
}




void MainWindow::adjustChartAxes3()
{



        // 初始化X轴的全局最小值和最大值
        qreal minX = std::numeric_limits<qreal>::max();
        qreal maxX = std::numeric_limits<qreal>::lowest();

        // 自动调整Y轴范围
        qreal globalMinY = std::numeric_limits<qreal>::max();
        qreal globalMaxY = std::numeric_limits<qreal>::lowest();
        for (auto series : seriesList3) {
            QList<QPointF> points = series->points();
            if (points.isEmpty()) continue;

            // 计算当前系列的Y轴范围
            qreal minY = points[0].y();
            qreal maxY = points[0].y();

            // 同时更新X轴的全局范围
            for (const auto& point : points) {
                minY = qMin(minY, point.y());
                maxY = qMax(maxY, point.y());
                minX = qMin(minX, point.x());
                maxX = qMax(maxX, point.x());
            }

            globalMinY = qMin(globalMinY, minY);
            globalMaxY = qMax(globalMaxY, maxY);
        }

        // 更灵活地扩展Y轴范围，这里简单示例按固定倍数扩展
        qreal yDiff = globalMaxY - globalMinY;
        qreal yPadding = yDiff * 0.1; // 10% 的边距
        globalMinY -= yPadding;
        globalMaxY += yPadding;

        // 获取关联的Y轴并设置范围
        for (auto series : seriesList3) {
            QList<QAbstractAxis*> axes = series->attachedAxes();
            for (auto axis : axes) {
                if (axis->orientation() == Qt::Vertical) {
                    QValueAxis* yAxis = qobject_cast<QValueAxis*>(axis);
                    if (yAxis) {
                        yAxis->setRange(globalMinY, globalMaxY);
                    }
                }
            }
        }

        // 如果有数据点，设置X轴范围
        if (minX <= maxX) {
            // 稍微扩展X轴范围
            qreal xDiff = maxX - minX;
            qreal xPadding = xDiff * 0.08; // 8% 的边距
            minX -= xPadding;
            maxX += xPadding;

            // 为所有系列关联的X轴设置范围
            for (auto series : seriesList3) {
                QList<QAbstractAxis*> axes = series->attachedAxes();
                for (auto axis : axes) {
                    if (axis->orientation() == Qt::Horizontal) {
                        QValueAxis* xAxis = qobject_cast<QValueAxis*>(axis);
                        if (xAxis) {
                            xAxis->setRange(minX, maxX);
                        } else {
                            // 轴类型转换失败处理
                            qWarning() << "Failed to cast axis to QValueAxis for setting X-axis range";
                        }
                    }
                }
            }
        }




}


bool MainWindow::loadDataFromExcel3(const QString &filePath, QList<QLineSeries *> &seriesListn)
{
    QXlsx::Document xlsx(filePath);



    // 清空现有数据
    for (auto series : seriesListn)
    {
        series->clear();
    }

    QXlsx::Worksheet *sheet = xlsx.currentWorksheet();
    if (!sheet)
    {
        QMessageBox::critical(this, "错误", "无法获取工作表！");
        return false;
    }

    QXlsx::CellRange range = sheet->dimension();
    if (range.rowCount() <= 1)
    {
        QMessageBox::information(this, "提示", "Excel文件中没有数据！");
        return true; // 没有数据但加载成功
    }

    // 读取数据（跳过标题行）
    for (int row = 2; row <= range.rowCount(); ++row)
    {
        // 获取X轴数据（第二列）
        QVariant xValue = sheet->read(row, 2);
        if (xValue.isNull())
        {
            continue;
        }

        bool ok;
        qreal x = xValue.toDouble(&ok);
        if (!ok)
        {
            continue;
        }

        // 获取Y轴数据（第3、4列）
        for (int col = 0; col < 2; ++col)
        {
            QVariant yValue = sheet->read(row, col + 3);
            if (!yValue.isNull())
            {
                qreal y = yValue.toDouble(&ok);
                if (ok)
                {
                    if (col < seriesListn.size())
                    {
                        seriesListn[col]->append(x, y);
                    }
                    else
                    {
                        // 处理列数超过seriesListn大小的情况
                        QMessageBox::warning(this, "警告", "列数超过seriesListn大小，无法添加数据！");
                    }
                }
            }
        }
    }

    return true;
}



void MainWindow::on_pushButton_71_clicked()
{
    if (seriesList3.size() < 2) {  // 假设流量数据在第二个系列中
        QMessageBox::warning(this, "警告", "没有足够的数据系列！");
        return;
    }

    // 获取流量系列数据
    QLineSeries* flowSeries = seriesList3[0];  // 假设索引1是流量系列




    // 清空缓冲区并填充数据
    flowDataBuffer3.clear();
    for (int i = 0; i < flowSeries->count(); ++i) {
        flowDataBuffer3.append(flowSeries->at(i).y());
        fyDataBuffer3.append(flowSeries->at(i).x());
    }

    ui->pushButton_71->setStyleSheet(
            "QPushButton {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #1cbf5e, stop:0.5 #0caa49, stop:1 #089c40);"
            "   color: white;"
            "   border: 1px solid #066f2d;"
            "   border-radius: 5px;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #1fd36a, stop:0.5 #0fc252, stop:1 #0ab144);"
            "}"
            "QPushButton:pressed {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #0a8a3a, stop:0.5 #097d33, stop:1 #066f2d);"
            "   padding-top: 11px;"
            "   padding-bottom: 9px;"
            "}"
        );

    sendNextFlowDataBatch3();
}


void MainWindow::sendNextFlowDataBatch3()
{
    // 每次发送3组数据
    QByteArray canData;
    static unsigned char k=1;

    // // k = static_cast<unsigned char>((18 - fyDataBuffer3[fcount3]) / 3.6 + 1);
    // k=(18 - fyDataBuffer3[fcount3]) / 3.6 + 1;
    double step1 = 18 - fyDataBuffer3[fcount3];      // 18 - 14.4 = 3.6
    double step2 = step1 / 3.6;     // 3.6 / 3.6 = 1.0
    double step3 = step2 + 1;       // 1.0 + 1 = 2.0
     k = static_cast<unsigned char>(step3);

    qDebug()<<fyDataBuffer3[fcount3]<<k;

    for (int j = 0; j < 2; j++) {
        if (fcount3 < flowDataBuffer3.size()) {
            // 有数据：转换并添加
            quint16 value = static_cast<quint16>(flowDataBuffer3[fcount3] * 10000);
            quint16 value1 = static_cast<quint16>(fyDataBuffer3[fcount3++] * 10);
            canData.append(static_cast<char>(value1 & 0xFF));
            canData.append(static_cast<char>(value & 0xFF));        // 低字节
            canData.append(static_cast<char>((value >> 8) & 0xFF)); // 高字节
        } else {
            // 无数据：补零
            canData.append('\x00');  // 低字节补0
            canData.append('\x00');
            canData.append('\x00');
        }
    }
    qDebug()<<fcount3;

    // 发送CAN数据
    if (!canData.isEmpty()) {
        int NID=ui->comboBox_14->currentData().toInt()+0x500;
        unsigned char data[]={static_cast<unsigned char>(canData.at(0)),static_cast<unsigned char>(canData.at(1)),
                                static_cast<unsigned char>(canData.at(2)),static_cast<unsigned char>(canData.at(3)),
                                static_cast<unsigned char>(canData.at(4)),static_cast<unsigned char>(canData.at(5)),k,0x52};
        if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                                NID,
                                0,
                                0,
                                data,8)){
            wdReceived=1;

            QString dataStr;
            for (int i = 0; i < 8; ++i) {
                dataStr += QString("%1 ").arg(static_cast<quint8>(data[i]), 2, 16, QChar('0')).toUpper();
            }

            ui->plainTextEdit_2->appendPlainText(
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") +
                QString(" 已成功发送位移/电压标定: 0x%1")
                    .arg(dataStr.trimmed())
                );
        }
    }



    // 检查是否还有数据需要发送
    if (fcount3 < flowDataBuffer3.size()) {
        // 延迟一段时间后发送下一批数据
        QTimer::singleShot(100, this, &MainWindow::sendNextFlowDataBatch3);
    } else {
        // // 所有数据发送完成，发送保存指令(分组序号=0xAA)
        // int groupNumber = 0xAA;
        // canData.clear();

        // // 填充全零数据
        // for (int i = 0; i < 6; ++i) {
        //     canData.append('\x00');
        // }

        // // 添加分组序号(0xAA)
        // canData.append(groupNumber);

        // // 添加固定值 0x52
        // canData.append(static_cast<char>(0x52));

        // // 发送保存指令
        // if (!canData.isEmpty()) {
        //     int frameId = 0x500 + ui->comboBox_14->currentData().toInt();
        //     unsigned char data[8];
        //     for (int i = 0; i < canData.size(); ++i) {
        //         data[i] = static_cast<unsigned char>(canData.at(i));
        //     }

        //     if (canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
        //                             frameId,
        //                             0,
        //                             0,
        //                             data,
        //                             8)) {
        //         ui->plainTextEdit_2->appendPlainText(
        //             QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") +
        //             " 已发送标定保存指令"
        //             );
        //     }
        // }
        k=1;

        // 重置计数器
        fcount3 = 0;
        ui->pushButton_71->setStyleSheet("QPushButton { font-size: 24px; }");
        QMessageBox::information(this, "信息", "位移/电压标定数据发送完成！");
    }
}












void MainWindow::on_LVDTBt_2_clicked()
{
    unsigned char NID=ui->comboBox_14->currentData().toInt();
    unsigned char lvdt=ui->comboBox_15->currentIndex();
    unsigned char lvdt1;
    switch (lvdt) {
    case 0:
        lvdt1=0x00;
        ui->plainTextEdit_2->appendPlainText("阀芯位移配置发送成功");
        break;
    case 1:
        lvdt1=0x10;
        ui->plainTextEdit_2->appendPlainText("PWMA流量起点配置发送成功");
        break;
    case 2:
        lvdt1=0x11;
        ui->plainTextEdit_2->appendPlainText("PWMA流量终点配置发送成功");
        break;
    case 3:
        lvdt1=0x20;
        ui->plainTextEdit_2->appendPlainText("PWMB流量起点配置发送成功");
        break;
    case 4:
        lvdt1=0x21;
        ui->plainTextEdit_2->appendPlainText("PWMB流量终点配置发送成功");
        break;
    default:
        return;
        break;
    }
    unsigned char data[]={0x13,NID,lvdt1,0x0,0x0,0x0,0x00,0x00};
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                            0x7e5,
                            0,
                            0,
                            data,8))
    {
        LVDTReceived=1;
        // AddDataToList(buildMessageList(ui->comboBox_4, 0x7e5, ui->comboBox_5,  data, 8));
    }
}


void MainWindow::on_saveBt_2_clicked()
{
    ui->plainTextEdit_2->appendPlainText("正在保存设置中");
    unsigned char NID=ui->comboBox_14->currentData().toInt();
    unsigned char data[]={0x17,NID,0x0,0x0,0x0,0x0,0x00,0x00};
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                            0x7e5,
                            0,
                            0,
                            data,8))
    {
        saveReceived2=1;
    }
}












// void MainWindow::on_pushButton_19_clicked()
// {
//     filePath4 = QFileDialog::getOpenFileName(
//         this,
//         "选择数据文件",
//         "./cantex/can原始数据",
//         "文本文件 (*.txt);;所有文件 (*)"
//         );

//     if (filePath4.isEmpty()) {
//         return;
//     }

//     ui->lineEdit_14->setText(filePath4);
//     ui->comboBox_16->clear();
//     ui->tableWidget->setRowCount(0);
//     frameDataMap.clear();

//     QFile file(filePath4);
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//         return;

//     QTextStream in(&file);
//     QString content = in.readAll();
//     file.close();

//QRegularExpression re("(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3})\\s+接收\\s+(0x000001[89A-Fa-f][0-9A-Fa-f]|0x000002[89A-Fa-f][0-9A-Fa-f])\\s+(([0-9A-Fa-f]{2}\\s+){8})");
//   //QRegularExpression re("(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3})\\s+接收\\s+(0x[0-9A-Fa-f]{8})\\s+(([0-9A-Fa-f]{2}\\s+){8})");
//     static  QRegularExpression re("(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3})\\s+接收\\s+(0x000001[89A-Fa-f][0-9A-Fa-f]|0x000002[89A-Fa-f][0-9A-Fa-f])\\s+(([0-9A-Fa-f]{2}\\s+){8})");
//     QRegularExpressionMatchIterator i = re.globalMatch(content);

//     while (i.hasNext()) {
//         QRegularExpressionMatch match = i.next();
//         QString timestamp = match.captured(1);  // 时间戳
//         QString frameId = match.captured(2);    // 帧ID
//         QString dataField = match.captured(3);  // 数据字段

//         // 提取8字节数据
//         QStringList bytes = dataField.simplified().split(" ");

//         // 确保有8个字节数据
//         if (bytes.size() != 8)
//             continue;

//         // 解析数据
//         QString displacement = QString::number((bytes[1].toUShort(0, 16) * 256 + bytes[0].toUShort(0, 16)) , 'f', 2);
//         QString currentA = QString::number((bytes[3].toUShort(0, 16) * 256 + bytes[2].toUShort(0, 16)), 'f', 0);
//         QString currentB = QString::number((bytes[5].toUShort(0, 16) * 256 + bytes[4].toUShort(0, 16)), 'f', 0);

//         // 解析故障字节
//         uchar faultByte = bytes[6].toUShort(0, 16);
//         QString lvdtStatus = (faultByte & 0x01) ? "异常" : "正常";
//         QString pwmaStatus = (faultByte & 0x02) ? "异常" : "正常";
//         QString pwmbStatus = (faultByte & 0x04) ? "异常" : "正常";

//         // 解析LVDT存在位
//         QString lvdtPresent = (bytes[7].toUShort(0, 16) & 0x01) ? "无LVDT" : "有LVDT";

//         // 存储解析后的数据
//         QString shortFrameId = "0x" + frameId.mid(6); // 转换为0x180格式
//         QStringList rowData = {timestamp, shortFrameId, displacement, currentA, currentB,
//                                lvdtStatus, pwmaStatus, pwmbStatus, lvdtPresent};

//         frameDataMap[shortFrameId].append(rowData);
//     }

//     // 更新下拉框
//     QStringList uniqueIds = frameDataMap.keys();
//     uniqueIds.sort();
//     ui->comboBox_16->addItems(uniqueIds);

//     if (uniqueIds.isEmpty()) {
//         QMessageBox::information(this, "提示", "未找到符合条件的完整帧数据");
//     } else {
//         ui->comboBox_16->setCurrentIndex(0);

//     }
// }




// void MainWindow::on_pushButton_19_clicked()
// {
//     // 选择数据文件
//     QString filePath4 = QFileDialog::getOpenFileName(
//         this,
//         "选择数据文件",
//         "./cantex/can原始数据",
//         "文本文件 (*.txt);;所有文件 (*)"
//         );

//     if (filePath4.isEmpty()) {
//         return;
//     }

//     // 初始化界面和数据结构
//     ui->lineEdit_14->setText(filePath4);
//     ui->comboBox_16->clear();
//     ui->tableWidget->setRowCount(0);
//     frameDataMap.clear(); // 假设frameDataMap是QMap<QString, QList<QStringList>>类型

//     // 读取文件内容
//     QFile file(filePath4);
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         QMessageBox::warning(this, "错误", "无法打开文件");
//         return;
//     }

//     QTextStream in(&file);
//     QString content = in.readAll();
//     file.close();

//     // 正则表达式匹配：0x00000180-0x000001FF 和 0x00000280-0x000002FF
//     QRegularExpression re("(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3})\\s+接收\\s+(0x000001[89A-Fa-f][0-9A-Fa-f]|0x000002[89A-Fa-f][0-9A-Fa-f])\\s+(([0-9A-Fa-f]{2}\\s+){8})");
//     QRegularExpressionMatchIterator i = re.globalMatch(content);

//     while (i.hasNext()) {
//         QRegularExpressionMatch match = i.next();
//         QString timestamp = match.captured(1);
//         QString frameId = match.captured(2); // 完整帧ID（如"0x00000292"）
//         QString dataField = match.captured(3).trimmed(); // 去除首尾空格

//         // 拆分8字节数据
//         QStringList bytes = dataField.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
//         if (bytes.size() != 8) {
//             continue; // 过滤不完整帧
//         }

//         // 提取vID：帧ID低11位 - 基准值（0x180或0x280）
//         bool ok;
//         uint frameIdValue = frameId.mid(2).toUInt(&ok, 16); // 转换为数值（如0x292）
//         if (!ok) {
//             continue;
//         }

//         uint base = 0;
//         if (frameId.startsWith("0x000001")) {
//             base = 0x180; // 位移/电流反馈帧基准值
//         } else if (frameId.startsWith("0x000002")) {
//             base = 0x280; // 模拟量/LVDT帧基准值
//         } else {
//             continue; // 非目标帧ID
//         }

//         uint vID = (frameIdValue - base) & 0xFF; // 取低8位作为vID（如0x292-0x280=0x12）
//         QString vIDStr = QString::number(vID, 16).toUpper(); // 转为十六进制字符串（如"12"）

//         // 解析数据字段
//         QStringList rowData;
//         rowData << timestamp << frameId; // 添加时间戳和完整帧ID

//         if (frameId.startsWith("0x000001")) {
//             // 解析0x180+vID帧（位移/电流反馈）
//             ushort displacementRaw = (bytes[1].toUShort(&ok, 16) << 8) | bytes[0].toUShort(&ok, 16);
//             rowData << QString::number(displacementRaw* 0.01 , 'f', 2); // 单位0.01mm

//             ushort currentA = (bytes[3].toUShort(&ok, 16) << 8) | bytes[2].toUShort(&ok, 16);
//             rowData << QString::number(currentA); // 单位mA

//             ushort currentB = (bytes[5].toUShort(&ok, 16) << 8) | bytes[4].toUShort(&ok, 16);
//             rowData << QString::number(currentB); // 单位mA

//             uchar faultByte = bytes[6].toUShort(&ok, 16);
//             rowData << ((faultByte & 0x01) ? "异常" : "正常") // LVDT状态
//                     << ((faultByte & 0x02) ? "异常" : "正常") // PWMA状态
//                     << ((faultByte & 0x04) ? "异常" : "正常"); // PWMB状态

//             bool hasLVDT = (bytes[7].toUShort(&ok, 16) & 0x01) == 0;
//             rowData << (hasLVDT ? "有LVDT" : "无LVDT");
//         } else if (frameId.startsWith("0x000002")) {
//             // 解析0x280+vID帧（模拟量/LVDT电压）
//             ushort aiInput = (bytes[1].toUShort(&ok, 16) << 8) | bytes[0].toUShort(&ok, 16);
//             rowData << QString::number(aiInput) + "mV"; // 手柄电压

//             ushort lvdtVoltage = (bytes[3].toUShort(&ok, 16) << 8) | bytes[2].toUShort(&ok, 16);
//             rowData << QString::number(lvdtVoltage) + "mV"; // LVDT电压

//             // 填充占位符（协议中未定义的字节）
//             rowData << "---" << "---" << "---" << "---";

//             uchar heartbeat = bytes[7].toUShort(&ok, 16);
//             rowData << QString::number(heartbeat); // 心跳计数器
//         }

//         // 存储数据（以vID为键）
//         frameDataMap[vIDStr].append(rowData);
//     }

//     // 更新下拉框：显示唯一的vID列表
//     QStringList uniqueVIDs = frameDataMap.keys();
//     uniqueVIDs.sort();
//     ui->comboBox_16->addItems(uniqueVIDs);

//     if (uniqueVIDs.isEmpty()) {
//         QMessageBox::information(this, "提示", "未找到符合条件的完整帧数据");
//     } else {
//         ui->comboBox_16->setCurrentIndex(0);
//         // 可选：自动填充表格（需实现updateTableWidget函数）
//         // updateTableWidget(uniqueVIDs.first());
//     }
// }



// void MainWindow::setupChart4()
// {

//     chart4 = new QChart();
//     chart4->setTitle("数据趋势图");
//     chart4->legend()->setVisible(true);
//     chart4->legend()->setAlignment(Qt::AlignBottom);
//     ui->graphicsView_4->setChart(chart4);

//     // 创建场景并添加图表项
//     // QGraphicsScene *scene = new QGraphicsScene(this);
//     // scene->addItem(chart4);  // QChart是QGraphicsItem的子类

//     // // 设置场景到graphicsView_4
//     // ui->graphicsView_4->setScene(scene);
//     // ui->graphicsView_4->setRenderHint(QPainter::Antialiasing);

//     // // 调整图表大小以适应视图
//     // ui->graphicsView_4->setSceneRect(chart4->boundingRect());
// }


// void MainWindow::on_pushButton_3_clicked()
// {
//     QString vID = ui->comboBox_16->currentText(); // 获取vID（如"12"）

//     if (!frameDataMap.contains(vID)) {
//         QMessageBox::information(this, "提示", "没有选中的帧数据");
//         return;
//     }

//     const QList<QStringList> &allRows = frameDataMap[vID];
//     if (allRows.size() < 2) {
//         QMessageBox::information(this, "提示", "数据点不足，无法绘制图表");
//         return;
//     }

//     // 分离两种帧类型的数据
//     QList<QStringList> displacementRows;    // 0x180+vID帧（位移/电流）
//     QList<QStringList> voltageRows;         // 0x280+vID帧（电压）
//     for (const QStringList &row : allRows) {
//         QString frameId = row[1]; // 数据行中的完整帧ID
//         if (frameId.startsWith("0x000001")) {
//             displacementRows.append(row);
//         } else if (frameId.startsWith("0x000002")) {
//             voltageRows.append(row);
//         }
//     }

//     // 清空图表
//     chart4->removeAllSeries();
//     chart4->axes().clear();

//     // 创建系列
//     QLineSeries *seriesDisplacement = new QLineSeries();
//     seriesDisplacement->setName("阀芯位移(mm)");
//     QLineSeries *seriesCurrentA = new QLineSeries();
//     seriesCurrentA->setName("PWMA电流(mA)");
//     QLineSeries *seriesCurrentB = new QLineSeries();
//     seriesCurrentB->setName("PWMB电流(mA)");
//     QLineSeries *seriesHandleVoltage = new QLineSeries();
//     seriesHandleVoltage->setName("手柄输入电压(mV)");
//     QLineSeries *seriesLVDTVoltage = new QLineSeries();
//     seriesLVDTVoltage->setName("阀芯实际电压(mV)");

//     // 存储系列指针以便后续使用
//     QList<QLineSeries*> allSeries = {
//         seriesDisplacement, seriesCurrentA, seriesCurrentB,
//         seriesHandleVoltage, seriesLVDTVoltage
//     };

//     // 时间轴
//     QDateTimeAxis *axisX = new QDateTimeAxis();
//     axisX->setTitleText("时间");
//     axisX->setFormat("hh:mm:ss");
//     axisX->setTickCount(10);

//     // 双Y轴
//     QValueAxis *axisY1 = new QValueAxis(); // 位移/电压
//     axisY1->setTitleText("位移(mm)/电压(mV)");
//     axisY1->setLabelFormat("%d");
//     QValueAxis *axisY2 = new QValueAxis(); // 电流
//     axisY2->setTitleText("电流(mA)");
//     axisY2->setLabelFormat("%d");

//     // 计算时间范围和数据范围
//     QDateTime minTime, maxTime;
//     double minDisp = DBL_MAX, maxDisp = -DBL_MAX;
//     double minCurrent = DBL_MAX, maxCurrent = -DBL_MAX;
//     double minVoltage = DBL_MAX, maxVoltage = -DBL_MAX;

//     // 处理位移/电流数据
//     if (!displacementRows.isEmpty()) {
//         minTime = QDateTime::fromString(displacementRows.first()[0], "yyyy-MM-dd hh:mm:ss.zzz");
//         maxTime = QDateTime::fromString(displacementRows.last()[0], "yyyy-MM-dd hh:mm:ss.zzz");

//         for (const QStringList &row : displacementRows) {
//             QDateTime ts = QDateTime::fromString(row[0], "yyyy-MM-dd hh:mm:ss.zzz");
//             double disp = row[2].toDouble();
//             double currA = row[3].toDouble();
//             double currB = row[4].toDouble();

//             seriesDisplacement->append(ts.toMSecsSinceEpoch(), disp);
//             seriesCurrentA->append(ts.toMSecsSinceEpoch(), currA);
//             seriesCurrentB->append(ts.toMSecsSinceEpoch(), currB);

//             minDisp = qMin(minDisp, disp);
//             maxDisp = qMax(maxDisp, disp);
//             minCurrent = qMin(minCurrent, qMin(currA, currB));
//             maxCurrent = qMax(maxCurrent, qMax(currA, currB));
//         }
//     }

//     // 处理电压数据
//     if (!voltageRows.isEmpty()) {
//         if (minTime.isNull() || voltageRows.first()[0] < minTime.toString("yyyy-MM-dd hh:mm:ss.zzz")) {
//             minTime = QDateTime::fromString(voltageRows.first()[0], "yyyy-MM-dd hh:mm:ss.zzz");
//         }
//         if (maxTime.isNull() || voltageRows.last()[0] > maxTime.toString("yyyy-MM-dd hh:mm:ss.zzz")) {
//             maxTime = QDateTime::fromString(voltageRows.last()[0], "yyyy-MM-dd hh:mm:ss.zzz");
//         }

//         for (const QStringList &row : voltageRows) {
//             QDateTime ts = QDateTime::fromString(row[0], "yyyy-MM-dd hh:mm:ss.zzz");
//             QString handleVoltageStr = row[5];
//             handleVoltageStr.remove("mV");
//             double handleVoltage = handleVoltageStr.toDouble();

//             QString lvdtVoltageStr = row[6];
//             lvdtVoltageStr.remove("mV");
//             double lvdtVoltage = lvdtVoltageStr.toDouble();

//             seriesHandleVoltage->append(ts.toMSecsSinceEpoch(), handleVoltage);
//             seriesLVDTVoltage->append(ts.toMSecsSinceEpoch(), lvdtVoltage);

//             minVoltage = qMin(minVoltage, qMin(handleVoltage, lvdtVoltage));
//             maxVoltage = qMax(maxVoltage, qMax(handleVoltage, lvdtVoltage));
//         }
//     }

//     // 设置坐标轴范围
//     if (minTime.isValid() && maxTime.isValid()) {
//         axisX->setRange(minTime, maxTime);
//     }
//     axisY1->setRange(qMin(minDisp, minVoltage) * 0.95, qMax(maxDisp, maxVoltage) * 1.05);
//     axisY2->setRange(minCurrent * 0.95, maxCurrent * 1.05);

//     // 添加系列和轴
//     chart4->addSeries(seriesDisplacement);
//     chart4->addSeries(seriesCurrentA);
//     chart4->addSeries(seriesCurrentB);
//     chart4->addSeries(seriesHandleVoltage);
//     chart4->addSeries(seriesLVDTVoltage);

//     chart4->addAxis(axisX, Qt::AlignBottom);
//     chart4->addAxis(axisY1, Qt::AlignLeft);
//     chart4->addAxis(axisY2, Qt::AlignRight);

//     // 关联系列和轴
//     seriesDisplacement->attachAxis(axisX);
//     seriesDisplacement->attachAxis(axisY1);
//     seriesCurrentA->attachAxis(axisX);
//     seriesCurrentA->attachAxis(axisY2);
//     seriesCurrentB->attachAxis(axisX);
//     seriesCurrentB->attachAxis(axisY2);
//     seriesHandleVoltage->attachAxis(axisX);
//     seriesHandleVoltage->attachAxis(axisY1);
//     seriesLVDTVoltage->attachAxis(axisX);
//     seriesLVDTVoltage->attachAxis(axisY1);

//     // 设置标题和图例
//     chart4->setTitle(QString("vID %1 数据趋势图").arg(vID));
//     chart4->legend()->setAlignment(Qt::AlignBottom);

//     // 为每个系列连接hovered信号
//     foreach (QLineSeries* series, allSeries) {
//         connect(series, &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
//             if (state) {
//                 // 找到最接近的实际数据点
//                 int closestIndex = 0;
//                 qreal minDistance = std::numeric_limits<qreal>::max();

//                 for (int i = 0; i < series->count(); ++i) {
//                     qreal distance = qAbs(series->at(i).x() - point.x());
//                     if (distance < minDistance) {
//                         minDistance = distance;
//                         closestIndex = i;
//                     }
//                 }

//                 // 获取最接近的数据点
//                 QPointF dataPoint = series->at(closestIndex);
//                 QDateTime timestamp = QDateTime::fromMSecsSinceEpoch(qint64(dataPoint.x()));

//                 // 构建提示信息
//                 QString unit = "";
//                 if (series == seriesDisplacement) unit = "mm";
//                 else if (series == seriesCurrentA || series == seriesCurrentB) unit = "mA";
//                 else unit = "mV";

//                 QString valueStr = (series == seriesDisplacement) ?
//                                        QString::number(dataPoint.y(), 'f', 2) :
//                                        QString::number(qRound(dataPoint.y()));

//                 QString tooltip = QString("时间: %1\n%2: %3%4")
//                                       .arg(timestamp.toString("hh:mm:ss.zzz"))
//                                       .arg(series->name())
//                                       .arg(valueStr)
//                                       .arg(unit);

//                 // 根据系列类型选择正确的数据行列表
//                 const QList<QStringList>* dataRows = nullptr;
//                 if (series == seriesDisplacement || series == seriesCurrentA || series == seriesCurrentB) {
//                     dataRows = &displacementRows;
//                 } else if (series == seriesHandleVoltage || series == seriesLVDTVoltage) {
//                     dataRows = &voltageRows;
//                 }

//                 // 如果找到了数据行列表且索引有效，则添加更多信息
//                 if (dataRows && closestIndex < dataRows->size()) {
//                     const QStringList &row = dataRows->at(closestIndex);

//                     // 添加位移/电流信息（针对位移系列）
//                     if (series == seriesDisplacement) {
//                         tooltip += QString("\nPWMA电流: %1mA\nPWMB电流: %2mA")
//                                        .arg(row[3])  // 假设row[3]是电流A
//                                        .arg(row[4]); // 假设row[4]是电流B
//                     }

//                     // 添加电压信息（针对电压系列）
//                     if (series == seriesHandleVoltage || series == seriesLVDTVoltage) {
//                         tooltip += QString("\n手柄电压: %1mV\n阀芯电压: %2mV")
//                                        .arg(row[5])  // 假设row[5]是手柄电压
//                                        .arg(row[6]); // 假设row[6]是阀芯电压
//                     }
//                 }

//                 // 显示工具提示
//                 QToolTip::showText(QCursor::pos(), tooltip, ui->graphicsView_4);
//             } else {
//                 QToolTip::hideText();
//             }
//         });
//     }

//     // 更新视图
//     ui->graphicsView_4->update();
// }

// void MainWindow::on_pushButton_3_clicked()
// {
//     QString vID = ui->comboBox_16->currentText(); // 获取vID（如"12"）

//     if (!frameDataMap.contains(vID)) {
//         QMessageBox::information(this, "提示", "没有选中的帧数据");
//         return;
//     }

//     const QList<QStringList> &allRows = frameDataMap[vID];
//     if (allRows.size() < 2) {
//         QMessageBox::information(this, "提示", "数据点不足，无法绘制图表");
//         return;
//     }

//     // 分离两种帧类型的数据
//     QList<QStringList> displacementRows;    // 0x180+vID帧（位移/电流）
//     QList<QStringList> voltageRows;         // 0x280+vID帧（电压）
//     for (const QStringList &row : allRows) {
//         QString frameId = row[1]; // 数据行中的完整帧ID
//         if (frameId.startsWith("0x000001")) {
//             displacementRows.append(row);
//         } else if (frameId.startsWith("0x000002")) {
//             voltageRows.append(row);
//         }
//     }

//     // 清空图表
//     chart4->removeAllSeries();
//     chart4->axes().clear();

//     // 创建系列
//     QLineSeries *seriesDisplacement = new QLineSeries();
//     seriesDisplacement->setName("阀芯位移(mm)");
//     QLineSeries *seriesCurrentA = new QLineSeries();
//     seriesCurrentA->setName("PWMA电流(mA)");
//     QLineSeries *seriesCurrentB = new QLineSeries();
//     seriesCurrentB->setName("PWMB电流(mA)");
//     QLineSeries *seriesHandleVoltage = new QLineSeries();
//     seriesHandleVoltage->setName("手柄输入电压(mV)");
//     QLineSeries *seriesLVDTVoltage = new QLineSeries();
//     seriesLVDTVoltage->setName("阀芯实际电压(mV)");

//     QList<QLineSeries*> allSeries = {seriesDisplacement, seriesCurrentA, seriesCurrentB,seriesHandleVoltage,seriesLVDTVoltage};

//     // 时间轴
//     QDateTimeAxis *axisX = new QDateTimeAxis();
//     axisX->setTitleText("时间");
//     axisX->setFormat("hh:mm:ss");
//     axisX->setTickCount(10);

//     // 双Y轴
//     QValueAxis *axisY1 = new QValueAxis(); // 位移/电压
//     axisY1->setTitleText("位移(mm)/电压(mV)");
//     axisY1->setLabelFormat("%d");
//     QValueAxis *axisY2 = new QValueAxis(); // 电流
//     axisY2->setTitleText("电流(mA)");
//     axisY2->setLabelFormat("%d");

//     // 计算时间范围和数据范围
//     QDateTime minTime, maxTime;
//     double minDisp = DBL_MAX, maxDisp = -DBL_MAX;
//     double minCurrent = DBL_MAX, maxCurrent = -DBL_MAX;
//     double minVoltage = DBL_MAX, maxVoltage = -DBL_MAX;

//     // 处理位移/电流数据
//     if (!displacementRows.isEmpty()) {
//         minTime = QDateTime::fromString(displacementRows.first()[0], "yyyy-MM-dd hh:mm:ss.zzz");
//         maxTime = QDateTime::fromString(displacementRows.last()[0], "yyyy-MM-dd hh:mm:ss.zzz");

//         for (const QStringList &row : displacementRows) {
//             QDateTime ts = QDateTime::fromString(row[0], "yyyy-MM-dd hh:mm:ss.zzz");
//             double disp = row[2].toDouble();
//             double currA = row[3].toDouble();
//             double currB = row[4].toDouble();

//             seriesDisplacement->append(ts.toMSecsSinceEpoch(), disp);
//             seriesCurrentA->append(ts.toMSecsSinceEpoch(), currA);
//             seriesCurrentB->append(ts.toMSecsSinceEpoch(), currB);

//             minDisp = qMin(minDisp, disp);
//             maxDisp = qMax(maxDisp, disp);
//             minCurrent = qMin(minCurrent, qMin(currA, currB));
//             maxCurrent = qMax(maxCurrent, qMax(currA, currB));
//         }
//     }

//     // 处理电压数据
//     if (!voltageRows.isEmpty()) {
//         if (minTime.isNull() || voltageRows.first()[0] < minTime.toString("yyyy-MM-dd hh:mm:ss.zzz")) {
//             minTime = QDateTime::fromString(voltageRows.first()[0], "yyyy-MM-dd hh:mm:ss.zzz");
//         }
//         if (maxTime.isNull() || voltageRows.last()[0] > maxTime.toString("yyyy-MM-dd hh:mm:ss.zzz")) {
//             maxTime = QDateTime::fromString(voltageRows.last()[0], "yyyy-MM-dd hh:mm:ss.zzz");
//         }

//         for (const QStringList &row : voltageRows) {
//             QDateTime ts = QDateTime::fromString(row[0], "yyyy-MM-dd hh:mm:ss.zzz");
//             QString handleVoltageStr = row[5];
//             handleVoltageStr.remove("mV");
//             double handleVoltage = handleVoltageStr.toDouble();

//             QString lvdtVoltageStr = row[6];
//             lvdtVoltageStr.remove("mV");
//             double lvdtVoltage = lvdtVoltageStr.toDouble();

//             seriesHandleVoltage->append(ts.toMSecsSinceEpoch(), handleVoltage);
//             seriesLVDTVoltage->append(ts.toMSecsSinceEpoch(), lvdtVoltage);

//             minVoltage = qMin(minVoltage, qMin(handleVoltage, lvdtVoltage));
//             maxVoltage = qMax(maxVoltage, qMax(handleVoltage, lvdtVoltage));
//         }
//     }

//     // 设置坐标轴范围
//     if (minTime.isValid() && maxTime.isValid()) {
//         axisX->setRange(minTime, maxTime);
//     }
//     axisY1->setRange(qMin(minDisp, minVoltage) * 0.95, qMax(maxDisp, maxVoltage) * 1.05);
//     axisY2->setRange(minCurrent * 0.95, maxCurrent * 1.05);

//     // 添加系列和轴
//     chart4->addSeries(seriesDisplacement);
//     chart4->addSeries(seriesCurrentA);
//     chart4->addSeries(seriesCurrentB);
//     chart4->addSeries(seriesHandleVoltage);
//     chart4->addSeries(seriesLVDTVoltage);

//     chart4->addAxis(axisX, Qt::AlignBottom);
//     chart4->addAxis(axisY1, Qt::AlignLeft);
//     chart4->addAxis(axisY2, Qt::AlignRight);

//     // 关联系列和轴
//     seriesDisplacement->attachAxis(axisX);
//     seriesDisplacement->attachAxis(axisY1);
//     seriesCurrentA->attachAxis(axisX);
//     seriesCurrentA->attachAxis(axisY2);
//     seriesCurrentB->attachAxis(axisX);
//     seriesCurrentB->attachAxis(axisY2);
//     seriesHandleVoltage->attachAxis(axisX);
//     seriesHandleVoltage->attachAxis(axisY1);
//     seriesLVDTVoltage->attachAxis(axisX);
//     seriesLVDTVoltage->attachAxis(axisY1);

//     // 设置标题和图例
//     chart4->setTitle(QString("vID %1 数据趋势图").arg(vID));
//     chart4->legend()->setAlignment(Qt::AlignBottom);



//     // 更新视图
//     ui->graphicsView_4->update();
// }



// void MainWindow::on_pushButton_3_clicked()
// {
//     QString frameId = ui->comboBox_16->currentText();

//     if (!frameDataMap.contains(frameId)) {
//         QMessageBox::information(this, "提示", "没有选中的帧数据");
//         return;
//     }

//     const QList<QStringList> &rows = frameDataMap[frameId];
//     if (rows.size() < 2) {
//         QMessageBox::information(this, "提示", "数据点不足，无法绘制图表");
//         return;
//     }

//     // 清空现有图表
//     chart4->removeAllSeries();
//     QList<QAbstractAxis *> axes = chart4->axes();
//     foreach (QAbstractAxis *axis, axes) {
//         chart4->removeAxis(axis);
//     }

//     // 创建数据系列
//     QLineSeries *seriesDisplacement = new QLineSeries();
//     seriesDisplacement->setName("阀芯位移(mm)");

//     QLineSeries *seriesCurrentA = new QLineSeries();
//     seriesCurrentA->setName("PWMA电流(mA)");

//     QLineSeries *seriesCurrentB = new QLineSeries();
//     seriesCurrentB->setName("PWMB电流(mA)");

//     // 存储系列指针以便后续使用
//     QList<QLineSeries*> allSeries = {seriesDisplacement, seriesCurrentA, seriesCurrentB};

//     // 时间轴
//     QDateTimeAxis *axisX = new QDateTimeAxis();
//     axisX->setTitleText("时间");
//     axisX->setFormat("hh:mm:ss");
//     axisX->setTickCount(10);

//     // 只使用一个Y轴
//     QValueAxis *axisY = new QValueAxis();
//     axisY->setTitleText("值"); // 通用标题，可根据实际情况修改
//     axisY->setLabelFormat("%d");

//     // 找到所有数据的共同范围
//     QDateTime minTime = QDateTime::fromString(rows.first()[0], "yyyy-MM-dd hh:mm:ss.zzz");
//     QDateTime maxTime = QDateTime::fromString(rows.last()[0], "yyyy-MM-dd hh:mm:ss.zzz");

//     double minValue = DBL_MAX, maxValue = -DBL_MAX;

//     // 添加数据点并计算共同范围
//     for (int i = 0; i < rows.size(); ++i) {
//         const QStringList &row = rows[i];
//         QDateTime timestamp = QDateTime::fromString(row[0], "yyyy-MM-dd hh:mm:ss.zzz");
//         qint64 timestampMs = timestamp.toMSecsSinceEpoch();

//         double disp = row[2].toDouble();
//         double currentA = row[3].toDouble();
//         double currentB = row[4].toDouble();

//         seriesDisplacement->append(timestampMs, disp);
//         seriesCurrentA->append(timestampMs, currentA);
//         seriesCurrentB->append(timestampMs, currentB);

//         // 更新共同范围
//         minValue = qMin(minValue, qMin(disp, qMin(currentA, currentB)));
//         maxValue = qMax(maxValue, qMax(disp, qMax(currentA, currentB)));
//     }

//     // 设置坐标轴范围（增加一些边距）
//     axisX->setRange(minTime, maxTime);
//     axisY->setRange(minValue * 0.95, maxValue * 1.05);

//     // 添加系列到图表
//     chart4->addSeries(seriesDisplacement);
//     chart4->addSeries(seriesCurrentA);
//     chart4->addSeries(seriesCurrentB);

//     // 设置坐标轴（只使用一个Y轴）
//     chart4->addAxis(axisX, Qt::AlignBottom);
//     chart4->addAxis(axisY, Qt::AlignLeft);

//     // 关联系列和坐标轴
//     seriesDisplacement->attachAxis(axisX);
//     seriesDisplacement->attachAxis(axisY);

//     seriesCurrentA->attachAxis(axisX);
//     seriesCurrentA->attachAxis(axisY);

//     seriesCurrentB->attachAxis(axisX);
//     seriesCurrentB->attachAxis(axisY);

//     // 设置图表标题
//     chart4->setTitle(QString("%1 数据趋势图").arg(frameId));

//     // 为每个系列连接hovered信号
//     foreach (QLineSeries* series, allSeries) {
//         connect(series, &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
//             if (state) {
//                 // 找到最接近的实际数据点
//                 int closestIndex = 0;
//                 qreal minDistance = std::numeric_limits<qreal>::max();

//                 for (int i = 0; i < series->count(); ++i) {
//                     qreal distance = qAbs(series->at(i).x() - point.x());
//                     if (distance < minDistance) {
//                         minDistance = distance;
//                         closestIndex = i;
//                     }
//                 }

//                 // 获取最接近的数据点
//                 QPointF dataPoint = series->at(closestIndex);
//                 QDateTime timestamp = QDateTime::fromMSecsSinceEpoch(qint64(dataPoint.x()));

//                 // 构建提示信息（根据系列类型显示不同单位）
//                 QString unit = series == seriesDisplacement ? "mm" : "mA";
//                 QString valueStr = series == seriesDisplacement ?
//                                        QString::number(dataPoint.y(), 'f', 2) :
//                                        QString::number(qRound(dataPoint.y()));

//                 QString tooltip = QString("时间: %1\n%2: %3%4")
//                                       .arg(timestamp.toString("hh:mm:ss.zzz"))
//                                       .arg(series->name())
//                                       .arg(valueStr)
//                                       .arg(unit);

//                 // 如果是位移系列，同时显示电流值
//                 if (series == seriesDisplacement && !rows.isEmpty() && closestIndex < rows.size()) {
//                     const QStringList &row = rows[closestIndex];
//                     tooltip += QString("\nPWMA电流: %1mA\nPWMB电流: %2mA")
//                                    .arg(row[3])
//                                    .arg(row[4]);
//                 }

//                 // 显示工具提示
//                 QToolTip::showText(QCursor::pos(), tooltip, ui->graphicsView_4);
//             } else {
//                 QToolTip::hideText();
//             }
//         });
//     }

//     // 更新图表视图
//     ui->graphicsView_4->update();
// }



void MainWindow::on_pushButton_19_clicked()
{
    // 选择数据文件
    QString filePath4 = QFileDialog::getOpenFileName(
        this,
        "选择数据文件",
        "./cantex/can原始数据",
        "文本文件 (*.txt);;所有文件 (*)"
        );

    if (filePath4.isEmpty()) {
        return;
    }

    // 初始化界面和数据结构
    ui->lineEdit_14->setText(filePath4);
    ui->comboBox_16->clear();
    ui->tableWidget->setRowCount(0);
    frameDataMap.clear(); // QMap<QString, QList<QStringList>>

    // 读取文件内容
    QFile file(filePath4);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    // 正则表达式匹配目标帧（0x00000180-0x000001FF 和 0x00000280-0x000002FF）
    QRegularExpression re(
        "(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3})\\s+接收\\s+"
        "(0x000001[89A-Fa-f][0-9A-Fa-f]|0x000002[89A-Fa-f][0-9A-Fa-f])\\s+"
        "(([0-9A-Fa-f]{2}\\s+){8})"
    );
    QRegularExpressionMatchIterator i = re.globalMatch(content);

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString timestamp = match.captured(1);
        QString frameId = match.captured(2);
        QString dataField = match.captured(3).trimmed();

        // 拆分8字节数据
        QStringList bytes = dataField.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
        if (bytes.size() != 8) {
            continue; // 过滤不完整帧
        }

        // 解析帧ID获取vID
        bool ok;
        uint frameIdValue = frameId.mid(2).toUInt(&ok, 16); // 转换为数值（如0x292）
        if (!ok) {
            continue;
        }

        uint base = (frameId.startsWith("0x000001")) ? 0x180 : 0x280;
        uint vID = (frameIdValue - base) & 0xFF; // 取低8位作为vID
        QString vIDStr = QString::number(vID, 16).toUpper(); // 转为十六进制字符串（如"12"）

        // 解析数据字段并存储原始单位（0.01mm）
        QStringList rowData;
        rowData << timestamp << frameId; // 时间戳 + 完整帧ID

        if (frameId.startsWith("0x000001")) {
            // 解析位移/电流帧（位移单位：0.01mm，电流单位：mA）
            ushort displacementRaw = (bytes[1].toUShort(&ok, 16) << 8) | bytes[0].toUShort(&ok, 16);
            rowData << QString::number(displacementRaw); // 原始值，单位0.01mm

            ushort currentA = (bytes[3].toUShort(&ok, 16) << 8) | bytes[2].toUShort(&ok, 16);
            rowData << QString::number(currentA); // mA

            ushort currentB = (bytes[5].toUShort(&ok, 16) << 8) | bytes[4].toUShort(&ok, 16);
            rowData << QString::number(currentB); // mA

            // 省略故障状态字段（保留关键数据）
            rowData << "---" << "---" << "---" << "---"; // 占位符
        } else if (frameId.startsWith("0x000002")) {
            // 解析电压帧（单位：mV）
            ushort aiInput = (bytes[1].toUShort(&ok, 16) << 8) | bytes[0].toUShort(&ok, 16);
            rowData << QString::number(aiInput) + "mV"; // 手柄电压


            ushort lvdtVoltage = (bytes[3].toUShort(&ok, 16) << 8) | bytes[2].toUShort(&ok, 16);
            rowData << QString::number(lvdtVoltage) + "mV"; // 阀芯电压


            rowData << "---" << "---" << "---" << "---"; // 占位符
        }

        // 存储数据（以vID为键）
        frameDataMap[vIDStr].append(rowData);
    }

    // 更新下拉框：显示唯一的vID列表
    QStringList uniqueVIDs = frameDataMap.keys();
    uniqueVIDs.sort();
    ui->comboBox_16->addItems(uniqueVIDs);

    if (uniqueVIDs.isEmpty()) {
        QMessageBox::information(this, "提示", "未找到符合条件的完整帧数据");
    } else {
        ui->comboBox_16->setCurrentIndex(0);
    }
}

void MainWindow::setupChart4()
{
    chart4 = new QChart();
    chart4->setTitle("数据趋势图");
    chart4->legend()->setVisible(true);
    chart4->legend()->setAlignment(Qt::AlignBottom);
    chart4->setAnimationOptions(QChart::AllAnimations);
    chart4->legend()->setAlignment(Qt::AlignTop);




    seriesDisp = new QLineSeries();
    seriesDisp->setName("阀芯位移(0.01mm)");

    seriesCurrA = new QLineSeries();
    seriesCurrA->setName("PWMA电流(mA)");

    seriesCurrB = new QLineSeries();
    seriesCurrB->setName("PWMB电流(mA)");

    seriesHVol = new QLineSeries();
    seriesHVol->setName("手柄电压(mV)");

    seriesLVolt = new QLineSeries();
    seriesLVolt->setName("阀芯电压(mV)");

    // 时间轴（X轴）
    axisX4 = new QDateTimeAxis();
    axisX4->setTitleText("时间");
    axisX4->setFormat("hh:mm:ss");
    axisX4->setTickCount(10);

    // 左Y轴（位移/电流，单位：0.01mm/mA）
    axisYLeft = new QValueAxis();
    axisYLeft->setTitleText("位移(0.01mm)/电流(mA)");
    axisYLeft->setLabelFormat("%d");

    // 右Y轴（电压，单位：mV）
    axisYRight = new QValueAxis();
    axisYRight->setTitleText("电压(mV)");
    axisYRight->setLabelFormat("%d");

    // 添加系列和轴
    chart4->addSeries(seriesDisp);
    chart4->addSeries(seriesCurrA);
    chart4->addSeries(seriesCurrB);
    chart4->addSeries(seriesHVol);
    chart4->addSeries(seriesLVolt);

    chart4->addAxis(axisX4, Qt::AlignBottom);
    chart4->addAxis(axisYLeft, Qt::AlignLeft);
    chart4->addAxis(axisYRight, Qt::AlignRight);

    // 关联系列到轴
    seriesDisp->attachAxis(axisX4);
    seriesDisp->attachAxis(axisYLeft);

    seriesCurrA->attachAxis(axisX4);
    seriesCurrA->attachAxis(axisYLeft);

    seriesCurrB->attachAxis(axisX4);
    seriesCurrB->attachAxis(axisYLeft);

    seriesHVol->attachAxis(axisX4);
    seriesHVol->attachAxis(axisYRight);

    seriesLVolt->attachAxis(axisX4);
    seriesLVolt->attachAxis(axisYRight);



    // // 设置图表视图
    ui->graphicsView_4->setChart(chart4);
    ui->graphicsView_4->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::on_pushButton_3_clicked()
{


    QString vID = ui->comboBox_16->currentText(); // 获取vID（如"12"）

    if (!frameDataMap.contains(vID)) {
        QMessageBox::information(this, "提示", "没有选中的帧数据");
        return;
    }

    const QList<QStringList> &allRows = frameDataMap[vID];
    if (allRows.size() < 2) {
        QMessageBox::information(this, "提示", "数据点不足，无法绘制图表");
        return;
    }

    // 分离位移/电流帧和电压帧
    QList<QStringList> dispCurrentRows; // 0x180+vID帧（位移/电流）
    QList<QStringList> voltageRows;      // 0x280+vID帧（电压）
    for (const QStringList &row : allRows) {
        if (row[1].startsWith("0x000001")) {
            dispCurrentRows.append(row);
        } else{
            voltageRows.append(row);
        }
    }

    chart4->removeAllSeries();
    foreach (QAbstractAxis* axis, chart4->axes()) {
        chart4->removeAxis(axis);
    }
    // chart4->legend()->hide();
    // chart4->setAnimationOptions(QChart::NoAnimation);
    chart4->legend()->setAlignment(Qt::AlignTop);





    // 创建系列（双Y轴：位移/电压左轴，电流右轴）
    QLineSeries *seriesDisp = new QLineSeries();
    seriesDisp->setName("阀芯位移(0.01mm)"); // 单位明确为0.01mm


    QLineSeries *seriesCurrA = new QLineSeries();
    seriesCurrA->setName("PWMA电流(mA)");


    QLineSeries *seriesCurrB = new QLineSeries();
    seriesCurrB->setName("PWMB电流(mA)");

    QLineSeries *seriesHVol = new QLineSeries();
    seriesHVol->setName("手柄电压(mV)");

    QLineSeries *seriesLVolt = new QLineSeries();
    seriesLVolt->setName("阀芯电压(mV)");

    // 时间轴（X轴）
    QDateTimeAxis *axisX4 = new QDateTimeAxis();
    axisX4->setTitleText("时间");
    axisX4->setFormat("hh:mm:ss");
    axisX4->setTickCount(10);

    // 左Y轴（位移/电压，单位：0.01mm/mV）
    QValueAxis *axisYLeft = new QValueAxis();
    axisYLeft->setTitleText("位移(0.01mm)/电流(mA)");
    axisYLeft->setLabelFormat("%d"); // 整数显示

    // 右Y轴（电流，单位：mA）
    QValueAxis *axisYRight = new QValueAxis();
    axisYRight->setTitleText("电压(mV)");
    axisYRight->setLabelFormat("%d");

    // 初始化数据范围
    QDateTime minTime;
    QDateTime maxTime;
    double minDisp = DBL_MAX, maxDisp = -DBL_MAX; // 位移原始值（0.01mm）
    double minVolt = DBL_MAX, maxVolt = -DBL_MAX; // 电压（mV）
    double minCurr = DBL_MAX, maxCurr = -DBL_MAX; // 电流（mA）

    // 处理位移/电流数据（位移为原始值，单位0.01mm）
    if (!dispCurrentRows.isEmpty()) {
        minTime = QDateTime::fromString(dispCurrentRows.first()[0], "yyyy-MM-dd hh:mm:ss.zzz");
        maxTime = QDateTime::fromString(dispCurrentRows.last()[0], "yyyy-MM-dd hh:mm:ss.zzz");

        for (const QStringList &row : dispCurrentRows) {
            QDateTime ts = QDateTime::fromString(row[0], "yyyy-MM-dd hh:mm:ss.zzz");
            double disp = row[2].toDouble(); // 原始值（如123表示1.23mm）
            double currA = row[3].toDouble();
            double currB = row[4].toDouble();

            seriesDisp->append(ts.toMSecsSinceEpoch(), disp);
            seriesCurrA->append(ts.toMSecsSinceEpoch(), currA);
            seriesCurrB->append(ts.toMSecsSinceEpoch(), currB);

            minDisp = qMin(minDisp, disp);
            maxDisp = qMax(maxDisp, disp);
            minCurr = qMin(minCurr, qMin(currA, currB));
            maxCurr = qMax(maxCurr, qMax(currA, currB));
        }
    }

    // 处理电压数据（单位：mV）
    if (!voltageRows.isEmpty()) {
        if (minTime.isNull()) {
            minTime = QDateTime::fromString(voltageRows.first()[0], "yyyy-MM-dd hh:mm:ss.zzz");
        }
        if (maxTime.isNull()) {
            maxTime = QDateTime::fromString(voltageRows.last()[0], "yyyy-MM-dd hh:mm:ss.zzz");
        }

        for (const QStringList &row : voltageRows) {
            QDateTime ts = QDateTime::fromString(row[0], "yyyy-MM-dd hh:mm:ss.zzz");
            QString hVolStr = row[2]; hVolStr.remove("mV");
            QString lVolStr = row[3]; lVolStr.remove("mV");
            double hVol = hVolStr.toDouble();
            double lVol = lVolStr.toDouble();

            seriesHVol->append(ts.toMSecsSinceEpoch(), hVol);
            seriesLVolt->append(ts.toMSecsSinceEpoch(), lVol);

            minVolt = qMin(minVolt, qMin(hVol, lVol));
            maxVolt = qMax(maxVolt, qMax(hVol, lVol));
        }
    }

    // 设置坐标轴范围
    if (minTime.isValid() && maxTime.isValid()) {
        axisX4->setRange(minTime, maxTime);
    }

    double minYLeft = qMin(minDisp, minCurr);
    double maxYLeft = qMax(maxDisp, maxCurr);
    axisYLeft->setRange(minYLeft * 0.95, maxYLeft * 1.05); // 5%边距

    // 左轴范围（位移原始值 + 电压）
    // double minYLeft = qMin(minDisp, minVolt);
    // double maxYLeft = qMax(maxDisp, maxVolt);
    // axisYLeft->setRange(minYLeft * 0.95, maxYLeft * 1.05); // 5%边距

    // 右轴范围（电流）
    axisYRight->setRange(minVolt * 0.95, maxVolt * 1.05);

    // 添加系列和轴
    chart4->addSeries(seriesDisp);
    chart4->addSeries(seriesCurrA);
    chart4->addSeries(seriesCurrB);
    chart4->addSeries(seriesHVol);
    chart4->addSeries(seriesLVolt);

    chart4->addAxis(axisX4, Qt::AlignBottom);
    chart4->addAxis(axisYLeft, Qt::AlignLeft);
    chart4->addAxis(axisYRight, Qt::AlignRight);


    seriesDisp->attachAxis(axisX4);
    seriesDisp->attachAxis(axisYLeft); // 位移左轴（0.01mm）

    seriesCurrA->attachAxis(axisX4);
    seriesCurrA->attachAxis(axisYLeft); // 电流右轴（mA）

    seriesCurrB->attachAxis(axisX4);
    seriesCurrB->attachAxis(axisYLeft); // 电流右轴（mA）

    seriesHVol->attachAxis(axisX4);
    seriesHVol->attachAxis(axisYRight); // 电压左轴（mV）

    seriesLVolt->attachAxis(axisX4);
    seriesLVolt->attachAxis(axisYRight); // 电压左轴（mV）

    // 设置图表标题
    // chart4->setTitle(QString("vID %1 数据趋势图").arg(vID));

    // 鼠标悬停提示（显示原始单位）
    QList<QLineSeries*> allSeries = {seriesDisp, seriesCurrA, seriesCurrB, seriesHVol, seriesLVolt};
    foreach (QLineSeries* series, allSeries) {
        connect(series, &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
            if (state) {
                // 查找最近数据点
                int closestIndex = 0;
                qreal minDist = std::numeric_limits<qreal>::max();
                for (int i = 0; i < series->count(); ++i) {
                    qreal dist = qAbs(series->at(i).x() - point.x());
                    if (dist < minDist) {
                        minDist = dist;
                        closestIndex = i;
                    }
                }

                QPointF dataPt = series->at(closestIndex);
                QDateTime ts = QDateTime::fromMSecsSinceEpoch(qint64(dataPt.x()));
                QString unit, valueStr, tooltip;

                // 设置单位和数值格式
                if (series == seriesDisp) {
                    unit = "0.01mm";
                    valueStr = QString::number(dataPt.y(), 'f', 0); // 整数显示
                    // 可选：添加换算后的mm值（如123 → 1.23mm）
                    tooltip = QString("时间: %1\n阀芯位移: %2 %3（%4mm）")
                              .arg(ts.toString("hh:mm:ss.zzz"))
                              .arg(valueStr)
                              .arg(unit)
                              .arg(dataPt.y() , 0, 'f', 2);//* 0.01
                } else if (series == seriesCurrA || series == seriesCurrB) {
                    unit = "mA";
                    valueStr = QString::number(qRound(dataPt.y())); // 电流取整
                    tooltip = QString("时间: %1\n%2: %3%4")
                              .arg(ts.toString("hh:mm:ss.zzz"))
                              .arg(series->name())
                              .arg(valueStr)
                              .arg(unit);
                } else {
                    unit = "mV";
                    valueStr = QString::number(qRound(dataPt.y())); // 电压取整
                    tooltip = QString("时间: %1\n%2: %3%4")
                              .arg(ts.toString("hh:mm:ss.zzz"))
                              .arg(series->name())
                              .arg(valueStr)
                              .arg(unit);
                }



                QToolTip::showText(QCursor::pos(), tooltip, ui->graphicsView_4);
            } else {
                QToolTip::hideText();
            }
        });
    }

    ui->graphicsView_4->update();
}


void MainWindow::on_pushButton_20_clicked()
{
    // 获取位移/电压轴（左Y轴）的输入值
    QString minText = ui->lineEdit_22->text();
    QString maxText = ui->lineEdit_23->text();

    // 验证输入是否为有效数字
    bool minOk, maxOk;
    double minValue = minText.toDouble(&minOk);
    double maxValue = maxText.toDouble(&maxOk);

    if (!minOk || !maxOk || minValue >= maxValue) {
        QMessageBox::warning(this, "输入错误", "请输入有效的位移/电压范围（最小值必须小于最大值）");
        return;
    }

    // 获取位移/电压轴（左Y轴）
    QList<QAbstractAxis*> yAxes = chart4->axes(Qt::Vertical);
    QValueAxis* axisYLeft = nullptr;

    foreach (QAbstractAxis* axis, yAxes) {
        QValueAxis* valueAxis = qobject_cast<QValueAxis*>(axis);
        if (valueAxis && valueAxis->titleText().contains("位移")) {
            axisYLeft = valueAxis;
            break;
        }
    }

    if (!axisYLeft) {
        qDebug() << "Error: 未找到位移/电压轴!";
        return;
    }

    // 设置新的Y轴范围并添加动画
    axisYLeft->setRange(minValue, maxValue);
    chart4->setAnimationOptions(QChart::SeriesAnimations);
    chart4->setAnimationDuration(500);

    ui->graphicsView_4->update();
}





void MainWindow::on_pushButton_21_clicked()
{
    // 获取电流轴（右Y轴）的输入值
    QString minText = ui->lineEdit_24->text();
    QString maxText = ui->lineEdit_25->text();

    // 验证输入是否为有效数字
    bool minOk, maxOk;
    double minValue = minText.toDouble(&minOk);
    double maxValue = maxText.toDouble(&maxOk);

    if (!minOk || !maxOk || minValue >= maxValue) {
        QMessageBox::warning(this, "输入错误", "请输入有效的电流范围（最小值必须小于最大值）");
        return;
    }

    // 获取电流轴（右Y轴）
    QList<QAbstractAxis*> yAxes = chart4->axes(Qt::Vertical);
    QValueAxis* axisYRight = nullptr;

    foreach (QAbstractAxis* axis, yAxes) {
        QValueAxis* valueAxis = qobject_cast<QValueAxis*>(axis);
        if (valueAxis && valueAxis->titleText().contains("电压")) {
            axisYRight = valueAxis;
            break;
        }
    }

    if (!axisYRight) {
        qDebug() << "Error: 未找到电压轴!";
        return;
    }

    // 设置新的Y轴范围并添加动画
    axisYRight->setRange(minValue, maxValue);
    chart4->setAnimationOptions(QChart::SeriesAnimations);
    chart4->setAnimationDuration(500);

    ui->graphicsView_4->update();
}





void MainWindow::on_openBt_clicked()
{


    qDebug() << "Open button clicked in thread:" << QThread::currentThread();

    // 解析串口参数
    QSerialPort::BaudRate baudrate = QSerialPort::Baud9600;
    switch (ui->baundrateCb->currentText().toInt()) {
    case 1200: baudrate = QSerialPort::Baud1200; break;
    case 4800: baudrate = QSerialPort::Baud4800; break;
    case 9600: baudrate = QSerialPort::Baud9600; break;
    case 38400: baudrate = QSerialPort::Baud38400; break;
    case 115200: baudrate = QSerialPort::Baud115200; break;
    }



    QSerialPort::DataBits databits = QSerialPort::Data8;
    switch (ui->dateCb->currentText().toInt()) {
    case 5: databits = QSerialPort::Data5; break;
    case 6: databits = QSerialPort::Data6; break;
    case 7: databits = QSerialPort::Data7; break;
    }

    QSerialPort::StopBits stopbits = QSerialPort::OneStop;
    if (ui->stopCb->currentText() == "1.5") {
        stopbits = QSerialPort::OneAndHalfStop;
    } else if (ui->stopCb->currentText() == "2") {
        stopbits = QSerialPort::TwoStop;
    }

    QSerialPort::Parity parity = QSerialPort::NoParity;
    if (ui->checkCb->currentText() == "偶校验") {
        parity = QSerialPort::EvenParity;
    } else if (ui->checkCb->currentText() == "奇校验") {
        parity = QSerialPort::OddParity;
    }

qDebug()<<666;
//if (!m_modbusThread) i
   if(ui->openBt->text() == tr("打开")){
       qDebug()<<6;
        isClosing=false;
        m_modbusThread = new QThread(this);
        m_modbusWorker = new ModbusWorker();
        m_modbusWorker->moveToThread(m_modbusThread);

        // 初始化流程
        connect(m_modbusThread, &QThread::started, m_modbusWorker, &ModbusWorker::initModbusDevice);

        // 初始化结果处理
        connect(m_modbusWorker, &ModbusWorker::initialized, this, [=](bool success) {
            if (!success) {
                QMessageBox::critical(this, "错误", "Modbus初始化失败");
                m_modbusThread->quit();
                return;
            }
            QMetaObject::invokeMethod(m_modbusWorker, [=]() {
                m_modbusWorker->setupModbusParameters(
                    ui->serialCb->currentText(),
                    baudrate,
                    databits,
                    stopbits,
                    parity
                );
            }, Qt::QueuedConnection);
        });

        // 参数设置结果处理
        connect(m_modbusWorker, &ModbusWorker::parametersSet, this, [=](bool success) {
            if (!success) {
                QMessageBox::critical(this, "错误", "参数设置失败");
                m_modbusThread->quit();
                return;
            }
            QMetaObject::invokeMethod(m_modbusWorker, &ModbusWorker::openSerialPort);
        });

        // 连接状态处理
        connect(m_modbusWorker, &ModbusWorker::connectionStateChanged, this, [=](bool connected) {
            qDebug()<<2;
            ui->openBt->setText(connected ? "断开连接" : "打开");
            QMessageBox::information(this, "提示", connected ? "连接成功" : "连接断开");
            if (connected) {
                // 连接成功后初始化UI状态
                ui->pushButton_22->setEnabled(true);
                ui->pushButton_23->setEnabled(true);
            }
        });

        // 错误处理
        connect(m_modbusWorker, &ModbusWorker::errorOccurred, this, [=](const QString &error) {
            ui->plainTextEdit_3->appendPlainText(QDateTime::currentDateTime().toString()
                                               + " [ERROR] " + error);
        });

        // 数据接收处理
        connect(m_modbusWorker, &ModbusWorker::dataReceived, this, &MainWindow::onDataReceived);
        connect(m_modbusWorker, &ModbusWorker::writeCompleted, this, &MainWindow::onWriteOperationCompleted);

        // 线程结束处理
        connect(m_modbusThread, &QThread::finished, m_modbusThread, &QObject::deleteLater);
        connect(m_modbusThread, &QThread::finished, m_modbusWorker, &QObject::deleteLater);

        m_modbusThread->start();
        ui->pushButton_22->setEnabled(true);
        ui->pushButton_23->setEnabled(true);
        ui->pushButton_23->setEnabled(true);
        ui->sendfaBt_4->setEnabled(true);
        ui->bautBt_2->setEnabled(true);
        ui->pushButton_24->setEnabled(true);
        ui->cycleBt_2->setEnabled(true);
        ui->cycleBt_3->setEnabled(true);
        ui->cycleBt_4->setEnabled(true);
        ui->cycleBt_5->setEnabled(true);
        ui->pushButton_27->setEnabled(true);
        ui->pushButton_28->setEnabled(true);
        ui->pushButton_29->setEnabled(true);
        ui->pushButton_22->setEnabled(true);
        ui->pushButton_32->setEnabled(true);
        issend=true;
    } else {
        isClosing = true;
        if (m_modbusWorker->isConnected()) {
            // QMetaObject::invokeMethod(m_modbusWorker, &ModbusWorker::closeSerialPort);
            // m_modbusThread->quit();
            // m_modbusThread->wait();
            // m_modbusThread = nullptr;
            // ui->openBt->setText("打开");
            // QMessageBox::information(this, "提示","连接断开");
            ui->pushButton_22->setEnabled(false);
            ui->pushButton_23->setEnabled(false);
            ui->pushButton_23->setEnabled(false);
            ui->sendfaBt_4->setEnabled(false);
            ui->bautBt_2->setEnabled(false);
            ui->pushButton_24->setEnabled(false);
            ui->cycleBt_2->setEnabled(false);
            ui->cycleBt_3->setEnabled(false);
            ui->cycleBt_4->setEnabled(false);
            ui->cycleBt_5->setEnabled(false);
            ui->pushButton_27->setEnabled(false);
            ui->pushButton_28->setEnabled(false);
            ui->pushButton_29->setEnabled(false);
            ui->pushButton_32->setEnabled(false);
            issend=false;
            // 停止所有定时器
            if (timer4 && timer4->isActive())
                timer4->stop();

            if (drawTimer && drawTimer->isActive())
                drawTimer->stop();

            if (modbusRequestTimer && modbusRequestTimer->isActive())
                modbusRequestTimer->stop();

            if (m_readTimer && m_readTimer->isActive())
                m_readTimer->stop();

            if (m_modbusWorker) {
                // 发送关闭请求
                QMetaObject::invokeMethod(m_modbusWorker, &ModbusWorker::closeSerialPort);

                // 等待一段时间让操作完成
                QEventLoop loop;
                QTimer::singleShot(500, &loop, &QEventLoop::quit);
                loop.exec();
            }
            qDebug()<<9;

            // 断开所有信号槽连接
            if (m_modbusWorker) {
                disconnect(m_modbusWorker, nullptr, this, nullptr);
            }
            qDebug()<<8;

            // 停止并释放Modbus线程
            if (m_modbusThread && m_modbusThread->isRunning()) {
                m_modbusThread->quit();
                m_modbusThread->wait();
            }
            qDebug()<<7;
            // 安全释放资源
            // if (m_modbusWorker) {
            //     delete m_modbusWorker;
            //     m_modbusWorker = nullptr;
            // }

            // if (m_modbusThread) {
            //     delete m_modbusThread;
            //     m_modbusThread = nullptr;
            // }
            qDebug()<<10;

            // 释放图表资源
            // if (qchart5) {
            //     delete qchart5;
            //     qchart5 = nullptr;
            // }
            return;
        }
    }

    for (int i = 10; i <= 1000; i += 10) {
            ui->comboBox_19->addItem(QString::number(i));
    }
    ui->comboBox_19->setCurrentIndex(1);
    timer4=new QTimer(this);
    connect(timer4,&QTimer::timeout,this,&MainWindow::RS485onTimerTimeout);


    // 初始化地址选择框
    initializeAddressCombobox(ui->comboBox_24, 0x01, 0x7F,false);
    initializeAddressCombobox(ui->comboBox_20, 0x01, 0x7F,false);
    initializeAddressCombobox(ui->comboBox_21, 0x01, 0x7F,false);
    // initializeAddressCombobox(ui->comboBox_28, 0x01, 0x7F,false);
    initializeAddressCombobox(ui->comboBox_18, 0x01, 0x7F, true);

    ui->comboBox_24->setCurrentIndex(15);
    // ui->comboBox_28->setCurrentIndex(15);

}

void MainWindow::initializeAddressCombobox(QComboBox *combobox, int min, int max, bool special)
{
    combobox->clear();
    for (int i = min; i <= max; ++i) {
        // QString hex = QString::number(i, 16).toUpper().rightJustified(2, '0');
        QString hex = QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
        QString text = hex;
        if (special && i == 0x7F) {
            text += " (全局配置)";
        }
        combobox->addItem(text, i);
    }
}





void MainWindow::onWriteOperationCompleted(quint16 address, quint16 value, bool success) {
    if(isClosing) return;
    QString status = success ? "成功" : "失败";
    switch (address) {
    case 0x3c:
        ui->plainTextEdit_3->appendPlainText("CANID设置成功");
        return;
    case 0x3D:
        ui->plainTextEdit_3->appendPlainText("CAN波特率设置成功");
        return;
    case 0x3E:
        ui->plainTextEdit_3->appendPlainText("CAN发送周期设置成功");
        return;
    case 0x3F:
        ui->plainTextEdit_3->appendPlainText("485主机ID设置成功");
        return;
    case 0x40:
        ui->plainTextEdit_3->appendPlainText("485从机ID设置成功");
        return;
    case 0x41:
        ui->plainTextEdit_3->appendPlainText("485波特率设置成功");
        return;
    default:
        break;
    }


    QString message = QString("【写操作】地址:0x%1 值:0x%2 状态:%3")
        .arg(address, 4, 16, QChar('0'))
        .arg(value, 4, 16, QChar('0'))
        .arg(status);

    ui->plainTextEdit_3->appendPlainText(message);

    if (success) {
        // 写成功后的UI更新（可选）
        // updateRegisterDisplay(address, value);
    }
}

void MainWindow::onDataReceived(quint16 address, const QVector<quint16> values) {
    if (isClosing || !m_modbusWorker) {modbusRequestTimer->stop();return;}
    // 记录接收时间
    QDateTime receiveTime = QDateTime::currentDateTime();

    if(ondata){
        // bool isChartData = false;

        // 加锁保护共享数据
        QMutexLocker locker(&dataMutex);

        // 处理图表相关寄存器
        if(address >= 0x44C && address <= 0x450) {
            // isChartData = true;
            for (int i = 0; i < values.size(); ++i) {
                quint16 regAddress = address + i;
                quint16 regValue = values[i];

                // 解析为图表数据（根据实际协议调整）
                switch(regAddress) {
                case 0x44C: // 位置值寄存器
                    latestData.position = static_cast<double>(regValue) ; // 示例转换
                    break;
                case 0x44D: // 电流A寄存器
                    latestData.currentA = static_cast<double>(regValue);
                    break;
                case 0x44E: // 电流B寄存器
                    latestData.currentB = static_cast<double>(regValue);
                    break;
                case 0x44F: // 电流B寄存器
                    latestData.lvdt = static_cast<double>(regValue);
                    break;
                case 0x450: // 电流B寄存器
                    latestData.er = static_cast<double>(regValue);
                    break;
                default:
                    break;
                }
            }
            latestData.timestamp = receiveTime;
            dataReady = true; // 标记新数据到达
            const qint64 elapsed = QDateTime::currentMSecsSinceEpoch() %ui->lineEdit_32->text().toInt();
            modbusRequestTimer->start(ui->lineEdit_32->text().toInt()- 50);
        }

    }
    if(address>=0x44C&&address<=0x450){
        for (int i = 0; i < values.size(); ++i) {
                quint16 regAddress = address + i;
                quint16 regValue = values[i];

                QString valueStr = QString("0x%1").arg(regValue, 4, 16, QChar('0'));
                QString parsedValue = parseRegisterValue(regAddress, regValue);

                QString regLog = QString("  - 寄存器 0x%1: 值=%2 (%3)")
                    .arg(regAddress, 4, 16, QChar('0'))
                    .arg(valueStr)
                    .arg(parsedValue);

                ui->plainTextEdit_3->appendPlainText(regLog);
            }
        ui->plainTextEdit_3->appendPlainText("");
        return;
        }










    for (int i = 0; i < values.size(); ++i) {
            quint16 regAddress = address + i;
            quint16 regValue = values[i];


            QString valueStr = QString("0x%1").arg(regValue, 4, 16, QChar('0'));
            QString parsedValue = parseRegisterValue(regAddress, regValue);

            QString regLog = QString("  - 寄存器 0x%1: 值=%2 %3")
                .arg(regAddress, 4, 16, QChar('0'))
                .arg(valueStr)
                .arg(receiveTime.toString("hh:mm:ss.zzz"));
            ui->plainTextEdit_3->appendPlainText(regLog);
        }
}


QString MainWindow::parseRegisterValue(quint16 address, quint16 value) {
    switch (address) {
        case 0x44C: // 阀芯位移
            return QString("%1 (0.01mm)").arg(static_cast<qint16>(value));

        case 0x44D: // PWMA电流
            return QString("%1 mA").arg(static_cast<qint16>(value));

        case 0x44E: // PWMB电流
            return QString("%1 mA").arg(static_cast<qint16>(value));

        case 0x44F: // 故障码
            if(value==0){
                return QString("LVDT异常");
            }else if(value==1){
                return QString("PWMA电流反馈异常");
            }else if(value==2){
                return QString("PWMB电流反馈异常");
            }

        case 0x450: // LVDT状态
            return (value == 0) ? "有LVDT" : "无LVDT";

        default:
            return "未知寄存器";
    }
}

















void MainWindow::on_pushButton_22_clicked()
{
    // 从输入框获取参数
    QString startAddrStr = ui->lineEdit_27->text().trimmed();
    QString quantityStr = ui->lineEdit_26->text().trimmed();

    // 校验起始地址（十六进制格式，如"0x1234"或"1234"）
    bool ok;
    quint16 startAddress = startAddrStr.toUInt(&ok, 16); // 按十六进制解析
    if (!ok || startAddress > 0xFFFF) {
        QMessageBox::warning(this, "错误", "起始地址格式错误（需为十六进制数）");
        return;
    }

    // 校验读取数量（1-125）
    quint16 quantity = quantityStr.toUInt(&ok);
    if (!ok || quantity < 1 || quantity > 125) {
        QMessageBox::warning(this, "错误", "读取数量需为1-125的整数");
        return;
    }

    if (m_modbusWorker) {
            m_modbusWorker->requestReadRegisters(startAddress, quantity, ui->comboBox_24->currentData().toInt());
            displayModbusRequest(startAddress, quantity,true);
            // 显示写操作正在进行
            // QString message = QString("【发送读请求】地址:0x%1 读写数量:0x%2")
            //     .arg(startAddress, 4, 16, QChar('0'))
            //     .arg(quantity, 4, 16, QChar('0'));
            // ui->plainTextEdit_3->appendPlainText(message);
        }
}



void MainWindow::displayModbusRequest(quint16 startAddress, quint16 quantity, bool isRead) {
    // 从站地址
    quint8 slaveAddress = ui->comboBox_24->currentData().toInt();
    // 功能码
    quint8 functionCode = isRead ? 0x03 : 0x06;

    // 构建请求数据（不含CRC校验）
    QByteArray requestData;
    requestData.append(slaveAddress);
    requestData.append(functionCode);
    requestData.append(static_cast<char>((startAddress >> 8) & 0xFF)); // 起始地址高字节
    requestData.append(static_cast<char>(startAddress & 0xFF));        // 起始地址低字节

    if (isRead) {
        // 读请求：添加读取数量
        requestData.append(static_cast<char>((quantity >> 8) & 0xFF));  // 数量高字节
        requestData.append(static_cast<char>(quantity & 0xFF));         // 数量低字节
    } else {
        // 写请求：添加写入值
        requestData.append(static_cast<char>((quantity >> 8) & 0xFF));  // 值高字节
        requestData.append(static_cast<char>(quantity & 0xFF));         // 值低字节
    }

    // 计算CRC校验（Modbus RTU特有）
    quint16 crc = calculateModbusCRC(requestData);
    requestData.append(static_cast<char>(crc & 0xFF));         // CRC低字节
    requestData.append(static_cast<char>((crc >> 8) & 0xFF));  // CRC高字节

    // 转换为十六进制字符串并显示
    QString hexData = requestData.toHex(' ').toUpper();
    QString operation = isRead ? "读" : "写";
    QString displayText = QString("发送%1请求 (RTU帧):\n%2\n\n")
                              .arg(operation)
                              .arg(hexData);

    // 在发送框中追加显示
    ui->plainTextEdit_3->appendPlainText(displayText);
}








quint16 MainWindow::calculateModbusCRC(const QByteArray &data)
{
    quint16 crc = 0xFFFF;
    for (char byte : data) {
        crc ^= static_cast<quint8>(byte);
        for (int i = 0; i < 8; ++i) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}


void MainWindow::on_pushButton_23_clicked()
{
    QString addrStr = ui->lineEdit_29->text().trimmed();
    QString valueStr = ui->lineEdit_28->text().trimmed();

    // 校验寄存器地址（十六进制格式）
    bool ok;
    quint16 address = addrStr.toUInt(&ok, 16); // 按十六进制解析
    if (!ok || address > 0xFFFF) {
        QMessageBox::warning(this, "错误", "寄存器地址格式错误（需为十六进制数）");
        return;
    }

    quint16 value;

    value = valueStr.toUInt(&ok,16);

    if (!ok || value > 0xFFFF) {
        QMessageBox::warning(this, "错误", "写入值格式错误（需为0-65535的整数）");
        return;
    }
    if (m_modbusWorker) {
            m_modbusWorker->requestWriteRegister(address, value, ui->comboBox_24->currentData().toInt());
            displayModbusRequest(address, value,false);

            // 显示写操作正在进行
            // QString message = QString("【发送写请求】地址:0x%1 值:0x%2")
            //     .arg(address, 4, 16, QChar('0'))
            //     .arg(value, 4, 16, QChar('0'));
            // ui->plainTextEdit_3->appendPlainText(message);
        }
}




void MainWindow::on_bautBt_2_clicked()
{
    // 1. 获取 ComboBox 选中的波特率值

    quint16 baudValue = ui->comboBox_17->currentIndex();
    quint16 baudValue1 = ui->comboBox_17->currentData().toInt();


    // 2. 寄存器地址为 0x3D（CAN_BPS 寄存器）
    quint16 registerAddress = 0x3D; // 协议中 CAN_BPS 的地址
    displayModbusRequest(registerAddress, baudValue,false);

    if (m_modbusWorker) {
            m_modbusWorker->requestWriteRegister(registerAddress, baudValue,ui->comboBox_24->currentData().toInt());
            ui->plainTextEdit_3->appendPlainText(
                QString("【发送】设置CAN波特率为 %1 kbps ")//(寄存器0x%2=0x%3)
                .arg(baudValue1)
                // .arg(registerAddress, 4, 16, QChar('0'))
                // .arg(baudValue, 4, 16, QChar('0'))
            );
        } else {
            QMessageBox::warning(this, "错误", "Modbus工作线程未初始化");
        }
}


void MainWindow::on_pushButton_24_clicked()
{

    quint16 CANIDValue = ui->comboBox_18->currentData().toInt();

    quint16 registerAddress = 0x3C;
    displayModbusRequest(registerAddress, CANIDValue,false);


    if (m_modbusWorker) {
            m_modbusWorker->requestWriteRegister(registerAddress, CANIDValue,ui->comboBox_24->currentData().toInt());
            ui->plainTextEdit_3->appendPlainText(
                QString("【发送】设置CANID为 %1 ")//(寄存器0x%2=0x%3)
                .arg(CANIDValue)

            );
        } else {
            QMessageBox::warning(this, "错误", "Modbus工作线程未初始化");
        }
}


void MainWindow::on_cycleBt_2_clicked()
{

    quint16 CANtimeValue = ui->comboBox_19->currentIndex()+1;
    quint16 CANtimeValue1 = ui->comboBox_19->currentData().toInt();



    quint16 registerAddress = 0x3E;
    displayModbusRequest(registerAddress, CANtimeValue, false);


    if (m_modbusWorker) {
            m_modbusWorker->requestWriteRegister(registerAddress, CANtimeValue,ui->comboBox_24->currentData().toInt());
            ui->plainTextEdit_3->appendPlainText(
                QString("【发送】设置CAN周期为 %1 ms")//(寄存器0x%2=0x%3)
                .arg(CANtimeValue1)

            );
        } else {
            QMessageBox::warning(this, "错误", "Modbus工作线程未初始化");
        }
}


void MainWindow::on_cycleBt_3_clicked()
{

    quint16 mainIDValue = ui->comboBox_20->currentData().toInt();



    quint16 registerAddress = 0x3F;
    displayModbusRequest(registerAddress, mainIDValue,false);
    if (m_modbusWorker) {
            m_modbusWorker->requestWriteRegister(registerAddress, mainIDValue,ui->comboBox_24->currentData().toInt());
            ui->plainTextEdit_3->appendPlainText(
                QString("【发送】设置主机ID %1 ")//(寄存器0x%2=0x%3)
                .arg(mainIDValue)

            );
        } else {
            QMessageBox::warning(this, "错误", "Modbus工作线程未初始化");
        }
}


void MainWindow::on_cycleBt_4_clicked()
{

    bool ok;
    quint16 slaveIDValue = ui->comboBox_21->currentData().toUInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "错误", "无效的波特率值");
        return;
    }


    quint16 registerAddress = 0x40;
    displayModbusRequest(registerAddress, slaveIDValue,false);

    if (m_modbusWorker) {
            m_modbusWorker->requestWriteRegister(registerAddress, slaveIDValue,ui->comboBox_24->currentData().toInt());
            ui->plainTextEdit_3->appendPlainText(
                QString("【发送】设置从机ID %1 ")//(寄存器0x%2=0x%3)
                .arg(slaveIDValue)

            );
        } else {
            QMessageBox::warning(this, "错误", "Modbus工作线程未初始化");
        }
}


void MainWindow::on_cycleBt_5_clicked()
{
    quint16 modbaudValue = ui->comboBox_22->currentIndex();
    quint16 modbaudValue1 = ui->comboBox_22->currentData().toInt();


    quint16 registerAddress = 0x41;
    displayModbusRequest(registerAddress, modbaudValue,false);
    if (m_modbusWorker) {
            m_modbusWorker->requestWriteRegister(registerAddress, modbaudValue,ui->comboBox_24->currentData().toInt());
            ui->plainTextEdit_3->appendPlainText(
                QString("【发送】设置485波特率 %1 Kbps")
                .arg(modbaudValue1)

            );
        } else {
            QMessageBox::warning(this, "错误", "Modbus工作线程未初始化");
        }

}













// void MainWindow::on_pushButton_25_clicked()
// {
//     m_readTimer->start(1000);

// }

// void MainWindow::readAllRegisters()
// {

//     if (!m_modbusWorker) return;
//         quint8 slaveId = ui->comboBox_24->currentData().toUInt(); // 获取从机ID
//         m_modbusWorker->requestReadRegisters(0x44C, 5, slaveId);

//     // 分5次读取，每次读取一个寄存器
//     // readHoldingRegisters(0x3C, 1); // 读取第1个寄存器
//     // readHoldingRegisters(0x3D, 1); // 读取第2个寄存器
//     // readHoldingRegisters(0x3E, 1); // 读取第3个寄存器
//     // readHoldingRegisters(0x3F, 1); // 读取第4个寄存器
//     // readHoldingRegisters(0x40, 1); // 读取第5个寄存器
// }



void MainWindow::initChart1()
{

    // 创建通用字体设置
    QFont font;
    font.setFamily("SimHei");  // 中文字体支持
    font.setPointSize(10);     // 字体大小


        qchart5 = new QChart();
        ui->graphicsView_6->setChart(qchart5);
        ui->graphicsView_6->setRenderHint(QPainter::Antialiasing); // 设置抗锯齿
        qchart5->setAnimationOptions(QChart::AllAnimations);
        ui->graphicsView_6->setRubberBand(QChartView::RectangleRubberBand);



        // 创建三条线
        QLineSeries *series0 = new QLineSeries;
        QLineSeries *series1 = new QLineSeries;
        QLineSeries *series2 = new QLineSeries;

        // 设置名字
        series0->setName("阀芯位移值");
        series1->setName("PWMA电流反馈值");
        series2->setName("PWMB电流反馈值");

        // 把线条放到chart里
        qchart5->addSeries(series0);
        qchart5->addSeries(series1);
        qchart5->addSeries(series2);

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

        QValueAxis *axisY3 = new QtCharts::QValueAxis();
        axisY3->setTitleText("PWMB电流值");//QObject::tr()
        axisY3->setTitleBrush(QBrush(QColorConstants::Svg::orange));

        // 设置 Y 轴轴线颜色
        axisY3->setLinePen(QPen(QColorConstants::Svg::orange));
        axisY3->setRange(0, 1000);
        axisY3->setTickCount(6);
        axisY3->setLabelFormat("%d");


        // 应用到标签
        axisY3->setLabelsFont(font);



        // 将坐标轴添加到图表
        qchart5->addAxis(axisX, Qt::AlignBottom);
        qchart5->addAxis(axisY, Qt::AlignLeft);
        qchart5->addAxis(axisY2, Qt::AlignRight);
        qchart5->addAxis(axisY3, Qt::AlignRight);

        //将系列绑定到坐标轴
        series0->attachAxis(axisX);
        series0->attachAxis(axisY);
        series1->attachAxis(axisX);
        series1->attachAxis(axisY2);
        series2->attachAxis(axisX);
        series2->attachAxis(axisY3);

        // 启用阴影效果
        qchart5->setDropShadowEnabled(true);


        qchart5->setMargins(QMargins(5, 5, 5, 5));

        // 清空列表（如果需要）
        yAxes5.clear();

        // 使用 append() 添加元素
        yAxes5.append(axisY);
        yAxes5.append(axisY2);
        yAxes5.append(axisY3);


        drawTimer = new QTimer(this);
        drawTimer->setInterval(ui->lineEdit_32->text().toInt()); // 严格200ms绘图间隔
        drawTimer->setTimerType(Qt::PreciseTimer);

        modbusRequestTimer = new QTimer(this);
        modbusRequestTimer->setSingleShot(true);
        modbusRequestTimer->setTimerType(Qt::PreciseTimer);
        initializeAddressCombobox(ui->comboBox_23, 0x01, 0x7F,false);
        ui->comboBox_23->setCurrentIndex(15);
        connect(drawTimer, &QTimer::timeout, this, &MainWindow::processChartData);
        connect(modbusRequestTimer, &QTimer::timeout, this,[this]{
            m_modbusWorker->requestReadRegisters(0x44c, 5, ui->comboBox_23->currentData().toInt());
        });

        connect(series0, &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
            if (state) {
                // 使用二分法查找最接近的点
                int closestIndex = 0;
                qreal targetX = point.x();
                int count = series0->count();

                if (count == 0) return;

                // 二分查找第一个大于等于targetX的点
                int left = 0, right = count - 1;
                while (left < right) {
                    int mid = left + (right - left) / 2;
                    if (series0->at(mid).x() >= targetX) {
                        right = mid;
                    } else {
                        left = mid + 1;
                    }
                }

                // 检查找到的点及其前一个点，取更接近的一个
                closestIndex = left;
                if (closestIndex > 0) {
                    qreal distCurrent = qAbs(series0->at(closestIndex).x() - targetX);
                    qreal distPrev = qAbs(series0->at(closestIndex - 1).x() - targetX);
                    if (distPrev < distCurrent) {
                        closestIndex--;
                    }
                }

                // 获取选中点的数据
                QDateTime ts = QDateTime::fromMSecsSinceEpoch(qint64(series0->at(closestIndex).x()));
                qreal measureValue = series0->at(closestIndex).y();

                // 构建提示信息
                QString tooltip = QString("时间：%1\n位移量: %2 (%3mm) ")
                                      .arg(ts.toString("hh:mm:ss.zzz"))
                                      .arg(measureValue)
                                      .arg(measureValue/10);

                // 显示提示信息
                QToolTip::showText(QCursor::pos(), tooltip, ui->graphicsView_6);
            } else {
                QToolTip::hideText();
            }
        });

        connect(series1, &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
            if (state) {
                // 使用二分法查找最接近的点
                int closestIndex = 0;
                qreal targetX = point.x();
                int count = series1->count();

                if (count == 0) return;

                // 二分查找第一个大于等于targetX的点
                int left = 0, right = count - 1;
                while (left < right) {
                    int mid = left + (right - left) / 2;
                    if (series1->at(mid).x() >= targetX) {
                        right = mid;
                    } else {
                        left = mid + 1;
                    }
                }

                // 检查找到的点及其前一个点，取更接近的一个
                closestIndex = left;
                if (closestIndex > 0) {
                    qreal distCurrent = qAbs(series1->at(closestIndex).x() - targetX);
                    qreal distPrev = qAbs(series1->at(closestIndex - 1).x() - targetX);
                    if (distPrev < distCurrent) {
                        closestIndex--;
                    }
                }

                // 获取选中点的数据
                QDateTime ts = QDateTime::fromMSecsSinceEpoch(qint64(series1->at(closestIndex).x()));
                qreal measureValue = series1->at(closestIndex).y();

                // 构建提示信息
                QString tooltip = QString("时间：%1\nPWMA电流: %2 (%3mA) ")
                                      .arg(ts.toString("hh:mm:ss.zzz"))
                                      .arg(measureValue)
                                      .arg(measureValue);

                // 显示提示信息
                QToolTip::showText(QCursor::pos(), tooltip, ui->graphicsView_6);
            } else {
                QToolTip::hideText();
            }
        });


        connect(series2, &QLineSeries::hovered, this, [=](const QPointF &point, bool state) {
            if (state) {
                // 使用二分法查找最接近的点
                int closestIndex = 0;
                qreal targetX = point.x();
                int count = series2->count();

                if (count == 0) return;

                // 二分查找第一个大于等于targetX的点
                int left = 0, right = count - 1;
                while (left < right) {
                    int mid = left + (right - left) / 2;
                    if (series2->at(mid).x() >= targetX) {
                        right = mid;
                    } else {
                        left = mid + 1;
                    }
                }

                // 检查找到的点及其前一个点，取更接近的一个
                closestIndex = left;
                if (closestIndex > 0) {
                    qreal distCurrent = qAbs(series2->at(closestIndex).x() - targetX);
                    qreal distPrev = qAbs(series2->at(closestIndex - 1).x() - targetX);
                    if (distPrev < distCurrent) {
                        closestIndex--;
                    }
                }

                // 获取选中点的数据
                QDateTime ts = QDateTime::fromMSecsSinceEpoch(qint64(series2->at(closestIndex).x()));
                qreal measureValue = series2->at(closestIndex).y();

                // 构建提示信息
                QString tooltip = QString("时间：%1\nPWMB电流: %2 (%3mA) ")
                                      .arg(ts.toString("hh:mm:ss.zzz"))
                                      .arg(measureValue)
                                      .arg(measureValue);

                // 显示提示信息
                QToolTip::showText(QCursor::pos(), tooltip, ui->graphicsView_6);
            } else {
                QToolTip::hideText();
            }
        });

        ui->lineEdit_30->setText("0");
        ui->lineEdit_31->setText("1000");
        ui->lineEdit_32->setText("200");
        ui->lineEdit_33->setText("3");

        ui->pushButton_22->setEnabled(false);
        ui->pushButton_23->setEnabled(false);
        ui->pushButton_23->setEnabled(false);
        ui->sendfaBt_4->setEnabled(false);
        ui->bautBt_2->setEnabled(false);
        ui->pushButton_24->setEnabled(false);
        ui->cycleBt_2->setEnabled(false);
        ui->cycleBt_3->setEnabled(false);
        ui->cycleBt_4->setEnabled(false);
        ui->cycleBt_5->setEnabled(false);
        ui->pushButton_27->setEnabled(false);
        ui->pushButton_28->setEnabled(false);
        ui->pushButton_29->setEnabled(false);
        ui->pushButton_32->setEnabled(false);






}

// void MainWindow::ReData_Slot(){



//     if (!isDrawing) {
//         return; // 如果没有在绘图，直接返回
//     }



//     QDateTime currentTime = QDateTime::currentDateTime();
//     uint duration = ui->lineEdit_33->text().toUInt() * 60;
//     if (startTime.secsTo(currentTime) >= duration) {
//         isDrawing = false; // 达到绘图时长，标记停止绘图
//         time1->stop(); // 停止定时器
//         return;
//     }
//     readAllRegisters();
//     // DisplayChart1();

//     saveDataToFile();

//     if(er==0){
//         ui->label_3->setText("LDVT异常");
//     }else if(er==1){
//         ui->label_3->setText("PWMA异常");
//     }else if(er==2){
//         ui->label_3->setText("PWMB异常");
//     }
//     if(hasLVDT==0){
//         ui->label_5->setText("有LVDT");
//     }else if(hasLVDT==1){
//         ui->label_5->setText("无LVDT");
//     }

//     position = 0;

//     currentA = 0;
//     currentB = 0;
//     er = 0;
//     hasLVDT = 0;


// }



void MainWindow::appendToFile(const QString& message)
{
    QFile file(fileName);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << "]"
            << " " << message << "\n";
        file.close();
    }
}

void MainWindow::clearCharts()
{
    QChart *qchart = ui->graphicsView_6->chart();
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

bool validateLineEditInput1(QLineEdit *lineEdit,  const QString &errorTitle = "输入错误") {//int minValue, int maxValue,
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



void MainWindow::on_pushButton_27_clicked()
{
    ondata=true;


    if (hasActiveSession && isPaused) {
        // 计算本次暂停的时长并累加到总暂停时间
        pauseDuration += pauseStartTime.msecsTo(QDateTime::currentDateTime());
        drawTimer->start();
        modbusRequestTimer->start(ui->lineEdit_32->text().toInt()-30);

        // 恢复图表数据
        QChart *chart1 = ui->graphicsView_6->chart();
        if (chart1 && chart1->series().size() >= 3) {
            qobject_cast<QLineSeries*>(chart1->series().at(0))->replace(savedSeries0Data);
            qobject_cast<QLineSeries*>(chart1->series().at(1))->replace(savedSeries1Data);
            qobject_cast<QLineSeries*>(chart1->series().at(2))->replace(savedSeries2Data);
        }
        isPaused = false;
        isDrawing = true;
        return;
    }

    if (!hasActiveSession || (!isDrawing && !isPaused)) {
        // 检查是否需要继续之前的会话
        if (!fileName.isEmpty() && QFile::exists(fileName)) {
            // 恢复之前的会话
            activeSessionFileName = fileName;
            fileName = activeSessionFileName;

            // 恢复图表数据
            QChart *chart1 = ui->graphicsView_6->chart();
            if (chart1 && chart1->series().size() >= 3) {
                qobject_cast<QLineSeries*>(chart1->series().at(0))->replace(savedSeries0Data);
                qobject_cast<QLineSeries*>(chart1->series().at(1))->replace(savedSeries1Data);
                qobject_cast<QLineSeries*>(chart1->series().at(2))->replace(savedSeries2Data);
            }
        }else {
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
            appendToFile(QString("阀设备：%1").arg(ui->comboBox_23->currentText().toInt()));

            // 记录会话开始时间
            sessionStartTime = QDateTime::currentDateTime();
            pauseDuration = 0;

            // 清除图表（全新会话）
            clearCharts();
        }

        xAxisRangeSet1 = false;
        xAxisRangeSet2 = false;


        // if (!(validateLineEditInput1(ui->lineEdit_32) && validateLineEditInput1(ui->lineEdit_33) )) {//&&validateLineEditInput1(ui->lineEdit_14) && validateLineEditInput1(ui->lineEdit)
        //     QMessageBox::warning(this, "输入错误", "绘图周期和绘图时间不能为空");
        //     drawTimer->stop();
        //     modbusRequestTimer->stop();
        //     return;
        // }

        // // 验证输入
        // if (!(validateLineEditInput1(ui->lineEdit_30) && validateLineEditInput1(ui->lineEdit_31) &&
        //       validateLineEditInput1(ui->lineEdit_32) && validateLineEditInput1(ui->lineEdit_33))) {
        //     // time1->stop();



        //     return;
        // }

        // if (ui->lineEdit_30->text().toInt() >= ui->lineEdit_31->text().toInt()) {
        //     QMessageBox::warning(this, "输入错误", "起始量程应该小于结束量程。");
        //     // time1->stop();
        //     drawTimer->stop();
        //     modbusRequestTimer->stop();


        //     return;
        // }

        // 开始绘图
        isDrawing = true;
        isPaused = false;
        hasActiveSession = true;
        drawTimer->start();
        modbusRequestTimer->start(ui->lineEdit_32->text().toInt()-30);
        qDebug()<<10;
        // time1->setInterval(ui->lineEdit->text().toInt());
        // time1->start();
        appendToFile("System started!");
}
}

void MainWindow::on_pushButton_28_clicked()
{
    if (isDrawing && !isPaused) {
        // 保存当前图表数据
        QChart *chart1 = ui->graphicsView_6->chart();
        if (chart1 && chart1->series().size() >= 3) {
            savedSeries0Data = qobject_cast<QLineSeries*>(chart1->series().at(0))->points();
            savedSeries1Data = qobject_cast<QLineSeries*>(chart1->series().at(1))->points();
            savedSeries2Data = qobject_cast<QLineSeries*>(chart1->series().at(2))->points();
        }



        // 记录暂停开始时间
        pauseStartTime = QDateTime::currentDateTime();


        drawTimer->stop();
        modbusRequestTimer->stop();
        ondata=false;

        isPaused = true;
        isDrawing = false;
        appendToFile("System paused!");
    }
}


void MainWindow::on_pushButton_29_clicked()
{
    // 停止当前会话
    if (isDrawing || isPaused) {

        drawTimer->stop();
        modbusRequestTimer->stop();


        // 保存最后数据
        if (isDrawing) {

            appendToFile("System restarted!");
        }

        isDrawing = false;
        isPaused = false;
        hasActiveSession = false;
    }

    if (!(validateLineEditInput1(ui->lineEdit_32) && validateLineEditInput1(ui->lineEdit_33) )) {//&&validateLineEditInput1(ui->lineEdit_14) && validateLineEditInput1(ui->lineEdit)
        QMessageBox::warning(this, "输入错误", "绘图周期和绘图时间不能为空");

        return;
    }



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
    appendToFile("> System restarted!");
    appendToFile("----------------------------------------------------------");
    appendToFile(QString("阀设备：%1").arg(ui->comboBox_23->currentText().toInt()));

    // 记录会话开始时间
    sessionStartTime = QDateTime::currentDateTime();
    pauseDuration = 0;
    ondata=true;

    // 清除图表
    clearCharts();

    // 连接信号并开始定时器



    drawTimer->start();
    modbusRequestTimer->start(ui->lineEdit_32->text().toInt()-30);

    // 重置图表状态
    xAxisRangeSet1 = false;


    // 验证输入


    // 开始绘图
    isDrawing = true;
    isPaused = false;
    hasActiveSession = true;

    // time1->setInterval(ui->lineEdit->text().toInt());
    // time1->start();
}




// 新增数据处理函数
void MainWindow::processChartData() {

    QDateTime currentTime = QDateTime::currentDateTime();
    uint duration = ui->lineEdit_33->text().toUInt() * 60;
    if (sessionStartTime.secsTo(currentTime) >= duration) {
        isDrawing = false; // 达到绘图时长，标记停止绘图
        drawTimer->stop();
        modbusRequestTimer->stop();
        ondata=false;
        return;
    }

    if(!dataReady) return;


    QMutexLocker locker(&dataMutex);

    // 更新界面显示
    ui->label_70->setText(QString::number(latestData.er));
    ui->label_72->setText(QString::number(latestData.lvdt));
    ui->label_74->setText(QString::number(latestData.position));
    ui->label_76->setText(QString::number(latestData.currentA));
    ui->label_78->setText(QString::number(latestData.currentB));

    // ui->label_76->setText(QString::number(latestData.currentA, 'f', 2));
    // ui->label_78->setText(QString::number(latestData.currentB, 'f', 2));

    // 更新图表
    QChart *chart1 = ui->graphicsView_6->chart();
    if(chart1 && chart1->series().size() >= 3) {
        QLineSeries* series0 = qobject_cast<QLineSeries*>(chart1->series().at(0));
        QLineSeries* series1 = qobject_cast<QLineSeries*>(chart1->series().at(1));
        QLineSeries* series2 = qobject_cast<QLineSeries*>(chart1->series().at(2));

        if(ui->checkBox_10->isChecked() && series0) {
            series0->append(latestData.timestamp.toMSecsSinceEpoch(), latestData.position);
        }
        if(ui->checkBox_11->isChecked() && series1) {
            series1->append(latestData.timestamp.toMSecsSinceEpoch(), latestData.currentA);
        }
        if(ui->checkBox_12->isChecked() && series2) {
            series2->append(latestData.timestamp.toMSecsSinceEpoch(), latestData.currentB);
        }

        // 自动滚动X轴
        if(!xAxisRangeSet1){
            QDateTimeAxis *xAxis = qobject_cast<QDateTimeAxis*>(chart1->axes(Qt::Horizontal).first());
            if(xAxis) {
                qint64 visibleDuration = ui->lineEdit_33->text().toInt() * 60 * 1000; // 分钟转毫秒
                xAxis->setRange(latestData.timestamp,latestData.timestamp.addMSecs(visibleDuration));
            }
            xAxisRangeSet1=true;
        }

    }

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);

            // out.setCodec("UTF-8");
            QDateTime now = QDateTime::currentDateTime();
            out << now.toString("yyyy-MM-dd hh:mm:ss.zzz") << "  "
                << QString("阀芯位移值: %1").arg(latestData.position)
                <<QString(", PWMA: %1").arg(latestData.currentA)
                <<QString(", PWMB: %1").arg(latestData.currentB)
                <<QString(", er: %1").arg(er)
                <<QString(", isLVDT: %1").arg(hasLVDT)
                <<QString(", 外部模拟量: %1").arg(0)
                <<QString(", LVDT反馈电压: %1").arg(0)
                << "\n";
            file.close();
        }
    }

    dataReady = false; // 重置数据就绪标志

}






void MainWindow::saveDataToFile()
{
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);

            // out.setCodec("UTF-8");
            QDateTime now = QDateTime::currentDateTime();
            out << now.toString("yyyy-MM-dd hh:mm:ss.zzz") << "  "
                << QString("阀芯位移值: %1").arg(position)
                <<QString(", PWMA: %1").arg(currentA)
                <<QString(", PWMB: %1").arg(currentB)
                <<QString(", er: %1").arg(er)
                <<QString(", isLVDT: %1").arg(hasLVDT)
                <<QString(", 外部模拟量: %1").arg(0)
                <<QString(", LVDT反馈电压: %1").arg(0)
                << "\n";

            file.close();
        }
    }
}


void MainWindow::on_sendfaBt_4_clicked()
{
    bool ok;
    if(ui->checkBox_20->isChecked()){
        startValue1 = ui->lineEdit_51->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "起始值必须是整数！");
            return;
        }

        // 获取结束值
        endValue1 = ui->lineEdit_55->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "结束值必须是整数！");
            return;
        }
    }else if(ui->checkBox_21->isChecked()){
        startValue1 = ui->lineEdit_50->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "起始值必须是整数！");
            return;
        }

        // 获取结束值
        endValue1 = ui->lineEdit_56->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "结束值必须是整数！");
            return;
        }
    }else if(ui->checkBox_19->isChecked()){
        startValue1 = ui->lineEdit_52->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "起始值必须是整数！");
            return;
        }

        // 获取结束值
        endValue1 = ui->lineEdit_57->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "警告", "结束值必须是整数！");
            return;
        }
    }
    // // 检查起始值是否小于结束值
    increasing1 = (startValue1 <= endValue1);
    // qDebug()<<increasing1;
    // if (!increasing1 && valueStep1 > 0) {
    //     valueStep1 = -valueStep1;  // 如果是递减，步长应为负数
    // }

    // 获取发送间隔（毫秒）
    sendInterval1 = ui->lineEdit_54->text().toInt(&ok);
    if (!ok || sendInterval1 <= 0) {
        QMessageBox::warning(this, "警告", "发送间隔必须是大于0的整数！");
        return;
    }

    totalStepCycles1=sendInterval1/200;

    // 获取步长
    int step = ui->lineEdit_53->text().toInt(&ok);
    if (!ok ) {
        // QMessageBox::warning(this, "警告", "步长必须是非零整数！");|| step == 0
        return;
    }

    // 设置步长，确保方向正确
    if ((increasing1 && step < 0) || (!increasing1 && step > 0)) {
        valueStep1 = -step;
    } else {
        valueStep1 = step;
    }



    currentValue1 = startValue1;
    stepCycleCount1 = 0;
    isStepChanging1 = true;

    ui->sendfaBt_4->setStyleSheet(
            "QPushButton {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #1cbf5e, stop:0.5 #0caa49, stop:1 #089c40);"
            "   color: white;"
            "   border: 1px solid #066f2d;"
            "   border-radius: 5px;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #1fd36a, stop:0.5 #0fc252, stop:1 #0ab144);"
            "}"
            "QPushButton:pressed {"
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                stop:0 #0a8a3a, stop:0.5 #097d33, stop:1 #066f2d);"
            "   padding-top: 11px;"
            "   padding-bottom: 9px;"
            "}"
        );



    // 启动定时器
    timer4->start(200);
    ui->plainTextEdit_3->appendPlainText(
        QString("开始发送：从%1到%2，初始步长%3，每200ms发送，%4秒后切换步长")
            .arg(startValue1).arg(endValue1).arg(valueStep1).arg(sendInterval1/1000));
}


void MainWindow::RS485sendCurrentValue()
{
    int controlAddress=0x3EA;
    int countAddress=0x3E8;
    int value;




    // 根据选中的CheckBox设置数据（保持原有逻辑）
    if (ui->checkBox_20->isChecked()) {
        value = 0x0;
    } else if (ui->checkBox_21->isChecked()) {
        value = 0x1;
    } else if (ui->checkBox_19->isChecked()) {
        value = 0x2;
    } else {
        return;
    }
    static bool a=0;
    if (m_modbusWorker){
        if(a==0){
            m_modbusWorker->requestWriteRegister(controlAddress, value,ui->comboBox_24->currentData().toInt());
            a=1;
        }
        m_modbusWorker->requestWriteRegister(countAddress, currentValue1,ui->comboBox_24->currentData().toInt());
        ui->plainTextEdit_3->appendPlainText(
            QString("发送值：%1")
                .arg(currentValue1));
        // displayModbusRequest(registerAddress, slaveIDValue,false);

    }






    // 更新当前值（仅在非切换阶段更新，避免重复计算）
    if (!isStepChanging1) {
        currentValue1 += valueStep1;
        isStepChanging1=true;
    }
}




void MainWindow::RS485onTimerTimeout()
{

    // if (isStepChanging) return;  // 防止切换时重复处理

    // 发送当前值
    RS485sendCurrentValue();
    stepCycleCount1++;  // 记录已发送的200ms周期数

    // 检查是否达到6秒（30个周期），切换步长
    if (stepCycleCount1 >= totalStepCycles1) {
        // isStepChanging = true;  // 锁定切换过程

        // 示例：步长值翻倍（可自定义为固定列表或其他逻辑）
        // valueStep *= 2;
        stepCycleCount1 = 0;  // 重置周期计数器
        // ui->plainTextEdit->appendPlainText(
        //     QString("步长切换：新步长%1，继续发送")
        //         .arg(valueStep));

        isStepChanging1 = false;  // 解锁
    }

    // 边界检查：到达结束值时停止
    if ((increasing1 && currentValue1 > endValue1) ||
        (!increasing1 && currentValue1 < endValue1)) {
        timer4->stop();
        ui->sendfaBt_4->setStyleSheet("QPushButton { font-size: 24px; }");
        ui->plainTextEdit_3->appendPlainText("发送完成：已达到目标范围");
    }


}

void MainWindow::on_pushButton_32_clicked()
{
    timer4->stop();
}


void MainWindow::on_pushButton_33_clicked()
{
    ui->plainTextEdit_3->clear();
}


QPair<int, int> MainWindow::getAxisAndChartIndex(const QString& optionText)
{
    // 图表索引：0 表示第一个图表，1 表示第二个图表
    // Y轴索引：根据不同图表和线条对应
    if (optionText == "阀芯位移值") {
        return QPair<int, int>(0, 0);
    } else if (optionText == "PWMA电流反馈值") {
        return QPair<int, int>(0, 1);
    } else if (optionText == "PWMB电流反馈值") {
        return QPair<int, int>(0, 2);
    }
    return QPair<int, int>(-1, -1); // 表示未找到对应的选项
}


void MainWindow::on_pushButton_26_clicked()
{
    QString selectedText = ui->comboBox_25->currentText();

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
    int min = ui->lineEdit_30->text().toInt();
    int max = ui->lineEdit_31->text().toInt();

    if (min >= max) {
        QMessageBox::warning(this, "输入错误", "最小值必须小于最大值");
        return;
    }

    // 更新对应的Y轴
    QValueAxis* targetAxis = nullptr;

    if (chartIndex == 0) {
        if (axisIndex < 3) targetAxis = yAxes5[axisIndex];
    }

    if (targetAxis) {
        targetAxis->setRange(min, max);
        // appendToFile(QString("调整 %1 量程为: %2 - %3").arg(selectedText).arg(min).arg(max));
    }
}




void MainWindow::on_tabWidget_currentChanged(int index)
{
    const int targetIndex = 4; // 请替换为你需要打开文档的标签页索引

        // 仅当切换到目标标签页时执行打开操作
        if (index == targetIndex){
            qDebug()<<QDir::currentPath();
            QString filePath = "./阀控板上位机使用说明.docx"; // 替换为实际文件路径

                // 检查文件是否存在
                if (!QFile::exists(filePath)) {
                    QMessageBox::warning(this, "错误", "文件不存在！");
                    return;
                }

                // 调用系统默认程序打开
                if (!QDesktopServices::openUrl(QUrl::fromLocalFile(filePath))) {
                    QMessageBox::critical(this, "错误", "无法打开文件！\n请检查文件格式或安装相关程序。");
                }
        }

}

