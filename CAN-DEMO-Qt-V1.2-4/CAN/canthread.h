#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QThread>
#include "windows.h"
#include "PCANBasic.h"
#include "ControlCAN.h"
#include <QDebug>

// 定义设备类型枚举
enum CAN_Device_Type {
    DEVICE_CONTROLCAN = 0,
    DEVICE_PCAN
};

class CANThread : public QThread
{
    Q_OBJECT
public:
    explicit CANThread(QObject *parent = nullptr);
    ~CANThread();

    void stop();

    // 设备操作接口
    bool openDevice(CAN_Device_Type deviceType, UINT deviceIndex, UINT channel, UINT baudRate);
    bool initCAN();
    bool startCAN();
    bool reSetCAN();
    void closeDevice();

    // 数据发送接口
    bool sendData(UINT channel, UINT ID, BYTE remoteFlag, BYTE externFlag, const unsigned char *data, BYTE len);

signals:
    void getProtocolData(VCI_CAN_OBJ *vco, DWORD dwRel, UINT channel);
    void dataSent(VCI_CAN_OBJ *vco);
    void boardInfo(VCI_BOARD_INFO vbi);
    void pcanError(TPCANStatus status);

protected:
    void run() override;

private:
    void sleep(int msec);
    TPCANBaudrate convertToPcanBaudrate(UINT baudRate);

    bool stopped;

    // 设备通用参数
    CAN_Device_Type m_deviceType;
    UINT m_deviceIndex;
    UINT m_baudRate;

    // ControlCAN专用
    VCI_INIT_CONFIG m_vic;

    // PCAN专用
    TPCANHandle m_pcanChannel;
    TPCANBaudrate m_pcanBaudrate;
};

#endif // CANTHREAD_H
