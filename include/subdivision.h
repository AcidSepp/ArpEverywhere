//
// Created by yannick on 9/9/26.
//

#ifndef ARPEVERYWHERE_SUBDEVISION_H
#define ARPEVERYWHERE_SUBDEVISION_H

typedef enum {
    _2_1 = 192,
    _1_1 = 96,
    _1_2 = 48,
    _1_4 = 24,
    _1_8 = 12,
    _1_16 = 6,
    _1_32 = 3,
} Subdivision;

Subdivision rotarySwitchNumberToSubdivision(int rotarySwitchNumber);

#endif //ARPEVERYWHERE_SUBDEVISION_H
