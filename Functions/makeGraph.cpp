/* 
 * Created by Jack Hong on 2018-08-20. (jhong@alumni.ubc.ca)
 */

#pragma once

#include "makeGraph.hpp"


/*
 * Return adjacency_list representation of an undirected graph.
 * All vertices are connected and weights are distances squared.
 */
graph_t makeGraph(vector<TargetBar> vertex_bars) {
    graph_t g;

    // Add vertices
    for (auto vertex_bar : vertex_bars) {
        vertex_descriptor_t v = boost::add_vertex(g);
        g[v].bar = vertex_bar;
    }

    int num_vertices = static_cast<int>(vertex_bars.size());
    // add edges
    for (int i=0; i<num_vertices-1; i++) {
        for (int j=i+1; j<num_vertices; j++) {
            vertex_descriptor_t vi = boost::vertex(i, g);
            vertex_descriptor_t vj = boost::vertex(j, g);
            std::pair<edge_descriptor_t,bool> edge = boost::add_edge(vi, vj, g);

            // use distances squared as weights
            double dist_sq = bg::comparable_distance(g[vi].bar.getCoord(), g[vj].bar.getCoord());
            g[edge.first].weight = dist_sq;
        }
    }

    return g;
}