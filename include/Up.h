//
// Created by yannick on 9/25/26.
//

#ifndef ARPEVERYWHERE_UP_H
#define ARPEVERYWHERE_UP_H


class Up {
    int index = 0;
public:
    Up();

    int next(int sustainedNoteCount);

    void reset();
};


#endif //ARPEVERYWHERE_UP_H
