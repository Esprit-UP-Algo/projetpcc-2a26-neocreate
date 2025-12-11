/*
 * Arduino PIR Sensor + Buzzer Integration
 * 
 * Pin Configuration:
 * - PIR Sensor OUT -> Pin 12
 * - Buzzer -> Pin 8
 * 
 * Communication Protocol:
 * - When motion detected: sends "CHECK_DB"
 * - When no motion: sends "CLEAR"
 * - Receives: "ALERT_COUNT:X" where X is number of days remaining
 * - Buzzer beeps X times based on alert count
 */

int pirPin = 12;      // PIR OUT pin
int buzzerPin = 8;    // Buzzer pin
bool lastMotionState = false;
bool motionDetectedSent = false;  // Flag to send CHECK_DB only once per detection
unsigned long lastCheckTime = 0;
const unsigned long CHECK_INTERVAL = 300; // Check every 300ms to avoid spam

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize buzzer to LOW
  digitalWrite(buzzerPin, LOW);
  
  Serial.println("Testing PIR + BUZZER...");
  delay(3000);  // Warm-up time for PIR sensor
}

void loop() {
  unsigned long currentTime = millis();
  
  // Check PIR sensor only every CHECK_INTERVAL milliseconds
  if (currentTime - lastCheckTime >= CHECK_INTERVAL) {
    int motion = digitalRead(pirPin);
    
    // Detect state change to avoid spam - send CHECK_DB only ONCE per detection
    if (motion == HIGH && !lastMotionState && !motionDetectedSent) {
      // Motion just detected - send CHECK_DB ONCE
      Serial.println("CHECK_DB");
      lastMotionState = true;
      motionDetectedSent = true;  // Mark as sent to avoid loops
    } 
    else if (motion == LOW && lastMotionState) {
      // Motion cleared - reset flag for next detection
      Serial.println("CLEAR");
      lastMotionState = false;
      motionDetectedSent = false;  // Reset flag to allow next detection
      digitalWrite(buzzerPin, LOW);  // Ensure buzzer is off
    }
    
    lastCheckTime = currentTime;
  }
  
  // Check for incoming messages from Qt
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    message.trim();
    
    // Check if message is ALERT_COUNT:X
    if (message.startsWith("ALERT_COUNT:")) {
      int alertCount = message.substring(12).toInt();
      
      // Activate buzzer based on alert count (notification color)
      // Red (expire) = 4 beeps
      // Orange (j1) = 3 beeps
      // Yellow (j3) = 2 beeps
      // Blue (j7) = 1 beep
      if (alertCount > 0) {
        // Beep 'alertCount' times for this notification
        for (int i = 0; i < alertCount; i++) {
          digitalWrite(buzzerPin, HIGH);
          delay(200);  // Beep duration
          digitalWrite(buzzerPin, LOW);
          delay(200);  // Pause between beeps
        }
        // Wait 5 seconds after completing beeps before processing next notification
        // This ensures clear separation between different notification beeps
        delay(5000);
      } else {
        // No alerts - ensure buzzer is off
        digitalWrite(buzzerPin, LOW);
      }
    }
  }
  
  delay(50); // Small delay to prevent overwhelming the serial port
}

