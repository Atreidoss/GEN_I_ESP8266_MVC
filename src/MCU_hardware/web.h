#ifndef web_h_
#define web_h_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#ifndef SETTINGS_WIFI
#define STASSID "mark2"     // Имя сети WiFi
#define STAPSK "mark2mark2" // Пароль сети WiFi
#endif

class web
{
public:
    web() : _httpServer(80)
    {
    }
    void handle(void)
    {
        _httpServer.handleClient();
        MDNS.update();
    }

    void setMode(bool isWifiOn)
    {
        if (isWifiOn)
        {
            start();
        }
        else
        {
            stop();
        }
    }
    
    String getIP()
    {
        return _ip.toString();
    }

private:
    IPAddress _ip;
    ESP8266WebServer _httpServer;
    ESP8266HTTPUpdateServer _httpUpdater;

    const char *host = "mark2";
    const char *ssid = STASSID;
    const char *password = STAPSK;
    const char *error_text = "";
    const char *serverIndex;
    bool _onceInit = false;

    void init(void)
    {
        MDNS.begin(host);
        _httpUpdater.setup(&_httpServer);
        _httpServer.begin();
        MDNS.addService("http", "tcp", 80);
    }

    void start(void)
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        if (WiFi.waitForConnectResult() == WL_CONNECTED)
        {
            if (_onceInit == false)
            {
                init();
                _onceInit = true;
            }
            _ip = WiFi.localIP();
        }
    }

    void stop(void)
    {
        WiFi.mode(WIFI_OFF);
    }
};

#endif