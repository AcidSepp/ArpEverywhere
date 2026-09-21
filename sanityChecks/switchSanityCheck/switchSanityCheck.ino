#include <MIDI.h>

constexpr int HOLD_ON_OFF_SWITCH_PIN = 9;
constexpr int CLOCK_SRC_SWITCH_PIN = 8;
constexpr int ARP_ON_OFF_SWITCH_PIN = 7;
constexpr int MIDI_1_THRU_ON_OFF_SWITCH_PIN = 6;

static bool hold = true;
static bool midi1ClockSource = true;
static bool arp = true;
static bool thru = true;

void setup() {
    Serial.begin(9600);

    pinMode(HOLD_ON_OFF_SWITCH_PIN, INPUT);
    pinMode(CLOCK_SRC_SWITCH_PIN, INPUT);
    pinMode(ARP_ON_OFF_SWITCH_PIN, INPUT);
    pinMode(MIDI_1_THRU_ON_OFF_SWITCH_PIN, INPUT);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    for (int i = 0; i < 5; i++) {
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
    }

    if (digitalRead(HOLD_ON_OFF_SWITCH_PIN) == HIGH) {
        Serial.println("Hold turned ON");
        hold = true;
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        Serial.println("Hold turned OFF");
        hold = false;
        digitalWrite(LED_BUILTIN, LOW);
    }

    if (digitalRead(CLOCK_SRC_SWITCH_PIN) == HIGH) {
        Serial.println("MIDI 1 is the clock source.");
        midi1ClockSource = true;
    } else {
        Serial.println("MIDI 2 is the clock source.");
        midi1ClockSource = false;
    }

    if (digitalRead(ARP_ON_OFF_SWITCH_PIN) == HIGH) {
        Serial.println("Arp turned ON");
        arp = true;
    } else {
        Serial.println("Arp turned OFF");
        arp = false;
    }

    if (digitalRead(MIDI_1_THRU_ON_OFF_SWITCH_PIN) == HIGH) {
        Serial.println("MIDI 1 Thru turned ON");
        thru = true;
    } else {
        Serial.println("MIDI 1 Thru turned OFF");
        thru = false;
    }
}

void loop() {
    if (digitalRead(HOLD_ON_OFF_SWITCH_PIN) == HIGH && !hold) {
        Serial.println("Hold turning ON");
        hold = true;
        delay(50);
    }
    if (digitalRead(HOLD_ON_OFF_SWITCH_PIN) == LOW && hold) {
        Serial.println("Hold turning OFF");
        hold = false;
        delay(50);
    }

    if (digitalRead(CLOCK_SRC_SWITCH_PIN) == HIGH && !midi1ClockSource) {
        Serial.println("MIDI 1 is now the clock source.");
        midi1ClockSource = true;
        delay(50);
    }
    if (digitalRead(CLOCK_SRC_SWITCH_PIN) == LOW && midi1ClockSource) {
        Serial.println("MIDI 2 is now the clock source.");
        midi1ClockSource = false;
        delay(50);
    }

    if (digitalRead(ARP_ON_OFF_SWITCH_PIN) == HIGH && !arp) {
        Serial.println("Arp turning ON");
        arp = true;
        delay(50);
    }
    if (digitalRead(ARP_ON_OFF_SWITCH_PIN) == LOW && arp) {
        Serial.println("Arp turning OFF");
        arp = false;
        delay(50);
    }

    if (digitalRead(MIDI_1_THRU_ON_OFF_SWITCH_PIN) == HIGH && !thru) {
        Serial.println("MIDI 1 Thru turning ON");
        thru = true;
        delay(50);
    }
    if (digitalRead(MIDI_1_THRU_ON_OFF_SWITCH_PIN) == LOW && thru) {
        Serial.println("MIDI 1 Thru turning OFF");
        thru = false;
        delay(50);
    }
}
