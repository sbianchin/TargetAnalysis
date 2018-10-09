///*
// * Created by Jack Hong on 2018-07-26. (jhong@alumni.ubc.ca)
// */
//#pragma once
//
//#include "fitTwoTracks.hpp"
//#include "fitTrack.hpp"
//#include "makeGraph.hpp"
//#include <iostream>
//#include "TGraph.h"
//#include "TCanvas.h"
//#include "TAxis.h"
//#include "TMath.h"
//#include <list>
//#include <algorithm>
//#include <boost/graph/graph_utility.hpp>
//#include "EventPlot.hpp"
//
//using std::cout;
//using std::endl;
//
//vector<Track> fitTwoTracks(vector<point_t> leptons, point_t k_stop, point_t tof1){
//
//    // ------ dijkstra's algorithm with squared distances as weights -------
//
//    // vertices of graph include the k_stop, tof1, and all leptons
//    vector<point_t> vertex_points{k_stop};
//    vertex_points.push_back(tof1);
//    vertex_points.insert(vertex_points.end(), leptons.begin(), leptons.end());
//
//    graph_t graph = makeGraph(vertex_points);
//    vertex_descriptor_t source = boost::vertex(0, graph);  // k_stop (0th element of vertices) is the source.
//    vertex_descriptor_t tof1_vertex = boost::vertex(1, graph);
//
//    // used in dijkstra_shortest_paths
//    vector<double> distances(boost::num_vertices(graph));
//    vector<vertex_descriptor_t> predecessors(boost::num_vertices(graph));
//
//    // result is stored in predecessors
//    boost::dijkstra_shortest_paths(graph, source,
//                                   boost::weight_map(boost::get(&edge_properties_t::weight, graph))
//                                           .distance_map(boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, graph)))
//                                           .predecessor_map(boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index,graph))));
//
//    // primary track includes shortest path points from k_stop to tof1
//    // secondary track includes points from k_stop to lepton that forms the largest area triangle with tof1 and k_stop,
//    // excluding the points in the primary track.
//
//    // assign leptons to polygon
//    polygon_t poly;
//    bg::assign_points(poly, leptons);
//    bg::append(poly, leptons[0]); // close the polygon
//
//    polygon_t hull;
//    bg::convex_hull(poly, hull);
//
//    point_t track2_endpoint = computeLargestTriangle(hull, k_stop, tof1);
//
//    // find the two end point vertices and the shortest paths to the endpoints
//    vertex_descriptor_t v1 = findVertex(tof1, graph);
//    vertex_descriptor_t v2 = findVertex(track2_endpoint, graph);
//    path_t path1;
//    path_t path2;
//    vertex_descriptor_t junction = findPaths(v1, v2, predecessors, path1, path2);
//
//    point_t junction_point = graph[junction].point;
//
//    segment_t seg1{k_stop, tof1};
//    segment_t seg2{junction_point, track2_endpoint};
//
//    // TODO: Decide if we actually want to do this or not
//    //assignRemainingPoints(graph, path1, path2, seg1, seg2);
//
//    path1.erase(tof1_vertex); // actually, we don't want to include the TOF1 in the fit...
//    vector<point_t> path1_points = pathToPoints(graph, path1);
//    vector<point_t> path2_points = pathToPoints(graph, path2);
////
////    std::cout << "Path 1:" << std::endl;
////    for (auto p : path1_points) {
////        std::cout << bg::dsv(p) << std::endl;
////    }
////    std::cout << std::endl;
////    std::cout << "Path 2: " << std::endl;
////    for (auto p : path2_points) {
////        std::cout << bg::dsv(p) << std::endl;
////    }
//
//    drawTwoPaths(path1, path2, graph);
//
//    Track track1 = fitTrack(path1_points);
//    Track track2 = fitTrack(path2_points);
//
//    vector<Track> tracks{track1, track2};
//
//    return tracks;
//}
//
///*
// * Return the lepton point that forms the largest triangle with the k_stop and tof1 points.
// */
//point_t computeLargestTriangle(polygon_t hull, point_t k_stop, point_t tof1) {
//    double max_area_so_far = 0;
//    point_t largest_triangle_so_far; // point that forms the largest triangle so far with k_stop and tof1
//    vector<point_t> hull_points = hull.outer();
//    for (auto &p : hull_points) {
//        polygon_t triangle{{k_stop, tof1, p, k_stop}};
//        double area = TMath::Abs(bg::area(triangle));
//        if (area > max_area_so_far) {
//            max_area_so_far = area;
//            largest_triangle_so_far = p;
//        }
//    }
//
//    return largest_triangle_so_far;
//}
//
//vertex_descriptor_t findVertex(point_t p, graph_t g) {
//    vertex_descriptor_t v = boost::vertex(0, g);
//    for (auto vi : boost::make_iterator_range(boost::vertices(g))) {
//        if (bg::equals(p, g[vi].point)) {
//            v = boost::vertex(vi, g);
//        }
//    }
//    return v;
//}
//
///*
// * Return the paths to v1 and v2, and the junction vertex.
// * path1 and path2 are returned by storing them in the path1 and path2 inputs.
// * The first common vertex is the junction point of the two paths, and is returned by the function.
// */
//vertex_descriptor_t findPaths(vertex_descriptor_t v1, vertex_descriptor_t v2,
//        vector<vertex_descriptor_t> p, path_t &path1, path_t &path2) {
//
//    path1.insert(v1);
//    vertex_descriptor_t u1 = p[v1];
//
//    // loop until you reach the source vertex (kstop)
//    while (u1 != v1) {
//        path1.insert(u1);
//        v1 = u1;
//        u1 = p[v1];
//    }
//
//    path2.insert(v2);
//    vertex_descriptor_t u2 = p[v2];
//
//    // backtrack until you reach the first vertex in common with path1. That vertex is the junction.
//    while (path1.find(u2) == path1.end()) {
//        path2.insert(u2);
//        v2 = u2;
//        u2 = p[v2];
//    }
//    path2.insert(u2);
//    // at the end of the loop, u2 is the junction vertex
//
//    return u2;
//
//}
//
//void assignRemainingPoints(graph_t g, path_t &p1, path_t &p2,
//        segment_t s1, segment_t s2) {
//    for (const auto vi : boost::make_iterator_range(boost::vertices(g))) {
//        // if the vertex is not in path 1 and path 2 assign it to the closest line
//        if ((p1.find(vi) == p1.end()) && (p2.find(vi) == p2.end())) {
//            point_t pt = g[vi].point;
//            bg::distance(pt, s1) < bg::distance(pt, s2) ? p1.insert(vi) : p2.insert(vi);
//        }
//    }
//}
//
//path_t makePathWithAllVertices(graph_t g) {
//    path_t path;
//    for (const auto vi : boost::make_iterator_range(boost::vertices(g))) {
//        path.insert(vi);
//    }
//    return path;
//}
//
//// Return the points in the path
//vector<point_t> pathToPoints (graph_t g, path_t p) {
//    vector<point_t> points;
//    for (auto &vi : p) {
//        points.push_back(g[vi].point);
//    }
//    return points;
//}
//
//void drawPath(path_t p, path_t all_p, graph_t g) {
//    vector<double> x;
//    vector<double> y;
//    for (auto &vi : p) {
//        x.push_back(g[vi].point.x());
//        y.push_back(g[vi].point.y());
//    }
//
//    vector<double> all_x;
//    vector<double> all_y;
//    for (auto &vi : all_p) {
//        all_x.push_back(g[vi].point.x());
//        all_y.push_back(g[vi].point.y());
//    }
//
//    TGraph *gr = new TGraph(all_x.size(), all_x.data(), all_y.data());
//    TGraph *gr2 = new TGraph(x.size(), x.data(), y.data());
//
//    gr->SetLineWidth(4);
//    gr->SetMarkerColor(1);
//    gr->SetMarkerSize(1.5);
//    gr->SetMarkerStyle(21);
//    gr->GetXaxis()->SetTitle("X");
//    gr->GetYaxis()->SetTitle("Y");
//    gr->GetXaxis()->SetLimits(-50, 50);
//    gr->GetYaxis()->SetRangeUser(-50, 50);
//    gr->Draw("PA");
//
//    gr2->SetLineWidth(4);
//    gr2->SetMarkerColor(2);
//    gr2->SetMarkerSize(1.5);
//    gr2->SetMarkerStyle(21);
//    gr2->Draw("P");
//}
//
//void drawTwoPaths(path_t p1, path_t p2, graph_t g) {
//    TCanvas *c = new TCanvas("c", "Polygons", 1000, 500);
//    path_t all_vertices = makePathWithAllVertices(g);
//    c->Divide(2, 1);
//    c->cd(1);
//    drawPath(p1, all_vertices, g);
//
//    c->cd(2);
//    drawPath(p2, all_vertices, g);
//}
//
//void drawPolygon (polygon_t p) {
//    vector<double> x;
//    vector<double> y;
//    for (auto &point : p.outer()) {
//        x.push_back(point.x());
//        y.push_back(point.y());
//    }
//
//    TGraph *gr = new TGraph(x.size(), x.data(), y.data());
//
//    gr->SetLineWidth(4);
//    gr->SetMarkerColor(4);
//    gr->SetMarkerSize(1.5);
//    gr->SetMarkerStyle(21);
//    gr->SetTitle("Polygon");
//    gr->GetXaxis()->SetTitle("X");
//    gr->GetYaxis()->SetTitle("Y");
//    gr->Draw("PAL");
//}
//
//void drawMultiplePolygons(vector<polygon_t> polygons) {
//    TCanvas *c = new TCanvas("c", "Polygons", 900, 700);
//    int n = static_cast<int>(polygons.size());
//    c->Divide(n, 1);
//    int current_pad = 1;
//    for (auto &polygon : polygons) {
//        c->cd(current_pad++);
//        drawPolygon(polygon);
//    }
//}
