#include <MIDI.h>

const int LED_BUILTIN = 2;

// !!!!The midi library uses the Pin Number not the GPIO Number!!!!
const int MIDI_RX_PIN = 16;
const int MIDI_TX_PIN = 17;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

void setup() {
    Serial.begin(31250, SERIAL_8N1, MIDI_RX_PIN, MIDI_TX_PIN);
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
