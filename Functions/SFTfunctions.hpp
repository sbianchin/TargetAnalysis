/*
 * Created by Jack Hong on 2018-07-05. (jhong@alumni.ubc.ca)
 */

#pragma once

#include <vector>

void fillVector(std::vector<int>& newMyVector);

void printVector(const std::vector<int>& newMyVector);

void Z_all(double phi=90., double p1=8., double p2=13., double p3=3., double p4=6.);

void Z_all_CR(double phi_top=90., double phi_bot=270., double p1=8., double p2=13., double p3=3., double p4=6.);

double calculate_Z_position(double phi = 90., int N = 7 , double p = 4.0, int layer = 4);

double *calculate_min_Z_position(double phi, double p1, double p2, double p3, double p4, double return_array[20], int iteration_counter, double delta_z[100]);

std::vector<double> Layer_averaging(std::vector<int> p_fibers, int layer);

std::vector<double> Batch_Layer_averaging(std::vector<int> p_fibers, int layer);

double SFT_print(double ADC_High_SFT_corr[128], int has_TDC_SFT_hit[128], int SFT_channel_to_fiber[128],
                 int evt, double phi, bool to_print, double TOF1_pos, bool use_TOF1, double C2X_centroid, double len_in_target);

std::vector<double> Z_Avg(double ADC_High_SFT_corr[128], int has_TDC_SFT_hit[128],
                          double phi, bool to_print, double TOF1_pos, bool use_TOF1, double C2X_centroid, double len_in_target);

std::vector<double> Z_Avg(double ADC_High_SFT_corr[128], int has_TDC_SFT_hit[128],
                          double phi, bool to_print, double TOF1_pos, bool use_TOF1, double C2X_centroid,
                          double len_in_target);

std::vector<double> Delta_Z(double ADC_High_SFT_corr[128], int has_TDC_SFT_hit[128], int SFT_channel_to_fiber[128],
                            double phi, bool to_print, double TOF1_pos, bool use_TOF1);

std::vector<double> Z_list2(double ADC_High_SFT_corr[128], int has_TDC_SFT_hit[128], int SFT_channel_to_fiber[128],
                            int evt, double phi, bool to_print, double TOF1_pos, bool use_TOF1, double C2X_centroid,
                            double len_in_target);

double SFT_Ana2(double ADC_High_SFT_corr[128], int has_TDC_SFT_hit[128], int SFT_channel_to_fiber[128],
            int evt, double phi, bool to_print, double TOF1_pos, bool use_TOF1, double C2X_centroid,
            double len_in_target);

void SFT_Ana3(int Run_Number, int evt, double ADC_High_SFT_corr[128], int has_TDC_SFT_hit[128], int SFT_channel_to_fiber[128],
          double phi, int gap_to_fit_left, int gap_to_fit_right, double C2_Z_top, double C2_Z_bottom);

std::vector<double> Batch_Ana3(double ADC_High_SFT_corr[128], int has_TDC_SFT_hit[128], int SFT_channel_to_fiber[128], double phi,
                               int gap_to_fit_left, int gap_to_fit_right, double C2_Z_top, double C2_Z_bottom);
