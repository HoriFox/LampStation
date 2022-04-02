#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include <EEManager.h>

struct LampData {
  char ssid[32] = "";
  char  password[32] = "";
  //char ssid[32] = "xxxxxx";
  //char  password[32] = "xxxxxx";
  char  local_device_name[20] = "AG_lamp_1";
  char  remote_device_name[20] = "AG_lamp_2";
  char ip_mqtt_service[32] = "public.i";
  uint16_t port_mqtt_service = 1883;
};

LampData data;
EEManager memory_point(data);

void updateData() {
  memory_point.updateNow();
}

#endif // MEMORY_H
