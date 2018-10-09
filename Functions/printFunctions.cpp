/* 
 * Created by Jack Hong on 2018-07-11. (jhong@alumni.ubc.ca)
 */
#pragma once

#include <iostream>
#include <iomanip>
#include "printFunctions.hpp"
#include "determineTOF1Gap.hpp"
#include "findKaonTDCAverage.hpp"
#include "CutsAndWindows.hpp"
#include "DetectorGeometry.hpp"


using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::setprecision;

namespace CW = CutsAndWindows;
namespace DG = DetectorGeometry;

void printEventSummary(DetectorData &data, string Time_walk_file, string SFT_mapping_file, string MWPC_mapping_file,
                       bool is_good_event, bool is_good_TARGET_event, bool is_good_TOF_event, bool is_good_MWPC_event,
                       bool is_event_on_blacklist) {
    cout << endl;
    cout << "*************************************************************************************************" << endl;

    cout << "File opened:               " << data.getRootFilePath() << endl;
    cout << "TimeWalk Parameter File:   " << Time_walk_file << endl;
    cout << "SFT Mapping File:          " << SFT_mapping_file << endl;
    cout << "MWPC Mapping File:         " << MWPC_mapping_file << endl;
    cout << "Total Number of Events:    " << data.getNumberOfEvents() << endl;
    printEventStatus(data.EvNum, is_good_event,
                     is_good_TARGET_event, is_good_TOF_event, is_good_MWPC_event,
                     is_event_on_blacklist);
    cout << "*************************************************************************************************" << endl;
    cout << endl;
}

void printEventStatus(int event_number, bool is_good_event,
                      bool is_good_TARGET_event, bool is_good_TOF_event, bool is_good_MWPC_event,
                      bool is_event_on_blacklist) {
    cout << "Event status:              ";
    cout << "EVENT " << event_number;

    if (is_good_event) {
        cout << "  --  GOOD EVENT!" << endl;
    }
    else if (is_event_on_blacklist) {
        cout << "  --  ON BLACKLIST!" << endl;
    }
    else {
        if (!is_good_MWPC_event) {
            cout << "  --  NO MWPC!";
        }
        if (!is_good_TOF_event) {
            cout << "  --  NO TOF!";
        }
        if (!is_good_TARGET_event) {
            cout <<"  --  NO TARGET!";
        }

        cout <<  endl;
        cout << ">>>>>  Please choose another event." << endl;
        cout <<  endl;
    }
}

void printTOFRawADC(const DetectorData &data){

    cout << endl;
    cout << " **** RAW ADCs" << endl;
    cout << " ///////////   TOF1   ///////////   //////////////////////   TOF2   //////////////////////" << endl;
    for(int i=0; i<12; i++){
        printf(" %2d   UP: %4d  |  DOWN: %4d    ||    %2d   AO: %4d  |  BO: %4d  |  AI: %4d  |  BI: %4d\n",
               i+1, data.ADC_TOF1U[i] + CW::TOF1U_ADC_Thr[i], data.ADC_TOF1D[i] + CW::TOF1D_ADC_Thr[i], i+1,
               data.ADC_TOF2AO[i] + CW::TOF2AO_ADC_Thr[i],
               data.ADC_TOF2BO[i] + CW::TOF2BO_ADC_Thr[i],
               data.ADC_TOF2AI[i] + CW::TOF2AI_ADC_Thr[i],
               data.ADC_TOF2BI[i] + CW::TOF2BI_ADC_Thr[i]);
    }
    cout << endl;
}

void printTimeCuts(const DetectorData &data, int kaon_TDC_min, int kaon_TDC_max, int TDC_min_Kstop, int TDC_max_Kstop){

    cout << endl;
    cout << "NEW" << endl;
    findKaonTDCAverage(data, true);

    cout << "TIME CUTS" << endl;
    cout << "# Lepton + Kaon : " << kaon_TDC_min << " <= " << "TDC" << " <= " << kaon_TDC_max << endl;
    cout << "# Kaon : " << TDC_min_Kstop << " <= " << "TDC" << " <= " << TDC_max_Kstop << endl;
    cout << endl;
}

