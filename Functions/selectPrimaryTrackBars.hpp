/* 
 * Created by Jack Hong on 2018-08-17. (jhong@alumni.ubc.ca)
 */
#pragma once 

#include "boost_geometry.hpp"
#include "boost_graph.hpp"
#include <vector>
#include "TargetBar.hpp"

using std::vector;

struct selectPrimaryTrackBarsResult {
    vector<TargetBar> primary_track_bars;
    vector<vertex_descriptor_t> primary_track_vertices;
    graph_t graph;
    vector<vertex_descriptor_t> predecessors;
};

selectPrimaryTrackBarsResult selectPrimaryTrackBars(vector<TargetBar> leptons, point_t src, point_t dest);