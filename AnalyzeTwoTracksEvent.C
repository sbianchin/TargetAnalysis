/* 
 * Created by Jack Hong on 2018-07-26. (jhong@alumni.ubc.ca)
 */
#pragma once

#include "AnalyzeTwoTracksEvent.h"
//#include "fitTwoTracks.hpp"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include "boost_geometry.hpp"
#include "boost_graph.hpp"
#include "drawTwoPaths.hpp"
#include "selectPrimaryTrackBars.hpp"
#include "selectSecondaryTrackBars.hpp"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"

using std::vector;

void AnalyzeTwoTracksEvent(int run_number=3994, int event_number=9) {
    vector <point_t> leptons{
            {0, 0.},
            {1,  1},
            {2.12,  2.12},
            {3, 3},
            {4,4},
            {5,5},
            {6,6},
            {7,7},
            {-2, -2 },
            {-3.1, -2.9},
            {-5, -5.1},
            {-6, -6.1},
            {3.0,  4.1},
            {4.1,  6.1},
            {5.0,  7.9},
            {6.0, 10.1}
    };

    vector<TargetBar> lepton_bars;
    for (auto lp : leptons) {
        TargetBar b(lp);
        lepton_bars.push_back(b);
    }
    point_t k_stop{-7.8, -8.2};
    point_t tof1{7, 7};

    auto result = selectPrimaryTrackBars(lepton_bars, k_stop, tof1);
    vector<TargetBar> secondary_bars = selectSecondaryTrackBars(k_stop, tof1, result);

    lepton_bars.push_back(tof1);
    lepton_bars.push_back(k_stop);
    TCanvas *c = new TCanvas("c", "Test two paths", 1000, 500);
    drawTwoPaths(c, result.primary_track_bars, secondary_bars, lepton_bars);
}