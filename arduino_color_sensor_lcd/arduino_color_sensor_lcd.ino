/*
  RGB Color Sensor with LCD Display - Enhanced Version
  Detects: RED, GREEN, BLUE, YELLOW 
  Displays equipment name on LCD based on detected color
  
  Hardware:
  - TCS3200 Color Sensor
  - 16x2 LCD Display (I2C or parallel)
  - Arduino Uno/Nano
  
  Wiring:
  TCS3200:
  - S0 -> Pin 4
  - S1 -> Pin 5  
  - S2 -> Pin 6
  - S3 -> Pin 7
  - OUT -> Pin 8
  - VCC -> 5V
  - GND -> GND
  
  LCD (I2C):
  - SDA -> A4 (Arduino Uno) 
  - SCL -> A5 (Arduino Uno)
  - VCC -> 5V
  - GND -> GND
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// LCD configuration (I2C address 0x27, 16x2 display)
// Common I2C addresses: 0x27, 0x3F, 0x20, 0x38
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Function to scan for I2C devices
void scanI2CDevices() {
  Serial.println("Scanning I2C devices...");
  
  int deviceCount = 0;
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      deviceCount++;
    }
  }
  
  if (deviceCount == 0) {
    Serial.println("No I2C devices found!");
  } else {
    Serial.print("Found ");
    Serial.print(deviceCount);
    Serial.println(" I2C device(s)");
  }
}

// Pins for TCS3200
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibration values (adjust based on your sensor)
int redMin = 20, redMax = 247;
int greenMin = 21, greenMax = 283;
int blueMin = 14, blueMax = 211;

// Variables
int redPW, greenPW, bluePW;
int redValue, greenValue, blueValue;
String lastDetectedColor = "";
String currentEquipment = "";

// Equipment mapping based on colors
struct EquipmentInfo {
  String colorName;
  String equipmentName;
  String type;
};

EquipmentInfo equipment[] = {
  {"RED", "Casques Audio Pro", "Casques"},
  {"GREEN", "Caméra HD 4K", "Caméra"}, 
  {"BLUE", "Micros Podcast", "Micros podcast"},
  {"YELLOW", "Webcam Full HD", "Webcam"}
};

void setup() {
  // Initialize color sensor pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Initialize serial communication first for debugging
  Serial.begin(9600);
  Serial.println("Starting Color Sensor with LCD...");
  
  // Scan for I2C devices before initializing LCD
  Wire.begin();
  scanI2CDevices();
  
  // Initialize LCD with error checking
  lcd.init();
  lcd.backlight();
  
  // Test LCD by clearing and setting cursor
  lcd.clear();
  delay(100);
  lcd.setCursor(0, 0);
  
  Serial.println("LCD initialized, displaying welcome message...");
  
  // Display startup message
  displayWelcomeMessage();
  
  Serial.println("Color Sensor with LCD - Ready");
}

void loop() {
  // Read color values
  String detectedColor = readColorSensor();
  
  // Only update if color changed
  if (detectedColor != lastDetectedColor && detectedColor != "UNKNOWN") {
    lastDetectedColor = detectedColor;
    
    // Find equipment info
    String equipmentName = getEquipmentName(detectedColor);
    
    // Send to Qt application
    Serial.println(detectedColor);
    
    // Update LCD display
    displayEquipmentInfo(equipmentName, detectedColor);
    
    // Wait a bit to avoid rapid changes
    delay(1000);
  }
  
  // Check for LCD commands from Qt application
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    processSerialCommand(command);
  }
  
  delay(200);
}

String readColorSensor() {
  // Read RED
  redPW = getPW(LOW, LOW);
  redValue = map(redPW, redMin, redMax, 255, 0);
  delay(50);

  // Read GREEN  
  greenPW = getPW(HIGH, HIGH);
  greenValue = map(greenPW, greenMin, greenMax, 255, 0);
  delay(50);

  // Read BLUE
  bluePW = getPW(LOW, HIGH);
  blueValue = map(bluePW, blueMin, blueMax, 255, 0);
  delay(50);

  // Determine dominant color
  if (redValue > greenValue && redValue > blueValue && redValue > 100) {
    return "RED";
  }
  else if (greenValue > redValue && greenValue > blueValue && greenValue > 100) {
    return "GREEN";
  }
  else if (blueValue > redValue && blueValue > greenValue && blueValue > 100) {
    return "BLUE";
  }
  else if (redValue > 150 && greenValue > 150 && blueValue < 100) {
    return "YELLOW";
  }
  else {
    return "UNKNOWN";
  }
}

// Generic function to get pulse width
int getPW(bool s2, bool s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  return pulseIn(sensorOut, LOW);
}

String getEquipmentName(String colorName) {
  for (int i = 0; i < 4; i++) {
    if (equipment[i].colorName == colorName) {
      return equipment[i].equipmentName;
    }
  }
  return "Équipement inconnu";
}

void displayWelcomeMessage() {
  Serial.println("Displaying welcome message on LCD...");
  
  lcd.clear();
  delay(100);  // Small delay after clear
  
  // Line 0: System detection
  lcd.setCursor(0, 0);
  lcd.print("ABIR Detection");
  
  // Line 1: Status
  lcd.setCursor(0, 1);
  lcd.print("Systeme Pret!");
  
  Serial.println("Welcome message displayed!");
}

// Test function to verify LCD is working
void testLCD() {
  Serial.println("Testing LCD display...");
  
  // Test 1: Simple text
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Test LCD");
  lcd.setCursor(0, 1);
  lcd.print("Ligne 2");
  delay(2000);
  
  // Test 2: Numbers
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Chiffres:");
  lcd.setCursor(0, 1);
  lcd.print("1234567890");
  delay(2000);
  
  // Test 3: Special characters
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Caracteres:");
  lcd.setCursor(0, 1);
  lcd.print("!@#$%^&*()");
  delay(2000);
  
  Serial.println("LCD test completed!");
}

void displayEquipmentInfo(String equipmentName, String color) {
  lcd.clear();
  
  // Line 0: Equipment name (truncate if too long)
  lcd.setCursor(0, 0);
  String line1 = "Equip: " + equipmentName;
  if (line1.length() > 16) {
    line1 = line1.substring(0, 13) + "...";
  }
  lcd.print(line1);
  
  // Line 1: Color
  lcd.setCursor(0, 1);
  String line2 = "Couleur: " + color;
  if (line2.length() > 16) {
    line2 = line2.substring(0, 16);
  }
  lcd.print(line2);
}

void displayNotFound(String color) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Couleur: " + color);
  lcd.setCursor(0, 1);
  lcd.print("Non trouve!");
}

void processSerialCommand(String command) {
  command.trim();
  
  if (command.startsWith("LCD:")) {
    // Parse LCD command: LCD:line:text or LCD:CLEAR
    if (command == "LCD:CLEAR") {
      lcd.clear();
    }
    else {
      int firstColon = command.indexOf(':');
      int secondColon = command.indexOf(':', firstColon + 1);
      
      if (firstColon > 0 && secondColon > firstColon) {
        int line = command.substring(firstColon + 1, secondColon).toInt();
        String text = command.substring(secondColon + 1);
        
        if (line >= 0 && line <= 1) {
          lcd.setCursor(0, line);
          // Clear the line first by printing spaces
          for (int i = 0; i < 16; i++) {
            lcd.print(" ");
          }
          lcd.setCursor(0, line);
          lcd.print(text);
        }
      }
    }
  }
  else if (command == "WELCOME") {
    displayWelcomeMessage();
  }
  else if (command == "TEST_LCD") {
    testLCD();
  }
  else if (command.startsWith("NOT_FOUND:")) {
    String color = command.substring(10);
    displayNotFound(color);
  }
}
