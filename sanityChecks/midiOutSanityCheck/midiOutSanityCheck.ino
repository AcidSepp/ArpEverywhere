#include <SoftwareSerial.h>
#include <MIDI.h>

const int LED_PIN = 13;

const int MIDI_RX_PIN = 2;
const int MIDI_TX_PIN = 3;

SoftwareSerial midiSerial(MIDI_RX_PIN, MIDI_TX_PIN);

MIDI_CREATE_INSTANCE(SoftwareSerial, midiSerial, MIDI);

void setup() {
  midiSerial.begin(31250);
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();

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
    digitalWrite(LED_BUILTIN, HIGH);
    MIDI.sendNoteOn(60, 127, 1);
    delay(1000);
    MIDI.sendNoteOff(60, 0, 1);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
