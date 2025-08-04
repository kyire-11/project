#include "canthread.h"
#include <QTime>
#include <QCoreApplication>
#include <QMetaType>

CANThread::CANThread(QObject *parent) : QThread(parent)
{
    stopped = false;
    m_deviceType = DEVICE_CONTROLCAN; // 默认使用ControlCAN
}

CANThread::~CANThread()
{
    closeDevice();
}

void CANThread::stop()
{
    stopped = true;
}

// 波特率转换函数
TPCANBaudrate CANThread::convertToPcanBaudrate(UINT baudRate)
{
    switch (baudRate) {
    case 1000: return PCAN_BAUD_1M;
    case 500:  return PCAN_BAUD_500K;
    case 250:  return PCAN_BAUD_250K;
    case 125:  return PCAN_BAUD_125K;
    case 100:  return PCAN_BAUD_100K;
    case 50:   return PCAN_BAUD_50K;
    case 20:   return PCAN_BAUD_20K;
    case 10:   return PCAN_BAUD_10K;
    default:   return PCAN_BAUD_500K; // 默认500K
    }
}




// bool CANThread::openDevice(CAN_Device_Type deviceType, UINT deviceIndex, UINT channel, UINT baudRate)
// {
//     m_deviceType = deviceType;
//     m_deviceIndex = deviceIndex;
//     m_baudRate = baudRate;

//     if (m_deviceType == DEVICE_CONTROLCAN) {
//         // ControlCAN 设备
//         UINT k=4;
//         DWORD dwRel = VCI_OpenDevice(k, m_deviceIndex, 0);
//         if(dwRel != 1) {
//             qDebug() << "ControlCAN: 打开设备失败";
//             return false;
//         }
//         qDebug() << "ControlCAN: 打开设备成功";
//         return true;
//     }
//     else if (m_deviceType == DEVICE_PCAN) {
//         // PCAN 设备
//         m_pcanChannel = static_cast<TPCANHandle>(channel);
//         m_pcanBaudrate = convertToPcanBaudrate(baudRate);

//         // 调试输出
//         qDebug() << "尝试初始化PCAN通道:" << m_pcanChannel;
//         qDebug() << "波特率值:" << baudRate << "转换后的PCAN波特率:" << m_pcanBaudrate;

//         TPCANStatus status = CAN_Initialize(
//             m_pcanChannel,
//             m_pcanBaudrate,
//             0, 0, 0
//             );

//         if(status != PCAN_ERROR_OK) {
//             // 获取错误信息文本
//             char errorText[256];
//             CAN_GetErrorText(status, 0x09, errorText);

//             qDebug() << "PCAN: 初始化失败，错误码:" << status
//                      << "错误信息:" << errorText;

//             // 获取当前可用的PCAN通道列表
//             qDebug() << "可用PCAN通道列表:";
//             for(int i = 0; i < 16; i++) {
//                 TPCANStatus checkStatus = CAN_Initialize(
//                     static_cast<TPCANHandle>(i),
//                     PCAN_BAUD_500K,
//                     0, 0, 0
//                     );
//                 if(checkStatus == PCAN_ERROR_OK) {
//                     qDebug() << "通道" << i << "可用";
//                     CAN_Uninitialize(static_cast<TPCANHandle>(i));
//                 } else {
//                     qDebug() << "通道" << i << "不可用，错误码:" << checkStatus;
//                 }
//             }

//             emit pcanError(status);
//             return false;
//         }

//         qDebug() << "PCAN: 初始化成功";
//         return true;
//     }

//     return false;
// }








// 1. 打开设备
bool CANThread::openDevice(CAN_Device_Type deviceType, UINT deviceIndex, UINT channel, UINT baudRate)
{
    m_deviceType = deviceType;
    m_deviceIndex = deviceIndex;
    m_baudRate = baudRate;

    if (m_deviceType == DEVICE_CONTROLCAN) {
        // ControlCAN 设备
        UINT k=4;
        DWORD dwRel = VCI_OpenDevice(k, m_deviceIndex, 0);
        if(dwRel != 1) {
            qDebug() << "ControlCAN: 打开设备失败";
            return false;
        }
        qDebug() << "ControlCAN: 打开设备成功";
        return true;
    }
    else if (m_deviceType == DEVICE_PCAN) {

        m_pcanChannel = static_cast<TPCANHandle>(channel);
        m_pcanBaudrate = convertToPcanBaudrate(baudRate);

        TPCANStatus status = CAN_Initialize(
            m_pcanChannel,
            m_pcanBaudrate,
            0, 0, 0
            );

        if(status != PCAN_ERROR_OK) {
            qDebug() << "PCAN: 初始化失败，错误码:" << status;
            emit pcanError(status);
            return false;
        }




        qDebug() << "PCAN: 初始化成功";
        return true;
    }

    return false;
}

