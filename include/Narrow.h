//
// Created by yannick on 9/25/26.
//

#ifndef ARPEVERYWHERE_NARROW_H
#define ARPEVERYWHERE_NARROW_H


class Narrow {
    int index = 0;
    bool up = true;

public:
    Narrow();

    int next(int sustainedNotesCount);

    void reset();
};


#endif //ARPEVERYWHERE_NARROW_H
