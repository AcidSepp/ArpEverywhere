//
// Created by yannick on 9/25/26.
//

#ifndef ARPEVERYWHERE_PYRAMID_H
#define ARPEVERYWHERE_PYRAMID_H


class Pyramid {
    int index = 0;
    bool low = true;

public:
    Pyramid();

    int next(int sustainedNotesCount);

    void reset();
};


#endif //ARPEVERYWHERE_PYRAMID_H
