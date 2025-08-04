#include "dbc.h"
#include "ui_dbc.h"

DBC::DBC(CANThread *canthread,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DBC)
    ,canthread1(canthread)
{
    ui->setupUi(this);
    resize(800, 400);
    setupUI();
    checkTimer = new QTimer(this);
    connect(checkTimer, &QTimer::timeout, this, &DBC::checkTimeoutFrames);
    checkTimer->start(500);
}

DBC::~DBC()
{
    delete ui;
    if (canthread1) {
        disconnect(canthread1, &CANThread::getProtocolData, this, &DBC::onSpecificIdDataReceived);
    }
}


void DBC::setupUI()
{
    QStringList listHeader;
    listHeader << "帧ID" << "周期" << "帧数"  << "操作"<< "帧数据";

    ui->tableWidget->setColumnCount(listHeader.count());
    ui->tableWidget->setHorizontalHeaderLabels(listHeader);

    ui->tableWidget->setColumnWidth(0, 150);  // 帧ID
    ui->tableWidget->setColumnWidth(1, 100);   // 周期
    ui->tableWidget->setColumnWidth(2, 100);   // 帧数
    ui->tableWidget->setColumnWidth(3, 100);  // 帧数据
    ui->tableWidget->setColumnWidth(4, 220);   // 操作

    connect(canthread1, &CANThread::getProtocolData, this, &DBC::onSpecificIdDataReceived);
    connect(canthread1, &CANThread::dataSent, this, &DBC::onDataSent);
}

void DBC::onDataSent(VCI_CAN_OBJ *vci)
{
    if (!vci) return; // 检查指针有效性

    unsigned int frameId = vci->ID;

    // 构建数据字符串
    QString dataStr;
    for (int j = 0; j < 8; ++j) {
        dataStr += QString("%1 ").arg(vci->Data[j], 2, 16, QChar('0')).toUpper();
    }

    QDateTime currentTime = QDateTime::currentDateTime();
    QString cycleStr;

    // 计算周期（与接收逻辑相同）
    if (lastReceiveTime.contains(frameId)) {
        qint64 cycleMs = lastReceiveTime[frameId].msecsTo(currentTime);
        cycleStr = QString("%1ms").arg(cycleMs);
    } else {
        cycleStr = "N/A";
    }
    lastReceiveTime[frameId] = currentTime;

    // 更新表格显示（与接收逻辑相同）
    if (frameIdToRow.contains(frameId)) {
        int row = frameIdToRow[frameId];

        // 更新周期、帧数和数据
        ui->tableWidget->item(row, 1)->setText(cycleStr);
        int count = ui->tableWidget->item(row, 2)->text().toInt() + 1;
        ui->tableWidget->item(row, 2)->setText(QString::number(count));
        ui->tableWidget->item(row, 4)->setText(dataStr);

        // 恢复行颜色（如果超时）
        QBrush originalBrush = QBrush(QColor(220, 255, 220));
        QBrush grayBrush = QBrush(QColor(220, 220, 220));

        QTableWidgetItem* firstItem = ui->tableWidget->item(row, 0);
        if (firstItem && firstItem->background() == grayBrush) {
            for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                QTableWidgetItem* item = ui->tableWidget->item(row, col);
                if (item) {
                    item->setBackground(originalBrush);
                }
            }
        }
    } else {
        // 新增行
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        // 设置帧ID、周期、帧数、方向和数据
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString("0x%1").arg(frameId, 8, 16, QChar('0')).toUpper()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(cycleStr));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem("1"));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem("发送")); // 标记为"发送"
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(dataStr));

        frameIdToRow[frameId] = row;

        // 设置初始行颜色为绿色
        QBrush greenBrush = QBrush(QColor(220, 255, 220));
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            QTableWidgetItem* item = ui->tableWidget->item(row, col);
            if (item) {
                item->setBackground(greenBrush);
            }
        }
    }
}


