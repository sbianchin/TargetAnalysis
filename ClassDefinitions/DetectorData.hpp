
/*
 * Created by Jack Hong on 2018-05-28 (jhong@alumni.ubc.ca)
 *
 * Usage: for loading and manipulating TREK data from root files. Instantiation
 * of this class initializes the ROOT Tree. Assumes root file is organized like
 * in Run3994MS.root.
 *
 * NB: Changes to root file layout will require changes to this class.
 *
 * Class automatically loaded on ROOT start up by the rootlogon.C script found in the offline_new/Macros directory
 * if you are working in that directory. Otherwise, you will need to load it with ".L DetectorData.C".
 *
 * EXAMPLE:
 *    // Load the data from run 3994 (Run3994MS.root) and set the arrays to data from event 9
 *    DetectorData data(3994, 9);
 *
 *    data.correctTimeWalk();      // apply time walk corrections to event 9 data
 *    data.isTimeWalkCorrected();  // true
 *    data.ADC_High_TARGET;        // get the ADC_High_TARGET array (data members are public)
 *    data.getEvent(12);           // switch to event 12
 *
 *    data.isTimeWalkCorrected()  // false because event switched
 *    data.getEvent(9)            // switch back to event 9
 *    data.isTimeWalkCorrected()  // false because GetEntry() resets data to root file values.
 */

#ifndef DetectorData_h
#define DetectorData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

class DetectorData : public TObject {
private:
    TTree *m_Chain;   //! pointer to the analyzed TTree or TChain
    Int_t m_Current;  //! current Tree number in a TChain
    TString m_root_file_path;
    Bool_t m_is_threshold_adjusted; //!
    Bool_t m_is_time_walk_corrected; //!

    // private function used to make the root file path.
    virtual TString makeRootFilePath(Int_t run_number);

    // Fixed size dimensions of array or collections stored in the TTree if any.
    // Use detectorData.m_Chain->GetEntry(3) to get the entries for event 3.
    // (This is already implemented by the getEntry public method).

    // List of branches
    TBranch *m_event;    //! DO NOT REMOVE these comments.
    TBranch *m_EvFlag;   //! They exclude a data member from the Streamer. (See ROOT manual)
    TBranch *m_EvTag;    //!
    TBranch *m_TDC_Trig;   //!
    TBranch *m_TDC_Hodo;   //!
    TBranch *m_TDC_Ck;   //!
    TBranch *m_TDC_Cpi;   //!
    TBranch *m_ADC_High_SFT;   //!
    TBranch *m_ADC_Low_SFT;   //!
    TBranch *m_TDC_LE_SFT;   //!
    TBranch *m_TDC_TE_SFT;   //!
    TBranch *m_ADC_High_TARGET;   //!
    TBranch *m_ADC_Low_TARGET;   //!
    TBranch *m_TDC_LE_TARGET;   //!
    TBranch *m_TDC_TE_TARGET;   //!
    TBranch *m_MWPCADC;   //!
    TBranch *m_ADC_C2X_R;   //!
    TBranch *m_ADC_C2X_L;   //!
    TBranch *m_ADC_C2Y_R;   //!
    TBranch *m_ADC_C2Y_L;   //!
    TBranch *m_ADC_C3X_R;   //!
    TBranch *m_ADC_C3X_L;   //!
    TBranch *m_ADC_C3Y_R;   //!
    TBranch *m_ADC_C3Y_L;   //!
    TBranch *m_ADC_C4X_R;   //!
    TBranch *m_ADC_C4X_L;   //!
    TBranch *m_ADC_C4Y_R;   //!
    TBranch *m_ADC_C4Y_L;   //!
    TBranch *m_ADC_TOF1U;   //!
    TBranch *m_ADC_TOF1D;   //!
    TBranch *m_TDC_TOF1U;   //!
    TBranch *m_TDC_TOF1D;   //!
    TBranch *m_ADC_TOF2AO;   //!
    TBranch *m_ADC_TOF2AI;   //!
    TBranch *m_ADC_TOF2BO;   //!
    TBranch *m_ADC_TOF2BI;   //!
    TBranch *m_TDC_TOF2AO;   //!
    TBranch *m_TDC_TOF2AI;   //!
    TBranch *m_TDC_TOF2BO;   //!
    TBranch *m_TDC_TOF2BI;   //!
    TBranch *m_ADC_ACU;   //!
    TBranch *m_ADC_ACD;   //!
    TBranch *m_TDC_ACU;   //!
    TBranch *m_TDC_ACD;   //!
    TBranch *m_ADC_GV;   //!
    TBranch *m_TDC_GV;   //!
    TBranch *m_ADC_TTC;   //!
    TBranch *m_TDC_TTC;   //!
    TBranch *m_ADC_PGC;   //!
    TBranch *m_TDC_PGC;   //!
    TBranch *m_ADC_PGC_Gap;   //!
    TBranch *m_TDC_PGC_Gap;   //!
    TBranch *m_HR_TDC;   //!
    TBranch *m_TKO_ADC;   //!
    TBranch *m_V792_ADC;   //!
    TBranch *m_VT48_TDC;   //!
    TBranch *m_TDC_TOF;   //!
    TBranch *m_AC_ADC;   //!
    TBranch *m_ADC_TOF1;   //!
    TBranch *m_ADC_TOF2;   //!
    TBranch *m_TDC_TOF1;   //!
    TBranch *m_TDC_TOF2;   //!
    TBranch *m_ADC_TOF;   //!

public:

