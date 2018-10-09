#pragma once

#include "TLine.h"
#include "CommonParameters.hpp"

namespace CP = CommonParameters;

namespace DetectorGeometry {

//******* TARGET

    // X coordinates of TARGET bars
    extern const double Xloc[CP::nBars];

    // Y coordinates of TARGET bars
    extern const double Yloc[CP::nBars];

    extern const int BarRow[CP::nBars];

    extern const int BarCol[CP::nBars];

    // Rotates the target by -90 deg.
    extern const int TARGET_Rotated_index[CP::nBars];

    // Rotates the target by +90 deg.
    extern const int TARGET_Rotated_index_inverse[CP::nBars];

    extern const int TARGET_neighbours[CP::nBars][8];

    //******* TOF1 & TOF2
    extern const int TOF1_Gap[CP::nTOF1];
    extern const int TOF1_UD[CP::nTOF1];
    extern const int TOF2_Gap[CP::nTOF2];
    extern const int TOF2_UD[CP::nTOF2];

    extern const double TOF_Gap1XLoc[3];
    extern const double TOF_Gap1YLoc[3];

    extern const double TOF_Gap2XLoc[3];
    extern const double TOF_Gap2YLoc[3];

    extern const double TOF_Gap3XLoc[3];
    extern const double TOF_Gap3YLoc[3];

    extern const double TOF_Gap4XLoc[3];
    extern const double TOF_Gap4YLoc[3];

    extern const double TOF_Gap5XLoc[3];
    extern const double TOF_Gap5YLoc[3];

    extern const double TOF_Gap6XLoc[3];
    extern const double TOF_Gap6YLoc[3];

    extern const double TOF_Gap7XLoc[3];
    extern const double TOF_Gap7YLoc[3];

    extern const double TOF_Gap8XLoc[3];
    extern const double TOF_Gap8YLoc[3];

    extern const double TOF_Gap9XLoc[3];
    extern const double TOF_Gap9YLoc[3];

    extern const double TOF_Gap10XLoc[3];
    extern const double TOF_Gap10YLoc[3];

    extern const double TOF_Gap11XLoc[3];
    extern const double TOF_Gap11YLoc[3];

    extern const double TOF_Gap12XLoc[3];
    extern const double TOF_Gap12YLoc[3];

    extern const double sigma_par;   // sigma_parallel
    extern const double sigma_perp;    // sigma perpendicular

    extern const double TOF1_Errors_X[12][5];

    extern const double TOF1_Errors_Y[12][5];

    extern const double TARGET_Errors_X;

    extern const double TARGET_Errors_Y;

    extern const double TOF_Xloc[36];

    extern const double TOF_Yloc[36];

    extern const double TOF1_Xloc[12][5];

    extern const double TOF1_Yloc[12][5];

    extern const double TOF1_length;

    extern const double X_TOF1_line[12][2];

    extern const double Y_TOF1_line[12][2];

    extern TLine *Gap1l;         //  12.5
    extern TLine *Gap2l;         //  12.5
    extern TLine *Gap3l;         //  12.5
    extern TLine *Gap4l;         //  12.5
    extern TLine *Gap5l;         //  12.5
    extern TLine *Gap6l;         //  12.5
    extern TLine *Gap7l;         //  12.5
    extern TLine *Gap8l;         //  12.5
    extern TLine *Gap9l;         //  12.5
    extern TLine *Gap10l;        //  12.5
    extern TLine *Gap11l;        //  12.5
    extern TLine *Gap12l;        //  12.5

    extern const double TOF1_line_slope[12];

    extern const int channel[12][12];

    extern const int TOF1_rotated[12];

//******* SFT

    extern const int SFT_channel_to_layer[128];

    extern const int SFT_channel_to_fiber[128];

    extern const char SFT_channel_to_US_DS[128];

//******* MWPCs

    extern const double C2_ZLoc[56];

    extern const double C2_YLoc[16];

    extern const int C2XL_Channels[56];

    extern const int C2XR_Channels[56];

    extern const int C2YL_Channels[16];

    extern const int C2YR_Channels[16];

    extern const int C3XL_Channels[64];

    extern const int C3XR_Channels[64];

    extern const int C3YL_Channels[16];

    extern const int C3YR_Channels[16];

    extern const int C4XL_Channels[72];

    extern const int C4XR_Channels[72];

    extern const int C4YL_Channels[16];

    extern const int C4YR_Channels[16];

    extern const int C2_strip[56];
};