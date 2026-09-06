#include <MIDI.h>
#include <set>

using namespace std;

// !!!!The midi library uses the PIN Number not the GPIO Number!!!!
constexpr int MIDI_RX_PIN = 16;
constexpr int MIDI_TX_PIN = 17;
constexpr int HOLD_ON_OFF_SWITCH_PIN = 22;
constexpr byte CHANNEL = 1;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

static void noteOn(byte channel, byte note, byte velocity);

static void noteOff(byte channel, byte note, byte velocity);

static void handleClock();

static set<int> pressedNotes;
static set<int> sustainedNotes;
static bool holdFunctionActivated;
static bool arpFunctionActivated = true;
static int clockCounter = 0;
static int lastArpNote = 0;
static int arpIndex = 0;

void setup() {
    Serial.begin(9600);

    Serial1.begin(31250, SERIAL_8N1, MIDI_RX_PIN, MIDI_TX_PIN);
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
    MIDI.setHandleNoteOn(noteOn);
    MIDI.setHandleNoteOff(noteOff);
    MIDI.setHandleClock(handleClock);

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
    } else {
        holdFunctionActivated = false;
        digitalWrite(LED_BUILTIN, LOW);
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

        for (const int sustainedNote: sustainedNotes) {
            if (!pressedNotes.count(sustainedNote)) {
                Serial.printf("Sending Note OFF: %d\n", sustainedNote);
                MIDI.sendNoteOff(sustainedNote, 0, CHANNEL);
            } else {
                Serial.printf("Not sending Note OFF: %d\n", sustainedNote);
            }
        }
        sustainedNotes.clear();

        Serial.println("Switching Hold function OFF");
        // add a little delay, to debounce the HOLD button
        delay(50);
    }

    MIDI.read();
}

void noteOn(const byte channel, const byte note, const byte velocity) {
    // if the arp is active, the note will be played automatically, so we need to prevent retriggers in that case
    if (!arpFunctionActivated) {
        MIDI.sendNoteOn(note, velocity, CHANNEL);
    }

    // the user is entering a new chord
    if (pressedNotes.empty()) {
        for (const int sustainedNote: sustainedNotes) {
            if (sustainedNote != note) {
                MIDI.sendNoteOff(sustainedNote, velocity, CHANNEL);
            }
        }
        sustainedNotes.clear();
    }
    pressedNotes.insert(note);
    sustainedNotes.insert(note);

    Serial.printf("Sustained Notes: %d\n", sustainedNotes.size());
}

void noteOff(const byte channel, const byte note, const byte velocity) {
    if (!holdFunctionActivated) {
        MIDI.sendNoteOff(note, velocity, CHANNEL);
        sustainedNotes.erase(note);
    }
    pressedNotes.erase(note);
}

static void handleClock() {
    if (clockCounter == 0) {
        Serial.println("Quarter Note!");

        Serial.printf("Sustained Notes: %d\n", sustainedNotes.size());

        if (!sustainedNotes.empty()) {
            int currentLoopIndex = 0;
            if (arpIndex >= sustainedNotes.size()) {
                arpIndex = 0;
            }

            Serial.printf("arpIndex: %d\n", arpIndex);

            // This is O(n) every quarter note. I know this can be improved by using a better data structure, but hey.
            for (const int sustainedNote: sustainedNotes) {
                if (currentLoopIndex == arpIndex) {
                    // Note Off needs to go first, in order to retrigger the note, if it is the only one sustained
                    MIDI.sendNoteOff(lastArpNote, 127, CHANNEL);

                    MIDI.sendNoteOn(sustainedNote, 127, CHANNEL);
                    lastArpNote = sustainedNote;
                }
                currentLoopIndex++;
            }

            arpIndex++;
        }
    }
    clockCounter = (clockCounter + 1) % 24;
}
