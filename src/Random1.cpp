//
// Created by yannick on 9/26/26.
//

#include "Random1.h"

#include <random>

Random1::Random1() {

}

int Random1::next(const int sustainedNoteCount) {
    // I know this sucks, but this is no cryptography xD
    return rand() % sustainedNoteCount;
}
