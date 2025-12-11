#include "lcd_display.h"
#include "connection_arduino.h"
#include <QDebug>

LcdDisplay::LcdDisplay(QObject *parent)
    : QObject(parent)
    , m_arduino(nullptr)
    , m_connected(false)
{
}

LcdDisplay::~LcdDisplay()
{
    // No need to delete m_arduino as we don't own it
}

bool LcdDisplay::connectToArduino(ConnectionArduino* arduino)
{
    if (!arduino) {
        qDebug() << "Arduino connection is null";
        emit errorOccurred("Arduino connection is null");
        return false;
    }
    
    if (!arduino->isOpen()) {
        qDebug() << "Arduino connection is not open";
        emit errorOccurred("Arduino connection is not open");
        return false;
    }
    
    m_arduino = arduino;
    m_connected = true;
    
    // Initialize LCD with welcome message
    displayWelcomeMessage();
    
    qDebug() << "LCD Display connected to Arduino";
    emit displayUpdated("LCD Display connected");
    
    return true;
}

bool LcdDisplay::displayText(const QString &text, int line)
{
    if (!m_connected || !m_arduino) {
        emit errorOccurred("LCD not connected to Arduino");
        return false;
    }
    
    if (line < 0 || line > 1) {
        emit errorOccurred("Invalid line number (0-1 only)");
        return false;
    }
    
    QString formattedText = formatTextForLcd(text);
    QString command = QString("LCD:%1:%2").arg(line).arg(formattedText);
    
    return sendLcdCommand(command);
}

bool LcdDisplay::clearScreen()
{
    if (!m_connected || !m_arduino) {
        emit errorOccurred("LCD not connected to Arduino");
        return false;
    }
    
    return sendLcdCommand("LCD:CLEAR");
}

bool LcdDisplay::displayEquipmentInfo(const QString &equipmentName, const QString &color)
{
    if (!m_connected || !m_arduino) {
        emit errorOccurred("LCD not connected to Arduino");
        return false;
    }
    
    // Clear screen first
    clearScreen();
    
    // Display equipment name on line 0
    QString line0 = formatTextForLcd("Équip: " + equipmentName, 16);
    
    // Display color on line 1
    QString line1 = formatTextForLcd("Couleur: " + color, 16);
    
    bool success = displayText(line0, 0) && displayText(line1, 1);
    
    if (success) {
        emit displayUpdated(QString("Displayed: %1 (%2)").arg(equipmentName, color));
    }
    
    return success;
}

bool LcdDisplay::displayWelcomeMessage()
{
    if (!m_connected || !m_arduino) {
        return false;
    }
    
    clearScreen();
    
    bool success = displayText("Syst. Détection", 0) && 
                   displayText("Couleur Prêt", 1);
                   
    if (success) {
        emit displayUpdated("Welcome message displayed");
    }
    
    return success;
}

bool LcdDisplay::displayNotFoundMessage(const QString &color)
{
    if (!m_connected || !m_arduino) {
        emit errorOccurred("LCD not connected to Arduino");
        return false;
    }
    
    clearScreen();
    
    QString line0 = formatTextForLcd("Couleur: " + color, 16);
    QString line1 = formatTextForLcd("Non trouvé!", 16);
    
    bool success = displayText(line0, 0) && displayText(line1, 1);
    
    if (success) {
        emit displayUpdated(QString("Equipment not found for color: %1").arg(color));
    }
    
    return success;
}

bool LcdDisplay::sendLcdCommand(const QString &command)
{
    if (!m_connected || !m_arduino) {
        return false;
    }
    
    QByteArray commandBytes = (command + "\\n").toUtf8();
    
    qDebug() << "Sending LCD command:" << command;
    
    bool success = m_arduino->sendCommand(commandBytes);
    
    if (!success) {
        emit errorOccurred("Failed to send LCD command");
    }
    
    return success;
}

QString LcdDisplay::formatTextForLcd(const QString &text, int maxLength)
{
    if (text.length() <= maxLength) {
        return text;
    }
    
    // Truncate and add dots if too long
    return text.left(maxLength - 3) + "...";
}