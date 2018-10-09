#include "DetectorData.hpp"
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
ClassImp(DetectorData);

DetectorData::DetectorData(int run_number, int event_number)
        : RunNum(run_number),
          m_Chain(0),
          m_is_threshold_adjusted(kFALSE),
          m_is_time_walk_corrected(kFALSE) {
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
    f->GetObject("Tree", tree);
    init(tree);
    getEvent(event_number);
}

DetectorData::DetectorData(TTree *tree) : m_Chain(0) {
// If parameter tree is not specified (or zero), try to connect the Run3994MS.root file
// from the user defined environment variable "path_merged".
    if (tree == 0) {
        TFile *f = (TFile *) gROOT->GetListOfFiles()->FindObject(
                "$path_merged/Run3994MS.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("$path_merged/Run3994MS.root");
        }
        f->GetObject("Tree", tree);
    }
    init(tree);
}

DetectorData::~DetectorData() {
    if (!m_Chain) return;
    delete m_Chain->GetCurrentFile();
}

void DetectorData::init(TTree *tree) {
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

    m_Chain->SetBranchAddress("EvNum", &EvNum, &m_event);
    m_Chain->SetBranchAddress("EvFlag", EvFlag, &m_EvFlag);
    m_Chain->SetBranchAddress("EvTag", EvTag, &m_EvTag);
    m_Chain->SetBranchAddress("TDC_Trig", TDC_Trig, &m_TDC_Trig);
    m_Chain->SetBranchAddress("TDC_Hodo", TDC_Hodo, &m_TDC_Hodo);
    m_Chain->SetBranchAddress("TDC_Ck", TDC_Ck, &m_TDC_Ck);
    m_Chain->SetBranchAddress("TDC_Cpi", TDC_Cpi, &m_TDC_Cpi);
    m_Chain->SetBranchAddress("ADC_High_SFT", ADC_High_SFT, &m_ADC_High_SFT);
    m_Chain->SetBranchAddress("ADC_Low_SFT", ADC_Low_SFT, &m_ADC_Low_SFT);
    m_Chain->SetBranchAddress("TDC_LE_SFT", TDC_LE_SFT, &m_TDC_LE_SFT);
    m_Chain->SetBranchAddress("TDC_TE_SFT", TDC_TE_SFT, &m_TDC_TE_SFT);
    m_Chain->SetBranchAddress("ADC_High_TARGET", ADC_High_TARGET, &m_ADC_High_TARGET);
    m_Chain->SetBranchAddress("ADC_Low_TARGET", ADC_Low_TARGET, &m_ADC_Low_TARGET);
    m_Chain->SetBranchAddress("TDC_LE_TARGET", TDC_LE_TARGET, &m_TDC_LE_TARGET);
    m_Chain->SetBranchAddress("TDC_TE_TARGET", TDC_TE_TARGET, &m_TDC_TE_TARGET);
    m_Chain->SetBranchAddress("MWPCADC", MWPCADC, &m_MWPCADC);
    m_Chain->SetBranchAddress("ADC_C2X_R", ADC_C2X_R, &m_ADC_C2X_R);
    m_Chain->SetBranchAddress("ADC_C2X_L", ADC_C2X_L, &m_ADC_C2X_L);
    m_Chain->SetBranchAddress("ADC_C2Y_R", ADC_C2Y_R, &m_ADC_C2Y_R);
    m_Chain->SetBranchAddress("ADC_C2Y_L", ADC_C2Y_L, &m_ADC_C2Y_L);
    m_Chain->SetBranchAddress("ADC_C3X_R", ADC_C3X_R, &m_ADC_C3X_R);
    m_Chain->SetBranchAddress("ADC_C3X_L", ADC_C3X_L, &m_ADC_C3X_L);
    m_Chain->SetBranchAddress("ADC_C3Y_R", ADC_C3Y_R, &m_ADC_C3Y_R);
    m_Chain->SetBranchAddress("ADC_C3Y_L", ADC_C3Y_L, &m_ADC_C3Y_L);
    m_Chain->SetBranchAddress("ADC_C4X_R", ADC_C4X_R, &m_ADC_C4X_R);
    m_Chain->SetBranchAddress("ADC_C4X_L", ADC_C4X_L, &m_ADC_C4X_L);
    m_Chain->SetBranchAddress("ADC_C4Y_R", ADC_C4Y_R, &m_ADC_C4Y_R);
    m_Chain->SetBranchAddress("ADC_C4Y_L", ADC_C4Y_L, &m_ADC_C4Y_L);
    m_Chain->SetBranchAddress("ADC_TOF1U", ADC_TOF1U, &m_ADC_TOF1U);
    m_Chain->SetBranchAddress("ADC_TOF1D", ADC_TOF1D, &m_ADC_TOF1D);
    m_Chain->SetBranchAddress("TDC_TOF1U", TDC_TOF1U, &m_TDC_TOF1U);
    m_Chain->SetBranchAddress("TDC_TOF1D", TDC_TOF1D, &m_TDC_TOF1D);
    m_Chain->SetBranchAddress("ADC_TOF2AO", ADC_TOF2AO, &m_ADC_TOF2AO);
    m_Chain->SetBranchAddress("ADC_TOF2AI", ADC_TOF2AI, &m_ADC_TOF2AI);
    m_Chain->SetBranchAddress("ADC_TOF2BO", ADC_TOF2BO, &m_ADC_TOF2BO);
    m_Chain->SetBranchAddress("ADC_TOF2BI", ADC_TOF2BI, &m_ADC_TOF2BI);
    m_Chain->SetBranchAddress("TDC_TOF2AO", TDC_TOF2AO, &m_TDC_TOF2AO);
    m_Chain->SetBranchAddress("TDC_TOF2AI", TDC_TOF2AI, &m_TDC_TOF2AI);
    m_Chain->SetBranchAddress("TDC_TOF2BO", TDC_TOF2BO, &m_TDC_TOF2BO);
    m_Chain->SetBranchAddress("TDC_TOF2BI", TDC_TOF2BI, &m_TDC_TOF2BI);
    m_Chain->SetBranchAddress("ADC_ACU", ADC_ACU, &m_ADC_ACU);
    m_Chain->SetBranchAddress("ADC_ACD", ADC_ACD, &m_ADC_ACD);
    m_Chain->SetBranchAddress("TDC_ACU", TDC_ACU, &m_TDC_ACU);
    m_Chain->SetBranchAddress("TDC_ACD", TDC_ACD, &m_TDC_ACD);
    m_Chain->SetBranchAddress("ADC_GV", ADC_GV, &m_ADC_GV);
    m_Chain->SetBranchAddress("TDC_GV", TDC_GV, &m_TDC_GV);
    m_Chain->SetBranchAddress("ADC_TTC", ADC_TTC, &m_ADC_TTC);
    m_Chain->SetBranchAddress("TDC_TTC", TDC_TTC, &m_TDC_TTC);
    m_Chain->SetBranchAddress("ADC_PGC", ADC_PGC, &m_ADC_PGC);
    m_Chain->SetBranchAddress("TDC_PGC", TDC_PGC, &m_TDC_PGC);
    m_Chain->SetBranchAddress("ADC_PGC_Gap", ADC_PGC_Gap, &m_ADC_PGC_Gap);
    m_Chain->SetBranchAddress("TDC_PGC_Gap", TDC_PGC_Gap, &m_TDC_PGC_Gap);
    m_Chain->SetBranchAddress("HR_TDC", HR_TDC, &m_HR_TDC);
    m_Chain->SetBranchAddress("TKO_ADC", TKO_ADC, &m_TKO_ADC);
    m_Chain->SetBranchAddress("V792_ADC", V792_ADC, &m_V792_ADC);
    m_Chain->SetBranchAddress("VT48_TDC", VT48_TDC, &m_VT48_TDC);
    m_Chain->SetBranchAddress("TDC_TOF", TDC_TOF, &m_TDC_TOF);
    m_Chain->SetBranchAddress("AC_ADC", AC_ADC, &m_AC_ADC);
    m_Chain->SetBranchAddress("ADC_TOF1", ADC_TOF1, &m_ADC_TOF1);
    m_Chain->SetBranchAddress("ADC_TOF2", ADC_TOF2, &m_ADC_TOF2);
    m_Chain->SetBranchAddress("TDC_TOF1", TDC_TOF1, &m_TDC_TOF1);
    m_Chain->SetBranchAddress("TDC_TOF2", TDC_TOF2, &m_TDC_TOF2);
    m_Chain->SetBranchAddress("ADC_TOF", ADC_TOF, &m_ADC_TOF);
    notify();
}

