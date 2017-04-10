// clock.cpp / clock.ino

#include "clock.h"

#include <time.h>
#include <math.h>

bool isLEDLightOn = false;

void ledLightOn(int ledPinNum = ledPin) {
  digitalWrite(ledPinNum, HIGH);
  if (ledPinNum == ledPin) isLEDLightOn = true;
}

void ledLightOff(int ledPinNum = ledPin) {
  digitalWrite(ledPinNum, LOW);
  if (ledPinNum == ledPin) isLEDLightOn = false;
}

time_t alarmRingTime;

bool isTimeUp() {
  time_t currentTime = time(NULL);
  return difftime(currentTime, alarmRingTime) >= 0;
}

bool isWaterLevelReached(int waterSensorPin = waterSensorInputPin) {
  double waterDepth = analogRead(waterSensorPin) / 410.0 * 4;

  // debug session
  if (DEBUG) {
    Serial.print("Calculated water depth from water sensor at pin ");
    Serial.print(waterSensorPin);
    Serial.print(": ");
    Serial.println(waterDepth);
  }
  /////

  return abs(waterDepth - targetWaterLevel) <= WATER_SENSOR_THRESHOD;
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
      if (alarmStopTimer != nullptr && difftime(time(NULL), *alarmStopTimer) == 0)
        break;
    }
  }
}

void ringAlarm() {
  play();
}

//////////////////////////

bool isAlarmTriggered;
bool isAlarmRang;

void setup() {
  alarmRingTime = time(NULL) + alarmTimeRemainingSecs;
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  isAlarmTriggered = true;
  isAlarmRang = false;

  // debug session
  if (DEBUG) {
    Serial.begin(9600);
    Serial.println("Debug Session started: ");
  }
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
