/* 
 * Created by Sebastien Bianchin on 2018-07-31. (s.bianchin@triumf.ca)
 */

#ifndef MACROS_PLOTEVENT2_H
#define MACROS_PLOTEVENT2_H

#include "TLine.h"
#include "TGraph.h"

#include "DetectorData.hpp"
#include "DisplayEvent.h"
#include "TargetBar.hpp"

int kaonFiber(double x_bar, double y_bar);

void drawPruning(int Run_Number, int ievt, vector<int> vec_kaons,
                 vector<double> vec_kstop_0,
                 vector<int> vec_triangle_leptons, vector<int> vec_line_leptons, vector<int> vec_pruned_backtracking,
                 vector<double> V_X_pruning_area, vector<double> V_Y_pruning_area,
                 TLine *line_fit_kaons, TLine *line_fit_leptons,
                 vector<double> vec_pruning_line1, vector<double> vec_pruning_line2,
                 TGraph *gr_kaons_final, TGraph *gr_kaons_unfitted,
                 TGraph *gr_leptons_0);


void drawFitting(bool to_rotate_leptons, bool to_rotate_kaons,
                 int Run_Number, int ievt, PruningType type,
                 TGraph *gr_leptons_fit1, TGraph *gr_leptons_fit2, TGraph *gr_leptons_fit3,
                 TGraph *gr_kaons_final, TLine *line_fit_kaons,
                 vector<double> vec_intersect_TOF1,
                 double a1, double b1,
                 double a2, double b2,
                 double a3, double b3);


void drawTargetFrame(int Run_Number, int ievt,
                     bool has_ADC_TOF1_hit[12], bool has_TDC_TOF1_hit[12],
                     bool has_ADC_TOF2_hit[12], bool has_TDC_TOF2_hit[12]);


void drawEventDisplay(const DetectorData &data, int Run_Number, int ievt, bool to_restore,
                      int TOF1_gap, int selected_section,  TLine *restored_line,
                      int TDC_min, int TDC_max, int TDC_min_Kstop, int TDC_max_Kstop,
                      bool has_kaon_sub, int kaon_bar, bool b_bbar, vector<double> vec_bbar,
                      bool has_ADC_TOF1_hit[12], bool has_TDC_TOF1_hit[12], bool has_ADC_TOF2_hit[12], bool has_TDC_TOF2_hit[12],
                      bool has_TDC_hit[256], int TDC_min_TARGET, bool has_TDC_hit_Kstop[256],
                      double angle_final, double delta_phi_deg, double ChiS_final, int ndf_final,
                      vector<double> vec_X_int_SFT, vector<double> vec_Y_int_SFT,
                      vector<double> vec_X_int_TARGET, vector<double> vec_Y_int_TARGET,
                      vector<double> vec_X_int_TOF1, vector<double> vec_Y_int_TOF1,
                      vector<double> vec_kstop_FINAL, vector<double> vec_intersect_TARGET_final,
                      TGraph *gr_leptons_final, TGraph *gr_kaons_final, TLine *line_fit_kaons,
                      PruningType type);


void drawBacktracking(vector<TargetBar> primaryTrack, vector<TargetBar> secondaryTrackA, vector<TargetBar> secondaryTrackB, 
                      vector<TargetBar> allBars);


#endif //MACROS_PLOTEVENT2_H