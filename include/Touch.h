//
// Created by yannick on 9/26/26.
//
#pragma once
#include <MIDI.h>

#ifndef ARPEVERYWHERE_TOUCH_H
#define ARPEVERYWHERE_TOUCH_H


class Touch {
    int index = 0;

public:
    Touch();

    int next(byte noteInputOrder[], int noteInputOrderPointer);
};


#endif //ARPEVERYWHERE_TOUCH_H
