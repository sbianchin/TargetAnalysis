/* 
 * Created by Jack Hong on 2018-07-19. (jhong@alumni.ubc.ca)
 */
#pragma once

#include "CutsAndWindows.hpp"

namespace CutsAndWindows {
    const int TARGET_ADC_Thr_HG_Offset = 20;
    const int TARGET_ADC_Thr_LG_Offset = 20;

    const int TDC_Thr_min = 760;
    const int TDC_Thr_max = 930;

    const int HG_KAON = 1000;
    const int LG_KAON = 100;

    const int TDC_Avg_Offset_min = -30;    // Lepton
    const int TDC_Avg_Offset_max = 10;

    const int TDC_Kstop_Avg_Offset_min = -10;    // Kaon
    const int TDC_Kstop_Avg_Offset_max = 10;

    const double TARGET_ADC_Ped_HG[256] = {
                                                    812.96, 816.49, 818.96, 819.76, 812.63, 824.23,
                                    817.20, 817.28, 812.58, 815.14, 814.78, 818.18, 809.37, 817.75, 812.76, 815.92,
                            818.25, 820.94, 814.83, 816.65, 820.90, 813.01, 818.54, 819.32, 821.21, 825.32, 818.34, 817.82,
                    816.29, 817.09, 813.31, 812.81, 773.55, 785.06, 785.35, 783.64, 776.43, 782.40, 784.15, 782.93, 782.93, 783.52,
            778.36, 780.07, 785.29, 781.64, 780.80, 771.93, 780.03, 777.97, 776.73, 785.98, 786.03, 783.68, 783.67, 779.14, 783.10, 776.06,
            778.46, 777.62, 777.68, 777.09, 782.63, 781.78, 764.99, 766.88, 771.84, 754.50, 761.06, 760.41, 771.44, 765.82, 766.64, 765.73,
    769.02, 767.74, 762.18, 765.10, 769.61, 766.55, 761.32, 760.76, 769.64, 769.96, 761.70, 766.63, 763.78, 758.64, 765.30, 767.44, 769.59, 769.19,
    767.00, 774.88, 764.85, 763.76, 812.94, 808.91, 810.48, 810.01, 808.58, 810.68, 814.32, 811.95, 809.87, 806.88, 803.83, 813.62, 810.25, 801.96,
    802.55, 813.38, 805.94, 812.95, 810.81, 808.07, 800.08, 808.29, 802.88, 811.25, 805.47, 803.37, 806.39, 814.44, 808.54, 807.30, 811.82, 806.08,
    788.63, 780.81, 786.32, 791.22, 783.00, 791.29, 786.10, 789.01, 792.04, 786.80, 785.95, 781.74, 780.66, 782.61, 789.72, 786.10, 783.18, 787.62,
    788.71, 786.88, 787.19, 776.24, 785.01, 792.88, 788.54, 782.27, 786.85, 784.38, 788.96, 790.78, 791.17, 782.33, 811.33, 806.11, 817.10, 810.75,
    814.15, 815.05, 805.16, 814.25, 817.29, 816.07, 817.55, 812.82, 804.98, 817.96, 811.67, 809.12, 813.75, 808.95, 809.28, 811.79, 811.76, 808.09,
            809.19, 812.81, 813.70, 808.69, 810.07, 811.42, 817.28, 811.83, 810.15, 811.16, 812.31, 817.43, 818.73, 819.84, 821.77, 816.18,
            819.27, 811.39, 822.44, 820.74, 818.98, 817.72, 818.00, 816.13, 815.58, 819.61, 812.17, 816.80, 817.09, 820.11, 813.47, 816.94,
                    819.71, 818.48, 813.76, 819.53, 821.04, 816.98, 815.14, 820.12, 814.65, 818.78, 835.65, 835.57, 831.44, 831.66,
                            834.62, 832.22, 839.41, 841.70, 837.92, 831.07, 838.56, 826.07, 827.31, 827.89, 837.05, 841.63,
                                    833.10, 829.16, 828.38, 833.69, 837.77, 830.26, 829.30, 833.41, 839.16, 828.07,
                                                    839.36, 834.46, 833.89, 832.17, 831.58, 834.43};

