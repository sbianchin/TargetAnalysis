#pragma once

#include "TLine.h"
#include "TMath.h"

// !!! NOTE: DO NOT declare your variables in here unless you absolutely have to.
//           These are supposed to be common parameters. Not variables.

namespace CommonParameters {
    // TODO: Cleanup unused variables and move the parameters that are not actually common to their respective files.

    const Double_t PI = TMath::Pi();
    const unsigned int lepton_cluster_size = 2;
    const unsigned int kaon_cluster_size = 3;    // mod from 5 to 3 by MH  sept 29/17
    const int min_hits = 2;  // ## Minimum number of hits required in the TARGET
    const int weight_edge_bars_fit1 = 2;
    const int weight_edge_bars_fit2 = 1;

    const int weight_TOF1_fit1 = 3;
    const int weight_TOF1_fit3 = 3;

    bool dist_pruned = false;
    const double DISTANCE_MAX_TO_KAON_PRUNED = 6.;  
    const double DISTANCE_MAX_TO_KAON_FINAL = 9.;

    int evt_counter = 1000;

    const float R_TARGET = 29.0;  
    const float R_TOF1 = 47.1;
    const float R_SFT_L1 = 41.6;
    const float R_Cut = 29.0;

    const Int_t nBars = 256;
    const Int_t nFibers = 128;
    const Int_t nEasiTDC = 16;
    const Int_t nTOF1 = 24;
    const Int_t nTOF2 = 48;
    const Int_t nGaps = 12;
    const double TOF1_Z_cut = 15;

    const int MWPC_cluster_separation = 1;


    const double max_dist = 4.5;  // 4.
    const double dist_to_kaon_fit = 4.;

    //Lepton hits ADC (digital) signals
    Int_t Xhit[nBars];
    Int_t Yhit[nBars];
    Int_t Thit[nBars];
    Int_t Ehit[nBars];
    Int_t hit_bars[nBars];

    int Lid[nBars];
    //Low Gain hits
    double XLGhit[nBars];
    double YLGhit[nBars];
    double TLGhit[nBars];
    double ELGhit[nBars];
    int LGid[nBars];
    //Kaon hits
    double EKhit[nBars];
    double XKhit[nBars];
    double YKhit[nBars];
    double TKhit[nBars];

    const int FirstBar[18] = {0, 6, 16, 28, 42, 58, 74, 92, 110, 128, 146, 164, 182, 198, 214, 228, 240, 250};
    const int LastBar[18] = {5, 15, 27, 41, 57, 73, 91, 109, 127, 145, 163, 181, 197, 213, 227, 239, 249, 255};
    const int nBarsPerRow[18] = {6, 10, 12, 14, 16, 16, 18, 18, 18, 18, 18, 18, 16, 16, 14, 12, 10, 6};


    // Bad bars info
    Int_t NoBar[nBars];
    Int_t nNoBars = 0;
    // thresholds etc.
    Double_t HGpedT[nBars];
    Double_t LGpedT[nBars];
    Double_t HGpedF[nFibers];
    Double_t LGpedF[nFibers];
    Double_t TpedL, TpedH;
    Double_t TcutLT[nBars], TcutHT[nBars];
    Double_t TcutLF[nFibers], TcutHF[nFibers];
    // Event number
    Int_t nEvent;
    Int_t nhits = 0;  // count number of high gain above pedestal hits found
    Int_t nLGhits = 0; // count of number of low gain above pedestal hits found

    Int_t nKhits = 0;  // count number of Kaon hits found
    Int_t nhitsorig = 0; //number of high gain pedestal hits before drop "bad" hits
    Int_t nhitsL = 0; // count of number of low gain pedestal hits found
    Int_t nhits_t = 0; // count of number of "real" high gain hits found for tdc
    Int_t nhitsF = 0;  // count number fibre high gain pedestal hits found
    Int_t nhitsLF = 0; // count fibre number of low gain pedestal hits found
    Int_t nhits_Ft = 0; // count fibre number of "real" high gain hits found for tdc
    Int_t nLhits; // count of number of largest hits

    int iDepth[16], nDepth;

    int Kid[nBars];
    double XEmax[4], YEmax[4];
    int EKid[nBars];
    int iE1, iE2, iE3, iE4, imaxT;
    int TarTlast;
    int TarThit;
    // tdc's
    int TargTDC_LEcutL = 820;
    int TargTDC_LEcutH = 860;
    int TargTDC_LEkcutL = 820;
    int TargTDC_LEkcutH = 1050;

    //Bar positions
    const double Offset_TOF1[12] = {180., 410., 0., 0., 310., 280., -30., 70., 0., 0., 390., 430.};
    const double Slope_correction_TOF1[12] = {0.70, 0.78, 1., 1., 0.70, 0.60, 0.86, 0.77, 1., 1., 0.67, 0.78};

    // Phillipe's parameters found in offline_new/alex/simulation/G4DataRootApr19.h
            // and TweakParameters.h
    const double TWO_TRACK_MIN_CHISQ = 1;
    const double TWO_TRACK_MIN_LEPTON_BARS = 5;

    const double FIT_TOF1_WEIGHT = 3;

    const double K_STOP_CENTROID_THRESH = 0.0; // mm

    const bool PATH_TRAVERSIAL_USE_ALL = true; // use FindShortestPath() instead of dijkstra()
    const double PATH_TRAVERSIAL_DIJKSTRA_JUMP_RADIUS = 9; // mm
    const double PATH_TRAVERSIAL_ALL_PENALTY = 1000;

    Int_t           n;
    Int_t           s_hit;
    Int_t           x_hit;
    Double_t        tof1charge[5];
    Int_t           tof1N[5];
    Double_t        px[10];
    Double_t        py[10];
    Double_t        pz[10];
    Double_t        u_x;
    Double_t        u_y;
    Double_t        u_z;
    Double_t        uto_x; // ⎫
    Double_t        uto_y; // ⎬ momentum unit vector of lepton at exit of detector
    Double_t        uto_z; // ⎭

    Double_t        delta_x;
    Double_t        delta_y;
    Double_t        delta_z;
    Double_t        delta_stop_x;
    Double_t        delta_stop_y;
    Double_t        delta_stop_z;
    Double_t        delta_ux;
    Double_t        delta_uy;
    Double_t        delta_uz;
    Double_t        delta_energy;
    Double_t        delta_length;
    Double_t        delta_length_xy;
    Double_t        delta_time;

    Double_t        genEvt;
    Double_t        genEne[10];
    Double_t        cosTh;
    Double_t        sinTh;
    Double_t        Phi;
    Double_t        dv_x;
    Double_t        dv_y;
    Double_t        dv_z;
    Double_t        targetE[5];
    Double_t        targetdE[256];
    Double_t        targetdt[256];
    Double_t        targL;
    Double_t        t1pL;
    Double_t        tof1E[5];
    Double_t        tof1wpos[5][3];
    Double_t        tof1dt;
    Char_t          secondP[5][100];
    Double_t        t1;
    Double_t        t1px;
    Double_t        t1py;
    Double_t        t1pz;
    Double_t        SFTwpos1[5][3];
    Double_t        SFTwpos2[5][3];
    Double_t        SFTpx;
    Double_t        SFTpy;
    Double_t        SFTpz;

    //Define cut parameters
    Double_t minADC = 0.0;
    Double_t Tstep = 0.2;
    double minADCValidHit = 0.0;
    // modified Nov 8 MH  2.0 --> 1.0 MeV
    double Min_E_k = 1; double Min_T_k = 3;
    // modified Oct 23 MH  2.5 --> 1.0
    double two_tracks_min_Chi_sq = 1.0;

};