#include "web.h"

const char* host = "mark2";
const char* ssid = STASSID;
const char* password = STAPSK;
const char* error_text = "";
bool block = 0;

IPAddress ip;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

//const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

void update_loop(void)
{
  web();
  while (1)
  {
    wb_loop();
  }
}

void web(void)
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    //WiFi.begin(ssid, password);
    //    Serial.println("WiFi failed, retrying.");
    //}

    MDNS.begin(host);

    httpUpdater.setup(&httpServer);
    httpServer.begin();

    MDNS.addService("http", "tcp", 80);
    //  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);

    ip = WiFi.localIP();
  }
  else
  {
    
  }
}

void wb_loop(void)
{
  httpServer.handleClient();
  MDNS.update();
}