    const double TARGET_ADC_Ped_LG[256] = {
                                                    812.96, 816.49, 818.96, 819.76, 812.63, 824.23,
                                    817.20, 817.28, 812.58, 815.14, 814.78, 818.18, 809.37, 817.75, 812.76, 815.92,
                            818.25, 820.94, 814.83, 816.65, 820.90, 813.01, 818.54, 819.32, 821.21, 825.32, 818.34, 817.82,
                    816.29, 817.09, 813.31, 812.81, 773.55, 785.06, 785.35, 783.64, 776.43, 782.40, 784.15, 782.93, 782.93, 783.52,
            778.36, 780.07, 785.29, 781.64, 780.80, 771.93, 780.03, 777.97, 776.73, 785.98, 786.03, 783.68, 783.67, 779.14, 783.10, 776.06,
            778.46, 777.62, 777.68, 777.09, 782.63, 781.78, 764.99, 766.88, 771.84, 754.50, 761.06, 760.41, 771.44, 765.82, 766.64, 765.73,
    769.02, 767.74, 762.18, 765.10, 769.61, 766.55, 761.32, 760.76, 769.64, 769.96, 761.70, 766.63, 763.78, 758.64, 765.30, 767.44, 769.59, 769.19,
    767.00, 774.88, 764.85, 763.76, 812.94, 808.91, 810.48, 810.01, 808.58, 810.68, 814.32, 811.95, 809.87, 806.88, 803.83, 813.62, 810.25, 801.96,
    802.55, 813.38, 805.94, 812.95, 810.81, 808.07, 800.08, 808.29, 802.88, 811.25, 805.47, 803.37, 806.39, 814.44, 808.54, 807.30, 811.82, 806.08,
    788.63, 780.81, 786.32, 791.22, 783.00, 791.29, 786.10, 789.01, 792.04, 786.80, 785.95, 781.74, 780.66, 782.61, 789.72, 786.10, 783.18, 787.62,
    788.71, 786.88, 787.19, 776.24, 785.01, 792.88, 788.54, 782.27, 786.85, 784.38, 788.96, 790.78, 791.17, 782.33, 811.33, 806.11, 817.10, 810.75,
    814.15, 815.05, 805.16, 814.25, 817.29, 816.07, 817.55, 812.82, 804.98, 817.96, 811.67, 809.12, 813.75, 808.95, 809.28, 811.79, 811.76, 808.09,
            809.19, 812.81, 813.70, 808.69, 810.07, 811.42, 817.28, 811.83, 810.15, 811.16, 812.31, 817.43, 818.73, 819.84, 821.77, 816.18,
            819.27, 811.39, 822.44, 820.74, 818.98, 817.72, 818.00, 816.13, 815.58, 819.61, 812.17, 816.80, 817.09, 820.11, 813.47, 816.94,
                    819.71, 818.48, 813.76, 819.53, 821.04, 816.98, 815.14, 820.12, 814.65, 818.78, 835.65, 835.57, 831.44, 831.66,
                            834.62, 832.22, 839.41, 841.70, 837.92, 831.07, 838.56, 826.07, 827.31, 827.89, 837.05, 841.63,
                                    833.10, 829.16, 828.38, 833.69, 837.77, 830.26, 829.30, 833.41, 839.16, 828.07,
                                                    839.36, 834.46, 833.89, 832.17, 831.58, 834.43};



    const int TARGET_TDC_min[256] = {
                            800,800,800,800,800,800,
                    800,800,800,800,800,800,800,800,800,800,
                800,800,800,800,800,800,800,800,800,800,800,800,
            800,800,800,800,800,800,800,800,800,800,800,800,800,800,
        800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
        800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
    800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
    800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
    800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
    800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
    800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
    800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
        800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
        800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,800,
            800,800,800,800,800,800,800,800,800,800,800,800,800,800,
                800,800,800,800,800,800,800,800,800,800,800,800,
                    800,800,800,800,800,800,800,800,800,800,
                            800,800,800,800,800,800};

    const int TARGET_TDC_max[256] = {
                            940,940,940,940,940,940,
                    940,940,940,940,940,940,940,940,940,940,
                940,940,940,940,940,940,940,940,940,940,940,940,
            940,940,940,940,940,940,940,940,940,940,940,940,940,940,
        940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
        940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
    940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
    940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
    940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
    940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
    940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
    940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
        940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
        940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
            940,940,940,940,940,940,940,940,940,940,940,940,940,940,
                940,940,940,940,940,940,940,940,940,940,940,940,
                    940,940,940,940,940,940,940,940,940,940,
                            940,940,940,940,940,940};

