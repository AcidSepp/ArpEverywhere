//
// Created by yannick on 9/25/26.
//

#include "Pyramid.h"

Pyramid::Pyramid() {
}

int Pyramid::next(const int sustainedNotesCount) {
    int result;
    if (low) {
        result = index % (sustainedNotesCount / 2);
    } else {
        result = sustainedNotesCount - 1 - index % (sustainedNotesCount / 2);
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
