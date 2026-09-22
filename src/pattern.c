#include "pattern.h"

Pattern rotarySwitchNumberToPattern(const int rotarySwitchNumber) {
    switch (rotarySwitchNumber) {
        case 0:
            return NARROW;
        case 1:
            return DOWN;
        case 2:
            return UP;
        case 3:
            return UP_DOWN;
        case 4:
            return HOURGLASS;
        case 5:
            return JUMP;
        case 6:
            return RND_1;
        case 7:
            return RND_2;
        case 8:
            return RND_3;
        case 9:
            return RND_4;
        case 10:
            return TOUCH;
        case 11:
            return PYRAMID;
        default:
            return UP;
    }
}

const char *patternToString(const Pattern pattern) {
    switch (pattern) {
        case UP:
            return "UP";
        case DOWN:
            return "DOWN";
        case NARROW:
            return "NARROW";
        case PYRAMID:
            return "PYRAMID";
        case TOUCH:
            return "TOUCH";
        case RND_4:
            return "RND_4";
        case RND_3:
            return "RND_3";
        case RND_2:
            return "RND_2";
        case RND_1:
            return "RND_1";
        case JUMP:
            return "JUMP";
        case HOURGLASS:
            return "HOURGLASS";
        case UP_DOWN:
            return "UP_DOWN";
        default:
            return "";
    }
}
