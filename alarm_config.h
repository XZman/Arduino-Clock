// alarm_config.h
#define ALARM_CONFIG_H

const unsigned maxAlarmTimes = 10; // how many times the alarm rings
const double alarmTimeRemaining = 1; // unit: minute; must be larger than 0;
const unsigned long ALARM_STOP_THRESHOLD = 3;

const unsigned long alarmTimeRemainingSecs = alarmTimeRemaining * 60;