void printTargetInfo(const DetectorData &data, bool Good_Event, int enable_cout, bool NoFile,
                     int ievt, int TDC_average){

    int TDC_print[256];
    for(int i=0; i<256; i++) TDC_print[i] = -1;
    int HG_TARGET_ADC_Thr[256] = {0};
    int LG_TARGET_ADC_Thr[256] = {0};
    int TDC_LE_TARGET_corrected[256][6] = {-1};
    char TDC_LE_TARGET_corr[256][6][20];

    for(int i=0; i<256; i++)  HG_TARGET_ADC_Thr[i] = round(CW::TARGET_ADC_Ped_HG[i]) + CW::TARGET_ADC_Thr_HG_Offset;
    for(int i=0; i<256; i++)  LG_TARGET_ADC_Thr[i] = round(CW::TARGET_ADC_Ped_LG[i]) + CW::TARGET_ADC_Thr_LG_Offset;


    for(int k=0; k<256; k++){
        for(int l=0; l<6; l++){
            TDC_LE_TARGET_corrected[k][l] = 9999;
            //if(tdc_le_target[k][l]>-1)  TDC_LE_TARGET_corrected[k][l] = tdc_le_target[k][l] - TDC_average_NEW;
            if(data.TDC_LE_TARGET[k][l]>-1)  TDC_LE_TARGET_corrected[k][l] = data.TDC_LE_TARGET[k][l]- TDC_average;
        }
    }

    for(int k=0; k<256; k++){
        for(int l=0; l<6; l++){
            if(TDC_LE_TARGET_corrected[k][l] == 9999) sprintf(TDC_LE_TARGET_corr[k][l],"----");
            if(TDC_LE_TARGET_corrected[k][l] != 9999) sprintf(TDC_LE_TARGET_corr[k][l],"%4d",TDC_LE_TARGET_corrected[k][l]);
        }
    }

    cout << endl;
    if(Good_Event && enable_cout==1){
        if(!NoFile) cout << "//////  TARGET  (WALK CORRECTION APPLIED !)  //////" << endl;
        if(NoFile) cout << "//////  TARGET  //////" << endl;
        cout << "Event: " << ievt << "     ADC Threshold Offset (HG): " << CW::TARGET_ADC_Thr_HG_Offset << "     ADC Threshold Offset (LG): " << CW::TARGET_ADC_Thr_LG_Offset << endl << endl;
        cout << "Fiber  HG-Ped  LG-Ped    TDC[0]   TDC[1]   TDC[2]   TDC[3]   TDC[4]   TDC[5]   Thr(HG)   Thr(LG)   HG/LG" << endl;
        for(int i=0; i<256; i++){
            if(data.TDC_LE_TARGET[i][0] > -1 || data.TDC_LE_TARGET[i][1] > -1 || data.TDC_LE_TARGET[i][2] > -1 || data.TDC_LE_TARGET[i][3] > -1){
                printf("%3d     %4d    %4d     %4d     %4d     %4d     %4d     %4d     %4d      %4d      %4d     %2.2f\n",
                       i, data.ADC_High_TARGET[i] + CW::TARGET_ADC_Thr_HG_Offset, data.ADC_Low_TARGET[i] + CW::TARGET_ADC_Thr_LG_Offset,
                       data.TDC_LE_TARGET[i][0], data.TDC_LE_TARGET[i][1], data.TDC_LE_TARGET[i][2], data.TDC_LE_TARGET[i][3], data.TDC_LE_TARGET[i][4], data.TDC_LE_TARGET[i][5],
                       HG_TARGET_ADC_Thr[i], LG_TARGET_ADC_Thr[i],
                       float(data.ADC_High_TARGET[i] + HG_TARGET_ADC_Thr[i] - round(CW::TARGET_ADC_Ped_HG[i])) / float(data.ADC_Low_TARGET[i] + LG_TARGET_ADC_Thr[i] - round(CW::TARGET_ADC_Ped_LG[i])));
            }
        }
    }

    cout << endl;
    if(Good_Event && (enable_cout==0 || enable_cout==9)){
        if(!NoFile) cout << "//////  TARGET  (WALK CORRECTION APPLIED !)  //////" << endl;
        if(NoFile) cout << "//////  TARGET  //////" << endl;
        cout << "Event: " << ievt << "     ADC Threshold Offset (HG): " << CW::TARGET_ADC_Thr_HG_Offset << "     ADC Threshold Offset (LG): " << CW::TARGET_ADC_Thr_LG_Offset << endl << endl;
        cout << "Fiber  HG-Ped   LG-Ped   T[0]-Av   T[1]-Av   T[2]-Av   T[3]-Av   ADC(HG)   ADC(LG)      TDC    Thr(HG)   Thr(LG)   HG/LG" << endl;
        for(int i=0; i<256; i++){
            //if(data.ADC_High_TARGET[i] > 0 || (data.ADC_Low_TARGET[i] > 0 && Switch==1)){
            if(data.ADC_High_TARGET[i] > 0 || (data.ADC_Low_TARGET[i] > 0)){
                for(int k=0; k<6; k++){
                    if(data.TDC_LE_TARGET[i][k] > -1){
                        TDC_print[i] = data.TDC_LE_TARGET[i][k];
                    }
                }

                printf("%3d     %4d    %4d      %s       %s      %s      %s      %4d      %4d      %4d     %4d      %4d     %2.2f\n",
                       i, data.ADC_High_TARGET[i] + CW::TARGET_ADC_Thr_HG_Offset, data.ADC_Low_TARGET[i] + CW::TARGET_ADC_Thr_LG_Offset,
                       TDC_LE_TARGET_corr[i][0], TDC_LE_TARGET_corr[i][1], TDC_LE_TARGET_corr[i][2], TDC_LE_TARGET_corr[i][3], data.ADC_High_TARGET[i], data.ADC_Low_TARGET[i], TDC_print[i],
                       HG_TARGET_ADC_Thr[i], LG_TARGET_ADC_Thr[i],
                       float(data.ADC_High_TARGET[i] + HG_TARGET_ADC_Thr[i] - round(CW::TARGET_ADC_Ped_HG[i])) / float(data.ADC_Low_TARGET[i] + LG_TARGET_ADC_Thr[i] - round(CW::TARGET_ADC_Ped_LG[i])));
            }
        }
    }

    cout << endl;
    if(Good_Event && enable_cout==2){
        if(!NoFile) cout << "//////  TARGET  (WALK CORRECTION APPLIED !)  //////" << endl;
        if(NoFile) cout << "//////  TARGET  //////" << endl;
        cout << "Event: " << ievt << "     ADC Threshold Offset (HG): " << CW::TARGET_ADC_Thr_HG_Offset << "     ADC Threshold Offset (LG): " << CW::TARGET_ADC_Thr_LG_Offset << endl << endl;
        cout << "Fiber  HG-Ped   LG-Ped   T[0]-Av   T[1]-Av   T[2]-Av   T[3]-Av   T[4]-Av   T[5]-Av   Thr(HG)   Thr(LG)   HG/LG" << endl;
        for(int i=0; i<256; i++){
            printf("%3d     %4d     %4d      %4d      %4d      %4d      %4d      %4d      %4d     %4d      %4d     %2.2f\n",
                   i, data.ADC_High_TARGET[i] + CW::TARGET_ADC_Thr_HG_Offset, data.ADC_Low_TARGET[i] + CW::TARGET_ADC_Thr_LG_Offset,
                   TDC_LE_TARGET_corrected[i][0], TDC_LE_TARGET_corrected[i][1], TDC_LE_TARGET_corrected[i][2], TDC_LE_TARGET_corrected[i][3], TDC_LE_TARGET_corrected[i][4], TDC_LE_TARGET_corrected[i][5],
                   HG_TARGET_ADC_Thr[i], LG_TARGET_ADC_Thr[i],
                   float(data.ADC_High_TARGET[i] + HG_TARGET_ADC_Thr[i] - round(CW::TARGET_ADC_Ped_HG[i])) / float(data.ADC_Low_TARGET[i] + LG_TARGET_ADC_Thr[i] - round(CW::TARGET_ADC_Ped_LG[i])));
            //float(data.ADC_High_TARGET[i] + HG_TARGET_ADC_Thr[i] - round(CW::TARGET_ADC_Ped_HG[i])));
        }
    }

    cout << endl;
}

