#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include <EEManager.h>

struct LampData {
  char ssid[32] = "";
  char password[32] = "";
  char local_device_name[20] = "AG_lamp_1";
  char remote_device_name[20] = "AG_lamp_2";
  char mqtt_service_host[32] = "argobay.ml";
  uint16_t mqtt_service_port = 1883;
  char mqtt_service_user[32] = "";
  char mqtt_service_pass[64] = "";
  uint16_t color_red = 100;
  uint16_t color_green = 100;
  uint16_t color_blue = 100;
};

LampData data;
EEManager memory_point(data);

void updateData() {
  memory_point.updateNow();
}

#endif // MEMORY_H
