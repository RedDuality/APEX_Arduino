/*
  Piezo Impact Detector for TTGO ESP32 LoRa
*/

const int PIEZO1_PIN = D0; // Analog pin connected to the piezo
const int PIEZO2_PIN = D1; // Analog pin connected to the piezo
const int PIEZO3_PIN = D2; // Analog pin connected to the piezo

const int THRESHOLD = 50; // Minimum vibration to trigger a print (0-4095)

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Piezo Sensor Ready!");
  
  // Set ADC resolution to 12 bits (0-4095)
  analogReadResolution(12);
}

void loop() {
  int s1 = analogRead(PIEZO1_PIN);
  int s2 = analogRead(PIEZO2_PIN);
  int s3 = analogRead(PIEZO3_PIN);

  if (s1 > THRESHOLD) {
    Serial.printf("Sensor 1: %d\n", s1);
  }
  if (s2 > THRESHOLD) {
    Serial.printf("Sensor 2: %d\n", s2);
  }
  if (s3 > THRESHOLD) {
    Serial.printf("Sensor 3: %d\n", s3);
  }

  // Smaller delay or no delay for better sensitivity
  delay(100); 
}




