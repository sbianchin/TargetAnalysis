// add TDC values for run 2748  and 3405   Ke3 calibration run
//   Dec 30/16   MH

#pragma once

namespace CutsAndWindows {

    //******* TARGET 
    extern const int TARGET_ADC_Thr_HG_Offset;
    extern const int TARGET_ADC_Thr_LG_Offset;

    extern const int TDC_Thr_min;
    extern const int TDC_Thr_max;

    // ADC Thresholds for determining K Stop
    extern const int HG_KAON;
    extern const int LG_KAON;

    // Window around TDC_Kstop_Avg
    extern const int TDC_Avg_Offset_min;    // Lepton
    extern const int TDC_Avg_Offset_max;

    extern const int TDC_Kstop_Avg_Offset_min;    // Kaon
    extern const int TDC_Kstop_Avg_Offset_max;

    /// TARGET - ADC High Gain(HG) Pedestals 
    extern const double TARGET_ADC_Ped_HG[256];

    /// TARGET - ADC Low Gain(LG) Pedestals                                                   
    extern const double TARGET_ADC_Ped_LG[256];

    extern const int TARGET_TDC_min[256];

    extern const int TARGET_TDC_max[256];

    /// OLD but still used by some macros
    extern const double Target_HG_ped[256];

    /// OLD but still used by some macros
    extern const double Target_LG_ped[256];

    //******* SFT 
    extern const int SFT_ADC_Thr_HG_Offset;
    extern const int SFT_ADC_Thr_LG_Offset;

    extern const int _SFT_TDC_min;
    extern const int _SFT_TDC_max;

    /// SFT - ADC High Gain(HG) Pedestals
    extern const double SFT_ADC_Thr_HG[128];

    /// SFT - ADC Low Gain(LG) Pedestals
    extern const double SFT_ADC_Thr_LG[128];

    extern const int SFT_TDC_min[128];

    extern const int SFT_TDC_max[128];


    //******* TOF1 & TOF2 
    /// TOF1 ADC CUt
    extern const int TOF1U_ADC_Thr[12];  // Mike Sept. 28 2016
    extern const int TOF1D_ADC_Thr[12];  // Mike Sept. 28 2016

    /// TOF1 TDC Window
    extern const int TOF1U_TDC_min[12];
    extern const int TOF1U_TDC_max[12];
    extern const int TOF1D_TDC_min[12];
    extern const int TOF1D_TDC_max[12];
    
    /// TOF2 ADC Cut
    extern const int TOF2AO_ADC_Thr[12];
    extern const int TOF2AI_ADC_Thr[12];
    extern const int TOF2BO_ADC_Thr[12];
    extern const int TOF2BI_ADC_Thr[12];
    
    /// TOF2 TDC Window
    extern const int TOF2AO_TDC_min[12];
    extern const int TOF2AO_TDC_max[12];
    extern const int TOF2AI_TDC_min[12];
    extern const int TOF2AI_TDC_max[12];
    extern const int TOF2BO_TDC_min[12];
    extern const int TOF2BO_TDC_max[12];
    extern const int TOF2BI_TDC_min[12];
    extern const int TOF2BI_TDC_max[12];

    //******* Cpi & Ck
    extern const int TDC_Ck_min;
    extern const int TDC_Ck_max;
    extern const int TDC_Cpi_min;
    extern const int TDC_Cpi_max;

    //******* B0
    extern const int TDC_B0_min;
    extern const int TDC_B0_max;

    //******* BDC
    extern const int TDC_BDC_min;
    extern const int TDC_BDC_max;

    
    //******* MWPCs
    extern const double MWPC_Thr_Offset_C2X;   // Threshold = Pedestal + MWPC_Thr_Offset
    extern const double MWPC_Thr_Offset_C2Y;   // Threshold = Pedestal + MWPC_Thr_Offset
    extern const double MWPC_Thr_Offset_C3X;   // Threshold = Pedestal + MWPC_Thr_Offset
    extern const double MWPC_Thr_Offset_C3Y;   // Threshold = Pedestal + MWPC_Thr_Offset
    extern const double MWPC_Thr_Offset_C4X;   // Threshold = Pedestal + MWPC_Thr_Offset
    extern const double MWPC_Thr_Offset_C4Y;   // Threshold = Pedestal + MWPC_Thr_Offset

    extern const double ADC_C2X_Thr_L[56];

    extern const double ADC_C2X_Thr_R[56];

    extern const double ADC_C2Y_Thr_L[16];

    extern const double ADC_C2Y_Thr_R[16];

    extern const double ADC_C3X_Thr_L[64];

    extern const double ADC_C3X_Thr_R[64];

    extern const double ADC_C3Y_Thr_L[16];

    extern const double ADC_C3Y_Thr_R[16];

    extern const double ADC_C4X_Thr_L[72];

    extern const double ADC_C4X_Thr_R[72];

    extern const double ADC_C4Y_Thr_L[16];

    extern const double ADC_C4Y_Thr_R[16];

    // LINEAR PRUNING
    extern const double GAP_LINE_SHIFT;

};
