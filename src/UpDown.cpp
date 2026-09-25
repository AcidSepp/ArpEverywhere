//
// Created by yannick on 9/25/26.
//

#include "UpDown.h"

UpDown::UpDown() {

}

int UpDown::next(const int sustainedNoteCount) {
    int result;
    if (up) {
        result = index % sustainedNoteCount;
    } else {
        result = sustainedNoteCount - 1 - index % sustainedNoteCount;
    }

    index++;
    if (index % sustainedNoteCount == 0) {
        up = !up;
    }
    if (index > 1024) {
        index = 0;
    }

    return result;
}
