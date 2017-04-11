// alarm_config.h
#define ALARM_CONFIG_H

#ifndef ARDUINO_H
#include "Arduino.h"
#endif

const int maxAlarmTimes = 10; // how many times the alarm rings
const double alarmTimeRemaining = 1; // unit: minute; must be larger than 0;
const int ALARM_STOP_THRESHOLD = 300; // unit: ms

const long alarmTimeRemainingMillis = alarmTimeRemaining * 60 * 1000;
