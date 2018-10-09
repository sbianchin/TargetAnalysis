#include "SimulationData.hpp"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <fstream>
#include "calculateThreshold.hpp"
#include "CutsAndWindows.hpp"
#include "CommonParameters.hpp"
#include "DetectorGeometry.hpp"
#include <iostream>

namespace CW = CutsAndWindows;
namespace CP = CommonParameters;

// line required to work with ROOT
ClassImp(SimulationData);

SimulationData::SimulationData(int run_number, int event_number)
        : RunNum(run_number),
          m_Chain(0){
          //m_is_threshold_adjusted(kFALSE),
          //m_is_time_walk_corrected(kFALSE) {
    // If run number is not specified, try to connect the Run3994MS.root file
    // from the user defined environment variable "path_merged".
    m_root_file_path = makeRootFilePath(run_number);

    ifstream finput(m_root_file_path, ios::in);
    if(!finput.good()){
        cout << endl;
        cout << endl;
        cout << m_root_file_path << " DOES NOT EXIST !" << endl;
        cout << endl;
        cout << endl;
        return;
    }

    TFile *f = (TFile *) gROOT->GetListOfFiles()->FindObject(m_root_file_path);
    if (!f || !f->IsOpen()) {
        f = new TFile(m_root_file_path);
    }
    if (!f->IsOpen()) {
        throw "File not found";
    }

    TTree *tree;
    f->GetObject("Kaon", tree);
    init(tree);
    getEvent(event_number);
}

SimulationData::SimulationData(TTree *tree) : m_Chain(0) {
// If parameter tree is not specified (or zero), try to connect the G4Run822.root file
// from the user defined environment variable "path_merged".
    if (tree == 0) {
        TFile *f = (TFile *) gROOT->GetListOfFiles()->FindObject(
                "$path_merged/G4Run822.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("$path_merged/G4Run822.root");
        }
        f->GetObject("Kaon", tree);
    }
    init(tree);
}

SimulationData::~SimulationData() {
    if (!m_Chain) return;
    delete m_Chain->GetCurrentFile();
}

