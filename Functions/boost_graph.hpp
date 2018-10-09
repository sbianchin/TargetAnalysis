/* 
 * Created by Jack Hong on 2018-08-23. (jhong@alumni.ubc.ca)
 */

#pragma once 

#include <utility>
#include "boost_geometry.hpp"
#include "TargetBar.hpp"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/unordered_set.hpp>

typedef std::pair<int, int> edge_t;

typedef struct vertex_properties {
    TargetBar bar;
} vertex_properties_t;

typedef struct edge_properties {
    double weight;
} edge_properties_t;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS,
vertex_properties_t, edge_properties_t> graph_t;
typedef graph_t::vertex_descriptor vertex_descriptor_t;
typedef graph_t::edge_descriptor edge_descriptor_t;
typedef boost::property_map<graph_t, boost::vertex_index_t>::type index_map_t;
typedef boost::iterator_property_map<vertex_descriptor_t*, index_map_t*,
        vertex_descriptor_t, vertex_descriptor_t&> predecessor_map_t;
typedef boost::unordered_set<vertex_descriptor_t> path_t;