    Int_t RunNum;

    // Declaration of leaf types. Names come from root file leaf names.
    Int_t EvNum;  // note: 0 based index for event numbering
    Bool_t EvFlag[40];
    Int_t EvTag[14];
    Int_t TDC_Trig[2][16];
    Int_t TDC_Hodo[24][16];
    Int_t TDC_Ck[14][16];
    Int_t TDC_Cpi[14][16];
    Int_t ADC_High_SFT[128];
    Int_t ADC_Low_SFT[128];
    Int_t TDC_LE_SFT[128][16];
    Int_t TDC_TE_SFT[128][16];
    Int_t ADC_High_TARGET[256];
    Int_t ADC_Low_TARGET[256];
    Int_t TDC_LE_TARGET[256][16];
    Int_t TDC_TE_TARGET[256][16];
    Int_t MWPCADC[512];
    Int_t ADC_C2X_R[56];
    Int_t ADC_C2X_L[56];
    Int_t ADC_C2Y_R[16];
    Int_t ADC_C2Y_L[16];
    Int_t ADC_C3X_R[64];
    Int_t ADC_C3X_L[64];
    Int_t ADC_C3Y_R[16];
    Int_t ADC_C3Y_L[16];
    Int_t ADC_C4X_R[72];
    Int_t ADC_C4X_L[72];
    Int_t ADC_C4Y_R[16];
    Int_t ADC_C4Y_L[16];
    Int_t ADC_TOF1U[12];
    Int_t ADC_TOF1D[12];
    Int_t TDC_TOF1U[12];
    Int_t TDC_TOF1D[12];
    Int_t ADC_TOF2AO[12];
    Int_t ADC_TOF2AI[12];
    Int_t ADC_TOF2BO[12];
    Int_t ADC_TOF2BI[12];
    Int_t TDC_TOF2AO[12];
    Int_t TDC_TOF2AI[12];
    Int_t TDC_TOF2BO[12];
    Int_t TDC_TOF2BI[12];
    Int_t ADC_ACU[12];
    Int_t ADC_ACD[12];
    Int_t TDC_ACU[12][16];
    Int_t TDC_ACD[12][16];
    Int_t ADC_GV[12];
    Int_t TDC_GV[12][16];
    Int_t ADC_TTC[12];
    Int_t TDC_TTC[12][16];
    Int_t ADC_PGC[96];
    Int_t TDC_PGC[96][16];
    Int_t ADC_PGC_Gap[12][8];
    Int_t TDC_PGC_Gap[12][8][16];
    Int_t HR_TDC[96];
    Int_t TKO_ADC[96];
    Int_t V792_ADC[256];
    Int_t VT48_TDC[256][16];
    Int_t TDC_TOF[96];
    Int_t AC_ADC[24];
    Int_t ADC_TOF1[24];
    Int_t ADC_TOF2[56];
    Int_t TDC_TOF1[24];
    Int_t TDC_TOF2[56];
    Int_t ADC_TOF[96];

    DetectorData(int run_number=3994, int event_number=0);

    DetectorData(TTree *tree = 0);

    virtual ~DetectorData();

    virtual void init(TTree *tree);

    virtual void adjustThreshold();

    virtual Bool_t isThresholdAdjusted();

    virtual void correctTimeWalk();

    virtual Bool_t isTimeWalkCorrected();

    virtual TString getRootFilePath();

    virtual int getEvent(int entry, Int_t getall = 0);

    virtual int getNumberOfEvents();

    virtual Long64_t loadTree(Long64_t entry);

    virtual Int_t cut(Long64_t entry);

    virtual Bool_t notify();

    virtual void show(Long64_t entry = -1);

    virtual void loop();

    // line required to work with ROOT
    ClassDef(DetectorData, 1);
};

#endif // DetectorData_h
