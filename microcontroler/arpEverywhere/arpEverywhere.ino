#include <MIDI.h>

const int LED_BUILTIN = 2;

// Explicit RX/TX pins for MIDI IN
// !!!!The midi library uses the PIN Number not the GPIO Number!!!!
const int MIDI_RX_PIN = 16;
const int MIDI_TX_PIN = 17;

// Bind MIDI to the default hardware Serial (UART0), but we'll re-init it
// explicitly on GPIO3/GPIO1 in setup() instead of relying on MIDI.begin() defaults.
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

int notesPressed[127];

void setup() {
    for (int i = 0; i < 127; i++) {
        notesPressed[i] = 0;
    }

    pinMode(LED_BUILTIN, OUTPUT);

    // Explicitly configure UART0 on GPIO3 (RX) / GPIO1 (TX) at MIDI baud rate (31250)
    Serial.begin(31250, SERIAL_8N1, MIDI_RX_PIN, MIDI_TX_PIN);

    MIDI.begin(MIDI_CHANNEL_OMNI);

    digitalWrite(LED_BUILTIN, LOW);

    for (int i = 0; i < 5; i++) {
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
    }

    MIDI.setHandleNoteOn(noteOn);
    MIDI.setHandleNoteOff(noteOff);
}

void loop() {
    MIDI.read();
}

bool notesPressedIsEmpty() {
    for (int i = 0; i < 127; i++) {
        if (notesPressed[i] == 1) {
            return false;
        }
    }
    return true;
}

void noteOn(const byte channel, const byte note, const byte velocity) {
//     if (notesPressedIsEmpty()) {
//         for (int i = 0; i < 127; i++) {
//             MIDI.sendNoteOff(i, velocity, channel);
//         }
//     }

    notesPressed[note] = 1;

    digitalWrite(LED_BUILTIN, HIGH);
    //MIDI.sendNoteOn(note, velocity, channel);
}

void noteOff(const byte channel, const byte note, const byte velocity) {
    notesPressed[note] = 0;
    digitalWrite(LED_BUILTIN, LOW);
}

