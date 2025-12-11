#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <QObject>
#include <QString>

class QSerialPort;
class ConnectionArduino;

class LcdDisplay : public QObject
{
    Q_OBJECT

public:
    explicit LcdDisplay(QObject *parent = nullptr);
    ~LcdDisplay();

    // Connect to Arduino with LCD
    bool connectToArduino(ConnectionArduino* arduino);
    
    // Display text on LCD (line 0 or 1)
    bool displayText(const QString &text, int line = 0);
    
    // Clear LCD screen
    bool clearScreen();
    
    // Display equipment information
    bool displayEquipmentInfo(const QString &equipmentName, const QString &color);
    
    // Display welcome message
    bool displayWelcomeMessage();
    
    // Display error message when equipment not found
    bool displayNotFoundMessage(const QString &color);

signals:
    void displayUpdated(const QString &message);
    void errorOccurred(const QString &error);

private:
    ConnectionArduino* m_arduino;
    bool m_connected;
    
    // Send command to Arduino for LCD
    bool sendLcdCommand(const QString &command);
    
    // Format text to fit LCD width (typically 16 or 20 characters)
    QString formatTextForLcd(const QString &text, int maxLength = 16);
};

#endif // LCD_DISPLAY_H