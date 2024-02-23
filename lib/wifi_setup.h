// wifi_setup.h

#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <Arduino.h>
#include <WiFi.h>

extern "C" {
    #include "freertos/FreeRTOS.h"
    #include "freertos/timers.h"
}

extern TimerHandle_t wifiReconnectTimer;

void connectToWifi();
void wifiSetup();

#endif // WIFI_SETUP_H