// TODO: Check if enable_cout is necessary
void printSFTInfo(const DetectorData &data, double ADC_High_SFT_corr[128], int has_TDC_SFT_hit[128]){

    int HG_SFT_ADC_Thr[128];
    int LG_SFT_ADC_Thr[128];

    for(int i=0; i<128; i++)  HG_SFT_ADC_Thr[i] = round(CW::SFT_ADC_Thr_HG[i]) + CW::SFT_ADC_Thr_HG_Offset;
    for(int i=0; i<128; i++)  LG_SFT_ADC_Thr[i] = round(CW::SFT_ADC_Thr_LG[i]) + CW::SFT_ADC_Thr_LG_Offset;

    cout << endl;

    cout << " " << endl;
    cout << " " << endl;
    cout << "//////  SFT  //////" << endl;
    cout << "ADC Threshold Offset (HG): " << CW::SFT_ADC_Thr_HG_Offset << endl;
    cout << "ADC Threshold Offset (LG): " << CW::SFT_ADC_Thr_LG_Offset << endl << endl;
    cout << "Channel   Layer     Fiber     HG-Thr     LG-Thr   TDC[0]    TDC[1]    TDC[2]    TDC[3]   (HG) Thr   (LG) Thr" << endl;
    for(Int_t i=0; i<128; i++){
        if((ADC_High_SFT_corr[i] != 0) && (has_TDC_SFT_hit[i] > 0)){
            printf("%3d       %3d      %3d-%1c      %4d       %4d      %4d     %4d      %4d      %4d       %4d       %4d\n",
                   i, DG::SFT_channel_to_layer[i], DG::SFT_channel_to_fiber[i], DG::SFT_channel_to_US_DS[i], data.ADC_High_SFT[i], data.ADC_Low_SFT[i],
                   data.TDC_LE_SFT[i][0], data.TDC_LE_SFT[i][1], data.TDC_LE_SFT[i][2], data.TDC_LE_SFT[i][3],
                   HG_SFT_ADC_Thr[i], LG_SFT_ADC_Thr[i]);
        }
    }
}

