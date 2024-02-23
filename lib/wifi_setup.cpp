#include <Arduino.h>
#include <WiFi.h>

#include "secret.h"
#include "mqtt.h"


extern "C" {
	#include "freertos/FreeRTOS.h"
	#include "freertos/timers.h"
}

TimerHandle_t wifiReconnectTimer;

void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(
    const_cast<char*>(SECRET_WIFI_SSID), 
    const_cast<char*>(SECRET_WIFI_PASSWORD)
  );
}

void wifiSetup() {
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));
  
  connectToWifi();
}
