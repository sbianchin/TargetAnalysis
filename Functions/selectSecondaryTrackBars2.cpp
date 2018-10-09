/*
 * Created by Jack Hong on 2018-08-22. (jhong@alumni.ubc.ca)
 */

#pragma once

#include "selectSecondaryTrackBars2.hpp"
#include "getSecondaryTrackEndVertex.hpp"
#include "boost_graph.hpp"
#include <boost/unordered_set.hpp>
#include <iostream>
#include <cmath>

vector<TargetBar> selectSecondaryTrackBars2(point_t k_stop, point_t tof1, selectPrimaryTrackBarsResult r) {
    vertex_descriptor_t dest_vertex = getSecondaryTrackEndVertex2(r, k_stop, tof1);
    //std::cout << "Second Track End Point: " << bg::dsv(r.graph[dest_vertex].bar.getCoord()) << std::endl;

    // primary track includes shortest path points from k_stop to tof1
    // secondary track includes points from k_stop to lepton that forms the largest area triangle with tof1 and k_stop,
    // excluding the points in the primary track.

    boost::unordered_set<vertex_descriptor_t> path1_vertices(r.primary_track_vertices.begin(), r.primary_track_vertices.end());
    vertex_descriptor_t v = dest_vertex;
    vertex_descriptor_t u = r.predecessors[v];

    vector<TargetBar> secondary_track_bars;
    // include the endpoint for track 2
    secondary_track_bars.push_back(r.graph[v].bar);

    while (path1_vertices.find(u) == path1_vertices.end()) {
        secondary_track_bars.push_back(r.graph[u].bar);
        v = u;
        u = r.predecessors[v];
    }
    secondary_track_bars.push_back(r.graph[u].bar);

    return secondary_track_bars;
}