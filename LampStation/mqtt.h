#pragma once
#ifndef MQTT_H
#define MQTT_H

void mqttUpdate();
void connectMQTT();
void callback(char* topic, byte* payload, uint16_t len);
void sendPacket(bool forcibly);

#endif // MQTT_H