void DetectorData::adjustThreshold() {
    if (m_is_threshold_adjusted || !m_Chain) return;

    int HG_TARGET_ADC_Thr[256];
    int LG_TARGET_ADC_Thr[256];
    int HG_SFT_ADC_Thr[128];
    int LG_SFT_ADC_Thr[128];

    calculateThreshold(256, HG_TARGET_ADC_Thr, CW::TARGET_ADC_Ped_HG, CW::TARGET_ADC_Thr_HG_Offset);
    calculateThreshold(256, LG_TARGET_ADC_Thr, CW::TARGET_ADC_Ped_LG, CW::TARGET_ADC_Thr_LG_Offset);
    calculateThreshold(128, HG_SFT_ADC_Thr, CW::SFT_ADC_Thr_HG, CW::SFT_ADC_Thr_HG_Offset);
    calculateThreshold(128, LG_SFT_ADC_Thr, CW::SFT_ADC_Thr_LG, CW::SFT_ADC_Thr_LG_Offset);

    Int_t TDC_min_SFT = CW::SFT_TDC_min[0];
    Int_t TDC_max_SFT = CW::SFT_TDC_max[0];

    //for (int j_TARGET=0; j_TARGET<256; j_TARGET++){
    //    ADC_High_TARGET[j_TARGET] -= HG_TARGET_ADC_Thr[j_TARGET];
    //    ADC_Low_TARGET[j_TARGET] -= LG_TARGET_ADC_Thr[j_TARGET];
    //}
    
    for (int j_TARGET=0; j_TARGET<256; j_TARGET++){
        ADC_High_TARGET[j_TARGET] -= int(round(HG_TARGET_ADC_Thr[j_TARGET]));  
        ADC_Low_TARGET[j_TARGET] -= int(round(LG_TARGET_ADC_Thr[j_TARGET]));
    }

    for (Int_t j_SFT=0; j_SFT<128; j_SFT++){
        ADC_High_SFT[j_SFT] -= HG_SFT_ADC_Thr[j_SFT];
        ADC_Low_SFT[j_SFT] -= LG_SFT_ADC_Thr[j_SFT];
    }

    for(int i=0; i<12; i++){
        ADC_TOF1[i] = ADC_TOF1U[i]-CW::TOF1U_ADC_Thr[i];
        ADC_TOF1[i+12] = ADC_TOF1D[i]-CW::TOF1D_ADC_Thr[i];
        ADC_TOF1U[i] -= CW::TOF1U_ADC_Thr[i];
        ADC_TOF1D[i] -= CW::TOF1D_ADC_Thr[i];
    }

    for (Int_t j_TOF2=0; j_TOF2<12; j_TOF2++) {
        ADC_TOF2AO[j_TOF2] -= CW::TOF2AO_ADC_Thr[j_TOF2];
        ADC_TOF2BO[j_TOF2] -= CW::TOF2BO_ADC_Thr[j_TOF2];
        ADC_TOF2AI[j_TOF2] -= CW::TOF2AI_ADC_Thr[j_TOF2];
        ADC_TOF2BI[j_TOF2] -= CW::TOF2BI_ADC_Thr[j_TOF2];
    }

    for(Int_t j_C2=0; j_C2<56; j_C2++){
        ADC_C2X_R[j_C2] -= CW::ADC_C2X_Thr_R[j_C2] + CW::MWPC_Thr_Offset_C2X;
        ADC_C2X_L[j_C2] -= CW::ADC_C2X_Thr_L[j_C2] + CW::MWPC_Thr_Offset_C2X;
    }

    for(Int_t j_C3=0; j_C3<64; j_C3++){
        ADC_C3X_R[j_C3] -= CW::ADC_C3X_Thr_R[j_C3] + CW::MWPC_Thr_Offset_C3X;
        ADC_C3X_L[j_C3] -= CW::ADC_C3X_Thr_L[j_C3] + CW::MWPC_Thr_Offset_C3X;
    }

    for(Int_t j_C4=0; j_C4<72; j_C4++){
        ADC_C4X_R[j_C4] -= CW::ADC_C4X_Thr_R[j_C4] + CW::MWPC_Thr_Offset_C4X;
        ADC_C4X_L[j_C4] -= CW::ADC_C4X_Thr_L[j_C4] + CW::MWPC_Thr_Offset_C4X;
    }

    for(Int_t j_CY=0; j_CY<16; j_CY++){
        ADC_C2Y_R[j_CY] -= CW::ADC_C2Y_Thr_R[j_CY] + CW::MWPC_Thr_Offset_C2Y;
        ADC_C2Y_L[j_CY] -= CW::ADC_C2Y_Thr_L[j_CY] + CW::MWPC_Thr_Offset_C2Y;
        ADC_C3Y_R[j_CY] -= CW::ADC_C3Y_Thr_R[j_CY] + CW::MWPC_Thr_Offset_C3Y;
        ADC_C3Y_L[j_CY] -= CW::ADC_C3Y_Thr_L[j_CY] + CW::MWPC_Thr_Offset_C3Y;
        ADC_C4Y_R[j_CY] -= CW::ADC_C4Y_Thr_R[j_CY] + CW::MWPC_Thr_Offset_C4Y;
        ADC_C4Y_L[j_CY] -= CW::ADC_C4Y_Thr_L[j_CY] + CW::MWPC_Thr_Offset_C4Y;
    }

    m_is_threshold_adjusted = kTRUE;
}