void printMWPCInfo(const DetectorData &data, int selected_TOF2, bool Good_Event,
                   int C2X_clusters, int C2Y_clusters,
                   int C3X_clusters, int C3Y_clusters,
                   int C4X_clusters, int C4Y_clusters){

    cout << endl;

    if(selected_TOF2 > 6){ //LEFT
        for(int i=0; i<56; i++){ // C2 Counters
            if(Good_Event && data.ADC_C2X_L[i]>0){
                cout << " ADC MWPC Channel " << DG::C2XL_Channels[i] << " -- " << "C2_X_" << i+1 << "_Left: " << int(data.ADC_C2X_L[i]) << endl;
            }
        }
        for(int i=0; i<16; i++){
            if(Good_Event && data.ADC_C2Y_L[i]>0){
                cout << " ADC MWPC Channel " << DG::C2YL_Channels[i] << " -- " << "C2_Y_" << i+1 << "_Left: " << int(data.ADC_C2Y_L[i]) << endl;
            }
        }

        cout << " " << endl;

        for(int i=0; i<64; i++){ // C3 Counters
            if(Good_Event && data.ADC_C3X_L[i]>0){
                cout << " ADC MWPC Channel " << DG::C3XL_Channels[i] << " -- " << "C3_X_" << i+1 << "_Left: " << int(data.ADC_C3X_L[i]) << endl;
            }
        }
        for(int i=0; i<16; i++){
            if(Good_Event && data.ADC_C3Y_L[i]>0){
                cout << " ADC MWPC Channel " << DG::C3YL_Channels[i] << " -- " << "C3_Y_" << i+1 << "_Left: " << int(data.ADC_C3Y_L[i]) << endl;
            }
        }

        cout << " " << endl;

        for(int i=0; i<72; i++){ // C4 Counters
            if(Good_Event && data.ADC_C4X_L[i]>0){
                cout << " ADC MWPC Channel " << DG::C4XL_Channels[i] << " -- " << "C4_X_" << i+1 << "_Left: " << int(data.ADC_C4X_L[i]) << endl;
            }
        }
        for(int i=0; i<16; i++){
            if(Good_Event && data.ADC_C4Y_L[i]>0){
                cout << " ADC MWPC Channel " << DG::C4YL_Channels[i] << " -- " << "C4_Y_" << i+1 << "_Left: " << int(data.ADC_C4Y_L[i]) << endl;
            }
        }
    }
    else{
        for(int i=0; i<56; i++){ // C2 Counters
            if(Good_Event && data.ADC_C2X_R[i]>0){
                cout << " ADC MWPC Channel " << DG::C2XR_Channels[i] << " -- " << "C2_X_" << i+1 << "_Right: " << int(data.ADC_C2X_R[i]) << endl;
            }
        }
        for(int i=0; i<16; i++){
            if(Good_Event && data.ADC_C2Y_R[i]>0){
                cout << " ADC MWPC Channel " << DG::C2YR_Channels[i] << " -- " << "C2_Y_" << i+1 << "_Right: " << int(data.ADC_C2Y_R[i]) << endl;
            }
        }

        cout << " " << endl;

        for(int i=0; i<64; i++){ // C3 Counters
            if(Good_Event && data.ADC_C3X_R[i]>0){
                cout << " ADC MWPC Channel " << DG::C3XR_Channels[i] << " -- " << "C3_X_" << i+1 << "_Right: " << int(data.ADC_C3X_R[i]) << endl;
            }
        }
        for(int i=0; i<16; i++){
            if(Good_Event && data.ADC_C3Y_R[i]>0){
                cout << " ADC MWPC Channel " << DG::C3YR_Channels[i] << " -- " << "C3_Y_" << i+1 << "_Right: " << int(data.ADC_C3Y_R[i]) << endl;
            }
        }

        cout << " " << endl;

        for(int i=0; i<72; i++){ // C4 Counters
            if(Good_Event && data.ADC_C4X_R[i]>0){
                cout << " ADC MWPC Channel " << DG::C4XR_Channels[i] << " -- " << "C4_X_" << i+1 << "_Right: " << int(data.ADC_C4X_R[i]) << endl;
            }
        }
        for(int i=0; i<16; i++){
            if(Good_Event && data.ADC_C4Y_R[i]>0){
                cout << " ADC MWPC Channel " << DG::C4YR_Channels[i] << " -- " << "C4_Y_" << i+1 << "_Right: " << int(data.ADC_C4Y_R[i]) << endl;
            }
        }
    }

    cout << endl;
    if(selected_TOF2 > 6) cout << " LEFT" << endl;
    else cout << " RIGHT" << endl;

    cout << " C2X clusters = " << C2X_clusters << endl;
    cout << " C2Y clusters = " << C2Y_clusters << endl;
    cout << " C3X clusters = " << C3X_clusters << endl;
    cout << " C3Y clusters = " << C3Y_clusters << endl;
    cout << " C4X clusters = " << C4X_clusters << endl;
    cout << " C4Y clusters = " << C4Y_clusters << endl;

    cout << endl;
}

