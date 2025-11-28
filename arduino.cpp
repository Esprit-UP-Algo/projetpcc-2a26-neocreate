#include "arduino.h"

Arduino::Arduino(QObject *parent) : QObject(parent)
{
    arduinoIsAvailable = false;
    arduinoPortName = "";
}

bool Arduino::connectArduino()
{
    // Scan des ports disponibles
    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts())
    {
        if (port.hasVendorIdentifier() && port.hasProductIdentifier())
        {
            // 🔥 Modifier ici selon ton Arduino :
            // ARDUINO UNO : vendor=0x2341 product=0x0043
            // CH340 : vendor=0x1A86 product=0x7523
            if ( (port.vendorIdentifier() == 0x2341) ||
                (port.vendorIdentifier() == 0x1A86) )
            {
                arduinoPortName = port.portName();
                arduinoIsAvailable = true;
                break;
            }
        }
    }

    if (!arduinoIsAvailable)
        return false;

    serial.setPortName(arduinoPortName);
    serial.setBaudRate(QSerialPort::Baud9600);

    if (!serial.open(QSerialPort::ReadWrite))
        return false;

    connect(&serial, &QSerialPort::readyRead, this, &Arduino::readFromArduino);

    return true;
}

void Arduino::disconnectArduino()
{
    if (serial.isOpen())
        serial.close();
}

bool Arduino::writeToArduino(const QByteArray &data)
{
    if (serial.isOpen())
    {
        serial.write(data);
        return true;
    }
    return false;
}

QString Arduino::getArduinoPort()
{
    return arduinoPortName;
}

bool Arduino::isConnected()
{
    return serial.isOpen();
}

void Arduino::readFromArduino()
{
    QByteArray data = serial.readAll();
    emit dataReceived(QString(data));
}