// 2. 初始化CAN
bool CANThread::initCAN()
{
    if (m_deviceType == DEVICE_CONTROLCAN) {
        // ControlCAN 初始化
        UINT k=4;
        DWORD dwRel = VCI_ClearBuffer(k,m_deviceIndex,  0);
        dwRel = VCI_ClearBuffer(k,m_deviceIndex, 1);

        m_vic.AccCode = 0x80000008;
        m_vic.AccMask = 0xFFFFFFFF;
        m_vic.Filter = 1;
        m_vic.Mode = 0;

        switch (m_baudRate) {
        case 10:  m_vic.Timing0 = 0x31; m_vic.Timing1 = 0x1c; break;
        case 20:  m_vic.Timing0 = 0x18; m_vic.Timing1 = 0x1c; break;
        case 40:  m_vic.Timing0 = 0x87; m_vic.Timing1 = 0xff; break;
        case 50:  m_vic.Timing0 = 0x09; m_vic.Timing1 = 0x1c; break;
        case 80:  m_vic.Timing0 = 0x83; m_vic.Timing1 = 0xff; break;
        case 100: m_vic.Timing0 = 0x04; m_vic.Timing1 = 0x1c; break;
        case 125: m_vic.Timing0 = 0x03; m_vic.Timing1 = 0x1c; break;
        case 200: m_vic.Timing0 = 0x81; m_vic.Timing1 = 0xfa; break;
        case 250: m_vic.Timing0 = 0x01; m_vic.Timing1 = 0x1c; break;
        case 400: m_vic.Timing0 = 0x80; m_vic.Timing1 = 0xfa; break;
        case 500: m_vic.Timing0 = 0x00; m_vic.Timing1 = 0x1c; break;
        case 666: m_vic.Timing0 = 0x80; m_vic.Timing1 = 0xb6; break;
        case 800: m_vic.Timing0 = 0x00; m_vic.Timing1 = 0x16; break;
        case 1000:m_vic.Timing0 = 0x00; m_vic.Timing1 = 0x14; break;
        case 33:  m_vic.Timing0 = 0x09; m_vic.Timing1 = 0x6f; break;
        case 66:  m_vic.Timing0 = 0x04; m_vic.Timing1 = 0x6f; break;
        case 83:  m_vic.Timing0 = 0x03; m_vic.Timing1 = 0x6f; break;
        default:  m_vic.Timing0 = 0x00; m_vic.Timing1 = 0x1c; break;
        }

        dwRel = VCI_InitCAN(k,m_deviceIndex,  0, &m_vic);
        dwRel = VCI_InitCAN(k,m_deviceIndex,  1, &m_vic);

        if(dwRel != 1) {
            qDebug() << "ControlCAN: 初始化失败";
            return false;
        }

        qDebug() << "ControlCAN: 初始化成功";
        return true;
    }
    else if (m_deviceType == DEVICE_PCAN) {
        // PCAN 初始化已在openDevice中完成
        qDebug() << "PCAN: 初始化已在打开设备时完成";
        return true;
    }

    return false;
}

// 3. 启动CAN
bool CANThread::startCAN()
{
    if (m_deviceType == DEVICE_CONTROLCAN) {
        // ControlCAN 启动
        if(VCI_StartCAN(4,m_deviceIndex,  0) != 1) {
            qDebug() << "ControlCAN: 启动通道0失败";
            return false;
        }

        if(VCI_StartCAN(4,m_deviceIndex,  1) != 1) {
            qDebug() << "ControlCAN: 启动通道1失败";
            return false;
        }

        qDebug() << "ControlCAN: 启动成功";
        return true;
    }
    else if (m_deviceType == DEVICE_PCAN) {
        // PCAN 启动已在初始化时完成
        qDebug() << "PCAN: 已在初始化时启动";
        return true;
    }

    return false;
}