void printCherenkovInfo(const DetectorData &data, int TDC_average,
                        vector<double> vec_Ck, double TDC_ck_avg, double TDC_ck_sigma,
                        vector<double> vec_Cpi, double TDC_cpi_avg, double TDC_cpi_sigma,
                        int TDC_ck_counter, double TDC_ck_avg2,
                        int TDC_cpi_counter, double TDC_cpi_avg2){

    cout << endl;

    cout << "//////  C_k / C_pi  //////" << endl;
    cout << "Counter       TDC[0]           TDC[1]           TDC[2]           TDC[3]           TDC[4]           TDC[5]" << endl;
    for(int i=0; i<14; i++){
        printf("%3d        %4d / %4d      %4d / %4d      %4d / %4d      %4d / %4d      %4d / %4d      %4d / %4d\n",
               i,
               data.TDC_Ck[i][0], data.TDC_Cpi[i][0], data.TDC_Ck[i][1], data.TDC_Cpi[i][1], data.TDC_Ck[i][2], data.TDC_Cpi[i][2],
               data.TDC_Ck[i][3], data.TDC_Cpi[i][3], data.TDC_Ck[i][4], data.TDC_Cpi[i][4], data.TDC_Ck[i][5], data.TDC_Cpi[i][5]);
    }

    cerr << endl;
    cerr << "N(Ck) = " << vec_Ck.size() << "   " << "TDC Ck Avg. = " << TDC_ck_avg << "   " << "Var(Ck) = " << TDC_ck_sigma << "   " << "Sigma(Ck) = " << TDC_ck_sigma/sqrt(vec_Ck.size()) << endl;
    cerr << "N(Cpi) =  " << vec_Cpi.size() << "   " << "TDC Cpi Avg. = " << TDC_cpi_avg << "   " << "Var(Cpi) = " << TDC_cpi_sigma << "   " << "Sigma(Cpi) = " << TDC_cpi_sigma/sqrt(vec_Cpi.size()) << endl;
    cerr << endl;
    cerr << "N'(Ck) = " << TDC_ck_counter << "   " << "TDC'(Ck) = " << TDC_ck_avg2 << endl;
    cerr << "N'(Cpi) = " << TDC_cpi_counter << "   " << "TDC'(Cpi) = " << TDC_cpi_avg2 << endl;
    cerr << endl;
    cerr << "TDC Mean Ck - TDC Average = " << TDC_ck_avg2 - TDC_average << endl;
    cerr << endl;

    cout << endl;
}

void printCkCorrectedTDC(const DetectorData &data, vector<int> vec_TARGET_bar_selected,
                         double TDC_ck_avg2){

    int n_bar_selected = vec_TARGET_bar_selected.size();
    char TDC_LE_TARGET_sel_string[n_bar_selected][16][20];

    for(unsigned int i = 0; i<vec_TARGET_bar_selected.size(); i++) {
        for (int j = 0; j < 16; j++) {
            if (data.TDC_LE_TARGET[vec_TARGET_bar_selected[i]][j] > 0) {
                sprintf(TDC_LE_TARGET_sel_string[i][j], "%5.1f",
                        550 -(0.91 * data.TDC_LE_TARGET[vec_TARGET_bar_selected[i]][j]
                              - 0.625 * (data.VT48_TDC[0][0] - TDC_ck_avg2)));
            }
            else sprintf(TDC_LE_TARGET_sel_string[i][j], "-----");
        }
    }


    cout << endl;

    cout << "////// TDC TARGET - TDC Ck (corrected)  //////" << endl;
    cout << "Fiber  HG-Ped   LG-Ped     T[0]-Ck    T[1]-Ck    T[2]-Ck    T[3]-Ck    T[4]-Ck    T[5]-Ck" << endl;
    for(unsigned int i=0; i<vec_TARGET_bar_selected.size(); i++){
        printf("%3d     %4d    %4d        %s      %s      %s      %s      %s      %s\n",
               vec_TARGET_bar_selected[i],
               data.ADC_High_TARGET[vec_TARGET_bar_selected[i]] + CW::TARGET_ADC_Thr_HG_Offset,
               data.ADC_Low_TARGET[vec_TARGET_bar_selected[i]] + CW::TARGET_ADC_Thr_LG_Offset,
               TDC_LE_TARGET_sel_string[i][0], TDC_LE_TARGET_sel_string[i][1], TDC_LE_TARGET_sel_string[i][2],
               TDC_LE_TARGET_sel_string[i][3], TDC_LE_TARGET_sel_string[i][4], TDC_LE_TARGET_sel_string[i][5]);
    }

    cout << endl;
}

