#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Starting...");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LED on");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LED off");
  delay(500);

  #ifdef RGB_BUILTIN
  Serial.println("LED is RED");
  neopixelWrite(RGB_BUILTIN,255,  0,  0); // Red
  delay(1000);
  Serial.println("LED is GREEN");
  neopixelWrite(RGB_BUILTIN,  0,255,  0); // Green
  delay(1000);
  Serial.println("LED is BLUE");
  neopixelWrite(RGB_BUILTIN,  0,  0,255); // Blue
  delay(1000);
  Serial.println("LED off");
  neopixelWrite(RGB_BUILTIN,0,0,0); // Off / black
  delay(500);
  #endif
}