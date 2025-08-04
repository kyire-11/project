#include "modbusworker.h"
#include <QThread>
#include <QDebug>


ModbusWorker::ModbusWorker(QObject *parent) : QObject(parent) {}

ModbusWorker::~ModbusWorker()
{

    closeSerialPort();
    if (m_modbusDevice) {
        m_modbusDevice->deleteLater();
    }
}

bool ModbusWorker::isConnected() const
{
    return m_modbusDevice && (m_modbusDevice->state() == QModbusDevice::ConnectedState);
}

void ModbusWorker::initModbusDevice()
{
    // qDebug() << "Initializing Modbus in thread:" << QThread::currentThread();
    if(m_isClosing) return;

    if (m_modbusDevice) {
        m_modbusDevice->deleteLater();
        m_modbusDevice = nullptr;
    }

    m_modbusDevice = new QModbusRtuSerialMaster(this);
    lastValidState = QModbusDevice::UnconnectedState;

    connect(m_modbusDevice, &QModbusDevice::errorOccurred, this, [this](QModbusDevice::Error error) {
        emit errorOccurred(QString("Modbus错误: %1").arg(m_modbusDevice->errorString()));
    });

    connect(m_modbusDevice, &QModbusDevice::stateChanged, this, [this](QModbusDevice::State state) {
        // static QModbusDevice::State lastValidState = QModbusDevice::UnconnectedState;

        if ((state == QModbusDevice::ConnectedState ||
             state == QModbusDevice::UnconnectedState) &&
            state != lastValidState)
        {
            lastValidState = state;
            emit connectionStateChanged(state == QModbusDevice::ConnectedState);
        }
    },Qt::QueuedConnection);

    m_timeoutTimer = new QTimer(this);
    m_timeoutTimer->setSingleShot(true);
    connect(m_timeoutTimer, &QTimer::timeout, this, &ModbusWorker::handleTimeout);

    emit initialized(m_modbusDevice != nullptr);
}

void ModbusWorker::setupModbusParameters(const QString &portName,
                                         QSerialPort::BaudRate baudRate,
                                         QSerialPort::DataBits dataBits,
                                         QSerialPort::StopBits stopBits,
                                         QSerialPort::Parity parity)
{
    // closeSerialPort();
    m_isClosing=false;
    if (m_modbusDevice) {
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, portName);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, baudRate);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, dataBits);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, stopBits);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, parity);
        emit parametersSet(true);
    } else {
        emit parametersSet(false);
    }
}

bool ModbusWorker::openSerialPort()
{

    if (!m_modbusDevice) {
        emit errorOccurred("Modbus设备未初始化");
        return false;
    }

    if (m_modbusDevice->state() == QModbusDevice::ConnectedState) {
        return true;
    }

    return m_modbusDevice->connectDevice();
}

void ModbusWorker::closeSerialPort()
{
    m_isClosing = true;
    if (m_modbusDevice && m_modbusDevice->state() == QModbusDevice::ConnectedState) {
        m_modbusDevice->disconnectDevice();
    }

    QMutexLocker locker(&m_requestMutex);
    m_readQueue.clear();
    m_writeQueue.clear();
    if (m_currentReply) {
        // 修改：使用 deleteLater 代替 abort
        m_currentReply->deleteLater();
        m_currentReply = nullptr;
    }
    m_isProcessingRequest = false;
}

// 其他成员函数实现与之前讨论的优化版本一致，保持相同逻辑

void ModbusWorker::requestReadRegisters(quint16 startAddress, quint16 quantity, quint8 slaveId)
{
    // qDebug() << "requestReadRegisters() called in thread:" << QThread::currentThread();
    if (m_isClosing) return;
    m_requestMutex.lock();
    m_readQueue.enqueue(qMakePair(startAddress, quantity));
    m_currentSlaveId = slaveId;
    m_requestMutex.unlock();

    // 使用Qt::QueuedConnection确保在worker线程执行
    QMetaObject::invokeMethod(this, &ModbusWorker::processNextRequest, Qt::QueuedConnection);
}

void ModbusWorker::requestWriteRegister(quint16 address, quint16 value, quint8 slaveId)
{
    if (m_isClosing) return;
    // qDebug() << "requestWriteRegister() called in thread:" << QThread::currentThread();
    QMutexLocker locker(&m_requestMutex);
    m_writeQueue.enqueue({address, value, slaveId});
    QMetaObject::invokeMethod(this, &ModbusWorker::processNextRequest, Qt::QueuedConnection);

    // m_requestMutex.lock();
    // m_currentAddress = address;
    // m_currentValue = value;
    // m_writeQueue.enqueue(qMakePair(address, value));
    // m_currentSlaveId = slaveId;
    // m_requestMutex.unlock();

    // // 使用Qt::QueuedConnection确保在worker线程执行
    // QMetaObject::invokeMethod(this, &ModbusWorker::processNextRequest, Qt::QueuedConnection);
}

