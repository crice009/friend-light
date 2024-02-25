#include <Arduino.h>
#include "../lib/secret.h"

/*
This example uses FreeRTOS softwaretimers as there is no built-in Ticker library
*/


#include <WiFi.h>
extern "C" {
	#include "freertos/FreeRTOS.h"
	#include "freertos/timers.h"
}
#include <AsyncMqttClient.h>

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(SECRET_WIFI_SSID, SECRET_WIFI_PASSWORD);
}

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void WiFiEvent(WiFiEvent_t event) {
    Serial.printf("[WiFi-event] event: %d\n", event);
    switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        connectToMqtt();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("WiFi lost connection");
        xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
        xTimerStart(wifiReconnectTimer, 0);
        break;
    }
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  uint16_t packetIdSub = mqttClient.subscribe("test/lol", 2);
  Serial.print("Subscribing at QoS 2, packetId: ");
  Serial.println(packetIdSub);
  uint16_t packetIdSubColor = mqttClient.subscribe("test/lol/color", 2);
  Serial.print("Subscribing at QoS 2, packetId: ");
  Serial.println(packetIdSubColor);
  mqttClient.publish("test/lol", 0, true, "test 1");
  Serial.println("Publishing at QoS 0");
  uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
  Serial.print("Publishing at QoS 1, packetId: ");
  Serial.println(packetIdPub1);
  uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
  Serial.print("Publishing at QoS 2, packetId: ");
  Serial.println(packetIdPub2);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");

  if (WiFi.isConnected()) {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

#include <cstring>

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  Serial.println("Message received.");
  Serial.print("  topic: ");
  Serial.println(topic);
  Serial.print("  payload: ");
  Serial.println(payload);

  // Check if the topic is the color topic
  if (strcmp(topic, "test/lol/color") != 0) {
    return;
  }

  Serial.println("message is in color category.");

  
  // Check if the payload is a valid hex color code
  size_t payloadLen = strlen(payload);
  // Check if the payload is a valid hex color code
  bool isValidHex = true;
  for (size_t i = 0; i < payloadLen; i++) {
    if (!isxdigit(payload[i])) {
      isValidHex = false;
      break;
    }
  }

  // Return the color code, if valid or a default color
  const char * hexColor = "000000";
  if (isValidHex) {
    hexColor = payload;
  }

  char r[3] = {hexColor[0], hexColor[1], '\0'};
  char g[3] = {hexColor[2], hexColor[3], '\0'};
  char b[3] = {hexColor[4], hexColor[5], '\0'};

  int rgb[3];
  rgb[0] = strtol(r, NULL, 16);
  rgb[1] = strtol(g, NULL, 16);
  rgb[2] = strtol(b, NULL, 16);

  Serial.print("  r: ");
  Serial.println(rgb[0]);
  Serial.print("  g: ");
  Serial.println(rgb[1]);
  Serial.print("  b: ");
  Serial.println(rgb[2]);
  #ifdef RGB_BUILTIN
  neopixelWrite(RGB_BUILTIN,rgb[0],rgb[1],rgb[2]);
  #endif
}

void onMqttPublish(uint16_t packetId) {
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

  WiFi.onEvent(WiFiEvent);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(SECRET_MQTT_SERVER, SECRET_MQTT_PORT);

  connectToWifi();
}

void loop() {
}