    const double Target_HG_ped[256] =
            {812.883, 817.335, 819.621, 820.555, 810.916, 822.595,
             817.115, 817.318, 812.429, 815.641, 814.163, 818.215, 808.578, 818.143, 812.204, 815.834,
             817.879, 820.927, 815.013, 817.252, 820.763, 812.375, 818.146, 820.251, 822.450, 825.660, 818.482, 818.320,
             815.416, 816.836, 812.779, 813.141, 774.000, 781.221, 784.574, 780.924, 773.882, 778.537, 779.040, 778.816,
             779.215, 781.517,
             771.608, 775.989, 785.676, 778.948, 777.245, 772.314, 779.313, 776.616, 775.140, 784.283, 785.703, 782.807,
             782.348, 775.649, 778.029, 773.884,
             772.575, 771.077, 777.336, 778.044, 780.314, 781.983, 762.776, 765.641, 769.672, 754.321, 758.207, 759.781,
             769.040, 763.760, 763.322, 763.934,
             770.216, 765.547, 758.039, 765.902, 765.553, 763.665, 760.249, 760.714, 768.728, 769.930, 761.120, 764.816,
             762.002, 758.784, 761.099, 762.113, 763.955, 763.335,
             760.180, 769.189, 763.108, 763.700, 811.746, 809.484, 810.974, 810.520, 808.232, 810.996, 813.702, 811.689,
             810.018, 807.386, 804.361, 812.378, 810.151, 800.111,
             802.855, 810.498, 802.231, 813.082, 811.070, 808.358, 797.824, 807.931, 803.177, 811.725, 805.630, 803.092,
             805.948, 811.411, 808.381, 807.349, 811.602, 806.859,
             785.636, 777.851, 784.629, 791.983, 781.323, 791.386, 785.832, 789.074, 791.279, 784.880, 785.235, 781.178,
             778.674, 782.701, 788.898, 781.929, 779.056, 782.742,
             787.125, 782.991, 783.295, 775.797, 781.823, 790.237, 789.199, 782.135, 785.983, 784.420, 785.440, 787.651,
             789.015, 781.680, 811.091, 805.927, 815.870, 808.191,
             810.278, 810.949, 800.614, 813.170, 816.500, 813.253, 818.166, 812.307, 800.583, 814.992, 811.158, 807.911,
             814.052, 807.941, 807.185, 807.895, 809.854, 805.209,
             804.554, 809.728, 813.420, 805.845, 808.558, 808.983, 817.217, 811.406, 810.004, 807.567, 813.035, 818.131,
             819.353, 819.941, 822.143, 815.073,
             819.161, 811.340, 822.999, 821.221, 819.615, 817.935, 817.741, 816.762, 816.266, 819.847, 809.258, 814.205,
             817.199, 820.368, 814.457, 817.052,
             819.513, 817.848, 813.470, 820.473, 820.933, 817.291, 816.249, 820.574, 815.281, 819.663, 832.652, 835.702,
             830.825, 829.093,
             832.150, 830.097, 836.134, 841.067, 837.092, 831.393, 838.775, 826.155, 825.341, 826.852, 836.284, 840.102,
             833.439, 827.205, 828.112, 833.427, 835.075, 828.940, 829.376, 830.045, 836.333, 824.707,
             835.880, 832.455, 831.515, 828.152, 828.133, 830.985};

