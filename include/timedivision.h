//
// Created by yannick on 9/9/26.
//

#ifndef ARPEVERYWHERE_TIME_DIVISION_H
#define ARPEVERYWHERE_TIME_DIVISION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    _32_4 = 384,
    _16_4 = 288,
    _8_4 = 192,
    _4_4 = 96,
    _1_2 = 48,
    _1_4 = 24,
    _1_8 = 12,
    _1_8T = 8,
    _1_16 = 6,
    _1_16T = 4,
    _1_32 = 3,
    _1_32T = 2,
} TimeDivision;

TimeDivision rotarySwitchNumberToTimeDivision(int rotarySwitchNumber);

const char* timeDivisionToString(TimeDivision);

#ifdef __cplusplus
}
#endif

#endif //ARPEVERYWHERE_TIME_DIVISION_H
