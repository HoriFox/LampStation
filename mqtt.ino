#include <PubSubClient.h>
#include "led.h"
#include "memory.h"

// опрашиваем mqtt
void mqttUpdate() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();
}

void connectMQTT() {
  // задаём случайный ID
  String id("WebLamp-");
  id += String(random(0xffffff), HEX);
  Serial.println(id); 
  // подписываемся на своё имя
  if (mqtt.connect(id.c_str(), data.mqtt_service_user, data.mqtt_service_pass)) {
    mqtt.subscribe(data.local_device_name);
  }
  delay(1000);
  if (mqtt.connected()) {
    Serial.println("Connected to MQTT server!"); 
  }
}

int getFromIndex(char* str, int idx, char div = ',') {
  int val = 0;
  uint16_t i = 0;
  int count = 0;
  bool sign = 0;
  while (str[i]) {
    if (idx == count) {
      if (str[i] == div) break;
      if (str[i] == '-') sign = -1;
      else {
        val *= 10L;
        val += str[i] - '0';
      }
    } else if (str[i] == div) count++;
    i++;
  }
  return sign ? -val : val;
}

// тут нам прилетел пакет от удалённой лампы
void callback(char* topic, byte* payload, uint16_t len) {
  payload[len] = '\0';        // закрываем строку
  char* str = (char*)payload; // для удобства
  Serial.println("Получили сообщение: " + String(str));
  
  // не наш пакет, выходим
  if (strncmp(str, MQTT_HEADER, strlen(MQTT_HEADER))) return;

  str += strlen(MQTT_HEADER);   // смещаемся для удобства чтения

  color_pro.checkoutPower(false, getFromIndex(str, 0));
  color_pro.setColor(getFromIndex(str, 1), getFromIndex(str, 2), getFromIndex(str, 3));
  
  if (getFromIndex(str, 4)) { 
    // Подмигнуть, активация действия
    color_pro.heil();
  }
  
  onlineTmr.restart();  // перезапуск таймера онлайна
}

// отправляем пакет
void sendPacket(bool forcibly) {
  // LS:power,color,wink
  String s;
  s.reserve(18);
  s += "LS:";
  s += color_pro.power;
  s += ',';
  s += color_pro.targetRed;
  s += ',';
  s += color_pro.targetGreen;
  s += ',';
  s += color_pro.targetBlue;
  s += ',';
  s += heilFlag;
  heilFlag = 0;   // сбрасываем флаг подмигивания

  if (forcibly) {
    Serial.println("Отправка сообщения (принудительная из-за активности): " + s); 
  } else {
    Serial.println("Отправка сообщения (регулярная): " + s); 
  }
  
  // отправляем
  mqtt.publish(data.remote_device_name, s.c_str());
  
  // принудительно сбрасываем таймер отправки, 
  // чтобы не отправлять слишком часто
  hbTmr.restart();
}
