#ifndef CONNECTION_ARDUINO_H
#define CONNECTION_ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QStringList>
#include <QRegularExpression>

class LcdDisplay;

class ConnectionArduino : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionArduino(QObject *parent = nullptr);
    ~ConnectionArduino();

    bool open(const QString &portName, qint32 baudRate = 9600);
    void close();
    bool isOpen() const;
    bool sendCommand(const QByteArray &payload);
    static QStringList availablePorts();
    
    // LCD display methods
    bool sendLcdCommand(const QString &command);
    bool displayEquipmentOnLcd(const QString &equipmentName, const QString &color);
    bool clearLcd();

signals:
    void colorReceived(int red, int green, int blue);
    void colorNameReceived(const QString &colorName);
    void rawLineReceived(const QString &line);
    void errorOccurred(const QString &message);
    void equipmentDetected(const QString &equipmentName, const QString &color);
    void motionDetected();  // PIR motion sensor detected movement
    void motionCleared();   // PIR motion sensor cleared (no movement)

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort serial;
    QByteArray buffer;

    void processBuffer();
    bool tryParseColor(const QString &line, int &r, int &g, int &b);
    void processColorName(const QString &colorName);
    QString lookupEquipmentByColor(const QString &colorName);
};

#endif // CONNECTION_ARDUINO_H
