#include "rotarySwitch.h"

int getRotarySwitchNumber(const int sensorValue) {
    if (sensorValue < 149) {
        return 0;
    }
    if (sensorValue >= 150 && sensorValue <= 438) {
        return 1;
    }
    if (sensorValue >= 450 && sensorValue <= 799) {
        return 2;
    }
    if (sensorValue >= 800 && sensorValue <= 1149) {
        return 3;
    }
    if (sensorValue >= 1150 && sensorValue <= 1499) {
        return 4;
    }
    if (sensorValue >= 1500 && sensorValue <= 1799) {
        return 5;
    }
    if (sensorValue >= 1800 && sensorValue <= 2099) {
        return 6;
    }
    if (sensorValue >= 2100 && sensorValue <= 2399) {
        return 7;
    }
    if (sensorValue >= 2400 && sensorValue <= 2799) {
        return 8;
    }
    if (sensorValue >= 2800 && sensorValue <= 3199) {
        return 9;
    }
    if (sensorValue >= 3200 && sensorValue <= 3699) {
        return 10;
    }
    if (sensorValue >= 3700) {
        return 11;
    }
    return 0;
}
