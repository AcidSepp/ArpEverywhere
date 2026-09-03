#include <MIDI.h>

const int LED_BUILTIN = 2;

// !!!!The midi library uses the PIN Number not the GPIO Number!!!!
const int MIDI_RX_PIN = 16;
const int MIDI_TX_PIN = 17;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

int notesPressed = 0;

void setup() {
    Serial.begin(31250, SERIAL_8N1, MIDI_RX_PIN, MIDI_TX_PIN);
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
    MIDI.sendNoteOn(note, velocity, channel);

    // this needs to be done after the new note is entered, otherwise the loop causes an input delay
    if (notesPressed == 0) {
        for (int i = 0; i < 127; i++) {
            if (i != note) { // do not stop the new note
                MIDI.sendNoteOff(i, velocity, channel);
            }
        }
    }
    notesPressed++;
    digitalWrite(LED_BUILTIN, HIGH);
}

void noteOff(const byte channel, const byte note, const byte velocity) {
    notesPressed--;
    digitalWrite(LED_BUILTIN, LOW);
}
