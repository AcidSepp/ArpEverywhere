#include <MIDI.h>
#include <set>

constexpr int TIME_DIVISION_ROTARY_SWITCH_PIN = A1;
constexpr int PATTERN_ROTARY_SWITCH_PIN = A2;

const int MIDI_1_RX_PIN = 2;
const int MIDI_1_TX_PIN = 3;
const int MIDI_2_RX_PIN = 4;
const int MIDI_2_TX_PIN = 3;

constexpr int HOLD_ON_OFF_SWITCH_PIN = 9;
constexpr int CLOCK_SRC_SWITCH_PIN = 8;
constexpr int ARP_ON_OFF_SWITCH_PIN = 7;
constexpr int MIDI_1_THRU_ON_OFF_SWITCH_PIN = 6;

typedef enum {
    _32_4 = 384,
    _16_4 = 288,
    _8_4 = 192,
    _4_4 = 96,
    _1_2 = 48,
    _1_4 = 24,
    _1_8 = 12,
    _1_8T = 8,
    _1_16 = 6,
    _1_16T = 4,
    _1_32 = 3,
    _1_32T = 2,
} TimeDivision;

typedef enum {
    UP,
    DOWN,
    NARROW,
    PYRAMID,
    TOUCH,
    RND_4,
    RND_3,
    RND_2,
    RND_1,
    JUMP,
    HOURGLASS,
    UP_DOWN
} Pattern;

void setup() {
    Serial.begin(9600);

    pinMode(TIME_DIVISION_ROTARY_SWITCH_PIN, INPUT);
    pinMode(PATTERN_ROTARY_SWITCH_PIN, INPUT);

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

TimeDivision rotarySwitchNumberToTimeDivision(const int rotarySwitchNumber) {
    switch (rotarySwitchNumber) {
        case 0:
            return _4_4;
        case 1:
            return _1_2;
        case 2:
            return _1_4;
        case 3:
            return _1_8;
        case 4:
            return _1_8T;
        case 5:
            return _1_16;
        case 6:
            return _1_16T;
        case 7:
            return _1_32;
        case 8:
            return _1_32T;
        case 9:
            return _32_4;
        case 10:
            return _16_4;
        case 11:
            return _8_4;
        default:
            return _4_4;
    }
}

const char *timeDivisionToString(const TimeDivision timeDivision) {
    switch (timeDivision) {
        case _32_4:
            return "_32_4";
        case _16_4:
            return "_16_4";
        case _8_4:
            return "_8_4";
        case _4_4:
            return "_4_4";
        case _1_2:
            return "_1_2";
        case _1_4:
            return "_1_4";
        case _1_8:
            return "_1_8";
        case _1_8T:
            return "_1_8T";
        case _1_16:
            return "_1_16";
        case _1_16T:
            return "_1_16T";
        case _1_32:
            return "_1_32";
        case _1_32T:
            return "_1_32T";
        default:
            return "";
    }
}

Pattern rotarySwitchNumberToPattern(const int rotarySwitchNumber) {
    switch (rotarySwitchNumber) {
        case 0:
            return NARROW;
        case 1:
            return DOWN;
        case 2:
            return UP;
        case 3:
            return UP_DOWN;
        case 4:
            return HOURGLASS;
        case 5:
            return JUMP;
        case 6:
            return RND_1;
        case 7:
            return RND_2;
        case 8:
            return RND_3;
        case 9:
            return RND_4;
        case 10:
            return TOUCH;
        case 11:
            return PYRAMID;
        default:
            return UP;
    }
}

const char *patternToString(const Pattern pattern) {
    switch (pattern) {
        case UP:
            return "UP";
        case DOWN:
            return "DOWN";
        case NARROW:
            return "NARROW";
        case PYRAMID:
            return "PYRAMID";
        case TOUCH:
            return "TOUCH";
        case RND_4:
            return "RND_4";
        case RND_3:
            return "RND_3";
        case RND_2:
            return "RND_2";
        case RND_1:
            return "RND_1";
        case JUMP:
            return "JUMP";
        case HOURGLASS:
            return "HOURGLASS";
        case UP_DOWN:
            return "UP_DOWN";
        default:
            return "";
    }
}

void loop() {
    delay(1000);
    const int patternRawValue = analogRead(PATTERN_ROTARY_SWITCH_PIN);
    Serial.printf("Pattern Raw Value %d\n", patternRawValue);
    Serial.printf("Pattern: %s\n", patternToString(rotarySwitchNumberToPattern(getRotarySwitchNumber(patternRawValue))));

    const int timeDivisionRawValue = analogRead(TIME_DIVISION_ROTARY_SWITCH_PIN);
    Serial.printf("TimeDivision Raw Value %d\n", timeDivisionRawValue);
    Serial.printf("TimeDivision: %s\n", timeDivisionToString(rotarySwitchNumberToTimeDivision(getRotarySwitchNumber(timeDivisionRawValue))));
}
