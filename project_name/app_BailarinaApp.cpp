#include "app_BailarinaApp.h"
static BailarinaApp* gApp = nullptr;
BailarinaApp::BailarinaApp(
  int pinServo, int pinBuzzer, int pinUS, int pinTouch, int pinLedRed, int pinLight,
  int lightThreshold,
  const char* line1, const char* line2
)

: wifi_("kvisbal", "99999999"),
  lcd_(),
  line1_(line1), line2_(line2),
  us_(pinUS),
  light_(pinLight, lightThreshold),
  touch_(pinTouch, 80),
  buzzer_(pinBuzzer),
  servo_(pinServo, 10, 170, 5),
  led_(pinLedRed)
{
  sensors_ = { &us_, &light_, &touch_ };
  actuators_ = { &buzzer_, &servo_, &led_ };
}

void BailarinaApp::begin() {
  Wire.begin(D2, D1);
  gApp = this;

  wifi_.onSetSong([](int i){ if (gApp) gApp->setSong(i); });
  wifi_.onSetMute([](bool m){ if (gApp) gApp->setMute(m); });
  wifi_.onSetLine1([](const String& s){ if (gApp) gApp->setLine1(s); });
  wifi_.onSetLine2([](const String& s){ if (gApp) gApp->setLine2(s); });

  wifi_.begin();

  lcd_.begin(16,2);
  lcd_.setRGB(255,255,255);

  for (auto* a : actuators_) a->begin();
  for (auto* s : sensors_) s->begin();

  buildSongs();
  updateLcdText();
}

void BailarinaApp::update() {
  wifi_.loop();
  if (touch_.clicked()) {
    currentSong_ = (currentSong_ + 1) % 3;
    updateLcdText();
  }

  float dist = us_.distanceCm();
  bool nightMode = light_.isNight();
  bool dancing = (dist > 0 && dist <= 10.0f);
  String json = "{";
  json += "\"dist\":" + String(dist, 1) + ",";
  json += "\"light\":" + String(light_.value()) + ",";
  json += "\"night\":" + String(nightMode ? 1 : 0) + ",";
  json += "\"dancing\":" + String(dancing ? 1 : 0) + ",";
  json += "\"song\":" + String(currentSong_) + ",";
  json += "\"mute\":" + String(mute_ ? 1 : 0);
  json += "}";
  wifi_.setStatusJson(json);

  if (!dancing) {
    buzzer_.stop();
    servo_.home();
    led_.off();
    delay(100);
    return;
  }

  led_.on();

  const Song& s = currentSong();
  for (size_t i = 0; i < s.size(); i++) {
    if (touch_.clicked()) {
      currentSong_ = (currentSong_ + 1) % 3;
      updateLcdText();
      break;
    }

    servo_.step();
    bool soundEnabled = (!mute_) && (!nightMode);
    buzzer_.playNote(s[i], soundEnabled);
    wifi_.loop(); // importante: entre notas

  }
}

void BailarinaApp::buildSongs() {
  song0_
    << Note{NOTE_C5,4} << Note{NOTE_G4,4} << Note{NOTE_E4,4} << Note{NOTE_A4,4}
    << Note{NOTE_B4,4} << Note{NOTE_A4,4} << Note{NOTE_E4,4} << Note{NOTE_G4,4}
    << Note{NOTE_C5,4} << Note{NOTE_G4,4} << Note{NOTE_E4,4} << Note{NOTE_F4,4}
    << Note{NOTE_G4,4} << Note{NOTE_E4,4} << Note{NOTE_D4,4} << Note{NOTE_C4,4};

  song1_
    << Note{NOTE_C4,8} << Note{NOTE_D4,8} << Note{NOTE_E4,8} << Note{NOTE_F4,8}
    << Note{NOTE_G4,8} << Note{NOTE_A4,8} << Note{NOTE_B4,8} << Note{NOTE_C5,4}
    << Note{NOTE_C5,8} << Note{NOTE_B4,8} << Note{NOTE_A4,8} << Note{NOTE_G4,8}
    << Note{NOTE_F4,8} << Note{NOTE_E4,8} << Note{NOTE_D4,8} << Note{NOTE_C4,4};

  song2_
    << Note{NOTE_G4,16} << Note{NOTE_G4,16} << Note{NOTE_G4,8} << Note{NOTE_A4,4} << Note{NOTE_G4,4}
    << Note{NOTE_G4,16} << Note{NOTE_G4,16} << Note{NOTE_G4,8}
    << Note{NOTE_G4,16} << Note{NOTE_G4,16} << Note{NOTE_G4,8} << Note{NOTE_A4,4}
    << Note{NOTE_G4,16} << Note{NOTE_G4,16} << Note{NOTE_G4,8} << Note{NOTE_G4,2};
}

const Song& BailarinaApp::currentSong() const {
  if (currentSong_ == 0) return song0_;
  if (currentSong_ == 1) return song1_;
  return song2_;
}

void BailarinaApp::updateLcdText() {
  lcd_.clear();
  lcd_.setCursor(0,0);
  lcd_.print(line1_);
  lcd_.setCursor(0,1);

  if (currentSong_ == 0) lcd_.print("chanson 1");
  else if (currentSong_ == 1) lcd_.print("chanson 2");
  else lcd_.print("capibara");
}
void BailarinaApp::setSong(int i) {
  if (i < 0) i = 0;
  currentSong_ = i % 3;
  updateLcdText();
}

void BailarinaApp::setMute(bool m) {
  mute_ = m;
  if (mute_) buzzer_.stop();
}

void BailarinaApp::setLine1(const String& s) {
  // si quieres, guarda String; si no, ignóralo y deja fijo
  // mínimo BE: puedes imprimir directo:
  lcd_.setCursor(0,0);
  lcd_.print("                ");
  lcd_.setCursor(0,0);
  lcd_.print(s.substring(0,16));
}

void BailarinaApp::setLine2(const String& s) {
  lcd_.setCursor(0,1);
  lcd_.print("                ");
  lcd_.setCursor(0,1);
  lcd_.print(s.substring(0,16));
}