void DBC::checkTimeoutFrames()
{
    QDateTime currentTime = QDateTime::currentDateTime();

    // 遍历所有已记录的帧ID
    for (auto it = lastReceiveTime.begin(); it != lastReceiveTime.end(); ++it) {
        unsigned int frameId = it.key();
        QDateTime lastTime = it.value();

        // 如果超过1秒未接收
        if (lastTime.msecsTo(currentTime) > 1000) {
            // 检查行是否存在
            if (frameIdToRow.contains(frameId)) {
                int row = frameIdToRow[frameId];

                // 设置整行为灰色
                for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                    QTableWidgetItem* item = ui->tableWidget->item(row, col);
                    if (item) {
                        item->setBackground(QBrush(QColor(220, 220, 220)));
                    }
                }
            }
        } else {
            // 如果行之前是灰色，恢复正常
            if (frameIdToRow.contains(frameId)) {
                int row = frameIdToRow[frameId];

                QBrush originalBrush = QBrush(QColor(220, 255, 220)); // 初始绿色背景色
                QBrush grayBrush = QBrush(QColor(220, 220, 220));

                // 检查第一列的背景色是否为灰色
                QTableWidgetItem* firstItem = ui->tableWidget->item(row, 0);
                if (firstItem && firstItem->background() == grayBrush) {
                    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                        QTableWidgetItem* item = ui->tableWidget->item(row, col);
                        if (item) {
                            item->setBackground(originalBrush); // 恢复为绿色
                        }
                    }
                }
            }
        }
    }
}

// 数据接收处理函数
void DBC::onSpecificIdDataReceived(VCI_CAN_OBJ *vci, unsigned int dwRel, unsigned int channel)
{
    for (unsigned int i = 0; i < dwRel; ++i) {
        unsigned int frameId = vci[i].ID;

        QString dataStr;
        for (int j = 0; j < 8; ++j) {
            dataStr += QString("%1 ").arg(vci[i].Data[j], 2, 16, QChar('0')).toUpper();
        }

        QDateTime currentTime = QDateTime::currentDateTime();
        QString cycleStr;

        if (lastReceiveTime.contains(frameId)) {
            qint64 cycleMs = lastReceiveTime[frameId].msecsTo(currentTime);
            cycleStr = QString("%1ms").arg(cycleMs);
        } else {
            cycleStr = "N/A";
        }
        lastReceiveTime[frameId] = currentTime;

        if (frameIdToRow.contains(frameId)) {
            int row = frameIdToRow[frameId];

            // 更新周期
            ui->tableWidget->item(row, 1)->setText(cycleStr);

            // 更新帧数计数
            int count = ui->tableWidget->item(row, 2)->text().toInt() + 1;
            ui->tableWidget->item(row, 2)->setText(QString::number(count));

            // 更新数据
            ui->tableWidget->item(row, 4)->setText(dataStr);

            // 恢复行颜色（如果之前是灰色）
            QBrush originalBrush = QBrush(QColor(220, 255, 220)); // 初始绿色背景色
            QBrush grayBrush = QBrush(QColor(220, 220, 220));

            QTableWidgetItem* firstItem = ui->tableWidget->item(row, 0);
            if (firstItem && firstItem->background() == grayBrush) {
                for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                    QTableWidgetItem* item = ui->tableWidget->item(row, col);
                    if (item) {
                        item->setBackground(originalBrush); // 恢复为绿色
                    }
                }
            }
        } else {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);

            // 设置帧ID
            QTableWidgetItem *idItem = new QTableWidgetItem(QString("0x%1").arg(frameId, 8, 16, QChar('0')).toUpper());
            ui->tableWidget->setItem(row, 0, idItem);

            // 设置周期
            QTableWidgetItem *cycleItem = new QTableWidgetItem(cycleStr);
            ui->tableWidget->setItem(row, 1, cycleItem);

            // 设置帧数 (初始为1)
            QTableWidgetItem *countItem = new QTableWidgetItem("1");
            ui->tableWidget->setItem(row, 2, countItem);

            QTableWidgetItem *dirItem = new QTableWidgetItem("接收");
            ui->tableWidget->setItem(row, 3, dirItem);

            // 设置数据
            QTableWidgetItem *dataItem = new QTableWidgetItem(dataStr);
            ui->tableWidget->setItem(row, 4, dataItem);

            frameIdToRow[frameId] = row;

            // 设置初始行颜色为绿色
            QBrush greenBrush = QBrush(QColor(220, 255, 220));
            for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                QTableWidgetItem* item = ui->tableWidget->item(row, col);
                if (item) {
                    item->setBackground(greenBrush);
                }
            }
        }
    }
}





void DBC::on_pushButton_clicked()
{
    ui->tableWidget->clear();
}

