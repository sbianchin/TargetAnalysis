//
// Created by Jack Hong on 2018-05-16. (jhong@alumni.ubc.ca)
//

#include "DetectorData.h"
#include "TFile.h"

void TestDetectorData() {
    cout << "Test started" << std::endl;

    // Test TTree constructor
    TFile *f = new TFile("$path_merged/Run3994MS.root");
    DetectorData data((TTree *) f->Get("Tree"));
    cout << "Construncted TTreeGeneratedClass object." << std::endl;
    cout << data.fChain->GetEntries() << std::endl;

    // Test run_number constructor
    DetectorData data2(3994);
    cout << data.fChain->GetEntries() << std::endl;
    cout << data.ADC_High_SFT[0] << std::endl;
}