    const double Target_LG_ped[256] =
            {815.315, 827.323, 821.160, 817.014, 823.704, 819.138,
             814.762, 820.148, 816.255, 819.645, 814.607, 823.797, 824.193, 814.641, 811.018, 815.669,
             822.631, 820.226, 819.302, 820.063, 819.686, 820.735, 819.331, 815.043, 819.719, 820.122, 814.065, 816.405,
             821.168, 816.778, 822.242, 817.404, 795.836, 798.737, 790.116, 795.592, 786.316, 792.053, 797.666, 794.398,
             790.643, 788.250,
             793.824, 795.107, 789.415, 793.776, 797.383, 787.140, 787.485, 791.384, 798.830, 789.620, 799.361, 787.279,
             792.003, 790.904, 787.963, 787.800,
             785.098, 794.853, 786.655, 786.927, 794.033, 785.293, 752.465, 759.185, 759.014, 756.370, 757.591, 757.568,
             757.318, 756.243, 761.466, 759.355,
             760.466, 762.733, 753.504, 761.872, 766.461, 753.202, 761.694, 756.732, 760.411, 752.075, 756.460, 761.499,
             755.128, 758.095, 752.893, 749.128, 762.696, 760.370,
             760.047, 758.043, 758.681, 750.633, 806.684, 802.095, 812.985, 809.138, 807.150, 800.308, 796.293, 809.786,
             801.710, 800.843, 803.525, 804.775, 800.681, 805.609,
             801.104, 801.420, 807.313, 809.709, 812.923, 803.269, 803.926, 809.184, 803.381, 807.403, 806.309, 803.375,
             803.282, 804.819, 804.932, 803.470, 804.734, 803.408,
             799.262, 798.628, 802.254, 808.818, 805.681, 804.777, 802.723, 801.440, 795.746, 802.379, 807.708, 803.246,
             798.548, 796.227, 798.094, 799.040, 798.684, 799.254,
             805.398, 797.327, 806.888, 802.176, 795.337, 804.763, 803.136, 797.103, 801.608, 799.279, 797.987, 805.648,
             803.051, 802.024, 804.968, 800.604, 799.714, 800.235,
             799.744, 806.775, 798.740, 806.059, 800.922, 803.143, 799.821, 801.269, 792.202, 807.415, 797.029, 800.488,
             803.269, 799.393, 802.263, 804.293, 794.542, 805.384,
             801.784, 803.665, 799.604, 801.233, 796.217, 808.852, 792.684, 795.114, 807.187, 795.957, 812.533, 819.999,
             813.051, 812.892, 808.033, 817.050,
             807.515, 814.922, 814.559, 814.408, 809.538, 809.268, 814.446, 809.295, 811.970, 813.817, 805.508, 807.476,
             809.579, 811.848, 819.433, 805.525,
             806.850, 809.350, 809.657, 812.711, 811.603, 808.360, 810.696, 809.181, 819.066, 807.079, 831.986, 836.182,
             826.441, 831.700,
             839.701, 833.761, 829.002, 831.964, 835.299, 830.357, 825.991, 831.412, 827.298, 827.478, 835.234, 829.555,
             828.959, 835.567, 832.097, 827.065, 827.885, 831.092, 828.111, 829.663, 828.778, 826.420,
             830.930, 835.293, 830.240, 828.094, 829.463, 830.340};

    //******* SFT
    const int SFT_ADC_Thr_HG_Offset = 30;
    const int SFT_ADC_Thr_LG_Offset = 30;

    const int _SFT_TDC_min = 730;
    const int _SFT_TDC_max = 940;


    /// SFT - ADC High Gain(HG) Pedestals
    const double SFT_ADC_Thr_HG[128] = {796.23, 787.06, 794.53, 794.71, 794.68, 795.94, 789.13, 789.09,
                                  791.42, 788.39, 791.13, 788.28, 795.25, 791.24, 790.02, 794.20,
                                  788.87, 791.72, 791.76, 788.76, 797.64, 787.99, 788.28, 789.32,
                                  790.92, 786.14, 786.99, 793.94, 791.78, 796.12, 782.11, 786.58,
                                  791.02, 786.47, 788.17, 789.50, 786.29, 788.06, 778.93, 784.59,
                                  789.06, 777.93, 788.50, 784.18, 780.29, 786.58, 789.02, 786.77,
                                  785.92, 788.98, 788.87, 784.58, 782.29, 791.81, 788.87, 786.43,
                                  780.26, 781.26, 787.62, 784.40, 780.66, 779.11, 788.17, 779.70,
                                  775.73, 779.79, 784.99, 779.66, 779.27, 777.65, 772.41, 784.59,
                                  784.22, 778.95, 784.58, 779.82, 781.88, 774.50, 779.18, 781.06,
                                  778.35, 776.47, 778.77, 779.32, 784.45, 779.77, 782.03, 777.96,
                                  776.26, 782.20, 774.07, 779.95, 779.56, 778.61, 778.31, 774.55,
                                  839.65, 837.16, 841.41, 839.63, 835.20, 842.97, 840.85, 843.54,
                                  840.48, 835.11, 836.22, 838.22, 836.59, 839.78, 844.29, 838.23,
                                  833.45, 844.80, 837.76, 834.69, 842.24, 834.68, 843.12, 847.44,
                                  830.53, 838.15, 837.48, 833.70, 841.82, 836.07, 841.58, 832.99};

