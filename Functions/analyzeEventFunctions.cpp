#ifndef __CINT__

#include "analyzeEventFunctions.hpp"
#include <iostream>
#include <math.h>
#include <fstream>
#include <iostream>
#include <TROOT.h>
#include "TSystem.h"
#include "TFile.h"
#include "TProfile.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TF1.h"
#include "TRandom.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TPolyLine.h"
#include "TLine.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TBranch.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TEllipse.h"
#include "TMarker.h"
#include "SFTfunctions.hpp"
#include "DetectorGeometry.hpp"
#include "CutsAndWindows.hpp"
#endif

using std::endl; using std::cout;
using namespace DetectorGeometry;
namespace CW = CutsAndWindows;

void _NEED_TO_ROTATE(vector<int> vec_myVector) {

    vector<double> vec_xx_vector;
    vec_xx_vector.clear();
    vector<double> vec_yy_vector;
    vec_yy_vector.clear();

    double sum = 0.;
    double mean = 0.;
    int counter = 0;

    for (unsigned int i = 0; i < vec_myVector.size(); i++) {
        vec_xx_vector.push_back(Xloc[vec_myVector[i]]);
        vec_yy_vector.push_back(Yloc[vec_myVector[i]]);
    }

    for (unsigned int j = 0; j < vec_myVector.size(); j++) {
        for (unsigned int k = 0; k < vec_myVector.size(); k++) {
            if (j < k) {
                sum += abs(vec_xx_vector[j] - vec_xx_vector[k]);
                counter++;
            }
        }
        cout << endl;
    }

    mean = sum / counter;

    return;
}

void _ADC_HG_SUM(vector<int> vec_myVector) {

    int ADC_High_TARGET[256];

    for (unsigned int i = 0; i < vec_myVector.size(); i++) {
    }

    cout << endl;

    return;
}


uncertainty calculate_uncertainty(double x, double y, double m, double b, double dm, double db) {
    double dy = pow(x * dm, 2) + pow(db, 2) + x * dm * db;
    double dx = pow((y - b) / (m * m) * dm, 2) + pow(db / m, 2) + (y - b) / (m * m * m) * dm * db;
    uncertainty d;
    d.dx = dx;
    d.dy = dy;
    return d;
}

bool check_vertical_kaon(vector<double> vec_xx_kaon) {
    bool vertical_kaon = true;
    for (unsigned int i = 1; i < vec_xx_kaon.size(); ++i) {
        if (vec_xx_kaon[i] != vec_xx_kaon[0]) {
            vertical_kaon = false;
            break;
        }
    }
    return vertical_kaon;
}

vector<double> SFT_Test_CR_Event(DetectorData data, double phi, double C2X_centroid, double length_in_target) {

    Int_t HG_SFT_ADC_Thr[128] = {0};

    for (int i = 0; i < 128; i++) HG_SFT_ADC_Thr[i] = round(CW::SFT_ADC_Thr_HG[i]) + CW::SFT_ADC_Thr_HG_Offset;

    Double_t ADC_High_SFT_corr[128];
    Int_t has_TDC_SFT_hit[128] = {0};

    char source_mapping[] = "SFT_Mapping_Oct14.txt";  // Mapping file !!!

    char file_mapping[200];
    sprintf(file_mapping, "../Mapping");

    char par_finput[200];
    sprintf(par_finput, "%s/%s", file_mapping, source_mapping);

    Int_t par_temp[2][128];
    ifstream fdat(par_finput, ios::in);
    for (Int_t ii = 0; ii < 128; ii++) fdat >> par_temp[0][ii] >> par_temp[1][ii];
    fdat.close();

    for (Int_t j_SFT = 0; j_SFT < 128; j_SFT++) {
        data.ADC_High_SFT[j_SFT] = data.ADC_High_SFT[j_SFT] - HG_SFT_ADC_Thr[j_SFT];
    }

    for (int j = 0; j < 128; j++) {
        if (data.ADC_High_SFT[j] < 0) ADC_High_SFT_corr[j] = 0;
        else ADC_High_SFT_corr[j] = data.ADC_High_SFT[j];
    }

    for (Int_t ii = 0; ii < 128; ii++) {
        for (Int_t qq = 0; qq < 6; qq++) {
            if (data.TDC_LE_SFT[ii][qq] > CW::SFT_TDC_min[ii] && data.TDC_LE_SFT[ii][qq] < CW::SFT_TDC_max[ii])
                has_TDC_SFT_hit[ii]++;
        }
    }

    vector<double> ZZ;
    ZZ = Z_Avg(ADC_High_SFT_corr, has_TDC_SFT_hit, phi, true, 0, false, C2X_centroid,
               length_in_target);

    return ZZ;
}
