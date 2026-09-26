//
// Created by yannick on 9/25/26.
//

#ifndef ARPEVERYWHERE_UPDOWN_H
#define ARPEVERYWHERE_UPDOWN_H

class UpDown {
    int index = 0;
    bool up = true;

public:
    UpDown();

    int next(int sustainedNotesCount);

    void reset();
};

#endif //ARPEVERYWHERE_UPDOWN_H
