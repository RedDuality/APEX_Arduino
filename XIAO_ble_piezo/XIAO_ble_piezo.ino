/* Main Sketch: PiezoScanner.ino
   Logic: Handles sensor reading and triggers BLE updates
*/

const int PIEZO_PINS[] = {D0, D1, D2};
const int THRESHOLD = 150;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  setupBLE("XIAO_S3_Piezo");
  
  Serial.println("System Ready. Waiting for BLE connection...");
}

void loop() {
  if (isBLEConnected()) {
    for (int i = 0; i < 3; i++) {
      int val = analogRead(PIEZO_PINS[i]);
      
      if (val > THRESHOLD) {
        // Send data using the helper function in the other file
        sendPiezoData(i + 1, val);
        
        Serial.printf("Sensor %d Triggered: %d\n", i + 1, val);
        delay(20); // Debounce
      }
    }
  }
}