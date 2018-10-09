/*
 * Created by Jack Hong on 2018-05-25.
 * Macro to load the required libraries using ROOT's ACLiC.
 * Comment out libraries you do not wish to load to speed up root start up.
 *
 * NOTE: Order matters here. You must load dependencies first :(
 */

#include "TClass.h"

void LoadLibrariesACLiC() {

    gROOT->ProcessLine(".L Parameters/DetectorGeometry.cpp+");
    gROOT->ProcessLine(".L Parameters/CutsAndWindows.cpp+");
    gROOT->ProcessLine(".L Parameters/KEKCCFile.cpp+");
    gROOT->ProcessLine(".L Parameters/DEBUG.cpp+");

    // Load classes and functions from ClassDefinitions/ and Functions/
    gROOT->ProcessLine(".L Functions/calculateThreshold.cpp+");
    gROOT->ProcessLine(".L ClassDefinitions/DetectorData.cpp+");
    gROOT->ProcessLine(".L ClassDefinitions/SimulationData.cpp+");
    gROOT->ProcessLine(".L ClassDefinitions/Track.cpp+");
    gROOT->ProcessLine(".L ClassDefinitions/EventPlot.cpp+");
    gROOT->ProcessLine(".L ClassDefinitions/TargetBar.cpp+");
    gROOT->ProcessLine(".L ClassDefinitions/Target.cpp+");

    gROOT->ProcessLine(".L Functions/determineTOF1Gap.cpp+");
    gROOT->ProcessLine(".L Functions/findGoodTargetEvents.cpp+");
    gROOT->ProcessLine(".L Functions/findGoodTOFEvents.cpp+");
    gROOT->ProcessLine(".L Functions/findGoodMWPCEvents.cpp+");
    gROOT->ProcessLine(".L Functions/intersect.cpp+");
    gROOT->ProcessLine(".L Functions/selectHitBars.cpp+");
    gROOT->ProcessLine(".L Functions/findKaons.cpp+");
    gROOT->ProcessLine(".L Functions/findLeptons.cpp+");
    gROOT->ProcessLine(".L Functions/helperFunctions.cpp+");
    gROOT->ProcessLine(".L Functions/leptonFitHelperFunctions.cpp+");
    gROOT->ProcessLine(".L Functions/findKaonTDCAverage.cpp+");
    gROOT->ProcessLine(".L Functions/findKaonCentroid.cpp+");
    gROOT->ProcessLine(".L Functions/pruningFunctions.cpp+");
    gROOT->ProcessLine(".L Functions/findKaonStop.cpp+");
    gROOT->ProcessLine(".L Functions/SFTfunctions.cpp+");
    gROOT->ProcessLine(".L Functions/analyzeEventFunctions.cpp+");
    gROOT->ProcessLine(".L Functions/makeGraph.cpp+");
    gROOT->ProcessLine(".L Functions/getSecondaryTrackEndVertex.cpp+");
    gROOT->ProcessLine(".L Functions/selectPrimaryTrackBars.cpp+");
    gROOT->ProcessLine(".L Functions/selectSecondaryTrackBars.cpp+");
    gROOT->ProcessLine(".L Functions/selectSecondaryTrackBars2.cpp+");
    gROOT->ProcessLine(".L Functions/fitTrack.cpp+");
    gROOT->ProcessLine(".L Functions/printFunctions.cpp+");
    gROOT->ProcessLine(".L Functions/findMWPCClusters.cpp+");
    gROOT->ProcessLine(".L Functions/plotEvent.cpp+");
    gROOT->ProcessLine(".L Functions/drawTwoPaths.cpp+");

    // Load macros from the Macros directory
    gROOT->ProcessLine(".L DisplayEvent.C+");
    //gROOT->ProcessLine(".L AnalyzeEvent.C+");
    gROOT->ProcessLine(".L BatchAnalysis.C+");
    gROOT->ProcessLine(".L AnalyzeTwoTracksEvent.C+");
}