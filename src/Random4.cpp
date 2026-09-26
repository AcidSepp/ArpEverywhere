//
// Created by yannick on 9/26/26.
//


#include "Random4.h"

#include <random>

Random4::Random4() {

}

int Random4::next(const int sustainedNoteCount) {
    const bool skip = rand() % 4 == 0;
    if (skip) {
        return -1;
    }
    // I know this sucks, but this is no cryptography xD
    return rand() % sustainedNoteCount;
}
