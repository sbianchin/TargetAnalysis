#ifndef __CINT__
#include "DisplayEvent.h"
#include <math.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "TROOT.h"
#include "TSystem.h"
#include "TF1.h"
#include "TFile.h"
#include "TProfile.h"
#include "TChain.h"
#include "TH1D.h"

#include "TH2F.h"
#include "TEllipse.h"

#include "TRandom.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TPolyLine.h"
#include "TLine.h"
#include "TArrow.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TBranch.h"
#include "C2_Strip_transform.h"
#include "Channel_to_Strip.h"
#include "SFTfunctions.hpp"
#include "plotEvent.hpp"
#include "analyzeEventFunctions.hpp"
#include "DetectorGeometry.hpp"
#include "CutsAndWindows.hpp"
#include "Target.hpp"
#include "TargetBar.hpp"
#include "determineTOF1Gap.hpp"
#include "intersect.hpp"
#include "findGoodTargetEvents.hpp"
#include "findGoodTOFEvents.hpp"
#include "findGoodMWPCEvents.hpp"
#include "findMWPCClusters.hpp"
#include "calculateThreshold.hpp"
#include "findKaons.hpp"
#include "findLeptons.hpp"
#include "printFunctions.hpp"
#include "findKaonTDCAverage.hpp"
#include "findKaonCentroid.hpp"
#include "findKaonStop.hpp"
#include "pruningFunctions.hpp"
#include "helperFunctions.hpp"
#include "leptonFitHelperFunctions.hpp"
#include "boost_geometry.hpp"
#include "selectPrimaryTrackBars.hpp"
#include "selectSecondaryTrackBars.hpp"
#include "selectSecondaryTrackBars2.hpp"
#include "drawTwoPaths.hpp"
#include "DEBUG.hpp"
#include "KEKCCFile.hpp"
#include "SimulationData.hpp"
//#include "fitTrack.hpp"

#endif

namespace DG = DetectorGeometry;
namespace CW = CutsAndWindows;
namespace CP = CommonParameters;
namespace KEKCC = KEKCCFile;



using std::cout; using std::endl;
using std::setprecision;
using std::vector;
using namespace DEBUG;


void DisplayEvent(int run_number, int event_number, PruningType type,
                  bool batch_mode, int enable_cout,
                  bool display, bool print_to_console, bool print_to_file, bool kekcc_file){



    DetectorData *data = new DetectorData(run_number, event_number);

    DisplayEvent(data, type, batch_mode, enable_cout, display, print_to_console, print_to_file, kekcc_file);
}

