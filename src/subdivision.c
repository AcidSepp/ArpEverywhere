#include "subdivision.h"

TimeDivision rotarySwitchNumberToSubdivision(const int rotarySwitchNumber) {
    switch (rotarySwitchNumber) {
        case 0:
            return _2_1;
        case 1:
            return _1_1;
        case 2:
            return _1_2;
        case 3:
            return _1_4;
        case 4:
            return _1_8;
        case 5:
            return _1_16;
        case 6:
            return _1_32;
        default:
            return _1_4;
    }
}
