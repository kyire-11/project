#ifndef MODBUSWORKER_H
#define MODBUSWORKER_H

#include <QObject>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QVector>
#include <QSerialPort>
#include <QTimer>
#include <QMutex>
#include <QQueue>
#include <QThread>


class ModbusWorker : public QObject
{
    Q_OBJECT
public:
    explicit ModbusWorker(QObject *parent = nullptr);
    ~ModbusWorker();

    bool isConnected() const;
    bool m_isClosing = false;

public slots:
    void initModbusDevice();
    void setupModbusParameters(const QString &portName,
                               QSerialPort::BaudRate baudRate,
                               QSerialPort::DataBits dataBits,
                               QSerialPort::StopBits stopBits,
                               QSerialPort::Parity parity);
    bool openSerialPort();
    void closeSerialPort();
    void requestReadRegisters(quint16 startAddress, quint16 quantity, quint8 slaveId);
    void requestWriteRegister(quint16 address, quint16 value, quint8 slaveId);

signals:
    void initialized(bool success);
    void parametersSet(bool success);
    void connectionStateChanged(bool connected);
    void dataReceived(quint16 startAddress, QVector<quint16> values);
    void writeCompleted(quint16 address, quint16 value, bool success);
    void errorOccurred(const QString &error);

private slots:
    void processNextRequest();
    void handleReplyFinished();
    void handleTimeout();

private:
    QModbusRtuSerialMaster *m_modbusDevice = nullptr;
    QTimer *m_timeoutTimer = nullptr;
    QMutex m_requestMutex;
    QQueue<QPair<quint16, quint16>> m_readQueue;
    // QQueue<QPair<quint16, quint16>> m_writeQueue;
    QModbusReply *m_currentReply = nullptr;
    quint8 m_currentSlaveId = 1;
    int m_maxRetries = 3;
    int m_currentRetry = 0;
    bool m_isProcessingRequest = false;
    quint16 m_currentAddress = 0;
    quint16 m_currentValue = 0;
    struct WriteRequest {
        quint16 address;
        quint16 value;
        quint8 slaveId;
    };
    QQueue<WriteRequest> m_writeQueue;
    QModbusDevice::State lastValidState;
};

#endif // MODBUSWORKER_H
