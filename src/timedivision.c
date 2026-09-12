#include "timedivision.h"

// see https://www.researchgate.net/publication/360666089/figure/fig1/AS:11431281100551166@1669381326555/Data-structure-chosen-to-allocate-simple-and-compound-meter-rhythms-The-horizontal-axis.png
TimeDivision rotarySwitchNumberToSubdivision(const int rotarySwitchNumber) {
    switch (rotarySwitchNumber) {
        case 0:
            return _32_4;
        case 1:
            return _16_4;
        case 2:
            return _8_4;
        case 3:
            return _4_4;
        case 4:
            return _1_2;
        case 5:
            return _1_4;
        case 6:
            return _1_8;
        case 7:
            return _1_8T;
        case 8:
            return _1_16;
        case 9:
            return _1_16T;
        case 10:
            return _1_32;
        case 11:
            return _1_32T;
    }
}
