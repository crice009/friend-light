#ifndef MQTT_SETUP_H
#define MQTT_SETUP_H

#include <Arduino.h>
#include <AsyncMqttClient.h>

extern AsyncMqttClient mqttClient;
extern TimerHandle_t mqttReconnectTimer;

void connectToMqtt();
void onMqttConnect(bool sessionPresent);
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
void onMqttSubscribe(uint16_t packetId, uint8_t qos);
void onMqttUnsubscribe(uint16_t packetId);
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
void onMqttPublish(uint16_t packetId);
void mqttSetup();

#endif // MQTT_SETUP_H