    /// SFT - ADC Low Gain(LG) Pedestals
    const double SFT_ADC_Thr_LG[128] = {796.23, 787.06, 794.53, 794.71, 794.68, 795.94, 789.13, 789.09,
                                  791.42, 788.39, 791.13, 788.28, 795.25, 791.24, 790.02, 794.20,
                                  788.87, 791.72, 791.76, 788.76, 797.64, 787.99, 788.28, 789.32,
                                  790.92, 786.14, 786.99, 793.94, 791.78, 796.12, 782.11, 786.58,
                                  791.02, 786.47, 788.17, 789.50, 786.29, 788.06, 778.93, 784.59,
                                  789.06, 777.93, 788.50, 784.18, 780.29, 786.58, 789.02, 786.77,
                                  785.92, 788.98, 788.87, 784.58, 782.29, 791.81, 788.87, 786.43,
                                  780.26, 781.26, 787.62, 784.40, 780.66, 779.11, 788.17, 779.70,
                                  775.73, 779.79, 784.99, 779.66, 779.27, 777.65, 772.41, 784.59,
                                  784.22, 778.95, 784.58, 779.82, 781.88, 774.50, 779.18, 781.06,
                                  778.35, 776.47, 778.77, 779.32, 784.45, 779.77, 782.03, 777.96,
                                  776.26, 782.20, 774.07, 779.95, 779.56, 778.61, 778.31, 774.55,
                                  839.65, 837.16, 841.41, 839.63, 835.20, 842.97, 840.85, 843.54,
                                  840.48, 835.11, 836.22, 838.22, 836.59, 839.78, 844.29, 838.23,
                                  833.45, 844.80, 837.76, 834.69, 842.24, 834.68, 843.12, 847.44,
                                  830.53, 838.15, 837.48, 833.70, 841.82, 836.07, 841.58, 832.99};

    const int SFT_TDC_min[128] = {730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,
                                  730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,
                                  730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,
                                  730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,
                                  730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,
                                  730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,730,
                                  730,730,730,730,730,730,730,730};

    const int SFT_TDC_max[128] = {940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
                            940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
                            940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
                            940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
                            940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
                            940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,940,
                            940,940,940,940,940,940,940,940};

    //******* TOF1 & TOF2 
    /// TOF1 ADC CUt
    const int TOF1U_ADC_Thr[12] = {170, 300, 200, 400, 400, 300, 400, 400, 400, 400, 300, 200};  // Mike Sept. 28 2016
    const int TOF1D_ADC_Thr[12] = {300, 300, 300, 400, 400, 400, 500, 400, 400, 400, 400, 400};  // Mike Sept. 28 2016

    /// TOF1 TDC Window
    const int TOF1U_TDC_min[12] = {300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300};
    const int TOF1U_TDC_max[12] = {800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800};
    const int TOF1D_TDC_min[12] = {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400};
    const int TOF1D_TDC_max[12] = {800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800};

    /// TOF2 ADC Cut
    const int TOF2AO_ADC_Thr[12] = {400, 1200, 1000, 1200, 1000, 700, 900, 900, 900, 900, 900, 800};
    const int TOF2AI_ADC_Thr[12] = {500, 1200, 800, 800, 1000, 900, 900, 900, 900, 500, 900, 900};
    const int TOF2BO_ADC_Thr[12] = {1000, 1500, 1300, 1100, 1000, 900, 700, 800, 1200, 600, 900, 600};
    const int TOF2BI_ADC_Thr[12] = {800, 1500, 1200, 800, 600, 500, 700, 1000, 900, 1100, 900, 1100};

    /// TOF2 TDC Window
    const int TOF2AO_TDC_min[12] = {800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800};
    const int TOF2AO_TDC_max[12] = {1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800};
    const int TOF2AI_TDC_min[12] = {800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800};
    const int TOF2AI_TDC_max[12] = {1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800};
    const int TOF2BO_TDC_min[12] = {800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800};
    const int TOF2BO_TDC_max[12] = {1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800};
    const int TOF2BI_TDC_min[12] = {800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800};
    const int TOF2BI_TDC_max[12] = {1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800};

    //******* Cpi & Ck
    const int TDC_Ck_min = 1510;
    const int TDC_Ck_max = 1580;
    const int TDC_Cpi_min = 1400;
    const int TDC_Cpi_max = 1600;

    //******* B0
    const int TDC_B0_min = 1450;
    const int TDC_B0_max = 1650;

    //******* BDC
    const int TDC_BDC_min = 1450;
    const int TDC_BDC_max = 1650;


