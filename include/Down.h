//
// Created by yannick on 9/25/26.
//

#ifndef ARPEVERYWHERE_DOWN_H
#define ARPEVERYWHERE_DOWN_H


class Down {
    int index = 0;
public:
    Down();

    int next(int sustainedNoteCount);

    void reset();
};


#endif //ARPEVERYWHERE_DOWN_H
