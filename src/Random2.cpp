//
// Created by yannick on 9/26/26.
//

#include "Random2.h"

#include <random>

#include <MIDI.h>

Random2::Random2() {

}

int Random2::next(const int sustainedNoteCount) {
    if (sustainedNoteCount <= 1) {
        return 0;
    }
    int result = rand() % sustainedNoteCount;
    while (result == lastNote) {
        result = rand() % sustainedNoteCount;
    }
    lastNote = result;
    return result;
}
