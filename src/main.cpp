#include <SoftwareSerial.h>
#include <MIDI.h>

constexpr int MIDI_RX_PIN = 2;
constexpr int MIDI_TX_PIN = 3;
constexpr int HOLD_ON_OFF_SWITCH_PIN = 4;
constexpr byte CHANNEL = 1;

SoftwareSerial midiSerial(MIDI_RX_PIN, MIDI_TX_PIN);

MIDI_CREATE_INSTANCE(SoftwareSerial, midiSerial, MIDI);

static void noteOn(byte channel, byte note, byte velocity);

static void noteOff(byte channel, byte note, byte velocity);

static bool pressedNotes[127];
static bool sustainedNotes[127];
static bool holdFunctionActivated;

static bool pressedNotesEmpty() {
    for (const bool pressedNote : pressedNotes) {
        if (pressedNote) {
            return false;
        }
    }
    return true;
}

static void printSustainedNotes() {
    Serial.print("Sustained Notes:");
    for (int i = 0; i < 127; i++) {
        if (sustainedNotes[i]) {
            Serial.print(i);
            Serial.print(" ");
        }
    }
    Serial.println();
}

static void printPressedNotes() {
    Serial.print("Pressed Notes:");
    for (int i = 0; i < 127; i++) {
        if (pressedNotes[i]) {
            Serial.print(i);
            Serial.print(" ");
        }
    }
    Serial.println();
}

static void noteOffForAllExceptPressed() {
    for (int i = 0; i < 127; i++) {
        if (!pressedNotes[i]) {
            MIDI.sendNoteOff(i, 0, CHANNEL);
        }
        sustainedNotes[i] = false;
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("Starting");

    pinMode(MIDI_RX_PIN, INPUT);
    pinMode(MIDI_TX_PIN, OUTPUT);
    midiSerial.begin(31250);
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
    MIDI.setHandleNoteOn(noteOn);
    MIDI.setHandleNoteOff(noteOff);

    noteOffForAllExceptPressed();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    for (int i = 0; i < 5; i++) {
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
    }

    pinMode(HOLD_ON_OFF_SWITCH_PIN, INPUT);
    if (digitalRead(HOLD_ON_OFF_SWITCH_PIN) == HIGH) {
        holdFunctionActivated = true;
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("Switching Hold function ON");
    } else {
        holdFunctionActivated = false;
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Switching Hold function OFF");
    }
}

void loop() {
    const bool oldHoldFunctionState = holdFunctionActivated;
    const bool newHoldFunctionState = digitalRead(HOLD_ON_OFF_SWITCH_PIN) == HIGH;

    // hold function was off and is now on
    if (!oldHoldFunctionState && newHoldFunctionState) {
        holdFunctionActivated = true;
        digitalWrite(LED_BUILTIN, HIGH);

        Serial.println("Switching Hold function ON");

        // add a little delay, to debounce the HOLD button
        delay(50);
    }

    // hold function is on and is now turned off
    if (oldHoldFunctionState && !newHoldFunctionState) {
        holdFunctionActivated = false;
        digitalWrite(LED_BUILTIN, LOW);

        printSustainedNotes();
        printPressedNotes();

        noteOffForAllExceptPressed();

        Serial.println("Switching Hold function OFF");
        // add a little delay, to debounce the HOLD button
        delay(50);
    }

    MIDI.read();
}

void noteOn(const byte channel, const byte note, const byte velocity) {
    MIDI.sendNoteOn(note, velocity, CHANNEL);

    // the user is entering a new chord
    if (pressedNotesEmpty()) {
        for (int i = 0; i < 127; i++) {
            if (sustainedNotes[i] && note != i) {
                Serial.print("Sending Note OFF: ");
                Serial.println(i);
                MIDI.sendNoteOff(i, 0, CHANNEL);
            }
            sustainedNotes[i] = false;
        }
    }
    pressedNotes[note] = true;
    sustainedNotes[note] = true;

    printSustainedNotes();
    printPressedNotes();
}

void noteOff(const byte channel, const byte note, const byte velocity) {
    if (!holdFunctionActivated) {
        MIDI.sendNoteOff(note, velocity, CHANNEL);
        sustainedNotes[note] = false;
    }
    pressedNotes[note] = false;

    printSustainedNotes();
    printPressedNotes();
}
