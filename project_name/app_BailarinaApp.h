#ifndef BAILARINA_APP_H
#define BAILARINA_APP_H

#include <Arduino.h>
#include <vector>
#include <Wire.h>
#include "rgb_lcd.h"
#include "wifi_WifiService.h"
#include "core_Sensor.h"
#include "core_Actuator.h"

#include "music_Song.h"

#include "sensors_UltrasonicSensor.h"
#include "sensors_LightSensor.h"
#include "sensors_TouchButton.h"

#include "actuators_BuzzerActuator.h"
#include "actuators_ServoActuator.h"
#include "actuators_LedActuator.h"

class BailarinaApp {
public:
  BailarinaApp(
    int pinServo, int pinBuzzer, int pinUS, int pinTouch, int pinLedRed, int pinLight,
    int lightThreshold,
    const char* line1, const char* line2
    void setSong(int i);
  void setMute(bool m);
  void setLine1(const String& s);
  void setLine2(const String& s);
  );

  void begin();
  void update();

private:
  // LCD
  rgb_lcd lcd_;
  const char* line1_;
  const char* line2_;

  // Sensors
  UltrasonicSensor us_;
  LightSensor light_;
  TouchButton touch_;
  std::vector<Sensor*> sensors_;

  // Actuators
  BuzzerActuator buzzer_;
  ServoActuator servo_;
  LedActuator led_;
  std::vector<Actuator*> actuators_;

  // Songs
  Song song0_, song1_, song2_;
  int currentSong_ = 0;

  // Notes constants
  static constexpr int NOTE_C4 = 262;
  static constexpr int NOTE_D4 = 294;
  static constexpr int NOTE_E4 = 330;
  static constexpr int NOTE_F4 = 349;
  static constexpr int NOTE_G4 = 392;
  static constexpr int NOTE_A4 = 440;
  static constexpr int NOTE_B4 = 494;
  static constexpr int NOTE_C5 = 523;

  void buildSongs();
  const Song& currentSong() const;
  void updateLcdText();

  bool mute_ = false;
  WifiService wifi_;
};

#endif
