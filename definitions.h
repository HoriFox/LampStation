#pragma once
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define MQTT_HEADER "LS:"    // Data packet header

#define BOARD_LED_PIN   2    // Assigning Pin 2 as the name LED
#define TOUCH_PIN       4    // Gpio4, touch sensor
#define ORING_LED_PIN   5    // Gpio5, led oring
#define NUMPIXELS       12

#define AP_PASSWORD "14159265"  // Default AP password

#define PACKET_SEND_DELAY 10000 // ms
#define ONLINE_TIMEOUT    22000 // ms

#include "version.h"

#endif // DEFINITIONS_H
