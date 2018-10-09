/* 
 * Created by Jack Hong on 2018-08-24. (jhong@alumni.ubc.ca)
 */

#pragma once

#include "drawTwoPaths.hpp"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"

void drawBars(vector<TargetBar> track_bars, vector<TargetBar> all_bars) {
    vector<double> x;
    vector<double> y;
    for (auto b : track_bars) {
        x.push_back(b.getCoord().x());
        y.push_back(b.getCoord().y());
    }

    vector<double> all_x;
    vector<double> all_y;
    for (auto b : all_bars) {
        all_x.push_back(b.getCoord().x());
        all_y.push_back(b.getCoord().y());
    }

    TGraph *gr = new TGraph(all_x.size(), all_x.data(), all_y.data());
    TGraph *gr2 = new TGraph(x.size(), x.data(), y.data());

    gr->SetLineWidth(4);
    gr->SetMarkerColor(1);
    gr->SetMarkerSize(1.5);
    gr->SetMarkerStyle(21);
    gr->GetXaxis()->SetTitle("X");
    gr->GetYaxis()->SetTitle("Y");
    gr->GetXaxis()->SetLimits(-50., 50.);
    gr->GetYaxis()->SetRangeUser(-50., 50.);
    gr->Draw("PA");

    gr2->SetLineWidth(4);
    gr2->SetMarkerColor(2);
    gr2->SetMarkerSize(1.5);
    gr2->SetMarkerStyle(21);
    gr2->Draw("P");
}

void drawTwoPaths(TCanvas *c, vector<TargetBar> p1, vector<TargetBar> p2, vector<TargetBar> all) {
    c->Divide(2, 1);
    c->cd(1);
    drawBars(p1, all);

    c->cd(2);
    drawBars(p2, all);
}