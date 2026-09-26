//
// Created by yannick on 9/26/26.
//

#include "Random3.h"
#include <random>

Random3::Random3() {

}

int Random3::next(const int sustainedNoteCount) {
    const bool changeDirection = rand() % 4 == 0;
    if (changeDirection) {
        up = !up;
    }

    int result;
    if (up) {
        result = index % sustainedNoteCount;
    } else {
        result = sustainedNoteCount - 1 - index % sustainedNoteCount;
    }

    index++;
    if (index > 1024) {
        index = 0;
    }

    return result;
}
