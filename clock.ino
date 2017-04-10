// clock.cpp / clock.ino

#define __DEBUG

#include "clock.h"

#include <time.h>
#include <math.h>

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
  time_t currentTime = time(NULL);
  time_t diffTime = difftime(currentTime, alarmRingTime);

  // debug session
  debug_print("Variable: time_t currentTime = ");
  debug_print(currentTime);
  debug_print("; difftime(currentTime, alarmRingTime) = ");
  debug_println(diffTime);
  /////

  return diffTime >= 0;
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
  if (isWaterLevelReached()) {
    if (timer == nullptr)
      time(timer);
    ledLightOff();
  } else {
    ledLightOn();
    timer = nullptr;
  }
}

void play(Melody melody = little_star, int buzzerPinNum = buzzerPin) {
  time_t* alarmStopTimer = nullptr;
  unsigned playedTimes = 0;
  while (playedTimes++ < maxAlarmTimes) {
    if (alarmStopTimer != nullptr && difftime(time(NULL), *alarmStopTimer) == 0)
      break;
    for (int thisNote = 0; thisNote < little_star.length; thisNote++) {
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / melody.noteDurations[thisNote];
      tone(buzzerPinNum, melody.notes[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(buzzerPinNum);
      checkWaterLevel(alarmStopTimer);
      if (alarmStopTimer != nullptr && difftime(time(NULL), *alarmStopTimer + ALARM_STOP_THRESHOLD) == 0)
        break;
    }
  }
}

void ringAlarm() {
  // debug session
  debug_println("Alarm triggered...");
  /////
  play();
}

//////////////////////////

bool isAlarmTriggered;
bool isAlarmRang;

void setup() {
  alarmRingTime = time(NULL) + alarmTimeRemainingSecs;

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  isAlarmTriggered = true;
  isAlarmRang = false;

  // debug session
  debug_begin(9600);
  debug_println("Setup Complete.");
  debug_println("Debug Session started: ");
  debug_println("Output Pin Configuration: ");
  debug_print("\tbuzzerPin = ");
  debug_println(buzzerPin);
  debug_print("\tledPin = ");
  debug_println(ledPin);
  debug_println("Analog Input Pin Configuration:");
  debug_print("\twaterSensorInputPin = ");
  debug_println(waterSensorInputPin);
  debug_print("Current Time: ");
  debug_println(time(NULL));
  debug_print("alarmRingTime = ");
  debug_println(alarmRingTime);
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
