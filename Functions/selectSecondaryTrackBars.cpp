/*
 * Created by Jack Hong on 2018-08-22. (jhong@alumni.ubc.ca)
 */

#pragma once

#include "selectSecondaryTrackBars.hpp"
#include "getSecondaryTrackEndVertex.hpp"
#include "boost_graph.hpp"
#include <cmath>
#include <iostream>

vector<TargetBar> selectSecondaryTrackBars(point_t k_stop, point_t tof1, selectPrimaryTrackBarsResult r) {
    vertex_descriptor_t src_vertex = getSecondaryTrackEndVertex2(r, k_stop, tof1);

    //std::cout << "Source:" << bg::dsv(r.graph[src_vertex].bar.getCoord()) << std::endl;
    // used in dijkstra_shortest_paths
    vector<double> distances(boost::num_vertices(r.graph));
    vector<vertex_descriptor_t> predecessors(boost::num_vertices(r.graph));

    // result is stored in predecessors
    boost::dijkstra_shortest_paths(r.graph, src_vertex,
                                   boost::weight_map(boost::get(&edge_properties_t::weight, r.graph))
                                           .distance_map(boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, r.graph)))
                                           .predecessor_map(boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index,r.graph))));

    double shortestPathSoFar = 1000000;
    vertex_descriptor_t junction = 0;  // intersect between primary and secondary track
    for (auto v : r.primary_track_vertices) {
        if (distances[v] < shortestPathSoFar) {
//            std::cout << "Primary track: " << bg::dsv(r.graph[v].bar.getCoord()) << std::endl;
//            std::cout << "Distance: " << distances[v] << std::endl;
            shortestPathSoFar = distances[v];
            junction = v;
        }
    }

    //std::cout << "Junction: " << bg::dsv(r.graph[junction].bar.getCoord()) << std::endl;

    vector<TargetBar> secondary_track_bars;
    vertex_descriptor_t v = junction;
    vertex_descriptor_t u = predecessors[v];

    // include the junction point
    secondary_track_bars.push_back(r.graph[v].bar);

    // loop until endpoint (src_vertex)
    while (u != v) {
        secondary_track_bars.push_back(r.graph[predecessors[u]].bar);
        v = u;
        u = predecessors[v];
    }

    return secondary_track_bars;
}