Bool_t DetectorData::isThresholdAdjusted() {
    return m_is_threshold_adjusted;
}

void DetectorData::correctTimeWalk() {
    if (m_is_time_walk_corrected || !m_Chain) return;

    Double_t par_in[256][3] = {0.};
    Double_t par_err[356][3] = {0.};
    Int_t ADCmax = 3450;
    Double_t Yfi = 0.;
    Double_t Ani = 0.;
    Double_t Yni = 0.;
    Double_t Tpi = 0.;
    Bool_t NoFile = kFALSE;

    char ParsTarg1[100];
    sprintf(ParsTarg1,"TimeWalk%d.dat", RunNum);

    if(!std::ifstream(ParsTarg1)) NoFile = true;

    std::ifstream parTARGdat(ParsTarg1, std::ios::in);
    Int_t ij = 0;
    Int_t ik = 0;

    // Read in parametersParsTarg1 and their errors. (errors not used)
    for (Int_t ii = 0; ii < CP::nBars; ii++) {
        parTARGdat >> ij >> ik >> par_in[ii][0] >> par_err[ii][0];
        parTARGdat >> ij >> ik >> par_in[ii][1] >> par_err[ii][1];
        parTARGdat >> ij >> ik >> par_in[ii][2] >> par_err[ii][2];
    }

    for (Int_t ii = 0; ii < 256; ii++) {
        Yfi = par_in[ii][0] - par_in[ii][1] / sqrt(ADCmax - par_in[ii][2]);
        Ani = ADC_High_TARGET[ii] - CW::TARGET_ADC_Ped_HG[ii]; //SEB

        if ((Ani >= CW::TARGET_ADC_Thr_HG_Offset) && (Ani < ADCmax)) { // SEB
            Yni = par_in[ii][0] - par_in[ii][1] / sqrt(Ani - par_in[ii][2]);
            Tpi = Yfi - Yni;
            for (int jj = 0; jj < 16; jj++) {
                if (TDC_LE_TARGET[ii][jj] > 0) TDC_LE_TARGET[ii][jj] += Tpi; 
           }
        }
    }

    m_is_time_walk_corrected = kTRUE;
}

