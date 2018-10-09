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

#ifndef SimulationData_h
#define SimulationData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

class SimulationData : public TObject {
private:
    TTree *m_Chain;   //! pointer to the analyzed TTree or TChain
    Int_t m_Current;  //! current Tree number in a TChain
    TString m_root_file_path;
    //Bool_t m_is_threshold_adjusted; //
    //Bool_t m_is_time_walk_corrected; //

    // private function used to make the root file path.
    virtual TString makeRootFilePath(Int_t run_number);

    // Fixed size dimensions of array or collections stored in the TTree if any.
    // Use detectorData.m_Chain->GetEntry(3) to get the entries for event 3.
    // (This is already implemented by the getEntry public method).

    // List of branches
    TBranch        *b_n;   //!
    TBranch        *b_s_hit;   //!
    //TBranch        *b_x-hit;   //!
    TBranch        *b_px;   //!
    TBranch        *b_py;   //!
    TBranch        *b_pz;   //!
    TBranch        *b_u_x;   //!
    TBranch        *b_u_y;   //!
    TBranch        *b_u_z;   //!
    TBranch        *b_genEvt;   //!
    TBranch        *b_genEne;   //!
    TBranch        *b_cosTh;   //!
    TBranch        *b_sinTh;   //!
    TBranch        *b_Phi;   //!
    TBranch        *b_dv_x;   //!
    TBranch        *b_dv_y;   //!
    TBranch        *b_dv_z;   //!
    TBranch        *b_targetE;   //!
    TBranch        *b_targetEe;   //!
    TBranch        *b_targetdE;   //!
    TBranch        *b_targetdEe;   //!
    TBranch        *b_targetdt;   //!
    TBranch        *b_targL;   //!
    TBranch        *b_delta_x;   //!
    TBranch        *b_delta_y;   //!
    TBranch        *b_delta_z;   //!
    TBranch        *b_delta_ux;   //!
    TBranch        *b_delta_uy;   //!
    TBranch        *b_delta_uz;   //!
    TBranch        *b_delta_length;   //!
    TBranch        *b_delta_energy;   //!
    TBranch        *b_delta_time;   //!
    TBranch        *b_delta_stop_x;   //!
    TBranch        *b_delta_stop_y;   //!
    TBranch        *b_delta_stop_z;   //!
    TBranch        *b_delta_elast;   //!
    TBranch        *b_delta_trackID;   //!
    TBranch        *b_delta_parentID;   //!
    TBranch        *b_tof1dt;   //!
    TBranch        *b_t1pL;   //!
    TBranch        *b_t1;   //!
    TBranch        *b_tof1E;   //!
    TBranch        *b_tof1wpos;   //!
    TBranch        *b_tof1TrackID;   //!
    TBranch        *b_jtrack;   //!
    TBranch        *b_tof1charge;   //!
    TBranch        *b_secondP;   //!
    TBranch        *b_tof1N;   //!
    TBranch        *b_t1px;   //!
    TBranch        *b_t1py;   //!
    TBranch        *b_t1pz;   //!
    TBranch        *b_SFTwpos1;   //!
    TBranch        *b_SFTwpos2;   //!
    TBranch        *b_SFTpx;   //!
    TBranch        *b_SFTpy;   //!
    TBranch        *b_SFTpz;   //!

public:

    Int_t RunNum;

    // Declaration of leaf types
    Int_t           n;
    Int_t           s_hit;
    Int_t           x_hit;
    Double_t        px[10];
    Double_t        py[10];
    Double_t        pz[10];
    Double_t        u_x;
    Double_t        u_y;
    Double_t        u_z;
    Double_t        genEvt;
    Double_t        genEne[10];
    Double_t        cosTh;
    Double_t        sinTh;
    Double_t        Phi;
    Double_t        dv_x;
    Double_t        dv_y;
    Double_t        dv_z;
    Double_t        targetE;
    Double_t        targetEe;
    Double_t        targetdE[256];
    Double_t        targetdEe[256];
    Double_t        targetdt[256];
    Double_t        targL;
    Double_t        delta_x;
    Double_t        delta_y;
    Double_t        delta_z;
    Double_t        delta_ux;
    Double_t        delta_uy;
    Double_t        delta_uz;
    Double_t        delta_length;
    Double_t        delta_energy;
    Double_t        delta_time;
    Double_t        delta_stop_x;
    Double_t        delta_stop_y;
    Double_t        delta_stop_z;
    Double_t        delta_elast;
    Int_t           delta_trackID;
    Int_t           delta_parentID;
    Double_t        tof1dt;
    Double_t        t1pL;
    Double_t        t1;
    Double_t        tof1E[5];
    Double_t        tof1wpos[5][3];
    Int_t           tof1TrackID[5];
    Int_t           jtrack[5];
    Double_t        tof1charge[5];
    Char_t          secondP[5][100];
    Int_t           tof1N[5];
    Double_t        t1px;
    Double_t        t1py;
    Double_t        t1pz;
    Double_t        SFTwpos1[5][3];
    Double_t        SFTwpos2[5][3];
    Double_t        SFTpx;
    Double_t        SFTpy;
    Double_t        SFTpz;

    SimulationData(int run_number=822, int event_number=0);

    SimulationData(TTree *tree = 0);

    virtual ~SimulationData();

    virtual void init(TTree *tree);

    //virtual void adjustThreshold();

    //virtual Bool_t isThresholdAdjusted();

    //virtual void correctTimeWalk();

    //virtual Bool_t isTimeWalkCorrected();

    virtual TString getRootFilePath();

    virtual int getEvent(int entry, Int_t getall = 0);

    virtual int getNumberOfEvents();

    virtual Long64_t loadTree(Long64_t entry);

    virtual Int_t cut(Long64_t entry);

    virtual Bool_t notify();

    virtual void show(Long64_t entry = -1);

    virtual void loop();

    // line required to work with ROOT
    ClassDef(SimulationData, 1);
};

#endif // DetectorData_h
