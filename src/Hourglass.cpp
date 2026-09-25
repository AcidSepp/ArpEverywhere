//
// Created by yannick on 9/25/26.
//

#include "Hourglass.h"

Hourglass::Hourglass() {
}

int Hourglass::next(const int sustainedNotesCount) {
    int result;
    if (low) {
        result = index % sustainedNotesCount;
    } else {
        result = sustainedNotesCount - 1 - index % sustainedNotesCount;
    }

    if (!low) {
        index++;
    }
    low = !low;
    if (index > 1024) {
        index = 0;
    }

    return result;
}
