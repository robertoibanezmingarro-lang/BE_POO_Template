#ifndef WIFI_SERVICE_H
#define WIFI_SERVICE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class WifiService {
public:
  WifiService(const char* ssid, const char* pass);

  void begin();
  void loop();

  // Estado que publicaremos
  void setStatusJson(const String& json);

  // Callbacks para controlar la app desde HTTP
  void onSetSong(void (*fn)(int));
  void onSetMute(void (*fn)(bool));
  void onSetLine1(void (*fn)(const String&));
  void onSetLine2(void (*fn)(const String&));

private:
  const char* ssid_;
  const char* pass_;
  ESP8266WebServer server_{80};

  String statusJson_ = "{}";

  void (*setSong_)(int) = nullptr;
  void (*setMute_)(bool) = nullptr;
  void (*setL1_)(const String&) = nullptr;
  void (*setL2_)(const String&) = nullptr;

  void routes();
};

#endif
