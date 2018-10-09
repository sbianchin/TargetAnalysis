/* 
 * Created by Sebastien Bianchin on 2018-08-31. (s.bianchin@triumf.ca)
 */
#pragma once
//#include "Track.h"
#include "DetectorData.hpp"

enum PruningType{
    line, triangle, backtracking   
};

void DisplayEvent(DetectorData *data, PruningType type = line,
                  bool batch_mode=false,
                  int enable_cout=0, bool display=true, bool print_to_console=true,
                  bool print_to_file=false, bool kekcc_file=false);

void DisplayEvent(int run_number=3994, int event_number=0, PruningType type = line,
                  bool batch_mode=false,
                  int enable_cout=0, bool display=true, bool print_to_console=true,
                  bool print_to_file=false, bool kekcc_file=false);

