#include <MIDI.h>
#include "rotarySwitch.h"
#include "timedivision.h"
#include "pattern.h"

constexpr int MIDI_1_RX_PIN = 2;
constexpr int MIDI_1_TX_PIN = 3;
constexpr int MIDI_2_RX_PIN = 4;
constexpr int MIDI_2_TX_PIN = 5;

constexpr int HOLD_ON_OFF_SWITCH_PIN = 9;
constexpr int CLOCK_SRC_SWITCH_PIN = 8;
constexpr int ARP_ON_OFF_SWITCH_PIN = 7;
constexpr int MIDI_1_THRU_ON_OFF_SWITCH_PIN = 6;

constexpr int TIME_DIVISION_ROTARY_SWITCH_PIN = A1;
constexpr int PATTERN_ROTARY_SWITCH_PIN = A2;

constexpr byte CHANNEL = 1;
constexpr bool DEBUG = true;

HardwareSerial MidiSerial1(1);
HardwareSerial MidiSerial2(2);

MIDI_CREATE_INSTANCE(HardwareSerial, MidiSerial1, MIDI1);
MIDI_CREATE_INSTANCE(HardwareSerial, MidiSerial2, MIDI2);

static void noteOn(byte channel, byte note, byte velocity);

static void noteOff(byte channel, byte note, byte velocity);

static void handleClock();

constexpr int NOTES_ARRAY_SIZE = 128;

static bool pressedNotes[NOTES_ARRAY_SIZE];
static int pressedNotesCount = 0;
static bool sustainedNotes[NOTES_ARRAY_SIZE];
static int sustainedNotesCount = 0;
static bool holdFunctionActivated;
static bool arpActivated = true;
static int clockCounter = 0;
static int arpIndex = 0;
static TimeDivision timeDivision = _1_4;
static Pattern pattern = UP;
static bool clockFromMidi1 = true;
static bool midi1Thru = false;

void resetCounters() {
    clockCounter = 0;
    arpIndex = 0;
}

static bool pressedNotesEmpty() {
    for (const bool pressedNote: pressedNotes) {
        if (pressedNote) {
            return false;
        }
    }
    return true;
}

static bool sustainedNotesEmpty() {
    for (const bool sustainedNote: sustainedNotes) {
        if (sustainedNote) {
            return false;
        }
    }
    return true;
}

static void clearSustainedNotes() {
    for (bool & sustainedNote : sustainedNotes) {
        sustainedNote = false;
    }
}

static void printSustainedNotes() {
    Serial.printf("Sustained Notes (%d): ", sustainedNotesCount);
    for (int i = 0; i < NOTES_ARRAY_SIZE; i++) {
        if (sustainedNotes[i]) {
            Serial.print(i);
            Serial.print(" ");
        }
    }
    Serial.println();
}

static void printPressedNotes() {
    Serial.printf("Pressed Notes (%d): ", pressedNotesCount);
    for (int i = 0; i < NOTES_ARRAY_SIZE; i++) {
        if (pressedNotes[i]) {
            Serial.print(i);
            Serial.print(" ");
        }
    }
    Serial.println();
}

static void sendNoteOn(const byte note, const byte velocity, const byte channel) {
    if (DEBUG) {
        Serial.printf("NOTE ON: n=%d\n", note);
    }
    if (!midi1Thru) {
        MIDI1.sendNoteOn(note, velocity, channel);
    }
    MIDI2.sendNoteOn(note, velocity, channel);
}

static void sendNoteOff(const byte note, const byte velocity, const byte channel) {
    if (DEBUG) {
        Serial.printf("NOTE OFF: n=%d\n", note);
    }
    if (!midi1Thru) {
        MIDI1.sendNoteOff(note, velocity, channel);
    }
    MIDI2.sendNoteOff(note, velocity, channel);
}

static void midi1AllNotesOff() {
    for (int channel = 0; channel < 11; ++channel) {
        for (int note = 0; note < 128; ++note) {
            MIDI1.sendNoteOff(note, 0, channel);
        }
    }
}

