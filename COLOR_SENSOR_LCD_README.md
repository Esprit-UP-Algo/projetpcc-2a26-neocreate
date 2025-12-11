# Arduino Color Sensor with LCD Display Integration

This implementation adds LCD display functionality to your color sensor system. When the sensor detects a color, it looks up the corresponding equipment in the database and displays the equipment name on an LCD screen.

## Features

- **Color Detection**: TCS3200 color sensor detects RED, GREEN, BLUE, YELLOW colors
- **Database Integration**: Equipment information stored with color mapping in MATERIEL table  
- **LCD Display**: 16x2 LCD shows equipment name and color when detected
- **Qt Application**: Real-time communication between Arduino and Qt application
- **Equipment Lookup**: Automatic database lookup based on detected color

## Hardware Requirements

### Components
- Arduino Uno/Nano
- TCS3200 RGB Color Sensor
- 16x2 LCD Display (I2C recommended)
- Jumper wires
- Breadboard

### Wiring Diagram

#### TCS3200 Color Sensor
```
TCS3200 Pin -> Arduino Pin
S0          -> Pin 4
S1          -> Pin 5
S2          -> Pin 6
S3          -> Pin 7
OUT         -> Pin 8
VCC         -> 5V
GND         -> GND
```

#### LCD Display (I2C)
```
LCD Pin -> Arduino Pin
SDA     -> A4 (Arduino Uno)
SCL     -> A5 (Arduino Uno)  
VCC     -> 5V
GND     -> GND
```

## Software Requirements

### Arduino Libraries
Install these libraries via Arduino IDE Library Manager:
- `LiquidCrystal_I2C` (for LCD display)
- `Wire` (for I2C communication)

### Qt Dependencies
The project already includes:
- `QSerialPort` (for Arduino communication)
- `QSqlDatabase` (for database operations)

## Database Schema

The MATERIEL table has been updated to include color information:

```sql
CREATE TABLE "ABIR"."MATERIEL" (
    "ID_MATERIEL" NUMBER,
    "NOM" VARCHAR2(50 BYTE),
    "TYPE" VARCHAR2(50 BYTE), 
    "ETAT" VARCHAR2(50 BYTE),
    "LOCALISATION" VARCHAR2(100 BYTE),
    "ID_PROJET" NUMBER,
    "QTE" NUMBER,
    "COULEUR" VARCHAR2(20 BYTE)
);
```

### Sample Equipment Data
```sql
-- Red equipment (Headsets)
INSERT INTO MATERIEL VALUES (111, 'Casques Audio Pro', 'Casques', 'fonctionnel', 'studio tournage', NULL, 5, 'red');

-- Green equipment (Camera)  
INSERT INTO MATERIEL VALUES (222, 'Caméra HD 4K', 'Caméra', 'fonctionnel', 'studio tournage', NULL, 3, 'green');

-- Blue equipment (Podcast Microphones)
INSERT INTO MATERIEL VALUES (333, 'Micros Podcast Studio', 'Micros podcast', 'fonctionnel', 'salle montage', NULL, 8, 'blue');

-- Yellow equipment (Webcam)
INSERT INTO MATERIEL VALUES (444, 'Webcam Full HD', 'Webcam', 'en maintenance', 'salle podcast', NULL, 6, 'yellow');
```

## Color-to-Equipment Mapping

| Color  | Equipment Type   | Equipment Name        |
|--------|------------------|-----------------------|
| RED    | Casques          | Casques Audio Pro     |
| GREEN  | Caméra           | Caméra HD 4K          |
| BLUE   | Micros podcast   | Micros Podcast Studio |
| YELLOW | Webcam           | Webcam Full HD        |

## How It Works

1. **Color Detection**: Arduino continuously reads color values from TCS3200 sensor
2. **Color Classification**: Arduino determines dominant color (RED/GREEN/BLUE/YELLOW)
3. **Database Lookup**: Qt application queries database for equipment with matching color
4. **LCD Display**: Equipment name and color are displayed on LCD screen
5. **User Notification**: Qt application shows popup with detected equipment information