    //******* MWPCs
    const double MWPC_Thr_Offset_C2X = 40.;   // Threshold = Pedestal + MWPC_Thr_Offset
    const double MWPC_Thr_Offset_C2Y = 40.;   // Threshold = Pedestal + MWPC_Thr_Offset
    const double MWPC_Thr_Offset_C3X = 40.;   // Threshold = Pedestal + MWPC_Thr_Offset
    const double MWPC_Thr_Offset_C3Y = 40.;   // Threshold = Pedestal + MWPC_Thr_Offset
    const double MWPC_Thr_Offset_C4X = 0.;   // Threshold = Pedestal + MWPC_Thr_Offset
    const double MWPC_Thr_Offset_C4Y = 0.;   // Threshold = Pedestal + MWPC_Thr_Offset

    const double ADC_C2X_Thr_L[56]={66.5545, 95.8892, 120.185, 54.0731, 69.9739, 93.1277, 119.348, 53.038,
                                           88.3171, 84.7184, 121.562, 46.3241, 88.3056, 86.2982, 118.92, 41.0855,
                                           97.6413, 87.9155, 103.882, 37.6557, 92.1287, 95.196, 93.4037, 52.9094,
                                           85.8086, 82.5912, 107.901, 35.1925, 84.7837, 92.1182, 101.036, 36.7544,
                                           77.7731, 87.9897, 103.328, 32.9986, 75.6906, 92.6121, 98.2558, 33.253,
                                           83.9423, 84.0012, 109.184, 50.7816, 86.6876, 86.401, 105.955, 46.9091,
                                           87.5527, 112.079, 95.7404, 51.5093, 77.5413, 96.8065, 80.5438, 42.3746};

    const double ADC_C2X_Thr_R[56]={29.55, 86.6342, 68.0566, 40.9405, 29.6225, 79.5462, 73.9034, 36.7829,
                                           31.6747, 87.1451, 67.4837, 52.3645, 20.451, 83.3092, 66.4248, 45.4406,
                                           25.1788, 77.6419, 76.5466, 28.5221, 18.6882, 82.93, 76.6559, 32.5156,
                                           17.6647, 99.9925, 85.3671, 27.8629, 25.2491, 103.819, 84.3523, 27.2205,
                                           27.2013, 87.7623, 83.8975, 39.8405, 33.024, 90.9467, 90.6602, 44.3489,
                                           19.5886, 86.5545, 75.205, 31.7794, 23.0508, 85.0448, 78.7735, 32.3749,
                                           24.4324, 79.2279, 70.0597, 43.5405, 20.0282, 79.1914, 70.3046, 40.1471};

    const double ADC_C2Y_Thr_L[16]={72.0133, 82.7221, 81.7371, 79.3077, 78.3803, 82.7384, 98.5305, 96.3329,
                                           107.001, 102.189, 84.4953, 86.0216, 94.6777, 95.2026, 101.888, 101.073};

    const double ADC_C2Y_Thr_R[16]={60.8138, 63.4316, 75.7469, 77.9281, 61.8813, 68.0862, 35.8727, 43.1298,
                                           80.9606, 74.3386, 45.1688, 46.7759, 70.7677, 60.9485, 70.0501, 77.1503};


    const double ADC_C3X_Thr_L[64]={81.9204, 83.652, 92.2328, 81.3602, 54.9127, 70.4812, 86.0275, 88.1204,
                                           90.9854, 84.102, 110.551, 114.307, 75.0869, 84.6211, 91.0224, 104.221,
                                           74.3842, 70.0302, 92.06, 91.0852, 79.8958, 76.1246, 94.7332, 95.9706,
                                           82.4372, 79.9362, 73.626, 81.9986, 67.0533, 73.2251, 66.7667, 66.5016,
                                           47.2311, 53.6122, 50.1829, 57.1743, 51.5258, 47.7801, 51.7205, 52.7671,
                                           49.3053, 49.4322, 39.0141, 38.3722, 58.7402, 65.4598, 56.8322, 48.5033,
                                           77.321, 76.8522, 100.148, 97.2606, 87.1056, 92.2552, 72.1111, 70.9876,
                                           65.6206, 68.6756, 71.0001, 76.5199, 72.4113, 79.8895, 83.6729, 82.7729};

