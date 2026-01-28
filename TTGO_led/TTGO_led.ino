// If it doesn't blink, try changing this to 25
const int LED_PIN = 2; 

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  
  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("ESP32 Setup Complete. Starting Blink...");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);   // Turn the LED on
  Serial.println("LED ON");
  delay(1000);                  // Wait for a second
  
  digitalWrite(LED_PIN, LOW);    // Turn the LED off
  Serial.println("LED OFF");
  delay(1000);                  // Wait for a second
}