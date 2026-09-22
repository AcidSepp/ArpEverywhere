#include <MIDI.h>
#include <set>

constexpr int TIME_DIVISION_ROTARY_SWITCH_PIN = A1;

const int MIDI_1_RX_PIN = 2;
const int MIDI_1_TX_PIN = 3;
const int MIDI_2_RX_PIN = 4;
const int MIDI_2_TX_PIN = 3;

constexpr int HOLD_ON_OFF_SWITCH_PIN = 9;
constexpr int CLOCK_SRC_SWITCH_PIN = 8;
constexpr int ARP_ON_OFF_SWITCH_PIN = 7;
constexpr int MIDI_1_THRU_ON_OFF_SWITCH_PIN = 6;

void setup() {
    Serial.begin(9600);

    pinMode(TIME_DIVISION_ROTARY_SWITCH_PIN, INPUT);

    pinMode(MIDI_1_RX_PIN, INPUT);
    pinMode(MIDI_1_TX_PIN, OUTPUT);
    pinMode(MIDI_2_RX_PIN, INPUT);
    pinMode(MIDI_2_TX_PIN, OUTPUT);

    pinMode(HOLD_ON_OFF_SWITCH_PIN, INPUT);
    pinMode(CLOCK_SRC_SWITCH_PIN, INPUT);
    pinMode(ARP_ON_OFF_SWITCH_PIN, INPUT);
    pinMode(MIDI_1_THRU_ON_OFF_SWITCH_PIN, INPUT);
}


static int getRotarySwitchNumber(const int sensorValue) {
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

void loop() {
    delay(1000);
    const int sensorValue = analogRead(TIME_DIVISION_ROTARY_SWITCH_PIN);
    Serial.printf("Raw Value %d\n", sensorValue);
    Serial.printf("Value: %d\n", getRotarySwitchNumber(sensorValue));
}
