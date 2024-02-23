#include <Arduino.h>


#include "../lib/mqtt.h"
#include "../lib/mqtt.cpp"

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);

  delay(3000);
  Serial.println("Starting...");

  wifiSetup();
  mqttSetup();

}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LED on");
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LED off");
  delay(500);
}