void printGapScoring(const DetectorData &data, int TOF2_counter, bool Good_Event){

    cout << endl;

    determineTOF1Gap(data, TOF2_counter, true);

    cout << endl;

    for (Int_t i = 0; i<12; i++){
        if(Good_Event){
            if (data.ADC_TOF1[i] > 0 || data.ADC_TOF1[i+12] > 0){
                if((data.TDC_TOF1U[i] > CW::TOF1U_TDC_min[i] && data.TDC_TOF1U[i] < CW::TOF1U_TDC_max[i]) ||
                   (data.TDC_TOF1D[i] > CW::TOF1D_TDC_min[i] && data.TDC_TOF1D[i] < CW::TOF1D_TDC_max[i])){
                    printf("ADC TOF1 Up-%2d: %5d -- Down-%2d: %5d  |  TDC TOF1 Up-%2d: %5d -- Down-%2d: %5d\n",
                           i+1, data.ADC_TOF1[i], i+1, data.ADC_TOF1[i+12], i+1, data.TDC_TOF1U[i], i+1, data.TDC_TOF1D[i]);
                }
                else {
                    printf("ADC TOF1 Up-%2d: %5d -- Down-%2d: %5d  |\n", i+1, data.ADC_TOF1[i], i+1, data.ADC_TOF1[i+12]);
                }
            }
            else {
                if((data.TDC_TOF1U[i] > CW::TOF1U_TDC_min[i] && data.TDC_TOF1U[i] < CW::TOF1U_TDC_max[i]) ||
                   (data.TDC_TOF1D[i] > CW::TOF1D_TDC_min[i] && data.TDC_TOF1D[i] < CW::TOF1D_TDC_max[i])){
                    printf("                                         |  TDC TOF1 Up-%2d: %5d -- Down-%2d: %5d\n", i+1, data.TDC_TOF1U[i], i+1, data.TDC_TOF1D[i]);
                }
            }
        }
    }

    cout << "" << endl;

    for (Int_t i = 0; i<12; i++) {
        if (data.ADC_TOF2AO[i] > 0 || data.ADC_TOF2AI[i] > 0){
            if ((data.TDC_TOF2AO[i] > CW::TOF2AO_TDC_min[i] && data.TDC_TOF2AO[i] < CW::TOF2AO_TDC_max[i]) ||
                (data.TDC_TOF2AI[i] > CW::TOF2AI_TDC_min[i] && data.TDC_TOF2AI[i] < CW::TOF2AI_TDC_max[i])) {
                printf("ADC TOF2 OutA-%2d: %5d -- InA-%2d: %5d  |  TDC TOF2 OutA-%2d: %5d -- InA-%2d: %5d\n",
                       i+1, data.ADC_TOF2AO[i], i+1, data.ADC_TOF2AI[i], i+1, data.TDC_TOF2AO[i], i+1, data.TDC_TOF2AI[i]);
            }
            else{
                printf("ADC TOF2 OutA-%2d: %5d -- InA-%2d: %5d  |\n", i+1, data.ADC_TOF2AO[i], i+1, data.ADC_TOF2AI[i]);
            }
        }
        else {
            if((data.TDC_TOF2AO[i] > CW::TOF2AO_TDC_min[i] && data.TDC_TOF2AO[i] < CW::TOF2AO_TDC_max[i]) ||
               (data.TDC_TOF2AI[i] > CW::TOF2AI_TDC_min[i] && data.TDC_TOF2AI[i] < CW::TOF2AI_TDC_max[i])) {
                printf("                                        |  TDC TOF2 OutA-%2d: %5d -- InA-%2d: %5d\n", i+1, data.TDC_TOF2AO[i], i+1, data.TDC_TOF2AI[i]);
            }
        }
    }


    for (Int_t i = 0; i<12; i++){
        if (i == 6) {
            if (data.ADC_TOF2BO[i] > 0 || data.ADC_TOF2BO[i] > 0) {
                if ((data.TDC_TOF2BO[6] > CW::TOF2BO_TDC_min[6] && data.TDC_TOF2BO[6] < CW::TOF2BO_TDC_max[6]) ||
                    (data.TDC_TOF2BI[6] > CW::TOF2BI_TDC_min[6] && data.TDC_TOF2BI[6] < CW::TOF2BI_TDC_max[6])) {
                    printf("ADC TOF2 OutB-%2d: %5d -- InB-%2d: %5d  |  TDC TOF2 OutB-%2d: %5d -- InB-%2d: %5d\n",
                           i+1, data.ADC_TOF2BO[i], i+1, data.ADC_TOF2BI[i], i+1, data.TDC_TOF2BO[i], i+1, data.TDC_TOF2BI[i]);
                }
                else{
                    cout << "ADC TOF2 OutB-" << i+1 << ": " << data.ADC_TOF2BO[i] << " -- InB-" << i+1 << ": " << data.ADC_TOF2BI[i] << endl;
                    printf("ADC TOF2 OutB-%2d: %5d -- InB-%2d: %5d  |\n", i+1, data.ADC_TOF2BO[i], i+1, data.ADC_TOF2BI[i]);
                }
            }
            else {
                if((data.TDC_TOF2BO[6] > CW::TOF2BO_TDC_min[6] && data.TDC_TOF2BO[6] > CW::TOF2BO_TDC_max[6]) ||
                   (data.TDC_TOF2BI[6] > CW::TOF2BI_TDC_min[6] && data.TDC_TOF2BI[6] > CW::TOF2BI_TDC_max[6])) {
                    printf("                                        |  TDC TOF2 OutB-%2d: %5d -- InB-%2d: %5d\n", i+1, data.TDC_TOF2BO[i], i+1, data.TDC_TOF2BI[i]);
                }
            }
        }
        else {
            if(data.ADC_TOF2BO[i] > 0 || data.ADC_TOF2BI[i] > 0) {
                if((data.TDC_TOF2BO[i] > CW::TOF2BO_TDC_min[i] && data.TDC_TOF2BO[i] < CW::TOF2BO_TDC_max[i]) ||
                   (data.TDC_TOF2BI[i] > CW::TOF2BI_TDC_min[i] && data.TDC_TOF2BI[i] < CW::TOF2BI_TDC_max[i])) {
                    printf("ADC TOF2 OutB-%2d: %5d -- InB-%2d: %5d  |  TDC TOF2 OutB-%2d: %5d -- InB-%2d: %5d\n",
                           i+1, data.ADC_TOF2BO[i], i+1, data.ADC_TOF2BI[i], i+1, data.TDC_TOF2BO[i], i+1, data.TDC_TOF2BI[i]);
                }
                else {
                    printf("ADC TOF2 OutB-%2d: %5d -- InB-%2d: %5d  |\n", i+1, data.ADC_TOF2BO[i], i+1, data.ADC_TOF2BI[i]);
                }
            }
            else {
                if((data.TDC_TOF2BO[i] > CW::TOF2BO_TDC_min[i] && data.TDC_TOF2BO[i] < CW::TOF2BO_TDC_max[i]) ||
                   (data.TDC_TOF2BI[i] > CW::TOF2BI_TDC_min[i] && data.TDC_TOF2BI[i] < CW::TOF2BI_TDC_max[i])) {
                    printf("                                        |  TDC TOF2 OutB-%2d: %5d -- InB-%2d: %5d\n", i+1, data.TDC_TOF2BO[i], i+1, data.TDC_TOF2BI[i]);
                }
            }
        }
    }

    cout << endl;
}

