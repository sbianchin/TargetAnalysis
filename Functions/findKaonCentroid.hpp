/*
 * Created by Sebastien Bianchin on 2018-07-20 (s.bianchin@tiumf.ca)
 */

#ifndef MACROS_FINDKAONCENTROID_H
#define MACROS_FINDKAONCENTROID_H

#include "CommonStructs.hpp"
#include "DetectorData.hpp"
#include <vector>

vector<double> findKaonCentroid(const DetectorData &data, vector<int> kaon_bars);

#endif //MACROS_FINDKAONCENTROID_H
