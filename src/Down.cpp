//
// Created by yannick on 9/25/26.
//

#include "Down.h"

Down::Down() {
}

int Down::next(const int sustainedNoteCount) {
    const int result = sustainedNoteCount - 1 - index % sustainedNoteCount;

    index++;
    if (index > 1024) {
        index = 0;
    }

    return result;
}

void Down::reset() {
    index = 0;
}
