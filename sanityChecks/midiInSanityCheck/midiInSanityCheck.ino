#include <MIDI.h>

const int MIDI_1_RX_PIN = 2;
const int MIDI_1_TX_PIN = 3;
const int MIDI_2_RX_PIN = 4;
const int MIDI_5_TX_PIN = 3;

HardwareSerial MidiSerial1(1);
HardwareSerial MidiSerial2(2);

MIDI_CREATE_INSTANCE(HardwareSerial, MidiSerial1, MIDI1);
MIDI_CREATE_INSTANCE(HardwareSerial, MidiSerial2, MIDI2);

void noteOn1(const byte channel, const byte note, const byte velocity) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.printf("MIDI_IN_1\tNOTE ON \tChannel=%d\tNote=%d\t\tVelocity=%d\n", channel, note, velocity);
}

void noteOff1(const byte channel, const byte note, const byte velocity) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.printf("MIDI_IN_1\tNOTE OFF\tChannel=%d\tNote=%d\t\tVelocity=%d\n", channel, note, velocity);
}

void noteOn2(const byte channel, const byte note, const byte velocity) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.printf("MIDI_IN_2\tNOTE ON \tChannel=%d\tNote=%d\t\tVelocity=%d\n", channel, note, velocity);
}

void noteOff2(const byte channel, const byte note, const byte velocity) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.printf("MIDI_IN_2\tNOTE OFF\tChannel=%d\tNote=%d\t\tVelocity=%d\n", channel, note, velocity);
}


void setup() {
    Serial.begin(9600);

    MidiSerial1.begin(31250, SERIAL_8N1, MIDI_1_RX_PIN, MIDI_1_TX_PIN);
    MIDI1.begin(MIDI_CHANNEL_OMNI);
    MIDI1.turnThruOff();
    MIDI1.setHandleNoteOn(noteOn1);
    MIDI1.setHandleNoteOff(noteOff1);

    MidiSerial2.begin(31250, SERIAL_8N1, MIDI_2_RX_PIN, MIDI_5_TX_PIN);
    MIDI2.begin(MIDI_CHANNEL_OMNI);
    MIDI2.turnThruOff();
    MIDI2.setHandleNoteOn(noteOn2);
    MIDI2.setHandleNoteOff(noteOff2);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    for (int i = 0; i < 5; i++) {
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
    }
}

void loop() {
    MIDI1.read();
    MIDI2.read();
}
