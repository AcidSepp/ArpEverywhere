#include <SoftwareSerial.h>
#include <MIDI.h>

const int MIDI_RX_PIN = 2;
const int MIDI_TX_PIN = 3;

SoftwareSerial midiSerial(MIDI_RX_PIN, MIDI_TX_PIN);

MIDI_CREATE_INSTANCE(SoftwareSerial, midiSerial, MIDI);

void setup() {

    pinMode(MIDI_RX_PIN, INPUT);

    midiSerial.begin(31250);
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
    MIDI.setHandleNoteOn(noteOn);
    MIDI.setHandleNoteOff(noteOff);

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
    MIDI.read();
}

void noteOn(const byte channel, const byte note, const byte velocity) {
    digitalWrite(LED_BUILTIN, HIGH);
}

void noteOff(const byte channel, const byte note, const byte velocity) {
    digitalWrite(LED_BUILTIN, LOW);
}
