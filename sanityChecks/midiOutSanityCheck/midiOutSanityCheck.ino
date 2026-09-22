#include <MIDI.h>

const int MIDI_1_RX_PIN = 2;
const int MIDI_1_TX_PIN = 3;
const int MIDI_2_RX_PIN = 4;
const int MIDI_2_TX_PIN = 5;

HardwareSerial MidiSerial1(1);
HardwareSerial MidiSerial2(2);

MIDI_CREATE_INSTANCE(HardwareSerial, MidiSerial1, MIDI1);
MIDI_CREATE_INSTANCE(HardwareSerial, MidiSerial2, MIDI2);

void setup() {
    Serial.begin(9600);

    MidiSerial1.begin(31250, SERIAL_8N1, MIDI_1_RX_PIN, MIDI_1_TX_PIN);
    MIDI1.begin(MIDI_CHANNEL_OMNI);
    MIDI1.turnThruOff();

    MidiSerial2.begin(31250, SERIAL_8N1, MIDI_2_RX_PIN, MIDI_2_TX_PIN);
    MIDI2.begin(MIDI_CHANNEL_OMNI);
    MIDI2.turnThruOff();

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
    for (int channel = 1; channel < 11; channel++) {
        MIDI1.sendNoteOn(60, 127, channel);
        MIDI2.sendNoteOn(61, 127, channel);
    }
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);

    for (int channel = 1; channel < 11; channel++) {
        MIDI1.sendNoteOff(60, 127, channel);
        MIDI2.sendNoteOff(61, 127, channel);
    }
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