static void midi2AllNotesOff() {
    for (int channel = 0; channel < 11; ++channel) {
        for (int note = 0; note < 128; ++note) {
            MIDI2.sendNoteOff(note, 0, channel);
        }
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("Staring...");

    MidiSerial1.begin(31250, SERIAL_8N1, MIDI_1_RX_PIN, MIDI_1_TX_PIN);
    MIDI1.begin(MIDI_CHANNEL_OMNI);
    MIDI1.setHandleNoteOn(noteOn);
    MIDI1.setHandleNoteOff(noteOff);

    pinMode(MIDI_1_THRU_ON_OFF_SWITCH_PIN, INPUT);
    if (digitalRead(MIDI_1_THRU_ON_OFF_SWITCH_PIN) == HIGH) {
        midi1Thru = true;
        Serial.println("MIDI 1 Thru: ON");
        MIDI1.turnThruOn();
    } else {
        midi1Thru = false;
        Serial.println("MIDI 1 Thru: OFF");
        MIDI1.turnThruOff();
    }
    midi1AllNotesOff();

    MidiSerial2.begin(31250, SERIAL_8N1, MIDI_2_RX_PIN, MIDI_2_TX_PIN);
    MIDI2.begin(MIDI_CHANNEL_OMNI);
    MIDI2.turnThruOff();
    midi2AllNotesOff();

    pinMode(CLOCK_SRC_SWITCH_PIN, INPUT);
    if (digitalRead(CLOCK_SRC_SWITCH_PIN) == HIGH) {
        clockFromMidi1 = true;
        Serial.println("Clock Source: MIDI 1");
        MIDI1.setHandleClock(handleClock);
        MIDI2.setHandleClock(nullptr);

        MIDI1.setHandleStart(resetCounters);
        MIDI1.setHandleStop(resetCounters);
        MIDI2.setHandleStart(nullptr);
        MIDI2.setHandleStop(nullptr);
    } else {
        clockFromMidi1 = false;
        Serial.println("Clock Source: MIDI 2");
        MIDI1.setHandleClock(nullptr);
        MIDI2.setHandleClock(handleClock);

        MIDI1.setHandleStart(nullptr);
        MIDI1.setHandleStop(nullptr);
        MIDI2.setHandleStart(resetCounters);
        MIDI2.setHandleStop(resetCounters);
    }

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
        Serial.println("Hold: ON");
    } else {
        holdFunctionActivated = false;
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Hold: OFF");
    }

    pinMode(TIME_DIVISION_ROTARY_SWITCH_PIN, INPUT);
    pinMode(PATTERN_ROTARY_SWITCH_PIN, INPUT);

    pinMode(ARP_ON_OFF_SWITCH_PIN, INPUT);
    if (digitalRead(ARP_ON_OFF_SWITCH_PIN) == HIGH) {
        arpActivated = true;
        Serial.println("Arp: ON");
    } else {
        arpActivated = false;
        Serial.println("Arp: OFF");
    }

    Serial.println("Started!");
}

static void clearAllSustainedNotesExceptPressed() {
    for (const int sustainedNote: sustainedNotes) {
        if (!pressedNotes[sustainedNote]) {
            Serial.printf("Sending Note OFF: %d\n", sustainedNote);
            sendNoteOff(sustainedNote, 0, CHANNEL);
        } else {
            Serial.printf("Not sending Note OFF: %d\n", sustainedNote);
        }
    }
}

void loop() {
    const bool oldClockFromMidi1 = clockFromMidi1;
    const bool newClockFromMidi1 = digitalRead(CLOCK_SRC_SWITCH_PIN) == HIGH;

    // midi 2 was the clock source and now midi 1 is the clock source
    if (!oldClockFromMidi1 && newClockFromMidi1) {
        clockFromMidi1 = true;
        Serial.println("Clock Source: MIDI 1");
        MIDI1.setHandleClock(handleClock);
        MIDI2.setHandleClock(nullptr);

        // add a little delay, to debounce the clock source switch
        delay(50);
    }

    // midi 1 was the clock source and now midi 2 is the clock source
    if (oldClockFromMidi1 && !newClockFromMidi1) {
        clockFromMidi1 = false;
        Serial.println("Clock Source: MIDI 2");
        MIDI1.setHandleClock(nullptr);
        MIDI2.setHandleClock(handleClock);

        // add a little delay, to debounce the clock source switch
        delay(50);
    }

    const bool oldHoldFunctionState = holdFunctionActivated;
    const bool newHoldFunctionState = digitalRead(HOLD_ON_OFF_SWITCH_PIN) == HIGH;

    // hold function was off and is now on
    if (!oldHoldFunctionState && newHoldFunctionState) {
        holdFunctionActivated = true;
        digitalWrite(LED_BUILTIN, HIGH);

        if (DEBUG) {
            Serial.println("Switching Hold function ON");
        }

        // add a little delay, to debounce the HOLD switch
        delay(50);
    }

    // hold function is on and is now turned off
    if (oldHoldFunctionState && !newHoldFunctionState) {
        holdFunctionActivated = false;
        digitalWrite(LED_BUILTIN, LOW);

        clearAllSustainedNotesExceptPressed();
        clearSustainedNotes();

        if (DEBUG) {
            Serial.println("Switching Hold function OFF");
        }
        // add a little delay, to debounce the HOLD switch
        delay(50);
    }

    const bool oldArpState = arpActivated;
    const bool newArpState = digitalRead(ARP_ON_OFF_SWITCH_PIN) == HIGH;

    // arp was off and is now on
    if (!oldArpState && newArpState) {
        clockCounter = 0;
        arpActivated = true;

        if (DEBUG) {
            Serial.println("Switching Arp ON");
        }
        // add a little delay, to debounce the ARP switch
        delay(50);
    }

    // arp was on and is now off
    if (oldArpState && !newArpState) {
        clockCounter = 0;
        arpActivated = false;

        clearAllSustainedNotesExceptPressed();

        if (holdFunctionActivated) {
            for (const int sustainedNote : sustainedNotes) {
                sendNoteOn(sustainedNote, 127, CHANNEL);
            }
        } else {
            for (const int pressedNote : pressedNotes) {
                sendNoteOn(pressedNote, 127, CHANNEL);
            }
        }

        if (DEBUG) {
            Serial.println("Switching Arp OFF");
        }
        // add a little delay, to debounce the ARP switch
        delay(50);
    }

    const bool oldMidi1Thru = midi1Thru;
    const bool newMidi1Thru = digitalRead(MIDI_1_THRU_ON_OFF_SWITCH_PIN) == HIGH;

    // MIDI 1 Thru was off and is now on
    if (!oldMidi1Thru && newMidi1Thru) {
        midi1AllNotesOff();
        midi1Thru = true;
        Serial.println("MIDI 1 Thru: ON");
        MIDI1.turnThruOn();
    }

    // MIDI 1 Thru was on in is now off
    if (oldMidi1Thru && !newMidi1Thru) {
        midi1Thru = false;
        Serial.println("MIDI 1 Thru: OFF");
        MIDI1.turnThruOff();
    }

    MIDI1.read();
    MIDI2.read();
}

