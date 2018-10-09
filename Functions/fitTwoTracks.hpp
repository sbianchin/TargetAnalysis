/* 
 * Created by Jack Hong on 2018-07-26. (jhong@alumni.ubc.ca)
 */
#pragma once 

#include <vector>
#include "TargetBar.hpp"
#include "boost_geometry.hpp"

using std::vector;

std::vector<TargetBar> fitTwoTracks(vector<point_t> leptons, point_t k_stop, point_t tof1);
point_t computeLargestTriangle(polygon_t hull, point_t k_stop, point_t tof1);
vertex_descriptor_t findVertex(point_t p, graph_t g);
vertex_descriptor_t findPaths(vertex_descriptor_t v1, vertex_descriptor_t v2,
                              vector<vertex_descriptor_t> p, path_t &path1, path_t &path2);
void assignRemainingPoints(graph_t g, path_t &p1, path_t &p2,
                  segment_t s1, segment_t s2);
path_t makePathWithAllVertices(graph_t g);
vector<point_t> pathToPoints (graph_t g, path_t p);
void drawPath(path_t p, path_t all_p, graph_t g);
void drawTwoPaths(path_t p1, path_t p2, graph_t g);
void drawPolygon(polygon_t p);
void drawMultiplePolygons(vector<polygon_t> polygons);