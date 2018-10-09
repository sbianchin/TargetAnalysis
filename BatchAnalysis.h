/* 
 * Created by Sebatien Bianchin on 2018-08-03 (s.bianchin@triumf.ca)
 */

#ifndef MACROS_BATCHANALYSIS_H
#define MACROS_BATCHANALYSIS_H

#include <limits>
//#include "AnalyzeEvent.h"
#include "DisplayEvent.h"

int max_int = std::numeric_limits<int>::max();

void BatchAnalysis(int run_number=3994,  PruningType type = triangle, int min_event=0, int max_event=max_int, 
                   bool print_to_console=false, bool print_to_file=true);

#endif //MACROS_BATCHANALYSIS_H

