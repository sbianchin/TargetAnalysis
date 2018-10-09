/*
 * Created by Jack Hong on 2018-08-22. (jhong@alumni.ubc.ca)
 */

#pragma once

#include <vector>
#include "boost_geometry.hpp"
#include "TargetBar.hpp"
#include "selectPrimaryTrackBars.hpp"


using std::vector;

/*
 * Return the bars that form the shortest path from the second path endpoint to the primary track.
 */
vector<TargetBar> selectSecondaryTrackBars(point_t k_stop, point_t tof1, selectPrimaryTrackBarsResult r);
