#include "timedivision.h"

// see https://www.researchgate.net/publication/360666089/figure/fig1/AS:11431281100551166@1669381326555/Data-structure-chosen-to-allocate-simple-and-compound-meter-rhythms-The-horizontal-axis.png
TimeDivision rotarySwitchNumberToTimeDivision(const int rotarySwitchNumber) {
    switch (rotarySwitchNumber) {
        case 0:
            return _4_4;
        case 1:
            return _1_2;
        case 2:
            return _1_4;
        case 3:
            return _1_8;
        case 4:
            return _1_8T;
        case 5:
            return _1_16;
        case 6:
            return _1_16T;
        case 7:
            return _1_32;
        case 8:
            return _1_32T;
        case 9:
            return _32_4;
        case 10:
            return _16_4;
        case 11:
            return _8_4;
        default:
            return _4_4;
    }
}

const char *timeDivisionToString(const TimeDivision timeDivision) {
    switch (timeDivision) {
        case _32_4:
            return "_32_4";
        case _16_4:
            return "_16_4";
        case _8_4:
            return "_8_4";
        case _4_4:
            return "_4_4";
        case _1_2:
            return "_1_2";
        case _1_4:
            return "_1_4";
        case _1_8:
            return "_1_8";
        case _1_8T:
            return "_1_8T";
        case _1_16:
            return "_1_16";
        case _1_16T:
            return "_1_16T";
        case _1_32:
            return "_1_32";
        case _1_32T:
            return "_1_32T";
        default:
            return "";
    }
}
