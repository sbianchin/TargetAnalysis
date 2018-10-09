/*
 * Created by Jack Hong on 2018-06-28. (jhong@alumni.ubc.ca)
 */

#include "findGoodTargetEvents.hpp"
#include "CommonParameters.hpp"
#include "CutsAndWindows.hpp"

namespace CP = CommonParameters;
namespace CW = CutsAndWindows;

bool findGoodTargetEvents(DetectorData &data) {
    bool is_good_TARGET_event = false;
    int TARGET_events_counter = 0;

    for (int i = 0; i < 256; i++) {
        if ((data.ADC_High_TARGET[i] > 0 && data.TDC_LE_TARGET[i][0] >= CW::TARGET_TDC_min[i] &&
             data.TDC_LE_TARGET[i][0] <= CW::TARGET_TDC_max[i]) ||
            (data.ADC_High_TARGET[i] > 0 && data.TDC_LE_TARGET[i][1] >= CW::TARGET_TDC_min[i] &&
             data.TDC_LE_TARGET[i][1] <= CW::TARGET_TDC_max[i]) ||
            (data.ADC_High_TARGET[i] > 0 && data.TDC_LE_TARGET[i][2] >= CW::TARGET_TDC_min[i] &&
             data.TDC_LE_TARGET[i][2] <= CW::TARGET_TDC_max[i]) ||
            (data.ADC_High_TARGET[i] > 0 && data.TDC_LE_TARGET[i][3] >= CW::TARGET_TDC_min[i] &&
             data.TDC_LE_TARGET[i][3] <= CW::TARGET_TDC_max[i]) ||
            (data.ADC_High_TARGET[i] < 0 && data.ADC_Low_TARGET[i] > 0))
            TARGET_events_counter++;
    }

    if (TARGET_events_counter >= CP::min_hits) is_good_TARGET_event = true;

    return is_good_TARGET_event;
}