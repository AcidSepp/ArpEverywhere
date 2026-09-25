//
// Created by yannick on 9/25/26.
//

#ifndef ARPEVERYWHERE_HOURGLASS_H
#define ARPEVERYWHERE_HOURGLASS_H


class Hourglass {
    int index = 0;
    bool low = true;

public:
    Hourglass();

    int next(int sustainedNotesCount);
};


#endif //ARPEVERYWHERE_HOURGLASS_H
