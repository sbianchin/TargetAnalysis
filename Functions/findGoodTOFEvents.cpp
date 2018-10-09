/*
 * Created by Jack Hong on 2018-06-28. (jhong@alumni.ubc.ca)
 */

#include "findGoodTOFEvents.hpp"
#include "CutsAndWindows.hpp"

namespace CW = CutsAndWindows;

bool findGoodTOFEvents(DetectorData &data) {
    bool is_good_TOF_event = false;

    bool Good_TOF1_ADC[12] = {false};
    bool Good_TOF2_ADC[12] = {false};
    bool Good_TOF1_TDC[12] = {false};
    bool Good_TOF2_TDC[12] = {false};
    bool Good_TOF1[12] = {false};
    bool Good_TOF2[12] = {false};
    bool Good_TOFs[12] = {false};

    for (int i = 0; i < 12; i++) {

        if (data.ADC_TOF1U[i] >= 0 || data.ADC_TOF1D[i] >= 0) Good_TOF1_ADC[i] = true;

        if ((data.TDC_TOF1U[i] >= CW::TOF1U_TDC_min[i] && data.TDC_TOF1U[i] <= CW::TOF1U_TDC_max[i]) ||
            (data.TDC_TOF1D[i] >= CW::TOF1D_TDC_min[i] && data.TDC_TOF1D[i] <= CW::TOF1D_TDC_max[i]))
            Good_TOF1_TDC[i] = true;

        if (Good_TOF1_TDC[i] || Good_TOF1_ADC[i]) Good_TOF1[i] = true;

        if ((data.ADC_TOF2AO[i] >= 0 && data.ADC_TOF2AI[i] >= 0) || (data.ADC_TOF2BO[i] >= 0 && data.ADC_TOF2BI[i] >= 0))
            Good_TOF2_ADC[i] = true;

        if (((data.TDC_TOF2AO[i] >= CW::TOF2AO_TDC_min[i] && data.TDC_TOF2AO[i] <= CW::TOF2AO_TDC_max[i]) &&
             (data.TDC_TOF2AI[i] >= CW::TOF2AI_TDC_min[i] && data.TDC_TOF2AI[i] <= CW::TOF2AI_TDC_max[i])) ||
            ((data.TDC_TOF2BO[i] >= CW::TOF2BO_TDC_min[i] && data.TDC_TOF2BO[i] <= CW::TOF2BO_TDC_max[i]) &&
             (data.TDC_TOF2BI[i] >= CW::TOF2BI_TDC_min[i] && data.TDC_TOF2BI[i] <= CW::TOF2BI_TDC_max[i])))
            Good_TOF2_TDC[i] = true;

        if (Good_TOF2_ADC[i] || Good_TOF2_TDC[i]) Good_TOF2[i] = true;
    }

    for (int k = 0; k < 12; k++) {
        if (k != 0 && k != 11) {
            if ((Good_TOF2[k] && Good_TOF1[k - 1]) || (Good_TOF2[k] && Good_TOF1[k]) ||
                (Good_TOF2[k] && Good_TOF1[k + 1]))
                Good_TOFs[k] = true;
        }
    }

    if ((Good_TOF2[0] && Good_TOF1[11]) || (Good_TOF2[0] && Good_TOF1[0]) ||
        (Good_TOF2[0] && Good_TOF1[1]))
        Good_TOFs[0] = true;

    if ((Good_TOF2[11] && Good_TOF1[10]) || (Good_TOF2[11] && Good_TOF1[11]) ||
        (Good_TOF2[11] && Good_TOF1[0]))
        Good_TOFs[11] = true;

    for (int kk = 0; kk < 12; kk++) {
        if (Good_TOFs[kk]) is_good_TOF_event = true;
    }

    return is_good_TOF_event;
}