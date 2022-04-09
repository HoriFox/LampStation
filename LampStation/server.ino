#include "server.h"
#include "led.h"
#include "memory.h"

//void ICACHE_RAM_ATTR onTimerRR(){
//  workFlagMetrics = false;
//  workFlagRelay = false;
//}

void serverRoot() {
  if (apWifiFlag) {
    server.send(200, "text/html", LOGIN_page);
  } else {
    server.send(200, "text/html", MAIN_page);
  }
}

void preData() {
  strncpy(data.ssid, server.arg("ssid").c_str(), sizeof(data.ssid));
  strncpy(data.password, server.arg("password").c_str(), sizeof(data.password));
  Serial.println(String(data.ssid) + " " + String(data.password));

  updateData();
  Serial.println("Данные ssid и пароля записаны в память");
  server.send(200, "text/plain", "savePreData");
  ESP.restart();
}

void loadData() {
  String response = "none";
  if (server.arg("firstFlag") == "true") {
  response = "ssid:" + String(data.ssid)
          //+ " password:" + String(data.password)
          + " local-device-name:" + String(data.local_device_name)
          + " remote-device-name:" + String(data.remote_device_name)
          + " mqtt-service-host:" + String(data.mqtt_service_host)
          + " mqtt-service-port:" + String(data.mqtt_service_port)
          + " mqtt-service-user:" + String(data.mqtt_service_user)
          //+ " mqtt-service-pass:" + String(data.mqtt_service_pass)
          + " light:" + String(color_pro.power)
          + " color-red:" + String(color_pro.targetRed)
          + " color-green:" + String(color_pro.targetGreen)
          + " color-blue:" + String(color_pro.targetBlue)
          + " pair-status:" + String(!onlineTmr.elapsed())
          + " mqtt-status:" + String(mqtt.connected());
  }

  server.send(200, "text/plain", response);
}

void saveData() {
  bool wifi_reconnect = false;
  if (strcmp(server.arg("ssid").c_str(), data.ssid) != 0 || 
      server.arg("password").length() >= MIN_WIFI_PASS_LEN && strcmp(server.arg("password").c_str(), data.password) != 0) {
    wifi_reconnect = true;
  }
  
  bool mqtt_reconnect = false;
  if (strcmp(server.arg("local_device_name").c_str(), data.local_device_name) != 0 || 
      strcmp(server.arg("mqtt_service_host").c_str(), data.mqtt_service_host) != 0 ||
      strcmp(server.arg("mqtt_service_user").c_str(), data.mqtt_service_user) != 0 ||
      strcmp(server.arg("mqtt_service_pass").c_str(), data.mqtt_service_pass) != 0 ||
      server.arg("mqtt_service_port").toInt() != data.mqtt_service_port) {
    mqtt_reconnect = true;
  }

  strncpy(data.ssid, server.arg("ssid").c_str(), sizeof(data.ssid));
  if (server.arg("password").length() >= MIN_WIFI_PASS_LEN) {
    strncpy(data.password, server.arg("password").c_str(), sizeof(data.password));
  }
  strncpy(data.local_device_name, server.arg("local_device_name").c_str(), sizeof(data.local_device_name));
  strncpy(data.remote_device_name, server.arg("remote_device_name").c_str(), sizeof(data.remote_device_name));
  strncpy(data.mqtt_service_host, server.arg("mqtt_service_host").c_str(), sizeof(data.mqtt_service_host));
  data.mqtt_service_port = server.arg("mqtt_service_port").toInt();
  strncpy(data.mqtt_service_user, server.arg("mqtt_service_user").c_str(), sizeof(data.mqtt_service_user));
  if (server.arg("mqtt_service_pass").length() >= MIN_MQTT_PASS_LEN) {
     strncpy(data.mqtt_service_pass, server.arg("mqtt_service_pass").c_str(), sizeof(data.mqtt_service_pass)); 
  }
  data.color_red = server.arg("color_red").toInt();
  data.color_green = server.arg("color_green").toInt();
  data.color_blue = server.arg("color_blue").toInt();
  
  updateData();
  
  color_pro.setColor(data.color_red, data.color_green, data.color_blue);
  color_pro.checkoutPower(false, server.arg("light").toInt());  
  sendPacket(true);
  onlineTmr.expire();

  Serial.println("Список данных записан в память");
  Serial.println(String(data.ssid) + " " + 
                 String(data.password) + " " + 
                 String(data.local_device_name) + " " + 
                 String(data.remote_device_name) + " " + 
                 String(data.mqtt_service_host) + " " + 
                 String(data.mqtt_service_user) + " " + 
                 String(data.mqtt_service_pass) + " " + 
                 data.mqtt_service_port + " " +
                 data.color_red + " " + data.color_green + " " + data.color_blue);

  server.send(200, "text/plain", "saveData");

  if (wifi_reconnect) {
    Serial.println("Изменены данные WiFi, перезагружаюсь");
    ESP.restart();
  }

  if (mqtt_reconnect) {
    Serial.println("Изменены данные MQTT, переподключаюсь");
    mqtt.disconnect();
    mqtt.setServer(data.mqtt_service_host, data.mqtt_service_port);
    connectMQTT();
  }
}

void restartPage() {
  server.send(200, "text/plain", "Restart ESP");
  ESP.restart();
}

void resetPage() {
  server.send(200, "text/plain", "Reset ESP to defaults");
  //resetAllData();
  //Serial.println("EEPROM очищен");
  ESP.restart();
}

void fileNotFound() {
  server.send(404, "text/plain", "File Not Found");
}

void setupServer() {
//  timer1_attachInterrupt(onTimerRR);
//  timer1_enable(TIM_DIV256, TIM_EDGE, TIM_SINGLE);
  
  server.on("/", serverRoot);
  server.on("/preData", preData);
  server.on("/loadData", loadData);
  server.on("/saveData", saveData);
  server.on("/restart", restartPage);
  server.on("/reset", resetPage);
  server.onNotFound(fileNotFound);
  server.begin();
}

void handleRequests() {
  server.handleClient();
}
