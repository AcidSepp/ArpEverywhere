//
// Created by yannick on 9/25/26.
//

#include "Narrow.h"

Narrow::Narrow() {
}

int Narrow::next(const int sustainedNotesCount) {
    int result;
    if (up) {
        result = index % sustainedNotesCount;
    } else {
        result = sustainedNotesCount - 1 - index % sustainedNotesCount;
    }

    index++;
    if (index % sustainedNotesCount == 0) {
        index++;
        up = !up;
    }
    if (index > 1024) {
        index = 0;
    }

    return result;
}

void Narrow::reset() {
    up = true;
    index = 0;
}
