#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting...");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LED on");
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LED off");
  delay(500);
}