// 4. 发送数据
bool CANThread::sendData(UINT channel, UINT ID, BYTE remoteFlag, BYTE externFlag,
                         const unsigned char *data, BYTE len)
{
    if (m_deviceType == DEVICE_CONTROLCAN) {
        // ControlCAN 发送
        VCI_CAN_OBJ vco;
        vco.ID = ID;
        vco.RemoteFlag = remoteFlag;
        vco.ExternFlag = externFlag;
        vco.DataLen = len;

        for(UINT j = 0; j < len; j++)
            vco.Data[j] = data[j];

        DWORD dwRel = VCI_Transmit(4,m_deviceIndex,  channel, &vco, 1);
        emit dataSent(&vco);

        return (dwRel > 0);
    }
    else if (m_deviceType == DEVICE_PCAN) {
        // PCAN 发送
        TPCANMsg msg;
        msg.ID = ID;
        msg.MSGTYPE = externFlag ? PCAN_MESSAGE_EXTENDED : PCAN_MESSAGE_STANDARD;

        if(remoteFlag) {
            msg.MSGTYPE |= PCAN_MESSAGE_RTR;
        }

        msg.LEN = len;
        memcpy(msg.DATA, data, len);

        TPCANStatus status = CAN_Write(m_pcanChannel, &msg);

        if(status != PCAN_ERROR_OK) {
            emit pcanError(status);
            return false;
        }

        // 转换为VCI格式用于信号发射
        VCI_CAN_OBJ vco;
        vco.ID = ID;
        vco.RemoteFlag = remoteFlag;
        vco.ExternFlag = externFlag;
        vco.DataLen = len;
        memcpy(vco.Data, data, len);
        emit dataSent(&vco);

        return true;
    }

    return false;
}

// 5. 关闭设备
void CANThread::closeDevice()
{
    if (m_deviceType == DEVICE_CONTROLCAN) {
        VCI_CloseDevice(4,m_deviceIndex );
        qDebug() << "ControlCAN: 设备已关闭";
    }
    else if (m_deviceType == DEVICE_PCAN) {
        TPCANStatus status = CAN_Uninitialize(m_pcanChannel);
        if(status != PCAN_ERROR_OK) {
            qDebug() << "PCAN: 关闭设备失败，错误码:" << status;
            emit pcanError(status);
        } else {
            qDebug() << "PCAN: 设备已关闭";
        }
    }
}

// 6. 复位设备
bool CANThread::reSetCAN()
{
    if (m_deviceType == DEVICE_CONTROLCAN) {
        if(VCI_ResetCAN(4,m_deviceIndex, 0) != 1) {
            qDebug() << "ControlCAN: 复位通道0失败";
            return false;
        }

        if(VCI_ResetCAN(4,m_deviceIndex,  1) != 1) {
            qDebug() << "ControlCAN: 复位通道1失败";
            return false;
        }

        qDebug() << "ControlCAN: 复位成功";
        return true;
    }
    else if (m_deviceType == DEVICE_PCAN) {
        TPCANStatus status = CAN_Reset(m_pcanChannel);
        if(status != PCAN_ERROR_OK) {
            qDebug() << "PCAN: 复位失败，错误码:" << status;
            emit pcanError(status);
            return false;
        }
        qDebug() << "PCAN: 复位成功";
        return true;
    }

    return false;
}

// 接收线程
void CANThread::run()
{
    while(!stopped) {
        if (m_deviceType == DEVICE_CONTROLCAN) {

            // ControlCAN 接收处理
            DWORD dwRel, dwRel1;
            VCI_CAN_OBJ vco[2500];
            bool hasData = false;

            dwRel = VCI_Receive(4,m_deviceIndex,  0, vco, 2500, 0);
            if(dwRel > 0) {
                emit getProtocolData(vco, dwRel, 0);
                hasData = true;
            }

            dwRel1 = VCI_Receive(4,m_deviceIndex,  1, vco, 2500, 0);
            if(dwRel1 > 0) {
                emit getProtocolData(vco, dwRel1, 1);
                hasData = true;
            }

            if (!hasData) {
                emit getProtocolData(nullptr, 0, 0);
            }
        }
        else if (m_deviceType == DEVICE_PCAN) {
            // PCAN 接收处理
            TPCANMsg msg;
            TPCANTimestamp timestamp;
            TPCANStatus status = CAN_Read(m_pcanChannel, &msg, &timestamp);

            if(status == PCAN_ERROR_OK) {
                // 转换为VCI格式
                VCI_CAN_OBJ vco[1];
                vco[0].ID = msg.ID;
                vco[0].TimeStamp = timestamp.millis + timestamp.micros / 1000.0;
                vco[0].RemoteFlag = (msg.MSGTYPE & PCAN_MESSAGE_RTR) ? 1 : 0;
                vco[0].ExternFlag = (msg.MSGTYPE & PCAN_MESSAGE_EXTENDED) ? 1 : 0;
                vco[0].DataLen = msg.LEN;
                memcpy(vco[0].Data, msg.DATA, msg.LEN);

                emit getProtocolData(vco, 1, static_cast<UINT>(m_pcanChannel));
            } else if (status != PCAN_ERROR_QRCVEMPTY) {
                emit pcanError(status);
            } else {
                // 空队列，发送空数据
                emit getProtocolData(nullptr, 0, static_cast<UINT>(m_pcanChannel));
            }
        }

        sleep(40);
    }
    stopped = false;
}

void CANThread::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