void SimulationData::init(TTree *tree) {
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set branch addresses and branch pointers
    if (!tree) return;
    m_Chain = tree;
    m_Current = -1;
    m_Chain->SetMakeClass(1);

    m_Chain->SetBranchAddress("n", &n, &b_n);
    m_Chain->SetBranchAddress("s_hit", &s_hit, &b_s_hit);
    //m_Chain->SetBranchAddress("x_hit", &x_hit, &b_x-hit);
    m_Chain->SetBranchAddress("px[10]", px, &b_px);
    m_Chain->SetBranchAddress("py[10]", py, &b_py);
    m_Chain->SetBranchAddress("pz[10]", pz, &b_pz);
    m_Chain->SetBranchAddress("u_x", &u_x, &b_u_x);
    m_Chain->SetBranchAddress("u_y", &u_y, &b_u_y);
    m_Chain->SetBranchAddress("u_z", &u_z, &b_u_z);
    m_Chain->SetBranchAddress("genEvt", &genEvt, &b_genEvt);
    m_Chain->SetBranchAddress("genEne[10]", genEne, &b_genEne);
    m_Chain->SetBranchAddress("cosTh", &cosTh, &b_cosTh);
    m_Chain->SetBranchAddress("sinTh", &sinTh, &b_sinTh);
    m_Chain->SetBranchAddress("Phi", &Phi, &b_Phi);
    m_Chain->SetBranchAddress("dv_x", &dv_x, &b_dv_x);
    m_Chain->SetBranchAddress("dv_y", &dv_y, &b_dv_y);
    m_Chain->SetBranchAddress("dv_z", &dv_z, &b_dv_z);
    m_Chain->SetBranchAddress("targetE", &targetE, &b_targetE);
    m_Chain->SetBranchAddress("targetEe", &targetEe, &b_targetEe);
    m_Chain->SetBranchAddress("targetdE[256]", targetdE, &b_targetdE);
    m_Chain->SetBranchAddress("targetdEe[256]", targetdEe, &b_targetdEe);
    m_Chain->SetBranchAddress("targetdt[256]", targetdt, &b_targetdt);
    m_Chain->SetBranchAddress("targL", &targL, &b_targL);
    m_Chain->SetBranchAddress("delta_x", &delta_x, &b_delta_x);
    m_Chain->SetBranchAddress("delta_y", &delta_y, &b_delta_y);
    m_Chain->SetBranchAddress("delta_z", &delta_z, &b_delta_z);
    m_Chain->SetBranchAddress("delta_ux", &delta_ux, &b_delta_ux);
    m_Chain->SetBranchAddress("delta_uy", &delta_uy, &b_delta_uy);
    m_Chain->SetBranchAddress("delta_uz", &delta_uz, &b_delta_uz);
    m_Chain->SetBranchAddress("delta_length", &delta_length, &b_delta_length);
    m_Chain->SetBranchAddress("delta_energy", &delta_energy, &b_delta_energy);
    m_Chain->SetBranchAddress("delta_time", &delta_time, &b_delta_time);
    m_Chain->SetBranchAddress("delta_stop_x", &delta_stop_x, &b_delta_stop_x);
    m_Chain->SetBranchAddress("delta_stop_y", &delta_stop_y, &b_delta_stop_y);
    m_Chain->SetBranchAddress("delta_stop_z", &delta_stop_z, &b_delta_stop_z);
    m_Chain->SetBranchAddress("delta_elast", &delta_elast, &b_delta_elast);
    m_Chain->SetBranchAddress("delta_trackID", &delta_trackID, &b_delta_trackID);
    m_Chain->SetBranchAddress("delta_parentID", &delta_parentID, &b_delta_parentID);
    m_Chain->SetBranchAddress("tof1dt", &tof1dt, &b_tof1dt);
    m_Chain->SetBranchAddress("t1pL", &t1pL, &b_t1pL);
    m_Chain->SetBranchAddress("t1", &t1, &b_t1);
    m_Chain->SetBranchAddress("tof1E[5]", tof1E, &b_tof1E);
    m_Chain->SetBranchAddress("tof1wpos[5][3]", tof1wpos, &b_tof1wpos);
    m_Chain->SetBranchAddress("tof1TrackID[5]", tof1TrackID, &b_tof1TrackID);
    m_Chain->SetBranchAddress("jtrack[5]", jtrack, &b_jtrack);
    m_Chain->SetBranchAddress("tof1charge[5]", tof1charge, &b_tof1charge);
    m_Chain->SetBranchAddress("secondP[5][100]", secondP, &b_secondP);
    m_Chain->SetBranchAddress("tof1N[5]", tof1N, &b_tof1N);
    m_Chain->SetBranchAddress("t1px", &t1px, &b_t1px);
    m_Chain->SetBranchAddress("t1py", &t1py, &b_t1py);
    m_Chain->SetBranchAddress("t1pz", &t1pz, &b_t1pz);
    m_Chain->SetBranchAddress("SFTwpos1[5][3]", SFTwpos1, &b_SFTwpos1);
    m_Chain->SetBranchAddress("SFTwpos2[5][3]", SFTwpos2, &b_SFTwpos2);
    m_Chain->SetBranchAddress("SFTpx", &SFTpx, &b_SFTpx);
    m_Chain->SetBranchAddress("SFTpy", &SFTpy, &b_SFTpy);
    m_Chain->SetBranchAddress("SFTpz", &SFTpz, &b_SFTpz);
    notify();
}

// void DetectorData::adjustThreshold() {
//     if (m_is_threshold_adjusted || !m_Chain) return;

//     int HG_TARGET_ADC_Thr[256];
//     int LG_TARGET_ADC_Thr[256];
//     int HG_SFT_ADC_Thr[128];
//     int LG_SFT_ADC_Thr[128];

//     calculateThreshold(256, HG_TARGET_ADC_Thr, CW::TARGET_ADC_Ped_HG, CW::TARGET_ADC_Thr_HG_Offset);
//     calculateThreshold(256, LG_TARGET_ADC_Thr, CW::TARGET_ADC_Ped_LG, CW::TARGET_ADC_Thr_LG_Offset);
//     calculateThreshold(128, HG_SFT_ADC_Thr, CW::SFT_ADC_Thr_HG, CW::SFT_ADC_Thr_HG_Offset);
//     calculateThreshold(128, LG_SFT_ADC_Thr, CW::SFT_ADC_Thr_LG, CW::SFT_ADC_Thr_LG_Offset);

//     Int_t TDC_min_SFT = CW::SFT_TDC_min[0];
//     Int_t TDC_max_SFT = CW::SFT_TDC_max[0];

//     //for (int j_TARGET=0; j_TARGET<256; j_TARGET++){
//     //    ADC_High_TARGET[j_TARGET] -= HG_TARGET_ADC_Thr[j_TARGET];
//     //    ADC_Low_TARGET[j_TARGET] -= LG_TARGET_ADC_Thr[j_TARGET];
//     //}

