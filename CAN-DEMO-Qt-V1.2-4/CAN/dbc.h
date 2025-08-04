#ifndef DBC_H
#define DBC_H

#include <QWidget>
#include <QTableWidget>
#include <qdatetime.h>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include "canthread.h"


namespace Ui {
class DBC;
}

class DBC : public QWidget
{
    Q_OBJECT

public:
    explicit DBC(CANThread *canthread= nullptr,QWidget *parent = nullptr);
    ~DBC();

    void setupUI();
    void checkTimeoutFrames();
    void onSpecificIdDataReceived(VCI_CAN_OBJ *vci, unsigned int dwRel, unsigned int channel);
    void onDataSent(VCI_CAN_OBJ *vci);
    // void onOpenButtonClicked(unsigned int frameId);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DBC *ui;
    // QMap<unsigned int, int> frameIdToRow;
    CANThread *canthread1;
    QMap<unsigned int, QDateTime> lastReceiveTime;
    // QMap<unsigned int, QDateTime> lastReceiveTime; // 记录最后接收时间
    QMap<unsigned int, int> frameIdToRow;           // 帧ID到行号的映射
    QTimer* checkTimer;

};

#endif // DBC_H