void ModbusWorker::processNextRequest()
{
    // qDebug() << "processNextRequest() called in thread:" << QThread::currentThread();
    if (m_isClosing) return;
    m_requestMutex.lock();
    if (m_isProcessingRequest || (m_readQueue.isEmpty() && m_writeQueue.isEmpty())) {
        m_requestMutex.unlock();
        return;
    }
    m_isProcessingRequest = true;
    m_requestMutex.unlock();

    // 优先处理写请求
    if (!m_writeQueue.isEmpty()) {
        auto request = m_writeQueue.dequeue();
        quint16 address = request.address;
        quint16 value = request.value;

        QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, address, 1);
        writeUnit.setValue(0, value);

        if (auto *reply = m_modbusDevice->sendWriteRequest(writeUnit, request.slaveId)) {
            reply->setProperty("address", request.address);
            reply->setProperty("value", request.value);
            connect(reply, &QModbusReply::finished, this, &ModbusWorker::handleReplyFinished);
            m_timeoutTimer->start(1000); // 设置超时
        } else {
            m_requestMutex.lock();
            m_isProcessingRequest = false;
            m_requestMutex.unlock();
            emit errorOccurred("无法发送写请求");
            processNextRequest();
        }
    } else if (!m_readQueue.isEmpty()) {
        auto request = m_readQueue.dequeue();
        quint16 startAddress = request.first;
        quint16 quantity = request.second;

        QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, startAddress, quantity);
        if (auto *reply = m_modbusDevice->sendReadRequest(readUnit, m_currentSlaveId)) {
            m_currentReply = reply;
            connect(reply, &QModbusReply::finished, this, &ModbusWorker::handleReplyFinished);
            m_timeoutTimer->start(1000);
        } else {
            m_requestMutex.lock();
            m_isProcessingRequest = false;
            m_requestMutex.unlock();
            emit errorOccurred("无法发送读请求");
            processNextRequest();
        }
    }
}

void ModbusWorker::handleReplyFinished()
{
    // qDebug() << "handleReplyFinished() called in thread:" << QThread::currentThread();

    if (m_isClosing) return;
    if (m_timeoutTimer->isActive()) {
        m_timeoutTimer->stop();
    }

    auto *reply = qobject_cast<QModbusReply*>(sender());
    if (!reply) return;
    if (reply->error() == QModbusDevice::NoError) {
        const auto pdu = reply->rawResult();
        if (pdu.functionCode() == QModbusPdu::WriteSingleRegister) {
            const quint16 address = reply->property("address").toUInt();
            const quint16 value = reply->property("value").toUInt();
            emit writeCompleted(address, value, true);
        }else if (pdu.functionCode() == QModbusPdu::ReadHoldingRegisters) {
            QModbusDataUnit unit = reply->result();
            QVector<quint16> values;
            for (int i = 0; i < unit.valueCount(); ++i) {
                values.append(unit.value(i));
            }
            emit dataReceived(unit.startAddress(), values);
        }
    }else {
        emit errorOccurred(QString("Modbus错误: %1").arg(reply->errorString()));
    }

    // if (!m_currentReply) return;

    // if (m_currentReply->error() == QModbusDevice::NoError) {
    //     const QModbusPdu &pdu = m_currentReply->rawResult();
    //     if (pdu.functionCode() == QModbusPdu::ReadHoldingRegisters) {
    //         QModbusDataUnit unit = m_currentReply->result();
    //         QVector<quint16> values;
    //         for (int i = 0; i < unit.valueCount(); ++i) {
    //             values.append(unit.value(i));
    //         }
    //         emit dataReceived(unit.startAddress(), values);
    //     } else if (pdu.functionCode() == QModbusPdu::WriteSingleRegister) {
    //         emit writeCompleted(m_currentAddress, m_currentValue, true);
    //     }
    // } else {
    //     emit errorOccurred(QString("Modbus错误: %1").arg(m_currentReply->errorString()));
    // }

    // m_currentReply->deleteLater();
    // m_currentReply = nullptr;
    m_currentRetry = 0;

    m_requestMutex.lock();
    m_isProcessingRequest = false;
    m_requestMutex.unlock();
    processNextRequest();
}

void ModbusWorker::handleTimeout()
{
    // qDebug() << "handleTimeout() called in thread:" << QThread::currentThread();
    if (m_isClosing) return;
    if (m_currentRetry < m_maxRetries) {
        m_currentRetry++;

        if (m_currentReply) {
            const QModbusPdu &pdu = m_currentReply->rawResult();

            if (pdu.functionCode() == QModbusPdu::ReadHoldingRegisters) {
                auto request = qMakePair(m_currentReply->result().startAddress(),
                                         m_currentReply->result().valueCount());
                requestReadRegisters(request.first, request.second, m_currentSlaveId);
            } else if (pdu.functionCode() == QModbusPdu::WriteSingleRegister) {
                requestWriteRegister(m_currentAddress, m_currentValue, m_currentSlaveId);
            }
        }
    } else {
        emit errorOccurred("超过最大重试次数");
        m_currentRetry = 0;
        processNextRequest();
    }
}



