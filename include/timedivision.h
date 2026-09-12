//
// Created by yannick on 9/9/26.
//

#ifndef ARPEVERYWHERE_SUBDEVISION_H
#define ARPEVERYWHERE_SUBDEVISION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    _2_1 = 192,
    _1_1 = 96,
    _1_2 = 48,
    _1_4 = 24,
    _1_8 = 12,
    _1_16 = 6,
    _1_32 = 3,
} TimeDivision;

TimeDivision rotarySwitchNumberToSubdivision(int rotarySwitchNumber);

#ifdef __cplusplus
}
#endif

#endif //ARPEVERYWHERE_SUBDEVISION_H
