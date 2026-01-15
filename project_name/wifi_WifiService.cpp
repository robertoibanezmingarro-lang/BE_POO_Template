#include "wifi_WifiService.h"

WifiService::WifiService(const char* ssid, const char* pass)
: ssid_(ssid), pass_(pass) {}

void WifiService::onSetSong(void (*fn)(int)) { setSong_ = fn; }
void WifiService::onSetMute(void (*fn)(bool)) { setMute_ = fn; }
void WifiService::onSetLine1(void (*fn)(const String&)) { setL1_ = fn; }
void WifiService::onSetLine2(void (*fn)(const String&)) { setL2_ = fn; }

void WifiService::setStatusJson(const String& json) { statusJson_ = json; }

void WifiService::begin() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_, pass_);

  // No te quedes bloqueado “esperando WiFi”
  unsigned long t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < 8000) {
    delay(200);
    yield();
  }

  routes();
  server_.begin();

  Serial.print("WiFi: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("connected, IP=");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("not connected (server still running)");
  }
}

void WifiService::loop() {
  server_.handleClient();
  yield();
}

void WifiService::routes() {
  server_.on("/", [this]() {
    String html =
      "<html><body>"
      "<h2>Bailarina ESP8266</h2>"
      "<p><a href='/status'>/status</a></p>"
      "<p>Song: <a href='/song?i=0'>0</a> <a href='/song?i=1'>1</a> <a href='/song?i=2'>2</a></p>"
      "<p>Mute: <a href='/mute?on=1'>ON</a> <a href='/mute?on=0'>OFF</a></p>"
      "</body></html>";
    server_.send(200, "text/html", html);
  });

  server_.on("/status", [this]() {
    server_.send(200, "application/json", statusJson_);
  });

  server_.on("/song", [this]() {
    if (!server_.hasArg("i")) { server_.send(400, "text/plain", "missing i"); return; }
    int i = server_.arg("i").toInt();
    if (setSong_) setSong_(i);
    server_.send(200, "text/plain", "ok");
  });

  server_.on("/mute", [this]() {
    if (!server_.hasArg("on")) { server_.send(400, "text/plain", "missing on"); return; }
    bool on = server_.arg("on").toInt() == 1;
    if (setMute_) setMute_(on);
    server_.send(200, "text/plain", "ok");
  });

  server_.on("/lcd", [this]() {
    if (server_.hasArg("l1") && setL1_) setL1_(server_.arg("l1"));
    if (server_.hasArg("l2") && setL2_) setL2_(server_.arg("l2"));
    server_.send(200, "text/plain", "ok");
  });
}
