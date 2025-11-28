#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);

    bool connectArduino();       // Connexion automatique
    void disconnectArduino();    // Déconnexion
    bool writeToArduino(const QByteArray &data);  // Envoyer commande

    QString getArduinoPort();    // Récupérer port utilisé
    bool isConnected();          // Vérifier si connecté

signals:
    void dataReceived(QString data);  // Signal quand Arduino envoie un message

private slots:
    void readFromArduino();      // lecture automatique

private:
    QSerialPort serial;
    QString arduinoPortName;
    bool arduinoIsAvailable;
};

#endif // ARDUINO_H