//     for (int j_TARGET=0; j_TARGET<256; j_TARGET++){
//         ADC_High_TARGET[j_TARGET] -= int(round(HG_TARGET_ADC_Thr[j_TARGET]));
//         ADC_Low_TARGET[j_TARGET] -= int(round(LG_TARGET_ADC_Thr[j_TARGET]));
//     }

//     for (Int_t j_SFT=0; j_SFT<128; j_SFT++){
//         ADC_High_SFT[j_SFT] -= HG_SFT_ADC_Thr[j_SFT];
//         ADC_Low_SFT[j_SFT] -= LG_SFT_ADC_Thr[j_SFT];
//     }

//     for(int i=0; i<12; i++){
//         ADC_TOF1[i] = ADC_TOF1U[i]-CW::TOF1U_ADC_Thr[i];
//         ADC_TOF1[i+12] = ADC_TOF1D[i]-CW::TOF1D_ADC_Thr[i];
//         ADC_TOF1U[i] -= CW::TOF1U_ADC_Thr[i];
//         ADC_TOF1D[i] -= CW::TOF1D_ADC_Thr[i];
//     }

//     for (Int_t j_TOF2=0; j_TOF2<12; j_TOF2++) {
//         ADC_TOF2AO[j_TOF2] -= CW::TOF2AO_ADC_Thr[j_TOF2];
//         ADC_TOF2BO[j_TOF2] -= CW::TOF2BO_ADC_Thr[j_TOF2];
//         ADC_TOF2AI[j_TOF2] -= CW::TOF2AI_ADC_Thr[j_TOF2];
//         ADC_TOF2BI[j_TOF2] -= CW::TOF2BI_ADC_Thr[j_TOF2];
//     }

//     for(Int_t j_C2=0; j_C2<56; j_C2++){
//         ADC_C2X_R[j_C2] -= CW::ADC_C2X_Thr_R[j_C2] + CW::MWPC_Thr_Offset_C2X;
//         ADC_C2X_L[j_C2] -= CW::ADC_C2X_Thr_L[j_C2] + CW::MWPC_Thr_Offset_C2X;
//     }

//     for(Int_t j_C3=0; j_C3<64; j_C3++){
//         ADC_C3X_R[j_C3] -= CW::ADC_C3X_Thr_R[j_C3] + CW::MWPC_Thr_Offset_C3X;
//         ADC_C3X_L[j_C3] -= CW::ADC_C3X_Thr_L[j_C3] + CW::MWPC_Thr_Offset_C3X;
//     }

//     for(Int_t j_C4=0; j_C4<72; j_C4++){
//         ADC_C4X_R[j_C4] -= CW::ADC_C4X_Thr_R[j_C4] + CW::MWPC_Thr_Offset_C4X;
//         ADC_C4X_L[j_C4] -= CW::ADC_C4X_Thr_L[j_C4] + CW::MWPC_Thr_Offset_C4X;
//     }

//     for(Int_t j_CY=0; j_CY<16; j_CY++){
//         ADC_C2Y_R[j_CY] -= CW::ADC_C2Y_Thr_R[j_CY] + CW::MWPC_Thr_Offset_C2Y;
//         ADC_C2Y_L[j_CY] -= CW::ADC_C2Y_Thr_L[j_CY] + CW::MWPC_Thr_Offset_C2Y;
//         ADC_C3Y_R[j_CY] -= CW::ADC_C3Y_Thr_R[j_CY] + CW::MWPC_Thr_Offset_C3Y;
//         ADC_C3Y_L[j_CY] -= CW::ADC_C3Y_Thr_L[j_CY] + CW::MWPC_Thr_Offset_C3Y;
//         ADC_C4Y_R[j_CY] -= CW::ADC_C4Y_Thr_R[j_CY] + CW::MWPC_Thr_Offset_C4Y;
//         ADC_C4Y_L[j_CY] -= CW::ADC_C4Y_Thr_L[j_CY] + CW::MWPC_Thr_Offset_C4Y;
//     }

//     m_is_threshold_adjusted = kTRUE;
// }

// Bool_t DetectorData::isThresholdAdjusted() {
//     return m_is_threshold_adjusted;
// }

// void DetectorData::correctTimeWalk() {
//     if (m_is_time_walk_corrected || !m_Chain) return;

