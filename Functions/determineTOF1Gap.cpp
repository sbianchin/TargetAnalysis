/*
 * Created by Jack Hong on 2018-05-28. (jhong@alumni.ubc.ca)
 *
 * Determine the TOF1 gap
 *
 */

#include <iostream>

#include "determineTOF1Gap.hpp"
#include "CommonParameters.hpp"
#include "CutsAndWindows.hpp"
#include "DetectorGeometry.hpp"

namespace CP = CommonParameters;
namespace CW = CutsAndWindows;
namespace DG = DetectorGeometry;


vector<int> determineTOF1Gap(const DetectorData &data, int TOF2_counter, bool printout) {

    int gap_counter[12] = {0};
    int high_gap_hit = 0;
    int gap_to_fit = 0;
    int gap_to_fit_rotated = 99;
    int score_max = 0;
    vector<int> GAP_TO_FIT;

    for (int gap=0; gap<12; gap++) {
        if (data.ADC_TOF1U[gap] >= 30)gap_counter[gap]++;
        if (data.ADC_TOF1D[gap] >= 30) gap_counter[gap]++;
        if (data.TDC_TOF1U[gap] >= CW::TOF1U_TDC_min[gap] && data.TDC_TOF1U[gap] <= CW::TOF1U_TDC_max[gap]) gap_counter[gap]++;
        if (data.TDC_TOF1D[gap] >= CW::TOF1D_TDC_min[gap] && data.TDC_TOF1D[gap] <= CW::TOF1D_TDC_max[gap]) gap_counter[gap]++;
        if ((data.TDC_TOF1U[gap] >= CW::TOF1U_TDC_min[gap] && data.TDC_TOF1U[gap] <= CW::TOF1U_TDC_max[gap]) &&
            (data.TDC_TOF1D[gap] >= CW::TOF1D_TDC_min[gap] && data.TDC_TOF1D[gap] <= CW::TOF1D_TDC_max[gap])) gap_counter[gap]++;
        if ((data.TDC_TOF1U[gap] >= CW::TOF1U_TDC_min[gap] && data.TDC_TOF1U[gap] <= CW::TOF1U_TDC_max[gap]) &&
            (data.TDC_TOF1D[gap] >= CW::TOF1D_TDC_min[gap] && data.TDC_TOF1D[gap] <= CW::TOF1D_TDC_max[gap]) &&
            (data.ADC_TOF1U[gap] >= 30 && data.ADC_TOF1D[gap] >= 30)) gap_counter[gap]++;
    }

    for (int gap = 0; gap < 12; gap++) {
        if (gap != 0 && gap != 11 && gap_counter[gap] > 0) {

            if (data.ADC_TOF2AO[gap] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2AO[gap - 1] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2AO[gap + 1] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2AI[gap] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2AI[gap - 1] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2AI[gap + 1] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2BO[gap] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2BO[gap - 1] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2BO[gap + 1] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2BI[gap] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2BI[gap - 1] >= 0) gap_counter[gap]++;
            if (data.ADC_TOF2BI[gap + 1] >= 0) gap_counter[gap]++;

            if (data.TDC_TOF2AO[gap] >= CW::TOF2AO_TDC_min[gap] && data.TDC_TOF2AO[gap] <= CW::TOF2AO_TDC_max[gap]) gap_counter[gap]++;
            if (data.TDC_TOF2AO[gap - 1] >= CW::TOF2AO_TDC_min[gap - 1] && data.TDC_TOF2AO[gap - 1] <= CW::TOF2AO_TDC_max[gap - 1]) gap_counter[gap]++;
            if (data.TDC_TOF2AO[gap + 1] >= CW::TOF2AO_TDC_min[gap + 1] && data.TDC_TOF2AO[gap + 1] <= CW::TOF2AO_TDC_max[gap + 1]) gap_counter[gap]++;
            if (data.TDC_TOF2AI[gap] >= CW::TOF2AI_TDC_min[gap] && data.TDC_TOF2AI[gap] <= CW::TOF2AI_TDC_max[gap]) gap_counter[gap]++;
            if (data.TDC_TOF2AI[gap - 1] >= CW::TOF2AI_TDC_min[gap - 1] && data.TDC_TOF2AI[gap - 1] <= CW::TOF2AI_TDC_max[gap - 1]) gap_counter[gap]++;
            if (data.TDC_TOF2AI[gap + 1] >= CW::TOF2AI_TDC_min[gap + 1] && data.TDC_TOF2AI[gap + 1] <= CW::TOF2AI_TDC_max[gap + 1]) gap_counter[gap]++;
            if (data.TDC_TOF2BO[gap] >= CW::TOF2BO_TDC_min[gap] && data.TDC_TOF2BO[gap] <= CW::TOF2BO_TDC_max[gap]) gap_counter[gap]++;
            if (data.TDC_TOF2BO[gap - 1] >= CW::TOF2BO_TDC_min[gap - 1] && data.TDC_TOF2BO[gap - 1] <= CW::TOF2BO_TDC_max[gap - 1]) gap_counter[gap]++;
            if (data.TDC_TOF2BO[gap + 1] >= CW::TOF2BO_TDC_min[gap + 1] && data.TDC_TOF2BO[gap + 1] <= CW::TOF2BO_TDC_max[gap + 1]) gap_counter[gap]++;
            if (data.TDC_TOF2BI[gap] >= CW::TOF2BI_TDC_min[gap] && data.TDC_TOF2BI[gap] <= CW::TOF2BI_TDC_max[gap]) gap_counter[gap]++;
            if (data.TDC_TOF2BI[gap - 1] >= CW::TOF2BI_TDC_min[gap - 1] && data.TDC_TOF2BI[gap - 1] <= CW::TOF2BI_TDC_max[gap - 1]) gap_counter[gap]++;
            if (data.TDC_TOF2BI[gap + 1] >= CW::TOF2BI_TDC_min[gap + 1] && data.TDC_TOF2BI[gap + 1] <= CW::TOF2BI_TDC_max[gap + 1]) gap_counter[gap]++;
        }
    }

    if (gap_counter[0] > 0) {
        if (data.ADC_TOF2AO[0] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2AO[1] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2AO[11] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2AI[0] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2AI[1] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2AI[11] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2BO[0] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2BO[1] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2BO[11] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2BI[0] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2BI[1] >= 0) gap_counter[0]++;
        if (data.ADC_TOF2BI[11] >= 0) gap_counter[0]++;
        if (data.TDC_TOF2AO[0] >= CW::TOF2AO_TDC_min[0] && data.TDC_TOF2AO[0] <= CW::TOF2AO_TDC_max[0]) gap_counter[0]++;
        if (data.TDC_TOF2AO[1] >= CW::TOF2AO_TDC_min[1] && data.TDC_TOF2AO[1] <= CW::TOF2AO_TDC_max[1]) gap_counter[0]++;
        if (data.TDC_TOF2AO[11] >= CW::TOF2AO_TDC_min[11] && data.TDC_TOF2AO[11] <= CW::TOF2AO_TDC_max[11]) gap_counter[0]++;
        if (data.TDC_TOF2AI[0] >= CW::TOF2AI_TDC_min[0] && data.TDC_TOF2AI[0] <= CW::TOF2AI_TDC_max[0]) gap_counter[0]++;
        if (data.TDC_TOF2AI[1] >= CW::TOF2AI_TDC_min[1] && data.TDC_TOF2AI[1] <= CW::TOF2AI_TDC_max[1]) gap_counter[0]++;
        if (data.TDC_TOF2AI[11] >= CW::TOF2AI_TDC_min[11] && data.TDC_TOF2AI[11] <= CW::TOF2AI_TDC_max[11]) gap_counter[0]++;
        if (data.TDC_TOF2BO[0] >= CW::TOF2BO_TDC_min[0] && data.TDC_TOF2BO[0] <= CW::TOF2BO_TDC_max[0]) gap_counter[0]++;
        if (data.TDC_TOF2BO[1] >= CW::TOF2BO_TDC_min[1] && data.TDC_TOF2BO[1] <= CW::TOF2BO_TDC_max[1]) gap_counter[0]++;
        if (data.TDC_TOF2BO[11] >= CW::TOF2BO_TDC_min[11] && data.TDC_TOF2BO[11] <= CW::TOF2BO_TDC_max[11]) gap_counter[0]++;
        if (data.TDC_TOF2BI[0] >= CW::TOF2BI_TDC_min[0] && data.TDC_TOF2BI[0] <= CW::TOF2BI_TDC_max[0]) gap_counter[0]++;
        if (data.TDC_TOF2BI[1] >= CW::TOF2BI_TDC_min[1] && data.TDC_TOF2BI[1] <= CW::TOF2BI_TDC_max[1]) gap_counter[0]++;
        if (data.TDC_TOF2BI[11] >= CW::TOF2BI_TDC_min[11] && data.TDC_TOF2BI[11] <= CW::TOF2BI_TDC_max[11]) gap_counter[0]++;
    }

    if (gap_counter[11] > 0) {
        if (data.ADC_TOF2AO[11] >= 0) gap_counter[11]++;
        if (data.ADC_TOF2AO[10] >= 0) gap_counter[11]++;
        if (data.ADC_TOF2AO[0] >= 0) gap_counter[11]++;

        if (data.ADC_TOF2AI[11] >= 0) gap_counter[11]++;
        if (data.ADC_TOF2AI[10] >= 0) gap_counter[11]++;
        if (data.ADC_TOF2AI[0] >= 0) gap_counter[11]++;

        if (data.ADC_TOF2BO[11] >= 0) gap_counter[11]++;
        if (data.ADC_TOF2BO[10] >= 0) gap_counter[11]++;
        if (data.ADC_TOF2BO[0] >= 0) gap_counter[11]++;

        if (data.ADC_TOF2BI[11] >= 0) gap_counter[11]++;
        if (data.ADC_TOF2BI[10] >= 0) gap_counter[11]++;
        if (data.ADC_TOF2BI[0] >= 0) gap_counter[11]++;

        if (data.TDC_TOF2AO[11] >= CW::TOF2AO_TDC_min[11] && data.TDC_TOF2AO[11] <= CW::TOF2AO_TDC_max[11]) gap_counter[11]++;
        if (data.TDC_TOF2AO[10] >= CW::TOF2AO_TDC_min[10] && data.TDC_TOF2AO[10] <= CW::TOF2AO_TDC_max[10]) gap_counter[11]++;
        if (data.TDC_TOF2AO[0] >= CW::TOF2AO_TDC_min[0] && data.TDC_TOF2AO[0] <= CW::TOF2AO_TDC_max[0]) gap_counter[11]++;

        if (data.TDC_TOF2AI[11] >= CW::TOF2AI_TDC_min[11] && data.TDC_TOF2AI[11] <= CW::TOF2AI_TDC_max[11]) gap_counter[11]++;
        if (data.TDC_TOF2AI[10] >= CW::TOF2AI_TDC_min[10] && data.TDC_TOF2AI[10] <= CW::TOF2AI_TDC_max[10]) gap_counter[11]++;
        if (data.TDC_TOF2AI[0] >= CW::TOF2AI_TDC_min[0] && data.TDC_TOF2AI[0] <= CW::TOF2AI_TDC_max[0]) gap_counter[11]++;

        if (data.TDC_TOF2BO[11] >= CW::TOF2BO_TDC_min[11] && data.TDC_TOF2BO[11] <= CW::TOF2BO_TDC_max[11]) gap_counter[11]++;
        if (data.TDC_TOF2BO[10] >= CW::TOF2BO_TDC_min[10] && data.TDC_TOF2BO[10] <= CW::TOF2BO_TDC_max[10]) gap_counter[11]++;
        if (data.TDC_TOF2BO[0] >= CW::TOF2BO_TDC_min[0] && data.TDC_TOF2BO[0] <= CW::TOF2BO_TDC_max[0]) gap_counter[11]++;

        if (data.TDC_TOF2BI[11] >= CW::TOF2BI_TDC_min[11] && data.TDC_TOF2BI[11] <= CW::TOF2BI_TDC_max[11]) gap_counter[11]++;
        if (data.TDC_TOF2BI[10] >= CW::TOF2BI_TDC_min[10] && data.TDC_TOF2BI[10] <= CW::TOF2BI_TDC_max[10]) gap_counter[11]++;
        if (data.TDC_TOF2BI[0] >= CW::TOF2BI_TDC_min[0] && data.TDC_TOF2BI[0] <= CW::TOF2BI_TDC_max[0]) gap_counter[11]++;
    }

    std::vector<int> tof1Ties;

    vector<int> tof1_ties;
    tof1_ties.clear();

    for (int gap = 0; gap < 12; gap++){

        if (gap_counter[gap] >= high_gap_hit) {
            if (gap_counter[gap] == high_gap_hit) tof1_ties.push_back(gap);
            else {
                tof1_ties.clear();
                tof1_ties.push_back(gap);
            }
            high_gap_hit = gap_counter[gap];
        }
    }

    bool tie_breaker = false;
    bool has_TDC_hit[256] = {false};


    if (tof1_ties.size() > 1) {  // only when there are more than 2 elements in tof1_ties!
        tie_breaker = true;
        for (unsigned int j = 0; j < tof1_ties.size(); j++) {
            for (int jj = 0; jj < 12; jj++) {
                if (data.ADC_High_TARGET[DG::channel[tof1_ties[j]][jj]] >= 0) {
                    gap_counter[tof1_ties[j]]++;
                    if (has_TDC_hit[DG::channel[tof1_ties[j]][jj]]) gap_counter[tof1_ties[j]]++;
                } else {
                    if (data.ADC_Low_TARGET[DG::channel[tof1_ties[j]][jj]] > 0) gap_counter[tof1_ties[j]]++;
                }
            }
        }
    }

    for (int gap = 0; gap < 12; gap++) {

        if(gap_counter[gap] > score_max) {
            score_max = gap_counter[gap];
            gap_to_fit = gap + 1;
        }
    }
    
    if(printout){
        cout << "//////  TOF1 SCORING  //////" << endl;
        for(int i=0; i<12; i++){
            cout << "TOF1 score" << i+1 << ": " << gap_counter[i] << endl; 
        } 
        cout << endl;
        cout << "TOF1 SELECTED FOR FITTING:  TOF1 " << gap_to_fit << endl;
    }


    gap_to_fit_rotated = DG::TOF1_rotated[gap_to_fit - 1] + 1;

    GAP_TO_FIT.push_back(gap_to_fit);

    bool k_stop_bar[256] = {false};
    bool k_stop_bar_initial[256] = {false};
    vector<int> good_k_stop_bars;

    for (int jj = 0; jj < 256; jj++) {
        k_stop_bar[jj] = false;
        k_stop_bar_initial[jj] = false;
    }

    good_k_stop_bars.clear();
    vector<int> vec_TARGET_bar_selected;
    bool has_TDC_hit_Kstop[256] = {false};

    for (int gap = 0; gap < 256; gap++) {
        if (data.ADC_High_TARGET[gap] > 0 || data.ADC_Low_TARGET[gap] > 0) vec_TARGET_bar_selected.push_back(gap);
        if (data.ADC_High_TARGET[gap] > CW::HG_KAON && data.ADC_Low_TARGET[gap] > CW::LG_KAON && has_TDC_hit_Kstop[gap]) {
            good_k_stop_bars.push_back(gap);
            k_stop_bar[gap] = true;
            k_stop_bar_initial[gap] = true;
        }
    }

    vector<int> vec_extra_TOF1;
    for(int i=0; i<12; i++){
        if(i != gap_to_fit-1){
            if(i+1 != TOF2_counter-1 && i+1 != TOF2_counter && i+1 != TOF2_counter+1){
                if(gap_counter[i] >= 3){
                    GAP_TO_FIT.push_back(i+1);
                }
            }
        }
    }

    return GAP_TO_FIT;
}