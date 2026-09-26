//
// Created by yannick on 9/26/26.
//

#ifndef ARPEVERYWHERE_RANDOM2_H
#define ARPEVERYWHERE_RANDOM2_H


class Random2 {
    int lastNote = 0;

public:
    Random2();

    int next(int sustainedNoteCount);
};


#endif //ARPEVERYWHERE_RANDOM2_H
