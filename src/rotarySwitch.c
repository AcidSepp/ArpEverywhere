#include "rotarySwitch.h"

static int getRotarySwitchNumber(const int sensorValue) {
    if (sensorValue < 150) {
        return 0;
    }
    if (sensorValue >= 150 && sensorValue <= 450) {
        return 1;
    }
    if (sensorValue >= 450 && sensorValue <= 800) {
        return 2;
    }
    if (sensorValue >= 800 && sensorValue <= 1200) {
        return 3;
    }
    if (sensorValue >= 1200 && sensorValue <= 1500) {
        return 4;
    }
    if (sensorValue >= 1500 && sensorValue <= 1800) {
        return 5;
    }
    if (sensorValue >= 1800 && sensorValue <= 2200) {
        return 6;
    }
    if (sensorValue >= 2200 && sensorValue <= 2700) {
        return 7;
    }
    if (sensorValue >= 2700 && sensorValue <= 2900) {
        return 8;
    }
    if (sensorValue >= 2900 && sensorValue <= 3300) {
        return 9;
    }
    if (sensorValue >= 3300 && sensorValue <= 3900) {
        return 10;
    }
    if (sensorValue >= 3900) {
        return 11;
    }
    return 0;
}
