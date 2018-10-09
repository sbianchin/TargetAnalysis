/* 
 * Created by Jack Hong on 2018-08-20. (jhong@alumni.ubc.ca)
 */

#pragma once 

#include "boost_geometry.hpp"
#include "boost_graph.hpp"
#include "TargetBar.hpp"

/*
 * Return adjacency_list representation of an undirected graph.
 * All vertices are connected and weights are distances squared.
 */
graph_t makeGraph(vector<TargetBar> vertex_bars);