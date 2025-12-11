#include "arduino.h"
#include <QDebug>

ArduinoManager::ArduinoManager(QObject *parent)
    : QObject(parent),
    m_serial(new QSerialPort(this))
{
}

bool ArduinoManager::connectArduino(const QString &portName)
{
    m_serial->setPortName(portName);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serial->open(QIODevice::ReadWrite)) {
        emit errorOccurred("Unable to connect to Arduino on " + portName);
        return false;
    }

    connect(m_serial, &QSerialPort::readyRead,
            this, &ArduinoManager::onDataReceived);

    return true;
}

void ArduinoManager::sendToArduino(const QString &data)
{
    if (m_serial && m_serial->isWritable()) {
        m_serial->write(data.toUtf8() + "\n");
    }
}

void ArduinoManager::onDataReceived()
{
    m_buffer += m_serial->readAll();

    int index;
    while ((index = m_buffer.indexOf('\n')) != -1)
    {
        QByteArray line = m_buffer.left(index);
        m_buffer.remove(0, index + 1);

        QString msg = QString::fromUtf8(line).trimmed();

        // Expect "ID:XXXXXXXX"
        if (msg.startsWith("ID:")) {
            QString id = msg.mid(3).trimmed();
            emit idReceived(id);
        } else {
            qDebug() << "[ARDUINO] Unhandled message:" << msg;
        }
    }
}
