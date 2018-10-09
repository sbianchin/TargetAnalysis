/* 
 * Created by Jack Hong on 2018-08-17. (jhong@alumni.ubc.ca)
 */

#include "selectPrimaryTrackBars.hpp"
#include "makeGraph.hpp"
#include <iostream>

selectPrimaryTrackBarsResult selectPrimaryTrackBars(vector<TargetBar> lepton_bars, point_t src, point_t dest) {

    // ------ dijkstra's algorithm with squared distances as weights -------

    // vertices of graph include the src, dest, and all leptons
    
    // Only require the point field to be properly initialized
    TargetBar src_bar(src);
    TargetBar dest_bar(dest);
    
    vector<TargetBar> vertex_bars{src_bar, dest_bar};
    vertex_bars.insert(vertex_bars.end(), lepton_bars.begin(), lepton_bars.end());

    graph_t graph = makeGraph(vertex_bars);
    vertex_descriptor_t src_vertex = boost::vertex(0, graph);  // k_stop (0th element of vertices) is the source.
    vertex_descriptor_t dest_vertex = boost::vertex(1, graph);

    // used in dijkstra_shortest_paths
    vector<double> distances(boost::num_vertices(graph));
    vector<vertex_descriptor_t> predecessors(boost::num_vertices(graph));

    // result is stored in predecessors
    boost::dijkstra_shortest_paths(graph, src_vertex,
                                   boost::weight_map(boost::get(&edge_properties_t::weight, graph))
                                           .distance_map(boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, graph)))
                                           .predecessor_map(boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index,graph))));

    selectPrimaryTrackBarsResult results;

    vertex_descriptor_t v = dest_vertex;
    // include the starting point (TOF1 by uncommenting the next line)
    //path_points.push_back(graph[predecessors[v]].bar);
    vertex_descriptor_t u = predecessors[v];

    // loop until you reach the source vertex (kstop)
    while (u != v) {
        TargetBar bar = graph[u].bar;
        results.primary_track_bars.push_back(bar);
        results.primary_track_vertices.push_back(u);
        v = u;
        u = predecessors[v];
    }

//    for (auto b : results.primary_track_bars) {
//        std::cout << bg::dsv(b.getCoord()) << std::endl;
//    }
//    for (auto v : results.primary_track_vertices) {
//        std::cout << bg::dsv(graph[v].bar.getCoord()) << std::endl;
//    }

    // Remove the k-stop from the list
//    results.primary_track_bars.pop_back();
//    results.primary_track_vertices.pop_back();

    results.graph = graph;
    results.predecessors = predecessors;

    return results;
}
