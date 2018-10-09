/*
 * Created by Sebastien Bianchin on 2018-07-17. (s.bianchin@triumf.ca)
 */

#ifndef MACROS_FINDKAONTDCAVERAGE_H
#define MACROS_FINDKAONTDCAVERAGE_H

#include "CommonStructs.hpp"
#include "DetectorData.hpp"
#include <vector>

vector<int> findKaonTDCAverage(const DetectorData &data, bool printout);

#endif //MACROS_FINDKAONTDCAVERAGE_H
