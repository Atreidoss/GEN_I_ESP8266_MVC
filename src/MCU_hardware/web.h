#ifndef web_h
#define web_h

#include "settings.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#ifndef STASSID
#define STASSID "mark2"
#define STAPSK "mark2mark2"
#endif

class WebServer
{
public:
    WebServer();

private:
};

#endif