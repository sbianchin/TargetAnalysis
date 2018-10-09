/*
 * Created by Jack Hong on 2018-06-05. (jhong@alumni.ubc.ca)
 */

#ifndef MACROS_FINDLEPTONS_H
#define MACROS_FINDLEPTONS_H

#include "CommonStructs.hpp"
#include "DetectorData.hpp"
#include <vector>

vector<int> findLeptons(const DetectorData &data, bool is_kaon[256], bool has_TDC_hit[256], int kaon_substitute);

#endif //MACROS_FINDLEPTONS_H