//     Double_t par_in[256][3] = {0.};
//     Double_t par_err[356][3] = {0.};
//     Int_t ADCmax = 3450;
//     Double_t Yfi = 0.;
//     Double_t Ani = 0.;
//     Double_t Yni = 0.;
//     Double_t Tpi = 0.;
//     Bool_t NoFile = kFALSE;

//     char ParsTarg1[100];
//     sprintf(ParsTarg1,"TimeWalk%d.dat", RunNum);

//     if(!std::ifstream(ParsTarg1)) NoFile = true;

//     std::ifstream parTARGdat(ParsTarg1, std::ios::in);
//     Int_t ij = 0;
//     Int_t ik = 0;

//     // Read in parametersParsTarg1 and their errors. (errors not used)
//     for (Int_t ii = 0; ii < CP::nBars; ii++) {
//         parTARGdat >> ij >> ik >> par_in[ii][0] >> par_err[ii][0];
//         parTARGdat >> ij >> ik >> par_in[ii][1] >> par_err[ii][1];
//         parTARGdat >> ij >> ik >> par_in[ii][2] >> par_err[ii][2];
//     }

//     for (Int_t ii = 0; ii < 256; ii++) {
//         Yfi = par_in[ii][0] - par_in[ii][1] / sqrt(ADCmax - par_in[ii][2]);
//         Ani = ADC_High_TARGET[ii] - CW::TARGET_ADC_Ped_HG[ii]; //SEB

//         if ((Ani >= CW::TARGET_ADC_Thr_HG_Offset) && (Ani < ADCmax)) { // SEB
//             Yni = par_in[ii][0] - par_in[ii][1] / sqrt(Ani - par_in[ii][2]);
//             Tpi = Yfi - Yni;
//             for (int jj = 0; jj < 16; jj++) {
//                 if (TDC_LE_TARGET[ii][jj] > 0) TDC_LE_TARGET[ii][jj] += Tpi;
//            }
//         }
//     }

//     m_is_time_walk_corrected = kTRUE;
// }

// Bool_t DetectorData::isTimeWalkCorrected() {
//     return m_is_time_walk_corrected;
// }

TString SimulationData::makeRootFilePath(Int_t runNumber) {
    // Return the file path of the root file matching the given run number.
    // User must have set the $path_merged environment variable to the directory
    // containing the root files.
    TString path_merged(getenv("path_merged"));
    TString file_name("G4Run" + TString::Itoa(runNumber, 10) + ".root");

    return path_merged + "/" + file_name;
}

TString SimulationData::getRootFilePath() {
    return m_root_file_path;
}

int SimulationData::getEvent(int entry, Int_t getall) {
    // Read contents of an entry (i.e. an event)
    // CAUTION: This method resets changes made to the public member data arrays (e.g. TDC_Trig etc.)
    // to the original root file values.
    if (!m_Chain) return 0;

    //m_is_threshold_adjusted = kFALSE;
    //m_is_time_walk_corrected = kFALSE;

    return static_cast<int>(m_Chain->GetEntry(static_cast<Long64_t>(entry), getall));
}

int SimulationData::getNumberOfEvents() {
    // Return the number of entries in the m_Chain.
    if (!m_Chain) return 0;
    return static_cast<int>(m_Chain->GetEntries());
}

Long64_t SimulationData::loadTree(Long64_t entry) {
// Set the environment to read one entry
    if (!m_Chain) return -5;
    Long64_t centry = m_Chain->LoadTree(entry);
    if (centry < 0) return centry;
    if (m_Chain->GetTreeNumber() != m_Current) {
        m_Current = m_Chain->GetTreeNumber();
        Notify();
    }
    return centry;
}


Int_t SimulationData::cut(Long64_t entry) {
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
    if (entry) return 1;
    else return -1;
}

Bool_t SimulationData::notify() {
    // The notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void SimulationData::show(Long64_t entry) {
// Print contents of entry.
// If entry is not specified, print current entry
    if (!m_Chain) return;
    m_Chain->Show(entry);
}


void SimulationData::loop() {
//   In a ROOT session, you can do:
//      root> .L DetectorData.C
//      root> DetectorData d
//      root> d.GetEntry(12); // Fill t data members with entry number 12
//      root> d.Show();       // Show values of entry 12
//      root> d.Show(16);     // Read and show values of entry 16
//      root> d.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    m_Chain->SetBranchStatus("*",0);  // disable all branches
//    m_Chain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    m_Chain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
    if (m_Chain == 0) return;

    Long64_t nentries = m_Chain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = loadTree(jentry);
        if (ientry < 0) break;
        nb = m_Chain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;
    }
}
