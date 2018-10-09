/* 
 * Created by Jack Hong on 2018-07-11. (jhong@alumni.ubc.ca)
 */

#ifndef MACROS_PRINTFUNCTIONS_H
#define MACROS_PRINTFUNCTIONS_H

//#pragma once
#include <string>
#include "DetectorData.hpp"
//#include "AnalyzeEvent.h"
#include "DisplayEvent.h"

void printEventSummary(DetectorData &data, std::string Time_walk_file, std::string SFT_mapping_file, std::string MWPC_mapping_file,
                       bool is_good_event,
                       bool is_good_TARGET_event, bool is_good_TOF_event, bool is_good_MWPC_event,
                       bool is_event_on_blacklist);

void printEventStatus(int event_number, bool is_good_event,
                      bool is_good_TARGET_event, bool is_good_TOF_event, bool is_good_MWPC_event,
                      bool is_event_on_blacklist);

void printTOFRawADC(const DetectorData &data);

void printTimeCuts(const DetectorData &data, int kaon_TDC_min, int kaon_TDC_max, int TDC_min_Kstop, int TDC_max_Kstop);

void printTargetInfo(const DetectorData &data, bool Good_Event, int enable_cout, bool NoFile,
					 int ievt, int TDC_average);

void printSFTInfo(const DetectorData &data, double ADC_High_SFT_corr[128], int has_TDC_SFT_hit[128]);

void printMWPCInfo(const DetectorData &data, int selected_TOF2, bool Good_Event,
                   int C2X_clusters, int C2Y_clusters,
                   int C3X_clusters, int C3Y_clusters,
                   int C4X_clusters, int C4Y_clusters);

void printCherenkovInfo(const DetectorData &data, int TDC_average,
                        vector<double> vec_Ck, double TDC_ck_avg, double TDC_ck_sigma,
                        vector<double> vec_Cpi, double TDC_cpi_avg, double TDC_cpi_sigma, 
                        int TDC_ck_counter, double TDC_ck_avg2,
                        int TDC_cpi_counter, double TDC_cpi_avg2);

void printCkCorrectedTDC(const DetectorData &data, vector<int> vec_TARGET_bar_selected,
                         double TDC_ck_avg2);

void printGapScoring(const DetectorData &data, int TOF2_counter, bool Good_Event);

void printTrackInfo(double angle_final, double delta_phi_deg, double ChiS_final, int ndf_final, 
                    vector<double> vec_XX_int_SFT, vector<double> vec_YY_int_SFT,
                    vector<double> vec_XX_int_TOF1, vector<double> vec_YY_int_TOF1,
                    double Length_in_target);

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
                    PruningType type, bool batch_mode, bool print_to_console);


#endif //MACROS_PRINTFUNCTIONS_H