    const double ADC_C3X_Thr_R[64]={77.1341, 64.4088, 62.7195, 56.2171, 66.2864, 78.6857, 76.496, 78.0683,
                                           78.106, 98.3189, 56.1186, 68.5249, 57.1083, 66.0588, 92.0051, 79.7732,
                                           55.6618, 56.0875, 68.51, 81.3279, 81.286, 84.977, 70.2921, 73.0777,
                                           83.9446, 81.4127, 77.5352, 81.3527, 91.3871, 83.6726, 72.2079, 90.2351,
                                           84.306, 85.089, 107.33, 111.514, 104.936, 104.995, 95.856, 98.1043,
                                           84.5501, 82.3805, 88.0781, 84.1474, 97.4266, 103.237, 85.4799, 89.844,
                                           140.817, 139.13, 111.516, 112.166, 114.949, 122.967, 111.366, 120.596,
                                           108.584, 118.927, 131.906, 132.31, 124.039, 143.851, 121.455, 112.845};

    const double ADC_C3Y_Thr_L[16]={85.391, 121.791, 108.675, 94.5681, 87.3374, 87.5986, 76.2033, 84.8874,
                                           94.8051, 94.649, 93.0969, 90.8621, 87.6673, 110.018, 99.1093, 110.992};

    const double ADC_C3Y_Thr_R[16]={63.3712, 81.7166, 89.8355, 78.4771, 56.2098, 73.0629, 69.5283, 69.117,
                                           81.3987, 91.1201, 62.2729, 60.8035, 75.5944, 73.2461, 54.1899, 66.869};

    const double ADC_C4X_Thr_L[72]={107.511, 116.55, 171.699, 170.267, 133.785, 133.218, 130.261, 125.26,
                                           125.081, 128.299, 142.069, 137.542, 148.332, 133.513, 115.42, 125.282,
                                           76.6605, 76.6743, 95.6186, 87.6874, 83.5615, 99.9537, 94.5614, 92.1477,
                                           88.5769, 85.3772, 94.4874, 98.5985, 81.1377, 92.9823, 80.5043, 95.3943,
                                           87.3063, 97.6263, 91.0658, 92.0181, 84.6295, 94.1096, 84.8214, 83.6138,
                                           97.1834, 83.4509, 86.3186, 101.253, 92.3661, 89.1872, 86.3897, 91.5512,
                                           78.0449, 91.0495, 95.2789, 89.7043, 79.9399, 70.5767, 84.3724, 80.0097,
                                           37.9791, 75.6572, 79.1595, 94.9582, 73.3976, 79.577, 73.6342, 84.1052,
                                           88.814, 98.0193, 88.0309, 86.2599, 97.2533, 93.0269, 77.3541, 82.7447};

    const double ADC_C4X_Thr_R[72]={99.3223, 97.7631, 83.8797, 124.577, 98.8741, 93.0015, 95.9852, 112.114,
                                           94.5493, 85.9135, 108.236, 128.651, 104.323, 90.2893, 98.5811, 108.04,
                                           41.722, 37.8692, 45.1685, 41.9049, 33.4329, 48.0689, 42.2893, 37.3286,
                                           31.2358, 43.6076, 28.3036, 32.668, 49.4871, 45.1138, 47.2021, 54.4416,
                                           102.428, 97.2873, 93.6965, 106.403, 106.658, 90.1518, 101.569, 103.839,
                                           111.599, 91.6956, 96.1903, 92.1995, 104.817, 91.1064, 100.435, 96.899,
                                           57.3325, 61.6432, 51.8135, 63.4155, 52.7229, 65.9241, 55.1616, 63.5117,
                                           34.3827, 53.4696, 74.6887, 67.0393, 64.8661, 73.0515, 63.72, 67.5834,
                                           118.301, 129.345, 109.35, 107.382, 115.681, 113.486, 118.775, 111.832};

    const double ADC_C4Y_Thr_L[16]={46.702, 54.5824, 42.8519, 43.6974, 45.7594, 45.6707, 66.1964, 59.6333,
                                           57.0467, 59.9273, 58.2799, 52.7275, 70.4067, 66.5787, 70.0195, 71.6155};

    const double ADC_C4Y_Thr_R[16]={100.344, 105.209, 108.322, 113.998, 101.508, 97.8996, 110.129, 125.808,
                                           109.224, 107.654, 90.7562, 116.188, 114.786, 113.753, 123.155, 132.888};

    // LINEAR PRUNING
    const double GAP_LINE_SHIFT = 8.;


}