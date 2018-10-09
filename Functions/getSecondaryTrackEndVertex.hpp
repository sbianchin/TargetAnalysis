/* 
 * Created by Jack Hong on 2018-08-24. (jhong@alumni.ubc.ca)
 */

#pragma once 

#include "boost_geometry.hpp"
#include "TargetBar.hpp"
#include "selectPrimaryTrackBars.hpp"

vertex_descriptor_t getSecondaryTrackEndVertex(selectPrimaryTrackBarsResult r, point_t k_stop, point_t tof1);
vertex_descriptor_t getSecondaryTrackEndVertex2(selectPrimaryTrackBarsResult r, point_t k_stop, point_t tof1);