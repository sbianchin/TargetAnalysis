/* 
 * Created by Jack Hong on 2018-08-24. (jhong@alumni.ubc.ca)
 */

#pragma once

#include "getSecondaryTrackEndVertex.hpp"
#include "boost_graph.hpp"


vertex_descriptor_t getSecondaryTrackEndVertex(point_t k_stop, point_t tof1, selectPrimaryTrackBarsResult r) {
    double max_area_so_far = 0;
    vertex_descriptor_t src = 0; // vertex that forms the largest triangle so far with k_stop and tof1

    for (auto vi : boost::make_iterator_range(boost::vertices(r.graph))) {
        point_t p = r.graph[vi].bar.getCoord();
        polygon_t triangle{{k_stop, tof1, p, k_stop}};

        double area = std::abs(bg::area(triangle));
        if (area > max_area_so_far) {
            max_area_so_far = area;
            src = vi;
        }

    }

    return src;
}

vertex_descriptor_t getSecondaryTrackEndVertex2(selectPrimaryTrackBarsResult r, point_t k_stop, point_t tof1) {
    double max_area_so_far = 0;
    vertex_descriptor_t src = 0; // vertex that forms the largest triangle so far with k_stop and tof1
    point_t p1 = r.primary_track_bars[0].getCoord();
    point_t p2 = r.primary_track_bars.back().getCoord();

    for (auto vi : boost::make_iterator_range(boost::vertices(r.graph))) {
        point_t p = r.graph[vi].bar.getCoord();
        if (bg::equals(p, k_stop) || bg::equals(p, tof1)) continue;
        polygon_t triangle{{p1, p2, p, p1}};

        double area = std::abs(bg::area(triangle));
        if (area >= max_area_so_far) {
            max_area_so_far = area;
            src = vi;
        }

    }
    return src;
}