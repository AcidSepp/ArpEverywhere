//
// Created by yannick on 9/25/26.
//

#ifndef ARPEVERYWHERE_JUMP_H
#define ARPEVERYWHERE_JUMP_H


class Jump {
    int index = 0;
    bool playLowestNote = true;

public:
    Jump();

    int next(int sustainedNotesCount);
};


#endif //ARPEVERYWHERE_JUMP_H