// TODO: What does enable_cout do??
void DisplayEvent(DetectorData *data,
                  PruningType type, bool batch_mode, int enable_cout,
                  bool display, bool print_to_console, bool print_to_file, bool kekcc_file){


    // SimulationData *sim = new SimulationData(822, data->EvNum);

    // vector<int> MC_Leptons;
    // vector<int> MC_Kaons;

    // double MC_Time_max = -1.;
    // double MC_Time_min = 10000.;
    // double MC_Time_mid = 1000.;

    // for(int i=0; i<256; i++){
    //     if(sim->targetdt[i] > 0){
    //         if(sim->targetdt[i] > MC_Time_max) MC_Time_max = sim->targetdt[i];
    //         if(sim->targetdt[i] < MC_Time_min) MC_Time_min = sim->targetdt[i];
    //     }
    // }

    // MC_Time_mid = 0.5*(MC_Time_max - MC_Time_min);

    // cout << endl;
    // cerr << "MAX : " << MC_Time_max << endl;
    // cerr << "MIN : " << MC_Time_min << endl;
    // cerr << "MID : " << MC_Time_mid << endl;
    // cout << endl;


    // for(int i=0; i<256; i++){
    //     if(sim->targetdt[i] > 0 && sim->targetdt[i] < MC_Time_mid){
    //         MC_Kaons.push_back(i);
    //     }
    //     else if(sim->targetdt[i] >= MC_Time_mid && sim->targetdt[i] < MC_Time_max){
    //         MC_Leptons.push_back(i);
    //     }
    // }

    // cout << "KAONS : " << endl;
    // for(unsigned int i=0; i<MC_Kaons.size(); i++){
    //     cout << MC_Kaons[i] << "  "  << sim->targetdt[MC_Kaons[i]] << endl;
    // }

    // cout << endl;
    // cout << "LEPTONS : " << endl;
    // for(unsigned int i=0; i<MC_Leptons.size(); i++){
    //     cout << MC_Leptons[i] << "  " << sim->targetdt[MC_Leptons[i]] << endl;
    // }


    /// TO BE DONE
    // PRINT KSTOP X and Y 

    //cout << "KSTOP : " << endl;
    // X = 
    // Y = 

    /// TO BE DONE 
    // PRINT TOF1 X and Y 

    // TRACK 0:
    // X = 
    // Y = 

    // TRACK 1: 
    // X = 
    // Y = 




    gROOT->SetBatch(batch_mode);
    gROOT->Clear();
    gStyle->Clear();
    TH1::AddDirectory(kFALSE);
    gStyle->SetOptStat(11);

    data->correctTimeWalk();
    data->adjustThreshold();

    Target *target = new Target(*data);

    char sft_map[200];
    char mwpc_map[200];

    int par_temp[2][128];
    char par_temp2[512][50];

    bool has_edge_bars = false;

    int ADC_High_corr_max = 0;

    double TDC_diff = -1;
    double tdc_ck_corr = 0.;

    char rootInput_file[100];
    const char* env_merged = getenv("path_merged");
    sprintf(rootInput_file,"%s/Run%dMS.root",env_merged, data->RunNum);

    char Time_walk_file[100];
    char Time_walk_file_printout[100];
    bool NoFile = false;
    sprintf(Time_walk_file,"TimeWalk%d.dat", data->RunNum);
    if(ifstream(Time_walk_file)){
        sprintf(Time_walk_file_printout,"TimeWalk%d.dat", data->RunNum);
    }
    else{
        sprintf(Time_walk_file_printout,"EMPTY !");
        NoFile = true;
    }

    char sft_mapping_file[] = "SFT_Mapping_Oct14.txt";  // Mapping file !!!
    char mwpc_mapping_file[] = "MWPC_map2.txt";

    sprintf(sft_map, "%s/Mapping/%s", getenv("path_offline_new"), sft_mapping_file);
    sprintf(mwpc_map, "%s/Mapping/%s", getenv("path_offline_new"), mwpc_mapping_file);

    ifstream fdat(sft_map, ios::in);
    for (int ii = 0; ii < 128; ii++) fdat >> par_temp[0][ii] >> par_temp[1][ii];
    fdat.close();

    ifstream fdat2(mwpc_map, ios::in);
    for (int ii = 0; ii < 512; ii++) fdat2 >> par_temp2[ii];
    fdat2.close();

    vector<double> vec_Ck;
    vector<double> vec_Cpi;

    int TDC_ck_sum = 0;
    double TDC_ck_avg = 0.;
    double TDC_ck_sigma = 0.;
    int TDC_cpi_sum = 0;
    double TDC_cpi_avg = 0.;
    double TDC_cpi_sigma = 0.;

    double TDC_ck_sigma2 = 0.;
    double TDC_cpi_sigma2 = 0.;

    int TDC_ck_sum2 = 0;
    double TDC_ck_avg2 = 0.;
    int TDC_ck_counter = 0;
    int TDC_cpi_sum2 = 0;
    double TDC_cpi_avg2 = 0.;
    int TDC_cpi_counter = 0;  

    // TODO: Move to BatchAnalysis so file write only happens once.
    ofstream fout_csv;
    char batch_output_csv[50];

    if(batch_mode && print_to_file){
        if(print_to_file){
            sprintf(batch_output_csv, "Run_%d_Batch_output.csv", data->RunNum);
            fout_csv.open(batch_output_csv, ios::app);
        }
    }

    // ******** Find good events in TARGET, TOF, and MWPC

    bool is_good_event = false;
    //********* GOOD TARGET EVENTS
    bool is_good_TARGET_event = findGoodTargetEvents(*data);
    if (enable_cout == 9) is_good_TARGET_event = true;

    //********* GOOD TOF EVENTS
    bool is_good_TOF_event = findGoodTOFEvents(*data);
    if (enable_cout == 9) is_good_TOF_event = true;

    //********* GOOD MWPC EVENTS
    bool is_good_MWPC_event = findGoodMWPCEvents(*data);
    if (enable_cout == 9) is_good_MWPC_event = true;

    bool is_event_on_blacklist = false;

    // TODO: Figure out how the blacklist works
    if (is_good_TARGET_event && is_good_TOF_event
        && is_good_MWPC_event && !is_event_on_blacklist) {
        is_good_event = true;
    }


    if(print_to_console && !batch_mode) {
        printEventSummary(*data, Time_walk_file_printout, sft_map, mwpc_map, is_good_event,
                          is_good_TARGET_event, is_good_TOF_event, is_good_MWPC_event, is_event_on_blacklist);
    }

    if (!is_good_event) {
        if (print_to_file) {
            fout_csv << ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,," << endl;
        }
        if (!batch_mode) {
            delete data;
            data = nullptr;
        }
        return;
    }


    double ADC_High_SFT_corr[128];
    for (int j = 0; j < 128; j++) {
        if (data->ADC_High_SFT[j] < 0) {
            ADC_High_SFT_corr[j] = 0;
        } else {
            ADC_High_SFT_corr[j] = data->ADC_High_SFT[j];
        }
    }

    ////////////////////  GEOMETRY !!!  ////////////////////////////////////////////

    //////// DETERMINE FIBER WITH HIGHEST AND SECOND HIGHEST LOW GAIN AMPLITUDE
    int max_index_all[256] = {-1};
    int max_ADC_all[256] = {-100000000};
    int max_index_flag = 0;

    for (int j = 0; j < 256; j++) {
        for (int i = 0; i < 256; i++) {
            max_index_flag = 0;

            for (int k = 0; k < 256; k++) {
                if (i == max_index_all[k]) {
                    max_index_flag = 1;
                    break;
                }
            }
            if (max_index_flag == 1) continue;

            else {
                if (data->ADC_Low_TARGET[i] > max_ADC_all[j]) {
                    max_index_all[j] = i;
                    max_ADC_all[j] = data->ADC_Low_TARGET[i];
                }
            }
        }
    }


    //Calculate TDC Average
    int TDC_average = -1;
    int kaon_substitute = -1;
    bool has_kaon_sub = false;
    vector<int> vec_TDCAverage;

    vec_TDCAverage = findKaonTDCAverage(*data, false);

    TDC_average = vec_TDCAverage[0];
    kaon_substitute = vec_TDCAverage[1];
    if(kaon_substitute > -1) has_kaon_sub = true;

    int kaon_TDC_min;
    int kaon_TDC_max;
    int TDC_min_Kstop;
    int TDC_max_Kstop;

    if(TDC_average > 0){
        kaon_TDC_min = TDC_average + CW::TDC_Avg_Offset_min;
        kaon_TDC_max = TDC_average + CW::TDC_Avg_Offset_max;
        TDC_min_Kstop = TDC_average + CW::TDC_Kstop_Avg_Offset_min;
        TDC_max_Kstop = TDC_average + CW::TDC_Kstop_Avg_Offset_max;
    }
    else{
        kaon_TDC_min = CW::TDC_Thr_min;
        kaon_TDC_max = CW::TDC_Thr_max;
        TDC_min_Kstop = CW::TDC_Thr_min;
        TDC_max_Kstop = CW::TDC_Thr_max;
    }

    int TDC_min_TARGET = kaon_TDC_min;

    bool has_TDC_hit[256] ={false};
    bool has_TDC_hit_Kstop[256] = {false};


    for (Int_t i = 0; i < 256; i++) {
        for (Int_t k = 0; k < 6; k++) {
            if ((data->TDC_LE_TARGET[i][k] >= TDC_min_Kstop) && (data->TDC_LE_TARGET[i][k] <= TDC_max_Kstop))
                has_TDC_hit_Kstop[i] = true;
            if ((data->TDC_LE_TARGET[i][k] >= kaon_TDC_min) && (data->TDC_LE_TARGET[i][k] <= kaon_TDC_max))
                has_TDC_hit[i] = true;
        }
    }

    for (Int_t ii = 0; ii < 128; ii++) {
        if (ADC_High_SFT_corr[ii] > ADC_High_corr_max) ADC_High_corr_max = ADC_High_SFT_corr[ii];
    }

    int has_TDC_SFT_hit[128] = {0};

    for (Int_t ii = 0; ii < 128; ii++) {
        for (Int_t qq = 0; qq < 6; qq++) {
            if (data->TDC_LE_SFT[ii][qq] > CW::SFT_TDC_min[ii] && data->TDC_LE_SFT[ii][qq] < CW::SFT_TDC_max[ii])
                has_TDC_SFT_hit[ii]++;
        }
    }

    int count = 0;

    int max_index = 0;
    int max_index2 = 0;
    int max_index3 = 0;
    int max_index4 = 0;

    int max_ADC = -100000000;
    int max_ADC2 = -100000000;
    int max_ADC3 = -100000000;
    int max_ADC4 = -100000000;

    for (Int_t q = 0; q < 256; q++) {
        if (data->ADC_High_TARGET[q] > max_ADC) {
            max_index = q;
            max_ADC = data->ADC_High_TARGET[q];
        }
    }

    for (Int_t q = 0; q < 256; q++) {
        if (q == max_index) continue;
        else {
            if (data->ADC_High_TARGET[q] > max_ADC2) {
                max_index2 = q;
                max_ADC2 = data->ADC_High_TARGET[q];
            }
        }
    }

    for (Int_t q = 0; q < 256; q++) {
        if ((q == max_index) || (q == max_index2)) continue;
        else {
            if (data->ADC_High_TARGET[q] > max_ADC3) {
                max_index3 = q;
                max_ADC3 = data->ADC_High_TARGET[q];
            }
        }
    }

    for (Int_t q = 0; q < 256; q++) {
        if ((q == max_index) || (q == max_index2) || (q == max_index3)) continue;
        else {
            if (data->ADC_High_TARGET[q] > max_ADC4) {
                max_index4 = q;
                max_ADC4 = data->ADC_High_TARGET[q];
            }
        }
    }

    double x_cent = DG::Xloc[max_index];
    double y_cent = DG::Yloc[max_index];
    double hyp[256] = {-1};

    for (int i = 0; i < 256; i++) hyp[i] = -1;

    for (Int_t j = 0; j < 256; j++) {
        hyp[j] = sqrt(pow(x_cent - DG::Xloc[j], 2) + pow(y_cent - DG::Yloc[j], 2));
    }

    bool has_ADC_TOF1_hit[12] = {false};
    bool has_TDC_TOF1_hit[12] = {false};
    bool has_ADC_TOF2_hit[12] = {false};
    bool has_TDC_TOF2_hit[12] = {false};
    bool has_both_ADC_TOF1_hit[12] = {false};
    bool has_both_TDC_TOF1_hit[12] = {false};

    ///Set TOF2 Lines
    for (int i = 0; i < 12; i++) {
        if ((data->ADC_TOF2AO[i] > 0 && data->ADC_TOF2AI[i] > 0) ||
            (data->ADC_TOF2BO[i] > 0 && data->ADC_TOF2BI[i] > 0)) { has_ADC_TOF2_hit[i] = true; }
        if ((((data->TDC_TOF2AO[i] > CW::TOF2AO_TDC_min[i] && data->TDC_TOF2AO[i] < CW::TOF2AO_TDC_max[i]) &&
              (data->TDC_TOF2AI[i] > CW::TOF2AI_TDC_min[i] && data->TDC_TOF2AI[i] < CW::TOF2AI_TDC_max[i])))
            || (((data->TDC_TOF2BO[i] > CW::TOF2BO_TDC_min[i] && data->TDC_TOF2BO[i] < CW::TOF2BO_TDC_max[i]) &&
                 (data->TDC_TOF2BI[i] > CW::TOF2BI_TDC_min[i] &&
                  data->TDC_TOF2BI[i] < CW::TOF2BI_TDC_max[i])))) { has_TDC_TOF2_hit[i] = true; }
    }

    ///Set TOF1 Lines
    for (int i = 0; i < 12; i++) {
        if (data->ADC_TOF1U[i] > 0 && data->ADC_TOF1D[i] > 0) { has_both_ADC_TOF1_hit[i] = true; }
        if (data->ADC_TOF1U[i] > 0 || data->ADC_TOF1D[i] > 0) { has_ADC_TOF1_hit[i] = true; }
        if ((data->TDC_TOF1U[i] > CW::TOF1U_TDC_min[i] && data->TDC_TOF1U[i] < CW::TOF1U_TDC_max[i]) &&
            (data->TDC_TOF1D[i] > CW::TOF1D_TDC_min[i] &&
             data->TDC_TOF1D[i] < CW::TOF1D_TDC_max[i])) { has_both_TDC_TOF1_hit[i] = true; }
        if ((data->TDC_TOF1U[i] > CW::TOF1U_TDC_min[i] && data->TDC_TOF1U[i] < CW::TOF1U_TDC_max[i]) ||
            (data->TDC_TOF1D[i] > CW::TOF1D_TDC_min[i] &&
             data->TDC_TOF1D[i] < CW::TOF1D_TDC_max[i])) { has_TDC_TOF1_hit[i] = true; }
    }

    int ADC_TOF1_hit[12] = {0};
    int ADCTDC_TOF1_hit[12] = {0};
    int ADC_TOF2_hit[12] = {0};
    int ADCTDC_TOF2_hit[12] = {0};

    for (int k = 0; k < 12; k++) {
        if (has_ADC_TOF1_hit[k]) {
            if (has_TDC_TOF1_hit[k]) ADCTDC_TOF1_hit[k]++;
            else ADC_TOF1_hit[k]++;
        }
        if (has_ADC_TOF2_hit[k]) {
            if (has_TDC_TOF2_hit[k]) ADCTDC_TOF2_hit[k]++;
            else ADC_TOF2_hit[k]++;
        }
    }

    int selected_TOF2 = 0;

    // Determine which TOF2 is hit
    for (int i = 0; i < 12; i++) {
        if (has_TDC_TOF2_hit[i] && has_ADC_TOF2_hit[i]) selected_TOF2 = i + 1;
    }

    if (selected_TOF2 == 0) {
        for (int i = 0; i < 12; i++) {
            if (has_TDC_TOF2_hit[i] || has_ADC_TOF2_hit[i]) selected_TOF2 = i + 1;
        }
    }

    vector<int> GAP_TO_FIT = determineTOF1Gap(*data, selected_TOF2, false);

    int gap_to_fit = GAP_TO_FIT[0];
    vector<int> extra_TOF1;
    for(unsigned int i=1; i<GAP_TO_FIT.size(); i++){
        extra_TOF1.push_back(GAP_TO_FIT[i]);
    }

    //for(unsigned int i=0; i<)

    vector<int> vec_TARGET_bar_selected;

    for (int i = 0; i < 256; i++) {
        if(data->ADC_High_TARGET[i] > 0 || data->ADC_Low_TARGET[i] > 0) vec_TARGET_bar_selected.push_back(i);
    }

    /// PRUNING
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DETERMINE KAON BARS //////////////////////////////////////////////////////////////////////////////

    vector<int> vec_lepton_bars_initial;
    vec_lepton_bars_initial.clear();
    vector<int> vec_lepton_bars_rotated_initial;
    vec_lepton_bars_rotated_initial.clear();

    // NEW
    vector<int> kaon_bars = findKaons(*data, has_TDC_hit_Kstop, has_kaon_sub, kaon_substitute);

    bool is_kaon[256] = {false};
    for(unsigned int i=0; i<kaon_bars.size(); i++){
        is_kaon[kaon_bars[i]] = true;
    }


    /// Fill Kaon Graph
    vector<double> vec_x_kaons;     vec_x_kaons.clear();
    vector<double> vec_y_kaons;     vec_y_kaons.clear();
    vector<double> vec_ex_kaons;    vec_ex_kaons.clear();
    vector<double> vec_ey_kaons;    vec_ey_kaons.clear();

    vector<double> vec_x_kaons_rot;     vec_x_kaons_rot.clear();
    vector<double> vec_y_kaons_rot;     vec_y_kaons_rot.clear();
    vector<double> vec_ex_kaons_rot;    vec_ex_kaons_rot.clear();
    vector<double> vec_ey_kaons_rot;    vec_ey_kaons_rot.clear();

    for(unsigned int i=0; i<kaon_bars.size(); i++){
        vec_x_kaons.push_back(DG::Xloc[kaon_bars[i]]);
        vec_y_kaons.push_back(DG::Yloc[kaon_bars[i]]);
        vec_ex_kaons.push_back(DG::TARGET_Errors_X);
        vec_ey_kaons.push_back(DG::TARGET_Errors_Y);
    }

    TGraph *gra_kaon_0;
    TGraph *gr_kaons_unfitted;
    TGraph *gr_kaons_final;

    gra_kaon_0 = new TGraphErrors(kaon_bars.size(), &vec_x_kaons[0], &vec_y_kaons[0],
                                  &vec_ex_kaons[0], &vec_ey_kaons[0]);

    gr_kaons_unfitted = new TGraphErrors(kaon_bars.size(), &vec_x_kaons[0], &vec_y_kaons[0],
                                         &vec_ex_kaons[0], &vec_ey_kaons[0]);

    gra_kaon_0->SetMarkerColor(4);
    gra_kaon_0->SetMarkerStyle(21);
    gra_kaon_0->SetMarkerSize(0.8);
    gra_kaon_0->GetYaxis()->SetTitle("Y title");
    gra_kaon_0->GetXaxis()->SetLimits(-50.,50.);
    gra_kaon_0->GetYaxis()->SetRangeUser(-50.,50.);

    gr_kaons_unfitted->SetMarkerColor(4);
    gr_kaons_unfitted->SetMarkerStyle(21);
    gr_kaons_unfitted->SetMarkerSize(0.8);
    gr_kaons_unfitted->GetYaxis()->SetTitle("Y title");
    gr_kaons_unfitted->GetXaxis()->SetLimits(-50.,50.);
    gr_kaons_unfitted->GetYaxis()->SetRangeUser(-50.,50.);

    double a_fit_kaon_0 = 999.99;
    double b_fit_kaon_0 = 999.99;
    double ChiS_kaon_0 = 999.99;
    int ndf_kaon_0 = 999;

    double a_fit_kaon_final = 999.99;
    double b_fit_kaon_final = 999.99;
    double ChiS_kaon_final = 999.99;
    int ndf_kaon_final = 999;

    bool to_rotate_kaons = false;

    TF1 *func_kaon_fit_0;
    func_kaon_fit_0 = new TF1("gr_kaon_0", "pol1");

    if(kaon_bars.size()>=CP::kaon_cluster_size){
        //gra_kaon_0->Fit("gr_kaon_0","QW");  // <--- OPTION "W" TO BE REMOVED IF TOO MANY ERROR MESSAGES !
        gra_kaon_0->Fit("gr_kaon_0","Q");

        func_kaon_fit_0 = gra_kaon_0->GetFunction("gr_kaon_0");
        func_kaon_fit_0->SetLineWidth(2);
        func_kaon_fit_0->SetLineColor(4);

        a_fit_kaon_0 = func_kaon_fit_0->GetParameter(1);
        b_fit_kaon_0 = func_kaon_fit_0->GetParameter(0);
        ChiS_kaon_0 = func_kaon_fit_0->GetChisquare();
        ndf_kaon_0 = func_kaon_fit_0->GetNDF();

        if(abs(a_fit_kaon_0) > 10) to_rotate_kaons = true;
    }

    TGraph *gr_kaons_rot;
    TLine *line_fit_kaons;

    if(!to_rotate_kaons){
        gr_kaons_final = gra_kaon_0;
        line_fit_kaons = new TLine(99., 99., 99., 99.);

        a_fit_kaon_final = a_fit_kaon_0;
        b_fit_kaon_final = b_fit_kaon_0;
        ChiS_kaon_final = ChiS_kaon_0;
        ndf_kaon_final = ndf_kaon_0;
    }
    else {
        for(unsigned int j=0; j<kaon_bars.size(); j++){
            vec_x_kaons_rot.push_back(DG::Xloc[DG::TARGET_Rotated_index[kaon_bars[j]]]);
            vec_y_kaons_rot.push_back(DG::Yloc[DG::TARGET_Rotated_index[kaon_bars[j]]]);
            vec_ex_kaons_rot.push_back(DG::TARGET_Errors_X);
            vec_ey_kaons_rot.push_back(DG::TARGET_Errors_Y);
        }

        gr_kaons_rot = new TGraphErrors(kaon_bars.size(), &vec_x_kaons_rot[0], &vec_y_kaons_rot[0],
                                        &vec_ex_kaons_rot[0], &vec_ey_kaons_rot[0]);

        TF1 *func_kaon_fit_rot;
        func_kaon_fit_rot = new TF1("gr_kaon_rot", "pol1");

        gr_kaons_rot->Fit("gr_kaon_rot","QW");  // <--- OPTION "W" TO BE REMOVED IF TOO MANY ERROR MESSAGES !
        gr_kaons_rot->Fit("gr_kaon_rot","Q");

        func_kaon_fit_rot = gr_kaons_rot->GetFunction("gr_kaon_rot");
        func_kaon_fit_rot->SetLineWidth(2);
        func_kaon_fit_rot->SetLineColor(4);

        a_fit_kaon_0 = func_kaon_fit_rot->GetParameter(1);
        b_fit_kaon_0 = func_kaon_fit_rot->GetParameter(0);
        ChiS_kaon_0 = func_kaon_fit_rot->GetChisquare();
        ndf_kaon_0 = func_kaon_fit_rot->GetNDF();
 
        // if(abs(a_fit2) > 100){

        // }

        //cerr << "a_fit2 : " << a_fit2 << endl; 

        // if(abs(a_fit2) > 100){
        //     gr_leptons_fit2->Fit("Leptons_fit2","QW");
        //     gr_leptons_fit2->Fit("Leptons_fit2","Q");

        //     TF1 *f_leptons_fit2 = gr_leptons_fit2->GetFunction("Leptons_fit2");
        //     a_fit2 = f_leptons_fit2->GetParameter(1);
        //     b_fit2 = f_leptons_fit2->GetParameter(0);
        //     Chis_fit2 = f_leptons_fit2->GetChisquare();
        //     ndf_fit2 = f_leptons_fit2->GetNDF();
        //     f_leptons_fit2->SetLineWidth(2);
        //     f_leptons_fit2->SetLineColor(2);









        TH2F *h_test = new TH2F("test", "test", 500, -50, 50, 500, -50, 50);
        TEllipse *ell_Target = new TEllipse(0, 0, CP::R_TARGET, 0);
        h_test->Draw();
        ell_Target->Draw("same");
        gr_kaons_rot->Draw("sameP");



        //cout << "a_fit_kaon_0 : " << a_fit_kaon_0 << endl;

        a_fit_kaon_final = -1/a_fit_kaon_0;
        b_fit_kaon_final = b_fit_kaon_0/a_fit_kaon_0;
        ChiS_kaon_final = ChiS_kaon_0 ;
        ndf_kaon_final = ndf_kaon_0;

        line_fit_kaons = new TLine(50.*a_fit_kaon_0 + b_fit_kaon_0, -50.,
                                   -50.*a_fit_kaon_0 + b_fit_kaon_0, 50.);

        gr_kaons_final = gr_kaons_unfitted;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DETERMINE LEPTON BARS ////////////////////////////////////////////////////////////////////////////

    vector<int> lepton_bars = findLeptons(*data, is_kaon, has_TDC_hit, kaon_substitute);
    vector<TargetBar> leptons;

    /// Fill Lepton Graph  
    vector<int> V_lepton_0;         V_lepton_0.clear();
    vector<double> V_x_lepton_0;    V_x_lepton_0.clear();
    vector<double> V_y_lepton_0;    V_y_lepton_0.clear();
    vector<double> V_ex_lepton_0;   V_ex_lepton_0.clear();
    vector<double> V_ey_lepton_0;   V_ey_lepton_0.clear();

    for(unsigned int i=0; i<lepton_bars.size(); i++){
        leptons.push_back(target->getBar(lepton_bars[i]));
        V_lepton_0.push_back(lepton_bars[i]);
        V_x_lepton_0.push_back(DG::Xloc[lepton_bars[i]]);
        V_ex_lepton_0.push_back(DG::TARGET_Errors_X);
        V_y_lepton_0.push_back(DG::Yloc[lepton_bars[i]]);
        V_ey_lepton_0.push_back(DG::TARGET_Errors_Y);
    }

    // Add Edge Bars
    for(unsigned int j=0; j<lepton_bars.size(); j++){
        if(IsIn(lepton_bars[j],DG::channel[gap_to_fit-1][0], DG::channel[gap_to_fit-1][1],   // Additional weight for fibers close to the edge if hit
                DG::channel[gap_to_fit-1][2], DG::channel[gap_to_fit-1][3],
                DG::channel[gap_to_fit-1][4], DG::channel[gap_to_fit-1][5],
                DG::channel[gap_to_fit-1][6], DG::channel[gap_to_fit-1][7],
                DG::channel[gap_to_fit-1][8], DG::channel[gap_to_fit-1][9],
                DG::channel[gap_to_fit-1][10], DG::channel[gap_to_fit-1][11])){

            has_edge_bars = true;

            for(int iw=0; iw<CP::weight_edge_bars_fit1; iw++){
                V_lepton_0.push_back(lepton_bars[j]);

                V_x_lepton_0.push_back(DG::Xloc[lepton_bars[j]]);
                V_ex_lepton_0.push_back(DG::TARGET_Errors_X);

                V_y_lepton_0.push_back(DG::Yloc[lepton_bars[j]]);
                V_ey_lepton_0.push_back(DG::TARGET_Errors_Y);
            }
        }
    }

    // Add TOF! with weight
    for(int k=0; k<CP::weight_TOF1_fit1; k++){
        V_x_lepton_0.push_back(DG::TOF1_Xloc[gap_to_fit-1][2]);
        V_ex_lepton_0.push_back(DG::TOF1_Errors_X[gap_to_fit-1][2]);

        V_y_lepton_0.push_back(DG::TOF1_Yloc[gap_to_fit-1][2]);
        V_ey_lepton_0.push_back(DG::TOF1_Errors_Y[gap_to_fit-1][2]);
    }

    TGraph *graph_lepton_0;
    TF1 *func_lepton_fit_0;

    TGraph *N_graph_lepton_0;
    TF1 *N_func_lepton_fit_0;

    graph_lepton_0 = new TGraphErrors(V_x_lepton_0.size(),&V_x_lepton_0[0],&V_y_lepton_0[0],
                                      &V_ex_lepton_0[0],&V_ey_lepton_0[0]);

    double a_fit_lepton_0 = 999.;
    double b_fit_lepton_0 = 999.;
    double ChiS_lepton_0 = 999.;
    double ndf_lepton_0 = 999.;

    func_lepton_fit_0 = new TF1("gr_lepton_0", "pol1");

    graph_lepton_0->SetMarkerColor(2);
    graph_lepton_0->SetMarkerStyle(21);
    graph_lepton_0->SetMarkerSize(0.8);
    graph_lepton_0->GetYaxis()->SetTitle("Y title");
    graph_lepton_0->GetXaxis()->SetLimits(-50.,50.);
    graph_lepton_0->GetYaxis()->SetRangeUser(-50.,50.);

    if(lepton_bars.size()>CP::lepton_cluster_size){
        //graph_lepton_0->Fit("gr_lepton_0","QW");  // <--- OPTION "W" TO BE REMOVED IF TOO MANY ERROR MESSAGES !
        graph_lepton_0->Fit("gr_lepton_0","Q");

        func_lepton_fit_0 = graph_lepton_0->GetFunction("gr_lepton_0");
        func_lepton_fit_0->SetLineWidth(2);
        func_lepton_fit_0->SetLineColor(2);

        a_fit_lepton_0 = func_lepton_fit_0->GetParameter(1);
        b_fit_lepton_0 = func_lepton_fit_0->GetParameter(0);
        ChiS_lepton_0 = func_lepton_fit_0->GetChisquare();
        ndf_lepton_0 = func_lepton_fit_0->GetNDF();
    }

    bool to_rotate_leptons = false;
    if(lepton_bars.size()>CP::lepton_cluster_size && abs(a_fit_lepton_0) > 10) to_rotate_leptons = true;

    vector<double> vec_x_leptons_rot;     vec_x_leptons_rot.clear();
    vector<double> vec_y_leptons_rot;     vec_y_leptons_rot.clear();
    vector<double> vec_ex_leptons_rot;    vec_ex_leptons_rot.clear();
    vector<double> vec_ey_leptons_rot;    vec_ey_leptons_rot.clear();

    TGraph *gr_leptons_unfitted;
    gr_leptons_unfitted = new TGraphErrors(V_x_lepton_0.size(), &V_x_lepton_0[0], &V_y_lepton_0[0],
                                           &V_ex_lepton_0[0], &V_ey_lepton_0[0]);

    double a_fit_lepton_final = 999.99;
    double b_fit_lepton_final = 999.99;
    double ChiS_lepton_final = 999.99;
    int ndf_lepton_final = 999;

    TGraph *gr_leptons_0_NEW = nullptr;
    TGraph *gr_leptons_rot;
    TLine *line_fit_leptons;
    int TOF1_gap = -1;

    if(!to_rotate_leptons){
        gr_leptons_0_NEW = graph_lepton_0;
        line_fit_leptons = new TLine(99., 99., 99., 99.);

        a_fit_lepton_final = a_fit_lepton_0;
        b_fit_lepton_final = b_fit_lepton_0;
        ChiS_lepton_final = ChiS_lepton_0;
        ndf_lepton_final = ndf_lepton_0;
    }
    else {

        TOF1_gap = DG::TOF1_rotated[gap_to_fit-1]+1;

        for(unsigned int i=0; i<lepton_bars.size(); i++){
            vec_x_leptons_rot.push_back(DG::Xloc[DG::TARGET_Rotated_index[lepton_bars[i]]]);
            vec_ex_leptons_rot.push_back(DG::TARGET_Errors_X);
            vec_y_leptons_rot.push_back(DG::Yloc[DG::TARGET_Rotated_index[lepton_bars[i]]]);
            vec_ey_leptons_rot.push_back(DG::TARGET_Errors_Y);
        }

        // Add Edge Bars
        for(unsigned int j=0; j<lepton_bars.size(); j++){
            // if(IsIn(lepton_bars[j],DG::channel[gap_to_fit-1][0], DG::channel[gap_to_fit-1][1],   // Additional weight for fibers close to the edge if hit
            //         DG::channel[gap_to_fit-1][2], DG::channel[gap_to_fit-1][3],
            //         DG::channel[gap_to_fit-1][4], DG::channel[gap_to_fit-1][5],
            //         DG::channel[gap_to_fit-1][6], DG::channel[gap_to_fit-1][7],
            //         DG::channel[gap_to_fit-1][8], DG::channel[gap_to_fit-1][9],
            //         DG::channel[gap_to_fit-1][10], DG::channel[gap_to_fit-1][11])){

            if(IsIn(lepton_bars[j],DG::channel[TOF1_gap-1][0], DG::channel[TOF1_gap-1][1],   // Additional weight for fibers close to the edge if hit
                    DG::channel[TOF1_gap-1][2], DG::channel[TOF1_gap-1][3],
                    DG::channel[TOF1_gap-1][4], DG::channel[TOF1_gap-1][5],
                    DG::channel[TOF1_gap-1][6], DG::channel[TOF1_gap-1][7],
                    DG::channel[TOF1_gap-1][8], DG::channel[TOF1_gap-1][9],
                    DG::channel[TOF1_gap-1][10], DG::channel[TOF1_gap-1][11])){


                has_edge_bars = true;

                for(int iw=0; iw<CP::weight_edge_bars_fit1; iw++){
                    vec_x_leptons_rot.push_back(DG::Xloc[DG::TARGET_Rotated_index[lepton_bars[j]]]);
                    vec_ex_leptons_rot.push_back(DG::TARGET_Errors_X);

                    vec_y_leptons_rot.push_back(DG::Yloc[DG::TARGET_Rotated_index[lepton_bars[j]]]);
                    vec_ey_leptons_rot.push_back(DG::TARGET_Errors_Y);
                }
            }
        }

        // Add TOF1 with weight
        for(int k=0; k<CP::weight_TOF1_fit1; k++){
            vec_x_leptons_rot.push_back(DG::TOF1_Xloc[TOF1_gap-1][2]);
            vec_ex_leptons_rot.push_back(DG::TOF1_Errors_X[TOF1_gap-1][2]);

            vec_y_leptons_rot.push_back(DG::TOF1_Yloc[TOF1_gap-1][2]);
            vec_ey_leptons_rot.push_back(DG::TOF1_Errors_Y[TOF1_gap-1][2]);
        }

        gr_leptons_rot = new TGraphErrors(vec_x_leptons_rot.size(), &vec_x_leptons_rot[0], &vec_y_leptons_rot[0],
                                          &vec_ex_leptons_rot[0], &vec_ey_leptons_rot[0]);

        TF1 *func_lepton_fit_rot;
        func_lepton_fit_rot = new TF1("gr_lepton_rot", "pol1");

        //gr_leptons_rot->Fit("gr_lepton_rot","QW");  // <--- OPTION "W" TO BE REMOVED IF TOO MANY ERROR MESSAGES !
        gr_leptons_rot->Fit("gr_lepton_rot","Q");


        func_lepton_fit_rot = gr_leptons_rot->GetFunction("gr_lepton_rot");
        func_lepton_fit_rot->SetLineWidth(2);
        func_lepton_fit_rot->SetLineColor(4);

        a_fit_lepton_0 = func_lepton_fit_rot->GetParameter(1);
        b_fit_lepton_0 = func_lepton_fit_rot->GetParameter(0);
        ChiS_lepton_0 = func_lepton_fit_rot->GetChisquare();
        ndf_lepton_0 = func_lepton_fit_rot->GetNDF();

        if(a_fit_lepton_0 != 0){
            a_fit_lepton_final = -1/a_fit_lepton_0;
            b_fit_lepton_final = b_fit_lepton_0/a_fit_lepton_0;
            ChiS_lepton_final = ChiS_lepton_0 ;
            ndf_lepton_final = ndf_lepton_0;
        }
        else{
            cout << "ERROR nan !" << endl;
            if (print_to_file) {
                fout_csv << ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,," << endl;
            }

            if (!batch_mode) {
                delete data;
                data = nullptr;
            }
            return;
        }


        line_fit_leptons = new TLine(50.*a_fit_lepton_0 + b_fit_lepton_0, -50.,
                                     -50.*a_fit_lepton_0 + b_fit_lepton_0, 50.);
        // line_fit_leptons = new TLine(-50., -50.*a_fit_lepton_final + b_fit_lepton_final, 
        //                               50., 50.*a_fit_lepton_final + b_fit_lepton_final);

        gr_leptons_0_NEW = gr_leptons_unfitted;
    }

    ////////////////////////////////////////////////////////////////////
    /// DETERMINE KAON CENTROID
    vector<double> V_centroid;
    V_centroid.clear();
    double N_centroid_X = 0.;
    double N_centroid_Y = 0.;

    V_centroid = findKaonCentroid(*data, kaon_bars);
    N_centroid_X = V_centroid[0];
    N_centroid_Y = V_centroid[1];

    /// Find Kaon Stop 0
    vector<double> vec_xx_kstop_0;
    vector<double> vec_yy_kstop_0;


    vector<double> vec_kstop_0 = findKaonStop_0(*data,kaon_bars, lepton_bars, V_centroid,
                                                 a_fit_kaon_final, b_fit_kaon_final, a_fit_lepton_final, b_fit_lepton_final);

    vec_xx_kstop_0.push_back(vec_kstop_0[0]);
    vec_yy_kstop_0.push_back(vec_kstop_0[1]);

    point_t kstop_0{vec_xx_kstop_0[0], vec_yy_kstop_0[0]};
    point_t tof1_0{DG::TOF1_Xloc[gap_to_fit][2], DG::TOF1_Yloc[gap_to_fit][2]};

    // TODO: Fit theses tracks and display in a plot
    auto result = selectPrimaryTrackBars(leptons, kstop_0, tof1_0);
    vector<TargetBar> track2a = selectSecondaryTrackBars(kstop_0, tof1_0, result);
    vector<TargetBar> track2b = selectSecondaryTrackBars2(kstop_0, tof1_0, result);

    vector<double> x;
    vector<double> y;
    vector<int> vec_pruned_backtracking;

    if(DEBUG_SELECT_TRACKS){
        cout << endl;
        cout << "////////////////////////////////////" << endl;
        cout << "DEBUG : SELECT TRACKS USING BACKTRACKING METHOD" << endl;
        cout << endl;
        cout << "Primary track: " << endl;
    }

    for (auto bar : result.primary_track_bars) {
        point_t bar_coord = bar.getCoord();
        vec_pruned_backtracking.push_back(bar.getBarNumber());
        x.push_back(bar_coord.x());
        y.push_back(bar_coord.y());
        if(DEBUG_SELECT_TRACKS) cerr << bg::dsv(bar_coord) << endl;
    }
    if(DEBUG_SELECT_TRACKS) cout << endl;

    vector<double> x2a;
    vector<double> y2a;
    if(DEBUG_SELECT_TRACKS) cout << "Secondary Track A: " << endl;
    for (auto bar : track2a) {
        point_t bar_coord = bar.getCoord();
        x2a.push_back(bar_coord.x());
        y2a.push_back(bar_coord.y());
        if(DEBUG_SELECT_TRACKS) cerr << bg::dsv(bar_coord) << endl;
    }
    if(DEBUG_SELECT_TRACKS) cout << endl;

    vector<double> x2b;
    vector<double> y2b;
    if(DEBUG_SELECT_TRACKS) cout << "Secondary Track B: " << endl;
    for (auto bar : track2b) {
        point_t bar_coord = bar.getCoord();
        x2b.push_back(bar_coord.x());
        y2b.push_back(bar_coord.y());
        if(DEBUG_SELECT_TRACKS) cerr << bg::dsv(bar_coord) << endl;
    }

    if(DEBUG_SELECT_TRACKS){
        cout << "////////////////////////////////////" << endl;
        cout << endl;
    }

    //TCanvas *c1 = new TCanvas("c1", "Primary and Secondary Track (A)", 1000, 500);
    //TCanvas *c2 = new TCanvas("c2", "Primary and Secondary Track (B)", 1000, 500);

    // if (display) {
    //     drawTwoPaths(c1, result.primary_track_bars, track2a, leptons);
    //     drawTwoPaths(c2, result.primary_track_bars, track2b, leptons);
    // }

    vec_pruned_backtracking.pop_back();  // Remove Kstop hit from lepton vector



    // TODO: Write a fit function for a vector of track bars
    //fitTrack(result.primary_track_bars);

    //////////////////////////////////////////////////////////////////////////////////
    /// TRIANGULAR PRUNING
    vector<int> TOF1_neighbours;
    TOF1_neighbours = TOF1Neighbours(gap_to_fit);

    vector<double> vec_xx_pruning_area;
    vector<double> vec_yy_pruning_area;

    vec_xx_pruning_area = PruningArea(vec_kstop_0[0], DG::TOF1_Xloc[TOF1_neighbours[0]][2], DG::TOF1_Xloc[TOF1_neighbours[1]][2]);
    vec_yy_pruning_area = PruningArea(vec_kstop_0[1], DG::TOF1_Yloc[TOF1_neighbours[0]][2], DG::TOF1_Yloc[TOF1_neighbours[1]][2]);

    TGraph *gr_pruning_area;
    gr_pruning_area = new TGraph(vec_xx_pruning_area.size(), &vec_xx_pruning_area[0], &vec_xx_pruning_area[0]);
    gr_pruning_area = new TGraph(vec_xx_pruning_area.size(), &vec_xx_pruning_area[0], &vec_yy_pruning_area[0]);
    gr_pruning_area->SetLineWidth(2);
    gr_pruning_area->SetLineColor(3);
    gr_pruning_area->SetMarkerStyle(34);
    gr_pruning_area->SetMarkerSize(1.3);
    gr_pruning_area->SetMarkerColor(2);

    vector<int> vec_pruned_triangle;

    vec_pruned_triangle = TriangularPruning(gap_to_fit, vec_xx_kstop_0[0], vec_yy_kstop_0[0], kaon_bars, lepton_bars);

    //////////////////////////////////////////////////////////////////////////////////
    /// LINE PRUNING
    vector<int> vec_pruned_line;
    vec_pruned_line = LinearPruning(gap_to_fit, vec_xx_kstop_0[0], vec_yy_kstop_0[0], lepton_bars, CW::GAP_LINE_SHIFT);

    vector<double> vec_pruning_line;
    vector<double> vec_pruning_line1;
    vector<double> vec_pruning_line2;

    vec_pruning_line = pruningLines(gap_to_fit, vec_xx_kstop_0[0], vec_yy_kstop_0[0], lepton_bars, CW::GAP_LINE_SHIFT);

    vec_pruning_line1.push_back(vec_pruning_line[0]);
    vec_pruning_line1.push_back(vec_pruning_line[1]);
    vec_pruning_line1.push_back(vec_pruning_line[2]);
    vec_pruning_line1.push_back(vec_pruning_line[3]);

    if(vec_pruning_line.size()>4){
        vec_pruning_line2.push_back(vec_pruning_line[4]);
        vec_pruning_line2.push_back(vec_pruning_line[5]);
        vec_pruning_line2.push_back(vec_pruning_line[6]);
        vec_pruning_line2.push_back(vec_pruning_line[7]);
    }
    else{
        vec_pruning_line2.clear();
    }

    //////////////////////////////////////////////////////////////////////////////////
    double Gap[12][5][2] = {{{0}}};

    for (int g = 0; g < 12; g++) {
        Gap[g][0][0] = DG::TOF1_Xloc[g][0];
        Gap[g][1][0] = DG::TOF1_Xloc[g][1];
        Gap[g][2][0] = DG::TOF1_Xloc[g][2];
        Gap[g][3][0] = DG::TOF1_Xloc[g][3];
        Gap[g][4][0] = DG::TOF1_Xloc[g][4];

        Gap[g][0][1] = DG::TOF1_Yloc[g][0];
        Gap[g][1][1] = DG::TOF1_Yloc[g][1];
        Gap[g][2][1] = DG::TOF1_Yloc[g][2];
        Gap[g][3][1] = DG::TOF1_Yloc[g][3];
        Gap[g][4][1] = DG::TOF1_Yloc[g][4];
    }

    ///////////////////////////////////////////////////////////////////////////////////////
    /// WORKING WITH PRUNED DATA
    vector<int> vec_leptons_pruned;
    vector<double> vec_xx_leptons_pruned;
    vector<double> vec_yy_leptons_pruned;

    if(type == line){
        vec_leptons_pruned = vec_pruned_line;
    }
    else if(type == triangle){
        vec_leptons_pruned = vec_pruned_triangle;
    }
    else{
        vec_leptons_pruned = vec_pruned_backtracking;       
    }

    if(to_rotate_leptons){
        for(unsigned int i=0; i<vec_leptons_pruned.size(); i++){
            vec_xx_leptons_pruned.push_back(DG::Xloc[DG::TARGET_Rotated_index[vec_leptons_pruned[i]]]);
            vec_yy_leptons_pruned.push_back(DG::Yloc[DG::TARGET_Rotated_index[vec_leptons_pruned[i]]]);
        }
    }
    else{
        for(unsigned int i=0; i<vec_leptons_pruned.size(); i++){
            vec_xx_leptons_pruned.push_back(DG::Xloc[vec_leptons_pruned[i]]);
            vec_yy_leptons_pruned.push_back(DG::Yloc[vec_leptons_pruned[i]]);
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    /// LEPTONS FIT 1
    vector<double> vec_line_parameters;
    vec_line_parameters.clear();

    if(to_rotate_leptons) TOF1_gap = DG::TOF1_rotated[gap_to_fit-1] + 1;
    else TOF1_gap = gap_to_fit;

    int EB_additional_weight = 0;

    /// GET SELECTED LEPTONS FOR FIT 1
    /// CAREFUL !!! : These lepon bars can be rotated !
    vector<int> vec_leptons_fit1;
    //vec_leptons_fit1 = selectLeptonsToFit(to_rotate_leptons, gap_to_fit, vec_leptons_pruned,
    //                                      vec_line_parameters, EB_additional_weight);

    vec_leptons_fit1 = selectLeptonsToFit(false, gap_to_fit, vec_leptons_pruned,
                                          vec_line_parameters, EB_additional_weight);


    bool to_restore = false;
    //if(to_rotate_leptons) to_restore = true;

    /// PREPARE TGRAPHERRORS gr_leptons_fit1 
    vector<double> vec_xx_leptons_fit1;
    vector<double> vec_yy_leptons_fit1;
    vector<double> vec_ex_leptons_fit1;
    vector<double> vec_ey_leptons_fit1;

    //*** Fill in the lepton bars (including "edge bars")
    for(unsigned int i=0; i<vec_leptons_fit1.size(); i++){
        vec_xx_leptons_fit1.push_back(DG::Xloc[vec_leptons_fit1[i]]);
        vec_yy_leptons_fit1.push_back(DG::Yloc[vec_leptons_fit1[i]]);
        vec_ex_leptons_fit1.push_back(DG::TARGET_Errors_X);
        vec_ey_leptons_fit1.push_back(DG::TARGET_Errors_Y);
    }

    // cout << endl;
    // cout << "TOF1 Gap : " << TOF1_gap << endl;
    // cout << endl;

    TOF1_gap = gap_to_fit;

    //*** Add TOF1 gap (weighted)
    /// ADD TOF1 GAP (WEIGHTED) TO THE FIT
    for(int i=0; i<CP::weight_TOF1_fit1; i++){
        vec_xx_leptons_fit1.push_back(DG::TOF1_Xloc[TOF1_gap-1][2]);
        vec_yy_leptons_fit1.push_back(DG::TOF1_Yloc[TOF1_gap-1][2]);
        vec_ex_leptons_fit1.push_back(DG::TOF1_Errors_X[TOF1_gap-1][2]);
        vec_ey_leptons_fit1.push_back(DG::TOF1_Errors_Y[TOF1_gap-1][2]);
    }

    TGraph *gr_leptons_fit1;
    TGraph *gr_leptons_fit1_unrotated;

    gr_leptons_fit1 = new TGraphErrors(vec_xx_leptons_fit1.size(), &vec_xx_leptons_fit1[0], &vec_yy_leptons_fit1[0],
                                       &vec_ex_leptons_fit1[0], &vec_ey_leptons_fit1[0]);

    gr_leptons_fit1_unrotated = new TGraphErrors(vec_xx_leptons_fit1.size(), &vec_xx_leptons_fit1[0], &vec_yy_leptons_fit1[0],
                                                 &vec_ex_leptons_fit1[0], &vec_ey_leptons_fit1[0]);


    gr_leptons_fit1->SetMarkerStyle(21);
    gr_leptons_fit1->SetMarkerColor(2);
    gr_leptons_fit1->SetMarkerSize(0.8);
    gr_leptons_fit1->GetXaxis()->SetLimits(-50.,50.);
    gr_leptons_fit1->GetYaxis()->SetRangeUser(-50.,50.);

    gr_leptons_fit1_unrotated->SetMarkerStyle(21);
    gr_leptons_fit1_unrotated->SetMarkerColor(2);
    gr_leptons_fit1_unrotated->SetMarkerSize(0.8);
    gr_leptons_fit1_unrotated->GetXaxis()->SetLimits(-50.,50.);
    gr_leptons_fit1_unrotated->GetYaxis()->SetRangeUser(-50.,50.);

    double a_fit1;
    double b_fit1;
    double Chis_fit1;
    double ndf_fit1;


    TF1 *f_leptons_fit_1 = new TF1("Leptons_fit1", "pol1");
    //gr_leptons_fit1->Fit("Leptons_fit1","QW");
    gr_leptons_fit1->Fit("Leptons_fit1","Q");
    //delete func_lepton_fit_1;

    TF1 *f_leptons_fit1 = gr_leptons_fit1->GetFunction("Leptons_fit1");
    a_fit1 = f_leptons_fit1->GetParameter(1);
    b_fit1 = f_leptons_fit1->GetParameter(0);
    Chis_fit1 = f_leptons_fit1->GetChisquare();
    ndf_fit1 = f_leptons_fit1->GetNDF();
    f_leptons_fit1->SetLineWidth(2);
    f_leptons_fit1->SetLineColor(2);

    /// CHECK IF A ROTATION IS NEEDED 
    // *** Or simply use the double fit method with first fit using option QW
    bool to_rotate_leptons_post_pruning = false;
    if(abs(a_fit1)>15) to_rotate_leptons_post_pruning = true;

    //if(!to_rotate_leptons && to_rotate_leptons_post_pruning){
    if(to_rotate_leptons_post_pruning){
        to_restore = true;

        vec_leptons_fit1 = rotateVector(vec_leptons_fit1);

        vec_xx_leptons_fit1.clear();
        vec_yy_leptons_fit1.clear();
        vec_ex_leptons_fit1.clear();
        vec_ey_leptons_fit1.clear();

        for(unsigned int i=0; i<vec_leptons_fit1.size(); i++){
            vec_xx_leptons_fit1.push_back(DG::Xloc[vec_leptons_fit1[i]]);
            vec_yy_leptons_fit1.push_back(DG::Yloc[vec_leptons_fit1[i]]);
            vec_ex_leptons_fit1.push_back(DG::TARGET_Errors_X);
            vec_ey_leptons_fit1.push_back(DG::TARGET_Errors_Y);
        }

        TOF1_gap = DG::TOF1_rotated[gap_to_fit-1] + 1;

        for(int i=0; i<CP::weight_TOF1_fit1; i++){
            vec_xx_leptons_fit1.push_back(DG::TOF1_Xloc[TOF1_gap-1][2]);
            vec_yy_leptons_fit1.push_back(DG::TOF1_Yloc[TOF1_gap-1][2]);
            vec_ex_leptons_fit1.push_back(DG::TOF1_Errors_X[TOF1_gap-1][2]);
            vec_ey_leptons_fit1.push_back(DG::TOF1_Errors_Y[TOF1_gap-1][2]);
        }

        gr_leptons_fit1->Set(0);
        gr_leptons_fit1 = new TGraphErrors(vec_xx_leptons_fit1.size(),&vec_xx_leptons_fit1[0],&vec_yy_leptons_fit1[0],
                                           &vec_ex_leptons_fit1[0],&vec_ey_leptons_fit1[0]);

        gr_leptons_fit1->SetMarkerStyle(21);
        gr_leptons_fit1->SetMarkerColor(2);
        gr_leptons_fit1->SetMarkerSize(0.8);
        gr_leptons_fit1->GetXaxis()->SetLimits(-50.,50.);
        gr_leptons_fit1->GetYaxis()->SetRangeUser(-50.,50.);

        TF1 *f_leptons_fit_1 = new TF1("Leptons_fit1", "pol1");
        gr_leptons_fit1->Fit("Leptons_fit1","Q");
        //delete func_lepton_fit_1;

        TF1 *f_leptons_fit1 = gr_leptons_fit1->GetFunction("Leptons_fit1");
        a_fit1 = f_leptons_fit1->GetParameter(1);
        b_fit1 = f_leptons_fit1->GetParameter(0);
        Chis_fit1 = f_leptons_fit1->GetChisquare();
        ndf_fit1 = f_leptons_fit1->GetNDF();
        f_leptons_fit1->SetLineWidth(2);
        f_leptons_fit1->SetLineColor(2);

        // TH2F *h_test = new TH2F("test", "test", 500, -50, 50, 500, -50, 50);
        // TEllipse *ell_Target = new TEllipse(0, 0, CP::R_TARGET, 0);
        // h_test->Draw();
        // //ell_Target->Draw("same");
        // gr_leptons_fit1->Draw("sameP");

        gr_leptons_fit1->Set(0);
        gr_leptons_fit1 = gr_leptons_fit1_unrotated;
    }


    vector<double> vec_line_parameters_fit1;
    vec_line_parameters_fit1.push_back(a_fit1);
    vec_line_parameters_fit1.push_back(b_fit1);

    bool To_rotate_TEST = false;
    if(to_rotate_leptons || to_rotate_leptons_post_pruning) To_rotate_TEST = true;

    ////////////////////////////////////////////////////////////////////////////////////////////
    /// LEPTONS FIT 2
    /// GET SELECTED LEPTONS FOR FIT 2
    /// CAREFUL !!! : These lepon bars can be rotated !
    vector<int> vec_leptons_fit2;   vec_leptons_fit2.clear();
    EB_additional_weight = 1;

    vector<double> vec_xx_leptons_fit2;
    vector<double> vec_yy_leptons_fit2;
    vector<double> vec_ex_leptons_fit2;
    vector<double> vec_ey_leptons_fit2;

    vector<double> vec_xx_leptons_fit_unrotated;
    vector<double> vec_yy_leptons_fit_unrotated;
    vector<double> vec_ex_leptons_fit_unrotated;
    vector<double> vec_ey_leptons_fit_unrotated;

    vec_leptons_fit2 = selectLeptonsToFit(false, TOF1_gap, vec_leptons_fit1,
                                          vec_line_parameters_fit1, EB_additional_weight);

    for(unsigned int i=0; i<vec_leptons_fit2.size(); i++){
        vec_xx_leptons_fit2.push_back(DG::Xloc[vec_leptons_fit2[i]]);
        vec_yy_leptons_fit2.push_back(DG::Yloc[vec_leptons_fit2[i]]);
        vec_ex_leptons_fit2.push_back(DG::TARGET_Errors_X);
        vec_ey_leptons_fit2.push_back(DG::TARGET_Errors_Y);
    }

    if(to_rotate_leptons_post_pruning){
        for(unsigned int i=0; i<vec_leptons_fit2.size(); i++){
            vec_xx_leptons_fit_unrotated.push_back(DG::Xloc[DG::TARGET_Rotated_index_inverse[vec_leptons_fit2[i]]]);
            vec_yy_leptons_fit_unrotated.push_back(DG::Yloc[DG::TARGET_Rotated_index_inverse[vec_leptons_fit2[i]]]);
            vec_ex_leptons_fit_unrotated.push_back(DG::TARGET_Errors_X);
            vec_ey_leptons_fit_unrotated.push_back(DG::TARGET_Errors_Y);
        }
    }

    TGraph *gr_leptons_fit2;
    TGraph *gr_leptons_fit2_unrotated;

    gr_leptons_fit2 = new TGraphErrors(vec_leptons_fit2.size(), &vec_xx_leptons_fit2[0], &vec_yy_leptons_fit2[0],
                                       &vec_ex_leptons_fit2[0], &vec_ey_leptons_fit2[0]);

    gr_leptons_fit2_unrotated = new TGraphErrors(vec_ey_leptons_fit_unrotated.size(),
                                                 &vec_xx_leptons_fit_unrotated[0], &vec_yy_leptons_fit_unrotated[0],
                                                 &vec_ex_leptons_fit_unrotated[0], &vec_ey_leptons_fit_unrotated[0]);

    gr_leptons_fit2_unrotated->SetMarkerStyle(21);
    gr_leptons_fit2_unrotated->SetMarkerColor(2);
    gr_leptons_fit2_unrotated->SetMarkerSize(0.8);


    double a_fit2 = 999.99;
    double b_fit2 = 999.99;
    double Chis_fit2 = 999.99;
    double ndf_fit2 = 999.99;
    vector<int> vec_leptons_pruned_unique;
    int Lepton_counter = -1;

    gr_leptons_fit2->SetMarkerStyle(21);
    gr_leptons_fit2->SetMarkerColor(2);
    gr_leptons_fit2->SetMarkerSize(0.8);
    gr_leptons_fit2->GetXaxis()->SetLimits(-50.,50.);
    gr_leptons_fit2->GetYaxis()->SetRangeUser(-50.,50.);

    TF1 *f_leptonsFit2 = new TF1("Leptons_fit2", "pol1", -50, 50);
    f_leptonsFit2->SetParameter(0, b_fit1);
    f_leptonsFit2->SetParameter(1, a_fit1);

    if(vec_leptons_fit2.size()>0){
        //gr_leptons_fit2->Fit("Leptons_fit2","QW");
        gr_leptons_fit2->Fit("Leptons_fit2","Q");

        TF1 *f_leptons_fit2 = gr_leptons_fit2->GetFunction("Leptons_fit2");
        a_fit2 = f_leptons_fit2->GetParameter(1);
        b_fit2 = f_leptons_fit2->GetParameter(0);
        Chis_fit2 = f_leptons_fit2->GetChisquare();
        ndf_fit2 = f_leptons_fit2->GetNDF();
        f_leptons_fit2->SetLineWidth(2);
        f_leptons_fit2->SetLineColor(2);      

        //cerr << "a_fit2 : " << a_fit2 << endl; 

        if(abs(a_fit2) > 100){
            gr_leptons_fit2->Fit("Leptons_fit2","QW");
            gr_leptons_fit2->Fit("Leptons_fit2","Q");

            TF1 *f_leptons_fit2 = gr_leptons_fit2->GetFunction("Leptons_fit2");
            a_fit2 = f_leptons_fit2->GetParameter(1);
            b_fit2 = f_leptons_fit2->GetParameter(0);
            Chis_fit2 = f_leptons_fit2->GetChisquare();
            ndf_fit2 = f_leptons_fit2->GetNDF();
            f_leptons_fit2->SetLineWidth(2);
            f_leptons_fit2->SetLineColor(2);
        
            //cerr << "a_fit2 : " << a_fit2 << endl;
        }
    }

    if(to_rotate_leptons_post_pruning){
        gr_leptons_fit2->Set(0);
        gr_leptons_fit2 = gr_leptons_fit2_unrotated;
    }

    vec_leptons_pruned_unique = removeDoubles(vec_leptons_fit2);
    Lepton_counter = vec_leptons_pruned_unique.size();

    //////////////////////////////////////////////////////////////////////////////////////////////
    /// LEPTONS FIT 3
    vector<double> vec_intersect_TOF1;
    int selected_TOF1_section = -1;

    if(vec_leptons_fit2.size() > 0){
        vec_intersect_TOF1 = intersectTOF1(TOF1_gap-1, a_fit2, b_fit2);
    }

    vector<double> int_with_circle;

    if(vec_leptons_fit2.size() > 0){
        int_with_circle = goodIntersectWithCircle(a_fit2, b_fit2, CP::R_TOF1, TOF1_gap);
    }

    if(vec_leptons_fit2.size()>0){
        selected_TOF1_section = whichTOF1Section(TOF1_gap, int_with_circle);
    }
    else selected_TOF1_section = -1;


    /// CAREFUL !!! : These lepon bars can be rotated !
    vector<int> vec_leptons_fit3;
    EB_additional_weight = 1;

    vector<double> vec_xx_leptons_fit3;
    vector<double> vec_yy_leptons_fit3;
    vector<double> vec_ex_leptons_fit3;
    vector<double> vec_ey_leptons_fit3;

    vec_xx_leptons_fit3 = vec_xx_leptons_fit2;
    vec_yy_leptons_fit3 = vec_yy_leptons_fit2;
    vec_ex_leptons_fit3 = vec_ex_leptons_fit2;
    vec_ey_leptons_fit3 = vec_ey_leptons_fit2;

    if(selected_TOF1_section != -1){
        for(int i=0; i<CP::weight_TOF1_fit3; i++){
            vec_xx_leptons_fit3.push_back(DG::TOF1_Xloc[TOF1_gap-1][selected_TOF1_section]);
            vec_yy_leptons_fit3.push_back(DG::TOF1_Yloc[TOF1_gap-1][selected_TOF1_section]);
            vec_ex_leptons_fit3.push_back(DG::TOF1_Errors_X[TOF1_gap-1][selected_TOF1_section]);
            vec_ey_leptons_fit3.push_back(DG::TOF1_Errors_Y[TOF1_gap-1][selected_TOF1_section]);
        }
    }

    if(to_rotate_leptons_post_pruning){
        for(int i=0; i<CP::weight_TOF1_fit3; i++){
            vec_xx_leptons_fit_unrotated.push_back(DG::TOF1_Xloc[gap_to_fit-1][selected_TOF1_section]);
            vec_yy_leptons_fit_unrotated.push_back(DG::TOF1_Yloc[gap_to_fit-1][selected_TOF1_section]);
            vec_ex_leptons_fit_unrotated.push_back(DG::TOF1_Errors_X[gap_to_fit-1][selected_TOF1_section]);
            vec_ey_leptons_fit_unrotated.push_back(DG::TOF1_Errors_Y[gap_to_fit-1][selected_TOF1_section]);
        }
    }

    TGraph *gr_leptons_fit3;
    TGraph *gr_leptons_fit3_unrotated;

    gr_leptons_fit3 = new TGraphErrors(vec_xx_leptons_fit3.size(), &vec_xx_leptons_fit3[0], &vec_yy_leptons_fit3[0],
                                       &vec_ex_leptons_fit3[0], &vec_ey_leptons_fit3[0]);
    gr_leptons_fit3_unrotated = new TGraphErrors(vec_xx_leptons_fit_unrotated.size(),
                                                 &vec_xx_leptons_fit_unrotated[0], &vec_yy_leptons_fit_unrotated[0],
                                                 &vec_ex_leptons_fit_unrotated[0], &vec_ey_leptons_fit_unrotated[0]);
    gr_leptons_fit3_unrotated->SetMarkerStyle(21);
    gr_leptons_fit3_unrotated->SetMarkerColor(2);
    gr_leptons_fit3_unrotated->SetMarkerSize(0.8);

    double a_fit3 = 999.99;
    double b_fit3 = 999.99;
    double Chis_fit3 = 999.99;
    int ndf_fit3 = 999;
    double a_fit3_error = 999.99;
    double b_fit3_error = 999.99;

    gr_leptons_fit3->SetMarkerStyle(21);
    gr_leptons_fit3->SetMarkerColor(2);
    gr_leptons_fit3->SetMarkerSize(0.8);
    gr_leptons_fit3->GetXaxis()->SetLimits(-50.,50.);
    gr_leptons_fit3->GetYaxis()->SetRangeUser(-50.,50.);

    TF1 *f_leptonsFit3 = new TF1("Leptons_fit3", "pol1");
    if(abs(a_fit2) > 20){
        f_leptonsFit3->SetParameter(0, b_fit1);
        f_leptonsFit3->SetParameter(1, a_fit1);
    }
    else{
        f_leptonsFit3->SetParameter(0, b_fit2);
        f_leptonsFit3->SetParameter(1, a_fit2);
    }


    if(vec_xx_leptons_fit3.size()>0){
        //gr_leptons_fit3->Fit("Leptons_fit3","QW");
        gr_leptons_fit3->Fit("Leptons_fit3","Q");

        TF1 *f_leptons_fit3 = gr_leptons_fit3->GetFunction("Leptons_fit3");
        a_fit3 = f_leptons_fit3->GetParameter(1);
        b_fit3 = f_leptons_fit3->GetParameter(0);
        Chis_fit3 = f_leptons_fit3->GetChisquare();
        ndf_fit3 = f_leptons_fit3->GetNDF();
        a_fit3_error = f_leptons_fit3->GetParError(1);
        b_fit3_error = f_leptons_fit3->GetParError(0);
        f_leptons_fit3->SetLineWidth(2);
        f_leptons_fit3->SetLineColor(2);

        //cerr << "a_fit3 : " << a_fit3 << endl;

        if(abs(a_fit3) > 100){
            gr_leptons_fit3->Fit("Leptons_fit3","QW");
            gr_leptons_fit3->Fit("Leptons_fit3","Q");

            TF1 *f_leptons_fit3 = gr_leptons_fit3->GetFunction("Leptons_fit3");
            a_fit3 = f_leptons_fit3->GetParameter(1);
            b_fit3 = f_leptons_fit3->GetParameter(0);
            Chis_fit3 = f_leptons_fit3->GetChisquare();
            ndf_fit3 = f_leptons_fit3->GetNDF();
            a_fit3_error = f_leptons_fit3->GetParError(1);
            b_fit3_error = f_leptons_fit3->GetParError(0);
            f_leptons_fit3->SetLineWidth(2);
            f_leptons_fit3->SetLineColor(2);

            //cerr << "a_fit3 : " << a_fit3 << endl;
        }
    }

    if(to_rotate_leptons_post_pruning){
        gr_leptons_fit3->Set(0);
        gr_leptons_fit3 = gr_leptons_fit3_unrotated;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    //// LEPTON GRAPH FINAL !
    vector<double> vec_xx_leptons_final;
    vector<double> vec_yy_leptons_final;
    vector<double> vec_ex_leptons_final;
    vector<double> vec_ey_leptons_final;

    TGraph *gr_leptons_final;

    if(to_restore){
        for(unsigned int i=0; i<vec_leptons_fit2.size(); i++){
            vec_xx_leptons_final.push_back(DG::Xloc[DG::TARGET_Rotated_index_inverse[vec_leptons_fit2[i]]]);
            vec_yy_leptons_final.push_back(DG::Yloc[DG::TARGET_Rotated_index_inverse[vec_leptons_fit2[i]]]);
            vec_ex_leptons_final.push_back(DG::TARGET_Errors_X);
            vec_ey_leptons_final.push_back(DG::TARGET_Errors_Y);
        }

        for(int i=0; i<CP::weight_TOF1_fit3; i++){
            vec_xx_leptons_final.push_back(DG::TOF1_Xloc[gap_to_fit-1][selected_TOF1_section]);
            vec_yy_leptons_final.push_back(DG::TOF1_Yloc[gap_to_fit-1][selected_TOF1_section]);
            vec_ex_leptons_final.push_back(DG::TOF1_Errors_X[gap_to_fit-1][selected_TOF1_section]);
            vec_ey_leptons_final.push_back(DG::TOF1_Errors_Y[gap_to_fit-1][selected_TOF1_section]);
        }

        gr_leptons_final = new TGraphErrors(vec_xx_leptons_final.size(), &vec_xx_leptons_final[0], &vec_yy_leptons_final[0],
                                            &vec_ex_leptons_final[0], &vec_ey_leptons_final[0]);
    }
    else gr_leptons_final = gr_leptons_fit3;

    vector<double> final_fit_XY;
    TLine *restored_fit_line;
    if(to_restore){
        final_fit_XY = restoreFitLine(a_fit3, b_fit3);

        restored_fit_line = new TLine(final_fit_XY[0], final_fit_XY[1],final_fit_XY[2],final_fit_XY[3]);

        restored_fit_line->SetLineWidth(2);
        restored_fit_line->SetLineColor(2);
    }
    else{
        restored_fit_line = new TLine(999., 999.,999.,999.);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////
    /// DETERMINE FINAL KSTOP  <---- TO FINISH !!!
    bool vertical_kaon = false;
    bool vertical_lepton = false;

    if(a_fit_kaon_final == 0){
        vertical_kaon = true;
    }

    if(a_fit3 == 0){
        vertical_lepton = true;

    }

    vector<double> vec_kstop_FINAL; vec_kstop_FINAL.clear();
    int i_kaon_bar = -1;
    double R_Kstop = 999.99;

    vec_kstop_FINAL = getKstopFinal(*data, to_restore,
                                    vec_leptons_fit2, kaon_bars, V_centroid,
                                    a_fit_kaon_final, b_fit_kaon_final, a_fit3, b_fit3,
                                    has_kaon_sub, kaon_substitute);

    i_kaon_bar = kaonFiber(vec_kstop_FINAL[0],vec_kstop_FINAL[1]);

    R_Kstop = sqrt(vec_kstop_FINAL[0]*vec_kstop_FINAL[0] + vec_kstop_FINAL[1]*vec_kstop_FINAL[1]);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// IF NO LEPTON LEFT 
    bool b_bbar = false;
    vector<double> vec_bbar;          vec_bbar.clear();
    vector<double> vec_slope_bbar;    vec_slope_bbar.clear();

    if(vec_leptons_fit2.size() == 0){
        vec_bbar = lineLeptonToTOF1(vec_leptons_fit2, gap_to_fit, vec_kstop_FINAL[0], vec_kstop_FINAL[1]);
        b_bbar = true;
    }

    if(b_bbar){
        vec_slope_bbar = getSlope(vec_bbar[0], vec_bbar[1], vec_bbar[2], vec_bbar[3]);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////

    double a_final = 999.99;
    double b_final = 999.99;
    double ChiS_final = 999.99;
    int ndf_final = 999;
    double a_final_error = 999.99;
    double b_final_error = 999.99;

    if(to_restore){
        if(a_fit3 !=0){
            a_final = -1/a_fit3;
            b_final = b_fit3/a_fit3;
            ChiS_final = Chis_fit3 ;
            ndf_final = ndf_fit3;
            a_final_error = a_fit3_error;
            b_final_error = b_fit3_error;
        }  
        //else cout << "NAN ALERT ! -- Evt : " << event_number << endl;
    }
    else{
        a_final = a_fit3;
        b_final = b_fit3;
        ChiS_final = Chis_fit3 ;
        ndf_final = ndf_fit3;
        a_final_error = a_fit3_error;
        b_final_error = b_fit3_error;
    }

    //////////////////////////////////////////////////////////////////////////////
    /// GET THE INTERSECT BETWEEN THE TWO FITTING LINES
    vector<double>vec_fit_lines_intersect_NEW;
    vec_fit_lines_intersect_NEW = TwoLinesIntersect(a_fit_kaon_final, b_fit_kaon_final, a_fit3, b_fit3);


    /// CALCULATE INTERSECT WITH TARGET, TOF1 and SFT
    // Intersect with TARGET
    vector<double> vec_intersect_TARGET_final;
    vector<double> vec_XX_int_TARGET;
    vector<double> vec_YY_int_TARGET;

    if(to_restore && a_fit3 == 0){
        vec_intersect_TARGET_final = intersectCircle(a_fit3, b_fit3, CP::R_TARGET, DG::TOF1_Xloc[gap_to_fit-1][2], DG::TOF1_Yloc[gap_to_fit-1][2]);
        if(vec_intersect_TARGET_final[1] != 0){
            vec_XX_int_TARGET.push_back(-vec_intersect_TARGET_final[1]);
            vec_YY_int_TARGET.push_back(vec_intersect_TARGET_final[0]);
        }
        else{
            vec_XX_int_TARGET.push_back(0.);
            vec_YY_int_TARGET.push_back(vec_intersect_TARGET_final[0]);           
        }
    }
    else{
        if(b_bbar){ 
            vec_intersect_TARGET_final = intersectCircle(vec_slope_bbar[0], vec_slope_bbar[1], CP::R_TARGET, DG::TOF1_Xloc[gap_to_fit-1][2], DG::TOF1_Yloc[gap_to_fit-1][2]);
        }
        else{
            vec_intersect_TARGET_final = intersectCircle(a_final, b_final, CP::R_TARGET, DG::TOF1_Xloc[gap_to_fit-1][2], DG::TOF1_Yloc[gap_to_fit-1][2]);    
        }

        vec_XX_int_TARGET.push_back(vec_intersect_TARGET_final[0]);
        vec_YY_int_TARGET.push_back(vec_intersect_TARGET_final[1]);
    }

    // Intersect with TOF1
    vector<double> vec_intersect_TOF1_final;
    vector<double> vec_XX_int_TOF1;
    vector<double> vec_YY_int_TOF1;

    if(to_restore && a_fit3 == 0){
        vec_intersect_TOF1_final = intersectCircle(a_fit3, b_fit3, CP::R_TOF1, DG::TOF1_Xloc[gap_to_fit-1][2], DG::TOF1_Yloc[gap_to_fit-1][2]);
        if(vec_intersect_TOF1_final[1] != 0){
            vec_XX_int_TARGET.push_back(-vec_intersect_TOF1_final[1]);
            vec_YY_int_TARGET.push_back(vec_intersect_TOF1_final[0]);
        }
        else{
            vec_XX_int_TOF1.push_back(0.);
            vec_YY_int_TOF1.push_back(vec_intersect_TOF1_final[0]);           
        }
    }
    else{
        if(b_bbar){
            vec_intersect_TOF1_final = intersectCircle(vec_slope_bbar[0], vec_slope_bbar[1], CP::R_TOF1, DG::TOF1_Xloc[gap_to_fit-1][2], DG::TOF1_Yloc[gap_to_fit-1][2]);
        }
        else{
            vec_intersect_TOF1_final = intersectCircle(a_final, b_final, CP::R_TOF1, DG::TOF1_Xloc[gap_to_fit-1][2], DG::TOF1_Yloc[gap_to_fit-1][2]);   
        }
        
        vec_XX_int_TOF1.push_back(vec_intersect_TOF1_final[0]);
        vec_YY_int_TOF1.push_back(vec_intersect_TOF1_final[1]);
    }

    // Intersect with SFT L1
    vector<double> vec_intersect_SFT_final;
    vector<double> vec_XX_int_SFT;
    vector<double> vec_YY_int_SFT;

    if(to_restore && a_fit3 == 0){
        vec_intersect_SFT_final = intersectCircle(a_fit3, b_fit3, CP::R_SFT_L1, DG::TOF1_Xloc[gap_to_fit-1][2], DG::TOF1_Yloc[gap_to_fit-1][2]);
        if(vec_intersect_SFT_final[1] != 0){
            vec_XX_int_SFT.push_back(-vec_intersect_SFT_final[1]);
            vec_YY_int_SFT.push_back(vec_intersect_SFT_final[0]);
        }
        else{
            vec_XX_int_SFT.push_back(0.);
            vec_YY_int_SFT.push_back(vec_intersect_SFT_final[0]);           
        }
    }
    else{
        if(b_bbar){
            vec_intersect_SFT_final = intersectCircle(vec_slope_bbar[0], vec_slope_bbar[1], CP::R_SFT_L1, DG::TOF1_Xloc[gap_to_fit-1][2], DG::TOF1_Yloc[gap_to_fit-1][2]);
        }
        else{
            vec_intersect_SFT_final = intersectCircle(a_final, b_final, CP::R_SFT_L1, DG::TOF1_Xloc[gap_to_fit-1][2], DG::TOF1_Yloc[gap_to_fit-1][2]);   
        }
        vec_XX_int_SFT.push_back(vec_intersect_SFT_final[0]);
        vec_YY_int_SFT.push_back(vec_intersect_SFT_final[1]);
    }

    /// LENGTH IN TARGET
    double length_in_target = -1.;
    length_in_target = distance(vec_kstop_FINAL[0],vec_kstop_FINAL[1],
                                vec_XX_int_TARGET[0],vec_YY_int_TARGET[0]);

    /// SUM ADC HG
    int sum_ADC_HG_lepton = 0;

    for(unsigned int i=0; i<vec_leptons_pruned_unique.size(); i++){
        sum_ADC_HG_lepton += data->ADC_High_TARGET[vec_leptons_pruned_unique[i]] + CW::TARGET_ADC_Thr_HG_Offset;
    }

    /// CALCULATE FINAL TRACK ANGLE
    double alpha_guide = 999.99;
    double angle_final = 999.99;
    double delta_phi = 999.99;
    double delta_phi_deg = 999.99;

    if(to_restore && a_fit3 == 0 && gap_to_fit == 12){
        angle_final = 90.;
        ChiS_final = Chis_fit3;
        ndf_final = ndf_fit3;
        if(b_fit3 !=0){
            delta_phi_deg = (180./TMath::Pi()) * (sin(atan(b_fit3))*cos(atan(b_fit3))*(b_fit3_error/b_fit3));
        }
        else{
            delta_phi_deg = -1.;
        }
    }
    else if(to_restore && a_fit3 == 0 && gap_to_fit == 6){
        angle_final = 270.;
        delta_phi_deg = (180./TMath::Pi()) * (sin(atan(b_fit3))*cos(atan(b_fit3))*(b_fit3_error/b_fit3));
        ChiS_final = Chis_fit3;
        ndf_final = ndf_fit3;
        if(b_fit3 !=0){
            delta_phi_deg = (180./TMath::Pi()) * (sin(atan(b_fit3))*cos(atan(b_fit3))*(b_fit3_error/b_fit3));
        }
        else{
            delta_phi_deg = -1.;
        }
    }
    else{
        if(!b_bbar){
            alpha_guide = atan(a_final);
            // angle_final = angleCalculation(a_final, vec_XX_int_TOF1[0], vec_YY_int_TOF1[0],
            //                                vec_XX_int_TARGET[0], vec_YY_int_TARGET[0]);
            angle_final = angleCalculation2(a_final, vec_XX_int_TOF1[0], vec_YY_int_TOF1[0],
                                           vec_XX_int_TARGET[0], vec_YY_int_TARGET[0]);

            delta_phi = sin(alpha_guide)*cos(alpha_guide)*(a_final_error/a_final);
            delta_phi_deg = (180./TMath::Pi())*delta_phi;
        }
        else{
            // angle_final = angleCalculation(vec_slope_bbar[0], vec_bbar[2], vec_bbar[3],
            //                                vec_XX_int_TARGET[0], vec_YY_int_TARGET[0]);
            angle_final = angleCalculation2(vec_slope_bbar[0], vec_bbar[2], vec_bbar[3],
                                           vec_XX_int_TARGET[0], vec_YY_int_TARGET[0]);
            delta_phi_deg = 99.99;
            ChiS_final = -1.;
            ndf_final = 1;
        }
    }

    // UNCERTAINTY
    double delta_X = 999.99;
    double delta_Y = 999.99;

    if(b_bbar){
        delta_X = 99.99;
        delta_Y = 99.99;
    }
    else{
        delta_X = sqrt(pow(DG::TARGET_Errors_X,2) + pow((sin(angle_final)*CP::R_TARGET*delta_phi),2));
        delta_Y = sqrt(pow(DG::TARGET_Errors_Y,2) + pow((cos(angle_final)*CP::R_TARGET*delta_phi),2));
    }

    /// HAS EDGE BARS  <---- TO REVIEW !
    int HasEdgeBars;
    if(has_edge_bars) HasEdgeBars = 1;
    else HasEdgeBars = 0;

    /// CHECK IF GOOD TOF1 EVENT  <--- TO REVIEW !
    bool IsGoodTOF1 = false;
    IsGoodTOF1 = goodTOF1(gap_to_fit-1,vec_intersect_TOF1_final);

    /// PRINTOUTS
    int Switch_Printout = 1;
    int TDC_print[256] = {-1};
    //for(int i=0; i<256; i++) TDC_print[i] = -1;

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////


    //// Don't do anything if the event has less than n_hits hits in the TARGET
    if (enable_cout == 9) count = CP::min_hits + 1;
    if (count < -10) {
        if (print_to_console && !batch_mode) {
            cout << " >>>>  Event " << data->EvNum << " has fewer than " << CP::min_hits
                 << " high gain hits in the TARGET (outliers and K stop removed)!" << endl;
            cout << " >>>>  Please, choose another event" << endl;
            cout << " " << endl;
        }
        if (!batch_mode) {
            delete data;
            data = nullptr;
        }
        return; // TODO: make this throw an error instead
    }


    // ### Display Ck and Cpi infomation
    int TDC_ck_selected[14] = {0};
    int TDC_cpi_selected[14] = {0};

    for (int ic = 0; ic < 14; ic++) {
        for (int jc = 0; jc < 6; jc++) {
            if (data->TDC_Ck[ic][jc] >= CW::TDC_Ck_min && data->TDC_Ck[ic][jc] <= CW::TDC_Ck_max)
                TDC_ck_selected[ic] = data->TDC_Ck[ic][jc];
            if (data->TDC_Cpi[ic][jc] >= CW::TDC_Cpi_min && data->TDC_Cpi[ic][jc] <= CW::TDC_Cpi_max)
                TDC_cpi_selected[ic] = data->TDC_Cpi[ic][jc];
        }
        if (TDC_ck_selected[ic] > 0) vec_Ck.push_back(TDC_ck_selected[ic]);
        if (TDC_cpi_selected[ic] > 0) vec_Cpi.push_back(TDC_cpi_selected[ic]);
        TDC_ck_selected[ic] = 0;
        TDC_cpi_selected[ic] = 0;
    }

    for (unsigned int ik = 0; ik < vec_Ck.size(); ik++) TDC_ck_sum += vec_Ck[ik];
    for (unsigned int ip = 0; ip < vec_Cpi.size(); ip++) TDC_cpi_sum += vec_Cpi[ip];

    if (vec_Ck.size() > 0) TDC_ck_avg = double(TDC_ck_sum) / double(vec_Ck.size());
    else TDC_ck_avg = -1;

    if (vec_Cpi.size() > 0) TDC_cpi_avg = double(TDC_cpi_sum) / double(vec_Cpi.size());
    else TDC_cpi_avg = -1;

    for (unsigned int i = 0; i < vec_Ck.size(); i++) TDC_ck_sigma2 += pow((vec_Ck[i] - TDC_ck_avg), 2);
    for (unsigned int j = 0; j < vec_Cpi.size(); j++) TDC_cpi_sigma2 += pow((vec_Cpi[j] - TDC_cpi_avg), 2);

    if (vec_Ck.size() > 1) TDC_ck_sigma = sqrt(TDC_ck_sigma2 / (vec_Ck.size() - 1));
    else TDC_ck_sigma = 0;

    if (vec_Cpi.size() > 1) TDC_cpi_sigma = sqrt(TDC_cpi_sigma2 / (vec_Cpi.size() - 1));
    else TDC_cpi_sigma = 0;

    for (unsigned int i = 0; i < vec_Ck.size(); i++) {
        if (abs(vec_Ck[i] - TDC_ck_avg) <= 1.4 * TDC_ck_sigma) {
            TDC_ck_sum2 += vec_Ck[i];
            TDC_ck_counter++;
        }
    }

    for (unsigned int j = 0; j < vec_Cpi.size(); j++) {
        if (abs(vec_Cpi[j] - TDC_cpi_avg) <= 1.4 * TDC_cpi_sigma) {
            TDC_cpi_sum2 += vec_Cpi[j];
            TDC_cpi_counter++;
        }
    }

    if (TDC_ck_counter > 0) TDC_ck_avg2 = double(TDC_ck_sum2) / double(TDC_ck_counter);
    else TDC_ck_avg2 = -1;

    if (TDC_cpi_counter > 0) TDC_cpi_avg2 = double(TDC_cpi_sum2) / double(TDC_cpi_counter);
    else TDC_cpi_avg2 = -1;

    /// TDC DIFF
    tdc_ck_corr = data->TDC_Trig[0][0] - TDC_ck_avg2;
    TDC_diff = 550. - (0.91*TDC_average - 0.625*tdc_ck_corr);


    ////////////////////////////////////////////////////////////////////
    /// AVERAGE TDCs
    // Leptons
    double sum_TDC_lepton = 0.;
    int counter_TDC_lepton = 0;
    double Average_TDC_lepton = 0.;

    for(unsigned int i=0; i<vec_leptons_pruned_unique.size(); i++){
        for(int j=0; j<16; j++){
            if(data->TDC_LE_TARGET[vec_leptons_pruned_unique[i]][j]>kaon_TDC_min && data->TDC_LE_TARGET[vec_leptons_pruned_unique[i]][j]<kaon_TDC_max){
                sum_TDC_lepton += 550-(0.91*data->TDC_LE_TARGET[vec_leptons_pruned_unique[i]][j] - 0.625*(data->VT48_TDC[0][0]-TDC_ck_avg2));
                counter_TDC_lepton++;
            }
        }
    }

    if (counter_TDC_lepton > 0) Average_TDC_lepton = sum_TDC_lepton / counter_TDC_lepton;
    else Average_TDC_lepton = -1;


    // Kaons
    double sum_TDC_kaon = 0.;
    int counter_TDC_kaon = 0;
    double Average_TDC_kaon = 0.;

    for(unsigned int i=0; i<kaon_bars.size(); i++){
        for(int j=0; j<16; j++){
            if(data->TDC_LE_TARGET[kaon_bars[i]][j]>TDC_min_Kstop && data->TDC_LE_TARGET[kaon_bars[i]][j]<TDC_max_Kstop){
                sum_TDC_kaon += 550-(0.91*data->TDC_LE_TARGET[kaon_bars[i]][j] - 0.625*(data->VT48_TDC[0][0]-TDC_ck_avg2));
                counter_TDC_kaon++;
            }
        }
    }

    if (counter_TDC_kaon > 0) Average_TDC_kaon = sum_TDC_kaon / counter_TDC_kaon;
    else Average_TDC_kaon = -1;

    ////////////////////////////////////////////////////////////////////

    /// PRINTOUTS
    if(print_to_console && !batch_mode){
        printTOFRawADC(*data);

        printTimeCuts(*data, kaon_TDC_min, kaon_TDC_max, TDC_min_Kstop, TDC_max_Kstop);

        printTargetInfo(*data, is_good_event, enable_cout, NoFile,
                        data->EvNum, TDC_average);

        printSFTInfo(*data, ADC_High_SFT_corr, has_TDC_SFT_hit);

    }

    double C2X_centroid = -1;
    C2X_centroid = findMWPCClusters(*data, is_good_event,
                                    selected_TOF2, (print_to_console && !batch_mode));


    if(print_to_console && !batch_mode){

        printCherenkovInfo(*data, TDC_average,
                           vec_Ck, TDC_ck_avg, TDC_ck_sigma,
                           vec_Cpi, TDC_cpi_avg, TDC_cpi_sigma,
                           TDC_ck_counter, TDC_ck_avg2,
                           TDC_cpi_counter, TDC_cpi_avg2);

        printCkCorrectedTDC(*data, vec_TARGET_bar_selected, TDC_ck_avg2);

        printGapScoring(*data, selected_TOF2, is_good_event);

        printTrackInfo(angle_final, delta_phi_deg, ChiS_final, ndf_final,
                       vec_XX_int_SFT, vec_YY_int_SFT,
                       vec_XX_int_TOF1, vec_YY_int_TOF1,
                       length_in_target);
    }

    if(print_to_console) {
        printTrackList(data->RunNum, data->EvNum, data->EvFlag[0], gap_to_fit, selected_TOF2, extra_TOF1.size(),
                       angle_final, delta_phi_deg, delta_X, delta_Y,
                       ChiS_final, ndf_final, Lepton_counter,
                       vec_XX_int_TARGET[0], vec_YY_int_TARGET[0],
                       vec_XX_int_SFT[0], vec_YY_int_SFT[0],
                       N_centroid_X, N_centroid_Y,
                       vec_fit_lines_intersect_NEW[0], vec_fit_lines_intersect_NEW[1],
                       vec_kstop_FINAL[0], vec_kstop_FINAL[1],
                       R_Kstop, i_kaon_bar, kaon_bars.size(),
                       ChiS_kaon_final, ndf_kaon_final,
                       vec_Ck.size(), vec_Cpi.size(),
                       length_in_target, C2X_centroid, TDC_diff, sum_ADC_HG_lepton,
                       Average_TDC_lepton, Average_TDC_kaon,
                       HasEdgeBars, IsGoodTOF1,
                       type, batch_mode, print_to_console);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// PLOTTING

    if(display) {
        gStyle->SetOptStat(0); // Remove legends
        gStyle->SetTitleW(0.9);
        gStyle->SetTitleH(0.05);

        drawFitting(to_rotate_leptons_post_pruning, to_rotate_kaons,
                    data->RunNum, data->EvNum, type,
                //gr_leptons_fit1, gr_leptons_fit2, gr_leptons_fit3,
                    gr_leptons_fit1, gr_leptons_fit2, gr_leptons_fit3,
                    gr_kaons_final, line_fit_kaons,
                    int_with_circle,
                    a_fit1, b_fit1,
                    a_fit2, b_fit2,
                    a_fit3, b_fit3);


        drawPruning(data->RunNum, data->EvNum, kaon_bars,
                    vec_kstop_0,
                    vec_pruned_triangle, vec_pruned_line, vec_pruned_backtracking,
                    vec_xx_pruning_area, vec_yy_pruning_area,
                    line_fit_kaons, line_fit_leptons,
                    vec_pruning_line1, vec_pruning_line2,
                    gr_kaons_final, gr_kaons_unfitted,
                    gr_leptons_0_NEW);


        drawBacktracking(result.primary_track_bars, track2a, track2b, leptons);


        drawEventDisplay(*data, data->RunNum, data->EvNum, to_restore,
                         gap_to_fit, selected_TOF1_section, restored_fit_line,
                         kaon_TDC_min, kaon_TDC_max, TDC_min_Kstop, TDC_max_Kstop,
                         has_kaon_sub, i_kaon_bar, b_bbar, vec_bbar,
                         has_ADC_TOF1_hit, has_TDC_TOF1_hit, has_ADC_TOF2_hit, has_TDC_TOF2_hit,
                         has_TDC_hit, TDC_min_TARGET, has_TDC_hit_Kstop,
                         angle_final, delta_phi_deg, ChiS_final, ndf_final,
                         vec_XX_int_SFT, vec_YY_int_SFT,
                         vec_XX_int_TARGET, vec_YY_int_TARGET,
                         vec_XX_int_TOF1, vec_YY_int_TOF1,
                         vec_kstop_FINAL, vec_intersect_TARGET_final,
                         gr_leptons_final, gr_kaons_final, line_fit_kaons,
                         type);
    }

    if(print_to_file){
        fout_csv << fixed;
        fout_csv << data->RunNum << ",";
        fout_csv << data->EvNum << ",";
        fout_csv << data->EvFlag[0] << ",";
        fout_csv << gap_to_fit << ",";
        fout_csv << selected_TOF2 << ",";
        fout_csv << extra_TOF1.size() << ",";
        fout_csv << setprecision(2) << angle_final << ",";
        fout_csv << setprecision(2) << delta_phi_deg << ",";
        fout_csv << setprecision(2) << delta_X << ",";
        fout_csv << setprecision(2) << delta_Y << ",";
        fout_csv << setprecision(2) << ChiS_final << ",";
        fout_csv << setprecision(0) << ndf_final << ",";
        fout_csv << setprecision(2) << ChiS_final/ndf_final << ",";
        fout_csv << Lepton_counter << ",";
        fout_csv << setprecision(2) << vec_XX_int_TARGET[0] << ",";
        fout_csv << setprecision(2) << vec_YY_int_TARGET[0] << "," ;
        fout_csv << setprecision(2) << vec_XX_int_SFT[0] << "," ;
        fout_csv << setprecision(2) << vec_YY_int_SFT[0] << "," ;
        fout_csv << setprecision(2) << N_centroid_X << ",";
        fout_csv << setprecision(2) << N_centroid_Y << ",";
        fout_csv << setprecision(2) << vec_fit_lines_intersect_NEW[0] << ",";
        fout_csv << setprecision(2) << vec_fit_lines_intersect_NEW[1] << ",";
        fout_csv << setprecision(2) << vec_kstop_FINAL[0] << ",";             // 21
        fout_csv << setprecision(2) << vec_kstop_FINAL[1] << ",";
        fout_csv << setprecision(2) << R_Kstop << ",";             // 22
        fout_csv << i_kaon_bar << ",";
        fout_csv << kaon_bars.size() << ",";
        fout_csv << setprecision(2) << ChiS_kaon_final/ndf_kaon_final << ",";
        fout_csv << vec_Ck.size() << ",";
        fout_csv << vec_Cpi.size() << ",";
        fout_csv << setprecision(2) << length_in_target << ",";
        fout_csv << setprecision(2) << C2X_centroid << ",";
        fout_csv << setprecision(1) << TDC_diff << ",";
        fout_csv << sum_ADC_HG_lepton << ",";
        fout_csv << setprecision(2) << Average_TDC_lepton << ",";
        fout_csv << setprecision(2) << Average_TDC_kaon << ",";
        fout_csv << setprecision(0) << HasEdgeBars << ",";
        fout_csv << setprecision(0) << IsGoodTOF1;
        fout_csv << endl;
        fout_csv.close();
    }

    bool fit_two_tracks = false;
    if (fit_two_tracks) {
        point_t kstop{vec_kstop_FINAL[0], vec_kstop_FINAL[1]};
        point_t tof1{vec_XX_int_TOF1[0], vec_YY_int_TOF1[0]};

        //fitTwoTracks(lepton_points, kstop, tof1);
    }

    if (!batch_mode) {
        delete data;
        data = nullptr;
    }

    return;
}
