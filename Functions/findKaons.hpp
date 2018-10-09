/*
 * Created by Sebastien Bianchin on 2018-07-17. (s.bianchin@triumf.ca)
 */

#ifndef MACROS_FINDKAONS_H
#define MACROS_FINDKAONS_H

#include "CommonStructs.hpp"
#include "DetectorData.hpp"
#include <vector>

vector<int> findKaons(const DetectorData &data, bool has_TDC_hit_KStop[256], bool has_kaon_sub, int kaon_substitute);

#endif //MACROS_FINDKAONS_H
