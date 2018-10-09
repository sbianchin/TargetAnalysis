/* 
 * Created by Jack Hong on 2018-08-24. (jhong@alumni.ubc.ca)
 */

#pragma once

#include "TCanvas.h"
#include "TargetBar.hpp"
#include <vector>

using std::vector;

void drawBars(vector<TargetBar> track_bars, vector<TargetBar> all_bars);
void drawTwoPaths(TCanvas *c, vector<TargetBar> p1, vector<TargetBar> p2, vector<TargetBar> all);