void noteOn(const byte channel, const byte note, const byte velocity) {
    // if the arp is active, the note will be played automatically, so we need to prevent retriggers in that case
    // In very slow arp speeds it would take a long time until the note sounds, so we play the first not anyways.
    if (!arpActivated || pressedNotesEmpty()) {
        sendNoteOn(note, velocity, CHANNEL);
    }

    // the user is entering a new chord
    if (pressedNotesEmpty()) {
        for (int sustainedNotesIndex = 0; sustainedNotesIndex < 128; ++sustainedNotesIndex) {
            if (sustainedNotes[sustainedNotesIndex] && sustainedNotesIndex != note) {
                MIDI1.sendNoteOff(sustainedNotesIndex, 0, channel);
            }
        }
        clearSustainedNotes();
        sustainedNotesCount = 0;
    }
    pressedNotes[note] = true;
    pressedNotesCount++;
    sustainedNotes[note] = true;
    sustainedNotesCount++;

    if (DEBUG) {
        printSustainedNotes();
        printPressedNotes();
    }
}

void noteOff(const byte channel, const byte note, const byte velocity) {
    if (!holdFunctionActivated) {
        sendNoteOff(note, velocity, CHANNEL);
        sustainedNotes[note] = false;
        sustainedNotesCount--;
    }
    pressedNotes[note] = false;
    pressedNotesCount--;
}

static void handleClock() {
    if (!arpActivated) {
        return;
    }

    if (clockCounter % timeDivision == 0) {
        if (DEBUG) {
            Serial.println("\n\nArp Pulse!");
            printSustainedNotes();
            printPressedNotes();
        }

        if (!sustainedNotesEmpty()) {
            if (arpIndex >= sustainedNotesCount) {
                arpIndex = 0;
            }

            if (DEBUG) {
                Serial.printf("arpIndex: %d\n", arpIndex);
            }

            int sustainedNotesIndex = 0;
            for (int note = 0; note < NOTES_ARRAY_SIZE; ++note) {
                if (sustainedNotes[note]) { // the current note is sustained
                    sendNoteOff(note, 127, CHANNEL);
                    if (sustainedNotesIndex == arpIndex) {
                        sendNoteOn(note, 127, CHANNEL);
                    }
                    sustainedNotesIndex++;
                }
            }
            arpIndex++;
        }
    }

    // Read the rotary switch every 1/4 note, this should suffice in accuracy
    if (clockCounter % _1_4 == 0) {
        const Pattern newPattern =
        rotarySwitchNumberToPattern(getRotarySwitchNumber(analogRead(PATTERN_ROTARY_SWITCH_PIN)));
        if (newPattern != pattern) {
            pattern = newPattern;
            Serial.printf("Pattern: %s\n", patternToString(pattern));
        }

        const TimeDivision newTimeDivision =
            rotarySwitchNumberToTimeDivision(getRotarySwitchNumber(analogRead(TIME_DIVISION_ROTARY_SWITCH_PIN)));
        if (newTimeDivision != timeDivision) {
            timeDivision = newTimeDivision;
            Serial.printf("TimeDivision: %s\n", timeDivisionToString(timeDivision));
        }
    }

    // the clock counter needs to stay in range between 0 and 32 quarter notes, as this is the biggest subdivision we support
    clockCounter = (clockCounter + 1) % _32_4;
}
