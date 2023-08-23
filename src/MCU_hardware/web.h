#ifndef web_h_
#define web_h_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#ifndef STASSID
//#define STASSID "Atreidos"
#define STASSID "mark2"
#define STAPSK  "mark2mark2" 
#endif

extern const char* host;
extern const char* ssid;
extern const char* password;
extern IPAddress ip;
extern bool block;
extern const char* error_text;

extern const char* serverIndex;

void web(void);
void wb_loop(void);
void update_loop(void);

#endif 
