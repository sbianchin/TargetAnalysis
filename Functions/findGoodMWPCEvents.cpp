/*
 * Created by Jack Hong on 2018-06-28. (jhong@alumni.ubc.ca)
 */

#include "findGoodMWPCEvents.hpp"

bool findGoodMWPCEvents(DetectorData &data) {
    int count_C2X = 0;
    int count_C2Y = 0;
    int count_C3X = 0;
    int count_C3Y = 0;
    int count_C4X = 0;
    int count_C4Y = 0;
    bool is_good_MWPC_event = false;

    for (int i = 0; i < 56; i++) {
        if (data.ADC_C2X_R[i] > 0. || data.ADC_C2X_L[i] > 0.) count_C2X++;
    }

    for (int ii = 0; ii < 16; ii++) {
        if (data.ADC_C2Y_R[ii] > 0. || data.ADC_C2Y_L[ii] > 0.) count_C2Y++;
    }

    for (int j = 0; j < 64; j++) {
        if (data.ADC_C3X_R[j] > 0. || data.ADC_C3X_L[j] > 0.) count_C3X++;
    }

    for (int jj = 0; jj < 16; jj++) {
        if (data.ADC_C3Y_R[jj] > 0. || data.ADC_C3Y_L[jj] > 0.) count_C3Y++;
    }

    for (int k = 0; k < 72; k++) {
        if (data.ADC_C4X_R[k] > 0. || data.ADC_C4X_L[k] > 0.) count_C4X++;
    }

    for (int kk = 0; kk < 16; kk++) {
        if (data.ADC_C4Y_R[kk] > 0. || data.ADC_C4Y_L[kk] > 0.) count_C4Y++;
    }

    if (count_C2X > 0 && count_C2Y > 0 && count_C3X > 0 && count_C3Y > 0 && count_C4X > 0 &&
        count_C4Y > 0) {
        is_good_MWPC_event = true;
    }

    return is_good_MWPC_event;

}