Bool_t DetectorData::isTimeWalkCorrected() {
    return m_is_time_walk_corrected;
}

TString DetectorData::makeRootFilePath(Int_t runNumber) {
    // Return the file path of the root file matching the given run number.
    // User must have set the $path_merged environment variable to the directory
    // containing the root files.
    TString path_merged(getenv("path_merged"));
    TString file_name("Run" + TString::Itoa(runNumber, 10) + "MS.root");

    return path_merged + "/" + file_name;
}

TString DetectorData::getRootFilePath() {
    return m_root_file_path;
}

int DetectorData::getEvent(int entry, Int_t getall) {
    // Read contents of an entry (i.e. an event)
    // CAUTION: This method resets changes made to the public member data arrays (e.g. TDC_Trig etc.)
    // to the original root file values.
    if (!m_Chain) return 0;

    m_is_threshold_adjusted = kFALSE;
    m_is_time_walk_corrected = kFALSE;

    return static_cast<int>(m_Chain->GetEntry(static_cast<Long64_t>(entry), getall));
}

int DetectorData::getNumberOfEvents() {
    // Return the number of entries in the m_Chain.
    if (!m_Chain) return 0;
    return static_cast<int>(m_Chain->GetEntries());
}

Long64_t DetectorData::loadTree(Long64_t entry) {
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


Int_t DetectorData::cut(Long64_t entry) {
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
    if (entry) return 1;
    else return -1;
}

Bool_t DetectorData::notify() {
    // The notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void DetectorData::show(Long64_t entry) {
// Print contents of entry.
// If entry is not specified, print current entry
    if (!m_Chain) return;
    m_Chain->Show(entry);
}


void DetectorData::loop() {
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