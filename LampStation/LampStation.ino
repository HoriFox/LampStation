#include "definitions.h"
#include "server.h"
#include "button.h"
#include "mqtt.h"
#include "timer.h"
#include "memory.h"
#include "led.h"

#include "ESP8266mDNS.h"
#include "WiFiUdp.h"
#include "ArduinoOTA.h"

WiFiClient espClient;
PubSubClient mqtt(espClient);

bool heilFlag = false;
bool apWifiFlag = false;
bool startFlag = false;

Timer onlineTmr(ONLINE_TIMEOUT, false);  // таймаут онлайна
Timer hbTmr(PACKET_SEND_DELAY);          // период отправки пакета

void setupAP() {
  apWifiFlag = true;
  WiFi.mode(WIFI_AP);
  WiFi.softAP(("WebLamp_" + String(WiFi.macAddress())).c_str(), AP_PASSWORD);
  Serial.println("Switch to AP mode");
}

void setRandomColor() {
  data.color_red = uint16_t(random(256));
  data.color_green = uint16_t(random(256));
  data.color_blue = uint16_t(random(256));
  color_pro.setColor(data.color_red, data.color_green, data.color_blue);
  updateData();
}

void setup(void) {
  pinMode(TOUCH_PIN, INPUT);
  pinMode(BOARD_LED_PIN, OUTPUT);
  pinMode(ORING_LED_PIN, OUTPUT);

  delay(1000);
  Serial.begin(115200);

  EEPROM.begin(sizeof(data) + 1); // +1 на ключ
  memory_point.begin(0, 'd');     // запускаем менеджер памяти
  //memory_point.reset();

  if (data.ssid != NULL && data.password != NULL && data.ssid != "" && data.password != "") {
    WiFi.mode(WIFI_STA);
    WiFi.begin(data.ssid, data.password);

    color_pro.blinkNow(255, 255, 255, 600); // Белый

    int countTry = 0;
    while (WiFi.status() != WL_CONNECTED) {
      countTry += 1;
      delay(500);
      Serial.print(".");
      if (countTry >= MAX_COUNT_TRY) {
        Serial.println("Attempts limit reached");
        color_pro.blinkNow(255, 0, 0, 600); // Красный
        break;
      }
    }

    ArduinoOTA.onStart([]() {
      Serial.println("Start");
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      color_pro.blinkNow(255, 0, 0, 600, 2); // Красный, 2 моргания
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.setHostname(("WebLampESP_" + String(WiFi.macAddress())).c_str());
    ArduinoOTA.setPassword("5331");
    ArduinoOTA.begin();

    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("Connected to: ");
      Serial.println(data.ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      mqtt.setServer(data.mqtt_service_host, data.mqtt_service_port);
      mqtt.setCallback(callback);
    } else {
      Serial.println("Cant connect to wifi with data");
      setupAP();
    }
  } else {
    Serial.println("Dont exist wifi data");
    setupAP();
  }
  
  setupServer();
  Serial.println("HTTP-server started");

  if (apWifiFlag) { 
    color_pro.setAlpha(1); 
  } else {
    color_pro.blinkNow(0, 255, 0, 600); // Зелёный
  }

  color_pro.setColor(data.color_red, data.color_green, data.color_blue);
  Serial.println("Setup color_pro");
}

void loop(void) {
  // отправляем пакет что мы онлайн
  if (hbTmr.period() && !apWifiFlag) {
    if (startFlag) sendPacket(false);
    else startFlag = true;
  }

  int button = checkButton();
  switch (button) {
    case 1:
      color_pro.setAlpha(1);
      color_pro.checkoutPower();
      break;
    case 2:
      setRandomColor();
      break;
    case 3:
      color_pro.heil();
      heilFlag = true;
      break;
  }
  if (button != 0) {
    sendPacket(true);
    Serial.println("Button: " + String(button));
  }

  if (color_pro.isReachTarget() && apWifiFlag) {
    color_pro.setColor(0, 0, abs(color_pro.blue-255));
  }

  color_pro.updateLed();
  if (!apWifiFlag) mqttUpdate();
  handleRequests();
  ArduinoOTA.handle();
}
