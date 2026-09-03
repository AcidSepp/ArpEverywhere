#include <MIDI.h>

const int LED_BUILTIN = 2;

// Explicit RX/TX pins for MIDI IN
// !!!!The midi library uses the PIN Number not the GPIO Number!!!!
const int MIDI_RX_PIN = 16;
const int MIDI_TX_PIN = 17;

// Bind MIDI to the default hardware Serial (UART0), but we'll re-init it
// explicitly on GPIO3/GPIO1 in setup() instead of relying on MIDI.begin() defaults.
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    // Explicitly configure UART0 on GPIO3 (RX) / GPIO1 (TX) at MIDI baud rate (31250)
    Serial.begin(31250, SERIAL_8N1, MIDI_RX_PIN, MIDI_TX_PIN);

    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();

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