## File Structure

### New Files Added
- `lcd_display.h` - LCD display handler header
- `lcd_display.cpp` - LCD display implementation
- `arduino_color_sensor_lcd.ino` - Updated Arduino code with LCD support

### Modified Files
- `database.sql` - Updated MATERIEL table schema and sample data
- `materiel.h` - Added color field and lookup methods
- `materiel.cpp` - Implemented color-based equipment lookup
- `connection_arduino.h` - Added LCD command support
- `connection_arduino.cpp` - Enhanced Arduino communication with LCD
- `mainwindow.h` - Added LCD integration declarations
- `mainwindow.cpp` - Implemented Arduino and LCD event handling
- `gestiondeclient.pro` - Added new source files to project

## Usage Instructions

### 1. Hardware Setup
1. Connect TCS3200 sensor and LCD display to Arduino according to wiring diagram
2. Upload `arduino_color_sensor_lcd.ino` to your Arduino
3. Connect Arduino to PC via USB

### 2. Qt Application Setup  
1. Build and run the Qt application
2. Ensure Arduino is connected to correct COM port (default: COM7)
3. The application will automatically connect to Arduino and setup LCD

### 3. Testing the System
1. Place colored objects near the color sensor:
   - **Red object** → LCD shows "Casques Audio Pro"
   - **Green object** → LCD shows "Caméra HD 4K"  
   - **Blue object** → LCD shows "Micros Podcast Studio"
   - **Yellow object** → LCD shows "Webcam Full HD"

2. The Qt application will show popup notifications when equipment is detected

### 4. Calibration (if needed)
Adjust these values in Arduino code if colors are not detected properly:
```cpp
int redMin = 20, redMax = 247;
int greenMin = 21, greenMax = 283;
int blueMin = 14, blueMax = 211;
```

## LCD Display Format

The LCD shows information in this format:
```
Line 0: Equip: [Equipment Name]
Line 1: Couleur: [Color]
```

Example:
```
Equip: Casques...
Couleur: RED
```

## Communication Protocol

### Arduino to Qt
- `RED` - Red color detected
- `GREEN` - Green color detected  
- `BLUE` - Blue color detected
- `YELLOW` - Yellow color detected

### Qt to Arduino (LCD Commands)
- `LCD:0:Text` - Display text on line 0
- `LCD:1:Text` - Display text on line 1
- `LCD:CLEAR` - Clear LCD screen
- `WELCOME` - Show welcome message
- `NOT_FOUND:Color` - Show equipment not found message

## Troubleshooting

### Common Issues

1. **Arduino not connecting**
   - Check COM port in `mainwindow.cpp` (line with `COM7`)
   - Verify Arduino is properly connected via USB
   - Check Windows Device Manager for correct port

2. **LCD not displaying**
   - Verify I2C address (default: 0x27)
   - Check LCD wiring connections
   - Test LCD with simple Arduino sketch

3. **Colors not detected properly**
   - Adjust lighting conditions
   - Calibrate sensor values in Arduino code
   - Check color sensor wiring

4. **Database connection issues**
   - Ensure Oracle database is running
   - Verify database credentials in `connection.cpp`
   - Check MATERIEL table exists with COULEUR column

### Debug Information

Enable debug output in Qt application:
```cpp
qDebug() << "[ARDUINO] Connected on" << portName;
qDebug() << "[LCD] Display updated:" << message;
qDebug() << "[ARDUINO] Color detected:" << colorName;
```

## Future Enhancements

- Support for additional colors
- Equipment quantity tracking on LCD  
- Multiple equipment per color
- Voice announcements
- Barcode scanner integration
- Mobile app interface

## Support

For technical support or questions about this implementation, please refer to:
- Arduino documentation for TCS3200 and LCD
- Qt documentation for QSerialPort
- Oracle SQL documentation for database operations