void printTrackInfo(double angle_final, double delta_phi_deg, double ChiS_final, int ndf_final,
                    vector<double> vec_XX_int_SFT, vector<double> vec_YY_int_SFT,
                    vector<double> vec_XX_int_TOF1, vector<double> vec_YY_int_TOF1,
                    double Length_in_target){

    cout << endl;

    cerr << "Final Angle (deg.) = " << angle_final << " +- " << delta_phi_deg << "  ( GUIDE )" << endl;
    cerr << "Chi Square = " << ChiS_final << endl;
    cerr << "NdF = " << ndf_final << endl;
    cerr << "Reduced Chi Square = " << ChiS_final/ndf_final << endl;
    cerr << "" << endl;
    cerr << "" << endl;

    cerr << "Intersect with SFT Layer 1:  " << "x = " << vec_XX_int_SFT[0] << "   " << "y = " << vec_YY_int_SFT[0] << endl;
    cerr << "Intersect with TOF1:  " << "x = " << vec_XX_int_TOF1[0] << "   " << "y = " << vec_YY_int_TOF1[0] << endl;
    cerr << endl;

    printf("Length of track in target (xy plane) = %5.2f\n", Length_in_target);

    cout << endl;
}

void printTrackList(int run_number, int event_number, int Event_flag, int gap_to_fit, int selected_TOF2, int extra_TOF1,
                    double angle_final, double delta_phi_deg, double delta_X, double delta_Y,
                    double ChiS_final, int ndf_final, int Lepton_counter,
                    double vec_XX_int_TARGET, double vec_YY_int_TARGET,
                    double vec_XX_int_SFT, double vec_YY_int_SFT,
                    double N_centroid_X, double N_centroid_Y,
                    double vec_xx_fit_lines_intersect, double vec_yy_fit_lines_intersect,
                    double vec_xx_kstop_FINAL, double vec_yy_kstop_FINAL,
                    double R_Kstop, int i_kaon_bar, int kaon_bar_size,
                    double ChiS_kaon_final, int ndf_kaon_final,
                    int vec_Ck_size, int vec_Cpi_size,
                    double length_in_target, double C2X_centroid, double TDC_diff, int sum_ADC_HG_lepton,
                    double Average_TDC_lepton, double Average_TDC_kaon,
                    bool HasEdgeBars, bool IsGoodTOF1,
                    PruningType type, bool batch_mode, bool print_to_console){

    //cout << endl;

    if(batch_mode || print_to_console){
        cout << fixed;
        cout << setw(4) << run_number << " ";
        cout << setw(7) << event_number << " ";
        cout << setw(2) << Event_flag << " ";
        cout << setw(2) << gap_to_fit << " ";
        cout << setw(2) << selected_TOF2 << " ";
        cout << setw(2) << extra_TOF1 << " ";
        cout << setw(6) << setprecision(2) << angle_final << " ";
        cout << setw(6) << setprecision(2) << delta_phi_deg << " ";
        cout << setw(6) << setprecision(2) << delta_X << " ";
        cout << setw(6) << setprecision(2) << delta_Y << " ";
        cout << setw(7) << setprecision(2) << ChiS_final << " ";
        cout << setw(3) << setprecision(0) << ndf_final << " ";
        cout << setw(6) << setprecision(2) << ChiS_final/ndf_final << " ";
        cout << setw(3) << Lepton_counter << "  ";
        cout << setw(6) << setprecision(2) << vec_XX_int_TARGET << " ";
        cout << setw(6) << setprecision(2) << vec_YY_int_TARGET << " " ;
        cout << setw(6) << setprecision(2) << vec_XX_int_SFT << " ";
        cout << setw(6) << setprecision(2) << vec_YY_int_SFT << " " ;       
        cout << setw(7) << setprecision(2) << N_centroid_X << " ";
        cout << setw(7) << setprecision(2) << N_centroid_Y << " ";
        cout << setw(7) << setprecision(2) << vec_xx_fit_lines_intersect << " ";
        cout << setw(7) << setprecision(2) << vec_yy_fit_lines_intersect << " ";
        cout << setw(7) << setprecision(2) << vec_xx_kstop_FINAL << " ";             // 21
        cout << setw(7) << setprecision(2) << vec_yy_kstop_FINAL << " ";
        cout << setw(7) << setprecision(2) << R_Kstop << " ";             // 22
        cout << setw(3) << i_kaon_bar << " ";
        cout << setw(3) << kaon_bar_size << " ";
        cout << setw(5) << setprecision(2) << ChiS_kaon_final/ndf_kaon_final << " ";
        cout << setw(3) << vec_Ck_size << " ";
        cout << setw(3) << vec_Cpi_size << " ";
        cout << setw(7) << setprecision(2) << length_in_target << " ";
        cout << setw(7) << setprecision(2) << C2X_centroid << " ";
        cout << setw(6) << setprecision(1) << TDC_diff << " ";
        cout << setw(6) <<  sum_ADC_HG_lepton << " ";
        cout << setw(7) << setprecision(2) << Average_TDC_lepton << " ";
        cout << setw(7) << setprecision(2) << Average_TDC_kaon << " ";
        cout << setw(1) << setprecision(0) << HasEdgeBars << " ";
        cout << setw(1) << setprecision(0) << IsGoodTOF1 << " ";
        cout << endl;
    }

    if(!batch_mode){
        switch (type){
            case line : 
            cout << "LINE PRUNING USED" << endl;
            break;

            case triangle :
            cout << "TRIANGLE PRUNING USED" << endl;
            break;

            case backtracking :
            cout << "BACKTRACKING METHOD USED" << endl;
            break;
        }
    }

    //cout << endl;
    //cout << endl;
}

