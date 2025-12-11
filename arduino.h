#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>

class ArduinoManager : public QObject
{
    Q_OBJECT

public:
    explicit ArduinoManager(QObject *parent = nullptr);

    // Connect to Arduino (COM3 by default)
    bool connectArduino(const QString &portName = "COM3");

    // Send "OK" / "DENIED"
    void sendToArduino(const QString &data);

signals:
    void idReceived(QString id);
    void errorOccurred(QString error);

private slots:
    void onDataReceived();

private:
    QSerialPort *m_serial;
    QByteArray m_buffer;
};

#endif // ARDUINO_H
