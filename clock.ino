// clock.cpp / clock.ino

#define __DEBUG

#include "clock.h"

#include <math.h>

using time_t = long;

time_t getCurrentTime() {
  return millis();
}

time_t diffTime(time_t t1, time_t t2) {
  return t1 - t2;
}

bool isLEDLightOn = false;

void ledLightOn(int ledPinNum = ledPin) {
  digitalWrite(ledPinNum, HIGH);
  if (ledPinNum == ledPin) isLEDLightOn = true;

  // debug session
  debug_println("LED Light on.");
  /////
}

void ledLightOff(int ledPinNum = ledPin) {
  digitalWrite(ledPinNum, LOW);
  if (ledPinNum == ledPin) isLEDLightOn = false;

  // debug session
  debug_println("LED Light off.");
  /////
}

time_t alarmRingTime;

bool isTimeUp() {
  time_t currentTime = getCurrentTime();
  time_t diffeTime = diffTime(currentTime, alarmRingTime);

  // debug session
  debug_print("Variable: time_t currentTime = ");
  debug_print(currentTime);
  debug_print("; diffTime(currentTime, alarmRingTime) = ");
  debug_println(diffeTime);
  /////

  return diffeTime >= 0;
}

bool isWaterLevelReached(int waterSensorPin = waterSensorInputPin) {
  double waterDepth = analogRead(waterSensorPin) / 410.0 * 4;

  // debug session
  debug_print("Calculated water depth from water sensor at pin ");
  debug_print(waterSensorPin);
  debug_print(": ");
  debug_println(waterDepth);
  /////

  return abs(waterDepth - targetWaterLevel) <= WATER_SENSOR_THRESHOLD;
}

void checkWaterLevel(time_t* timer) {
  bool flag = isWaterLevelReached();
  debug_print("isWaterLevelReached: ");
  debug_println(flag);
  if (flag) {
    if (timer == nullptr)
      *timer = getCurrentTime();
    ledLightOff();
  } else {
    ledLightOn();
    timer = nullptr;
  }
}

void play(Melody melody = little_star, int buzzerPinNum = buzzerPin) {
  time_t* alarmStopTimer = nullptr;
  unsigned playedTimes = 0;
  debug_print("music length: ");
  debug_println(melody.length);
  while (playedTimes++ < maxAlarmTimes) {
    debug_print("Times played: ");
    debug_println(playedTimes);
    if (alarmStopTimer != nullptr && diffTime(getCurrentTime(), *alarmStopTimer + ALARM_STOP_THRESHOLD) == 0)
      break;
    for (int thisNote = 0; thisNote < melody.length; thisNote++) {
      debug_println(melody.notes[thisNote]);
      debug_println(melody.noteDurations[thisNote]);
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / melody.noteDurations[thisNote];
      tone(buzzerPinNum, melody.notes[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      debug_println(pauseBetweenNotes);
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(buzzerPinNum);
      debug_print("At note: ");
      debug_println(thisNote);
      checkWaterLevel(alarmStopTimer);
      debug_print("alarmStopTimer = ");
      debug_println(alarmStopTimer == nullptr ? -1 : *alarmStopTimer);
      if (alarmStopTimer != nullptr && diffTime(getCurrentTime(), *alarmStopTimer + ALARM_STOP_THRESHOLD) == 0)
        break;
    }
  }
  // debug session
  ledLightOff();
  noTone(buzzerPinNum);
  digitalWrite(buzzerPin, HIGH);
  debug_println("Alarm stopped.");
  /////
}

void ringAlarm() {
  // debug session
  debug_println("Alarm triggered...");
  /////
  play();
}

//////////////////////////

bool isAlarmTriggered = true;
bool isAlarmRang = false;

void setup() {
  alarmRingTime = getCurrentTime() + alarmTimeRemainingMillis;

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(ledPin, LOW);

  isAlarmTriggered = true;
  isAlarmRang = false;

  // debug session
  debug_begin(9600);
  debug_println("Setup Complete.");
  debug_println("Output Pin Configuration: ");
  debug_print("\tbuzzerPin = ");
  debug_println(buzzerPin);
  debug_print("\tledPin = ");
  debug_println(ledPin);
  debug_println("Analog Input Pin Configuration:");
  debug_print("\twaterSensorInputPin = ");
  debug_println(waterSensorInputPin);
  debug_print("Current Time: ");
  debug_println(getCurrentTime());
  debug_print("alarmRingTime = ");
  debug_println(alarmRingTime);
  debug_print("maxAlarmTimes = ");
  debug_println(maxAlarmTimes);
  debug_println("Debug Session started: ");
  /////
}

void loop() {
  if (isTimeUp() && !isAlarmRang) {
    isAlarmTriggered = false;
    isAlarmRang = true;
  }
  if (!isAlarmTriggered) {
    isAlarmTriggered = true;
    ledLightOn();
    ringAlarm();
  }
}
