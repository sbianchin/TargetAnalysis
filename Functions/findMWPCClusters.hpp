/*
 * Created by Sebastien Bianchin on 2018-08-03 (s.bianchin@tiumf.ca)
 */

#ifndef MACROS_FINDMWPCCLUSTERS_H
#define MACROS_FINDMWPCCLUSTERS_H

#include "DetectorData.hpp"

double findMWPCClusters(const DetectorData &data, bool is_good_event,
					    int selected_TOF2, bool print_to_console);



#endif //MACROS_FINDMWPCCLUSTERS_H
