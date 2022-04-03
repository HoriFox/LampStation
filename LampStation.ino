#include "definitions.h"
#include "server.h"
#include "button.h"
#include "mqtt.h"
#include "timer.h"
#include "memory.h"
#include "led.h"

WiFiClient espClient;
PubSubClient mqtt(espClient);
bool heilFlag = false;

bool apWifiFlag = false;

int maxCountTry = 20;

Timer onlineTmr(ONLINE_TIMEOUT, false);  // таймаут онлайна
Timer hbTmr(PACKET_SEND_DELAY); // период отправки пакета

void setup(void) {
  pinMode(TOUCH_PIN, INPUT);
  pinMode(BOARD_LED_PIN, OUTPUT);
  pinMode(ORING_LED_PIN, OUTPUT);

  delay(1000);
  Serial.begin(115200);

  EEPROM.begin(sizeof(data) + 1); // +1 на ключ
  memory_point.begin(0, 'd'); // запускаем менеджер памяти

  int countTry = 0;

  //memory_point.reset();

  if (data.ssid != NULL && data.password != NULL && data.ssid != "" && data.password != "") {
    WiFi.mode(WIFI_STA);
    WiFi.begin(data.ssid, data.password);
  
    while (WiFi.status() != WL_CONNECTED) {
      countTry += 1;
      delay(500);
      Serial.print(".");
      if (countTry >= maxCountTry) { 
        Serial.println("Attempts limit reached");
        break; 
      }
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("Connected to: ");
      Serial.println(data.ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    
      mqtt.setServer(data.mqtt_service_host, data.mqtt_service_port);
      mqtt.setCallback(callback);
    } else {
      Serial.println("Cant connect to wifi with data");
      apWifiFlag = true;
      WiFi.mode(WIFI_AP);
      WiFi.softAP(("WebLamp_" + String(WiFi.macAddress())).c_str(), AP_PASSWORD);
      Serial.println("Switch to AP mode");
    }
  } else {
    Serial.println("Dont exist wifi data");
    apWifiFlag = true;
    WiFi.mode(WIFI_AP);
    WiFi.softAP(("WebLamp_" + String(WiFi.macAddress())).c_str(), AP_PASSWORD);
    Serial.println("Switch to AP mode");
  }

  setupServer();
  Serial.println("HTTP server started");
}

void loop(void) {
  // отправляем пакет что мы онлайн
  if (hbTmr.period() && !apWifiFlag) sendPacket(false);

  int button = checkButton();
  if (button == 1) {
    color_pro.setAlpha(1);
    color_pro.checkoutPower();
    sendPacket(true);
  }
  if (button == 2) {
    color_pro.setRandomColor();
    sendPacket(true);
  }
  if (button == 3) {
    color_pro.heil();
    heilFlag = true;
    sendPacket(true);
  }
  if (button == -1) {}
  if (button != 0) {
    Serial.println("Кнопка: " + String(button));
  }

  color_pro.updateLed();
  if (!apWifiFlag) mqttUpdate();
  handleRequests();
}
