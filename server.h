#pragma once
#ifndef SERVER_H
#define SERVER_H

#include "definitions.h"
#include <ESP8266WebServer.h>
#include <PubSubClient.h>

#include "memory.h"
#include "led.h"
#include "pages.h"
#include "mqtt.h"

ESP8266WebServer server(80);

void serverRoot();
void switchPage();
void restartPage();
void resetPage();
void fileNotFound();
void setupServer();
void handleRequests();

#endif // SERVER_H
