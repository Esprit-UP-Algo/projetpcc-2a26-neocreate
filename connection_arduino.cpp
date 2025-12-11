#include "connection_arduino.h"
#include "materiel.h"

#include <QSerialPortInfo>
#include <QDebug>

ConnectionArduino::ConnectionArduino(QObject *parent)
    : QObject(parent)
{
    connect(&serial, &QSerialPort::readyRead, this, &ConnectionArduino::handleReadyRead);
    connect(&serial, &QSerialPort::errorOccurred, this, &ConnectionArduino::handleError);
}

ConnectionArduino::~ConnectionArduino()
{
    close();
}

bool ConnectionArduino::open(const QString &portName, qint32 baudRate)
{
    if (serial.isOpen()) {
        qDebug() << "Serial already open, closing before reopen" << serial.portName();
        serial.close();
    }

    qDebug() << "Opening serial port" << portName << "@" << baudRate;
    serial.setPortName(portName);
    serial.setBaudRate(baudRate);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (!serial.open(QIODevice::ReadWrite)) {
        const QString err = serial.errorString();
        qDebug() << "Failed to open serial port" << portName << ":" << err;
        emit errorOccurred(err);
        return false;
    }

    qDebug() << "Serial port opened" << portName;
    buffer.clear();
    return true;
}

void ConnectionArduino::close()
{
    if (serial.isOpen()) {
        qDebug() << "Closing serial port" << serial.portName();
        serial.close();
    }
    buffer.clear();
}

bool ConnectionArduino::isOpen() const
{
    return serial.isOpen();
}

bool ConnectionArduino::sendCommand(const QByteArray &payload)
{
    if (!serial.isOpen()) {
        emit errorOccurred(QStringLiteral("Serial port is not open"));
        return false;
    }

    qDebug() << "Sending command to Arduino, bytes:" << payload.size() << "data:" << payload;
    const qint64 written = serial.write(payload);
    if (written == -1) {
        emit errorOccurred(serial.errorString());
        return false;
    }

    return serial.waitForBytesWritten(50);
}

QStringList ConnectionArduino::availablePorts()
{
    QStringList ports;
    const auto infos = QSerialPortInfo::availablePorts();
    ports.reserve(infos.size());
    for (const QSerialPortInfo &info : infos) {
        ports << info.portName();
    }
    return ports;
}

void ConnectionArduino::handleReadyRead()
{
    const QByteArray chunk = serial.readAll();
    buffer.append(chunk);
    qDebug() << "Received" << chunk.size() << "bytes from Arduino" << chunk;
    processBuffer();
}

void ConnectionArduino::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) {
        return;
    }

    qDebug() << "Serial error" << error << serial.errorString();
    emit errorOccurred(serial.errorString());

    if (error == QSerialPort::ResourceError) {
        close();
    }
}

void ConnectionArduino::processBuffer()
{
    int newlineIndex = buffer.indexOf('\n');
    while (newlineIndex != -1) {
        QByteArray lineBytes = buffer.left(newlineIndex);
        buffer.remove(0, newlineIndex + 1);

        QString line = QString::fromUtf8(lineBytes).trimmed();
        if (!line.isEmpty()) {
            qDebug() << "Line from Arduino:" << line;
            emit rawLineReceived(line);

            // Check for PIR motion sensor messages
            if (line == "CHECK_DB" || line == "MOTION" || line.contains("Motion detected", Qt::CaseInsensitive)) {
                qDebug() << "PIR Motion detected - CHECK_DB/MOTION received!";
                qDebug() << "Emitting motionDetected signal...";
                emit motionDetected();
                qDebug() << "motionDetected signal emitted";
            }
            else if (line == "CLEAR" || line == "No motion" || line.toUpper() == "NO MOTION" || line.contains("No motion", Qt::CaseInsensitive)) {
                qDebug() << "PIR Motion cleared";
                emit motionCleared();
            }
            // Check if it's a color name (RED, GREEN, BLUE, YELLOW)
            else if (line == "RED" || line == "GREEN" || line == "BLUE" || line == "YELLOW") {
                processColorName(line);
            }
            else {
                // Try to parse RGB values
                int r = 0, g = 0, b = 0;
                if (tryParseColor(line, r, g, b)) {
                    qDebug() << "Parsed color" << r << g << b;
                    emit colorReceived(r, g, b);
                }
            }
        }

        newlineIndex = buffer.indexOf('\n');
    }
}

bool ConnectionArduino::tryParseColor(const QString &line, int &r, int &g, int &b)
{
    // Parse lines like: "Red = 123 - Green = 45 - Blue = 67"
    static const QRegularExpression regex(
        QStringLiteral("^Red\\s*=\\s*(\\d+)\\s*-\\s*Green\\s*=\\s*(\\d+)\\s*-\\s*Blue\\s*=\\s*(\\d+)$"),
        QRegularExpression::CaseInsensitiveOption);

    const QRegularExpressionMatch match = regex.match(line.trimmed());
    if (!match.hasMatch()) {
        return false;
    }

    r = match.captured(1).toInt();
    g = match.captured(2).toInt();
    b = match.captured(3).toInt();
    return true;
}

void ConnectionArduino::processColorName(const QString &colorName)
{
    qDebug() << "Color detected:" << colorName;
    emit colorNameReceived(colorName);
    
    // Look up equipment by color in database
    QString equipmentName = lookupEquipmentByColor(colorName);
    
    if (!equipmentName.isEmpty() && equipmentName != "Équipement non trouvé") {
        qDebug() << "Equipment found:" << equipmentName << "for color:" << colorName;
        emit equipmentDetected(equipmentName, colorName);
        
        // Display on LCD
        displayEquipmentOnLcd(equipmentName, colorName);
    }
    else {
        qDebug() << "No equipment found for color:" << colorName;
        // Display "not found" message on LCD
        sendLcdCommand("NOT_FOUND:" + colorName);
    }
}

QString ConnectionArduino::lookupEquipmentByColor(const QString &colorName)
{
    return Materiel::getMaterielNomByCouleur(colorName.toLower());
}

bool ConnectionArduino::sendLcdCommand(const QString &command)
{
    if (!serial.isOpen()) {
        emit errorOccurred("Serial port is not open for LCD command");
        return false;
    }
    
    QByteArray commandBytes = (command + "\n").toUtf8();
    qDebug() << "Sending LCD command:" << command;
    
    const qint64 written = serial.write(commandBytes);
    if (written == -1) {
        emit errorOccurred(serial.errorString());
        return false;
    }
    
    return serial.waitForBytesWritten(50);
}

bool ConnectionArduino::displayEquipmentOnLcd(const QString &equipmentName, const QString &color)
{
    // Clear LCD first
    clearLcd();
    
    // Format equipment name for LCD (16 characters max per line)
    QString line0 = "Equip: " + equipmentName;
    if (line0.length() > 16) {
        line0 = line0.left(13) + "...";
    }
    
    QString line1 = "Couleur: " + color;
    if (line1.length() > 16) {
        line1 = line1.left(16);
    }
    
    // Send commands to display on both lines
    bool success = sendLcdCommand("LCD:0:" + line0) &&
                   sendLcdCommand("LCD:1:" + line1);
                   
    return success;
}

bool ConnectionArduino::clearLcd()
{
    return sendLcdCommand("LCD:CLEAR");
}
