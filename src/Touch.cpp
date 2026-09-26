//
// Created by yannick on 9/26/26.
//

#include <MIDI.h>
#include "Touch.h"

Touch::Touch() {

}

int Touch::next(byte noteInputOrder[], const int noteInputOrderPointer) {
    const int result = noteInputOrder[index % noteInputOrderPointer];

    index++;
    if (index > 1024) {
        index = 0;
    }

    return result;
}
