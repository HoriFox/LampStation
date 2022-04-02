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
  Serial.println(String(data.ssid) + " " + 
                 String(data.password));

  updateData();

  Serial.println("Данные ssid и пароля записаны в память");
  
  server.send(200, "text/plain", "savePreData");

  //ESP.reset();
  //ESP.restart();
}

void loadData() {
  String response = "none";
  if (server.arg("firstFlag") == "true") {
  response = "ssid:" + String(data.ssid)
          + " password:" + String(data.password)
          + " local-device-name:" + String(data.local_device_name)
          + " remote-device-name:" + String(data.remote_device_name)
          + " ip-mqtt-service:" + String(data.ip_mqtt_service)
          + " port-mqtt-service:" + String(data.port_mqtt_service);
  }

  server.send(200, "text/plain", response);
}

void saveData() {
  bool mqtt_reconnect = false;

  if(strcmp(server.arg("local_device_name").c_str(), data.local_device_name) != 0 || 
     strcmp(server.arg("ip_mqtt_service").c_str(), data.ip_mqtt_service) != 0 ||
     server.arg("port_mqtt_service").toInt() != data.port_mqtt_service) {
     mqtt_reconnect = true;
  }
  
  strncpy(data.ssid, server.arg("ssid").c_str(), sizeof(data.ssid));
  strncpy(data.password, server.arg("password").c_str(), sizeof(data.password));
  strncpy(data.local_device_name, server.arg("local_device_name").c_str(), sizeof(data.local_device_name));
  strncpy(data.remote_device_name, server.arg("remote_device_name").c_str(), sizeof(data.remote_device_name));
  strncpy(data.ip_mqtt_service, server.arg("ip_mqtt_service").c_str(), sizeof(data.ip_mqtt_service));
  data.port_mqtt_service = server.arg("port_mqtt_service").toInt();

  updateData();

  Serial.println("Список данных записан в память");
  
  Serial.println(String(data.ssid) + " " + 
                 String(data.password) + " " + 
                 String(data.local_device_name) + " " + 
                 String(data.remote_device_name) + " " + 
                 String(data.ip_mqtt_service) + " " + 
                 data.port_mqtt_service);

  server.send(200, "text/plain", "saveData");

  if(mqtt_reconnect) {
    Serial.println("Изменены данные MQTT, переподключаюсь");
    mqtt.disconnect();
    mqtt.setServer(data.ip_mqtt_service, data.port_mqtt_service);
    connectMQTT();
  }
}

//void metricsPage() {
//  if (!workFlagMetrics) {
//    static const size_t BUFSIZE = 1024;
//    static const char compile_date[] = __DATE__ " " __TIME__;
//    static const char *response_template =
//          "# HELP esp_module_reboot Device reboot count.\n"
//          "# TYPE esp_module_reboot gauge\n"
//          "# UNIT esp_module_reboot \n"
//          "esp_module_reboot %d\n"
//          "# HELP esp_module_uptime Device uptime in ms.\n"
//          "# TYPE esp_module_uptime gauge\n"
//          "# UNIT esp_module_uptime \n"
//          "esp_module_uptime %d\n"
//          "# HELP esp_module_info Device info.\n"
//          "# TYPE esp_module_info gauge\n"
//          "# UNIT esp_module_info \n"
//          "esp_module_info{build=\"%s\",date=\"%s\"} 1\n";
//    uint32_t count_reboot = 0;
//    uint32_t ms = millis();
//    char response[BUFSIZE];
//    snprintf(response, BUFSIZE, response_template, count_reboot, ms, BUILD, compile_date);
//    server.send(200, "text/plain; charset=utf-8", response);
//
//    workFlagMetrics = true;
//    timer1_write(DELAY_SWITCH);
//  } 
//  else 
//  {
//    server.send(503, "text/plain; charset=utf-8", "custom response - reset request due to restriction");
//  }
//}

void restartPage() {
  server.send(200, "text/plain", "restart esp");
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
  server.onNotFound(fileNotFound);
  server.begin();
}

void handleRequests() {
  server.handleClient();
}
