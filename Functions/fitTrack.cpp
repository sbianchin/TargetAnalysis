/*
 * Created by Jack Hong on 2018-08-10. (jhong@alumni.ubc.ca)
 */
#pragma once

#include "fitTrack.hpp"
#include "TPrincipal.h"
#include <iostream>
#include "TBrowser.h"

Track fitTrack(vector<TargetBar> track_bars) {
    TPrincipal * pca = new TPrincipal(2, "ND");

    Double_t *data_point = new Double_t[2];
    for (auto bar : track_bars) {
        point_t p = bar.getCoord();
        data_point[0] = p.x();
        data_point[1] = p.y();
        pca->AddRow(data_point);
    }
    delete [] data_point;

    pca->MakePrincipals();
    pca->Print();
    pca->Test();
    pca->GetEigenVectors()->Print();

    Track track;
    return track;
}