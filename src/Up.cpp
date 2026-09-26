//
// Created by yannick on 9/25/26.
//

#include "Up.h"

Up::Up() {

}

int Up::next(const int sustainedNoteCount) {
    const int result = index % sustainedNoteCount;

    index++;
    if (index > 1024) {
        index = 0;
    }

    return result;
}

void Up::reset() {
    index = 0;
}