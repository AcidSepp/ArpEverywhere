//
// Created by yannick on 9/25/26.
//

#include "Jump.h"

Jump::Jump() {

}

int Jump::next(int sustainedNotesCount) {
    if (playLowestNote) {
        playLowestNote = false;
        return 0;
    }

    if (index % sustainedNotesCount == 0) {
        index++;
    }
    int result = index % sustainedNotesCount;
    index++;
    if (index > 1024) {
        index = 0;
    }

    playLowestNote = true;
    return result;
}
