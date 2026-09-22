//
// Created by yannick on 9/9/26.
//

#ifndef ARPEVERYWHERE_PATTERN_H
#define ARPEVERYWHERE_PATTERN_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    UP,
    DOWN,
    NARROW,
    PYRAMID,
    TOUCH,
    RND_4,
    RND_3,
    RND_2,
    RND_1,
    JUMP,
    HOURGLASS,
    UP_DOWN
} Pattern;

Pattern rotarySwitchNumberToPattern(int rotarySwitchNumber);

const char* patternToString(Pattern);

#ifdef __cplusplus
}
#endif

#endif //ARPEVERYWHERE_PATTERN_H
