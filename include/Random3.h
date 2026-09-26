//
// Created by yannick on 9/26/26.
//

#ifndef ARPEVERYWHERE_RANDOM3_H
#define ARPEVERYWHERE_RANDOM3_H


class Random3 {
    bool up = true;
    int index = 0;

public:
    Random3();

    int next(int sustainedNoteCount);
};


#endif //ARPEVERYWHERE_RANDOM3_H
