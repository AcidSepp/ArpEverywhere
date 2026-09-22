#include <MIDI.h>
#include <set>

constexpr int ROTARY_SWITCH_PIN = A2;

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

    pinMode(ROTARY_SWITCH_PIN, INPUT);

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

void loop() {
    delay(1000);
    const int sensorValue = analogRead(ROTARY_SWITCH_PIN);
    Serial.printf("Raw Value %d\n", sensorValue);
    Serial.printf("Value: %d\n", getRotarySwitchNumber(sensorValue));
}
