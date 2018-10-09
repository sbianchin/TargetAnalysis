/* 
 * Created by Sebastien Bianchin on 2018-07-31. (s.bianchin@triumf.ca)
 */

#include <iostream>
#include "plotEvent.hpp"
#include "helperFunctions.hpp"

#include "TCanvas.h"
#include "TEllipse.h"
#include "TH2F.h"
#include "TGraphErrors.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TMarker.h"
#include "TArrow.h"

#include "DetectorGeometry.hpp"
#include "CommonParameters.hpp"
#include "CutsAndWindows.hpp"

#include "CommonStructs.hpp"
#include "DetectorData.hpp"
#include "EventPlot.hpp"


namespace DG = DetectorGeometry;
namespace CP = CommonParameters;
namespace CW = CutsAndWindows;


int kaonFiber(double x_bar, double y_bar){

    double dist_min = 999.;
    int i_min = 999;


    for(int i=0; i<256; i++){
        if(sqrt(pow(abs(DG::Xloc[i] - x_bar),2) + pow(abs(DG::Yloc[i] - y_bar),2)) < dist_min){
            dist_min = sqrt(pow(abs(DG::Xloc[i] - x_bar),2) + pow(abs(DG::Yloc[i] - y_bar),2));
            i_min = i;
        }
    }

    return i_min;
}


void TOF1_Detector_Attributes() {
  DG::Gap1l->SetLineWidth(10);
  DG::Gap1l->SetLineColor(15);

  DG::Gap2l->SetLineWidth(10);
  DG::Gap2l->SetLineColor(15);

  DG::Gap3l->SetLineWidth(10);
  DG::Gap3l->SetLineColor(15);

  DG::Gap4l->SetLineWidth(10);
  DG::Gap4l->SetLineColor(15);

  DG::Gap5l->SetLineWidth(10);
  DG::Gap5l->SetLineColor(15);

  DG::Gap6l->SetLineWidth(10);
  DG::Gap6l->SetLineColor(15);

  DG::Gap7l->SetLineWidth(10);
  DG::Gap7l->SetLineColor(15);

  DG::Gap8l->SetLineWidth(10);
  DG::Gap8l->SetLineColor(15);

  DG::Gap9l->SetLineWidth(10);
  DG::Gap9l->SetLineColor(15);

  DG::Gap10l->SetLineWidth(10);
  DG::Gap10l->SetLineColor(15);

  DG::Gap11l->SetLineWidth(10);
  DG::Gap11l->SetLineColor(15);

  DG::Gap12l->SetLineWidth(10);
  DG::Gap12l->SetLineColor(15);
}

void drawPruning(int Run_Number, int ievt, vector<int> vec_kaons,
                 vector<double> vec_kstop_0,
                 vector<int> vec_triangle_leptons, vector<int> vec_line_leptons, vector<int> vec_pruned_backtracking,
                 vector<double> V_X_pruning_area, vector<double> V_Y_pruning_area,
                 TLine *line_fit_kaons, TLine *line_fit_leptons,
                 vector<double> vec_pruning_line1, vector<double> vec_pruning_line2,
                 TGraph *gr_kaons_final, TGraph *gr_kaons_unfitted,
                 TGraph *gr_leptons_0){

  TCanvas *c_pruning;
  c_pruning = new TCanvas("Pruning","PRUNING PROCEDURE",50,500,700,700);
  c_pruning->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",0,0, "ProcEvent(Int_t,Int_t,Int_t,TObject*)");
  c_pruning->Divide(3,3);

  float R_TARGET = 29.0; 
  TEllipse *ell_Target = new TEllipse(0, 0, R_TARGET, 0); 

  TH2F *h_Pruning2[2];   
  char Title_Pruning2[3][100];   
  char Name_Pruning2[2][100];

  sprintf(Title_Pruning2[0],"Linear Pruning  |  Run %d, Evt %d", Run_Number, ievt); 
  sprintf(Name_Pruning2[0],"Linear Pruning"); 

  sprintf(Title_Pruning2[1],"Triangular Pruning  |  Run %d, Evt %d", Run_Number, ievt); 
  sprintf(Name_Pruning2[1],"Triangular Pruning"); 

  sprintf(Title_Pruning2[2],"Backtracking Method  |  Run %d, Evt %d", Run_Number, ievt); 

  h_Pruning2[0] = new TH2F(Name_Pruning2[0],Title_Pruning2[0],100,-50,50,100,-50,50);
  h_Pruning2[1] = new TH2F(Name_Pruning2[1],Title_Pruning2[1],100,-50,50,100,-50,50);


  /////// KAONS
  vector<double> vec_x_kaons;   vec_x_kaons.clear();
  vector<double> vec_y_kaons;   vec_y_kaons.clear();
  vector<double> vec_ex_kaons;  vec_ex_kaons.clear();
  vector<double> vec_ey_kaons;  vec_ey_kaons.clear();

  for(unsigned int i=0; i<vec_kaons.size(); i++){
    vec_x_kaons.push_back(DG::Xloc[vec_kaons[i]]);
    vec_y_kaons.push_back(DG::Yloc[vec_kaons[i]]);
    vec_ex_kaons.push_back(DG::TARGET_Errors_X);
    vec_ey_kaons.push_back(DG::TARGET_Errors_Y);
  }

  TGraph *gr_kaons;
  gr_kaons = new TGraphErrors(vec_kaons.size(),&vec_x_kaons[0],&vec_y_kaons[0],
                              &vec_ex_kaons[0],&vec_ey_kaons[0]);
    
  gr_kaons->SetMarkerColor(4);
  gr_kaons->SetMarkerStyle(21);
  gr_kaons->SetMarkerSize(0.8);

  line_fit_kaons->SetLineWidth(2);
  line_fit_kaons->SetLineColor(4);
    
  line_fit_leptons->SetLineWidth(2);
  line_fit_leptons->SetLineColor(2);
    
  //******* Kstop_0
  vector<double> vec_x_kstop_0;   vec_x_kstop_0.clear();
  vector<double> vec_y_kstop_0;   vec_y_kstop_0.clear();

  vec_x_kstop_0.push_back(vec_kstop_0[0]);
  vec_y_kstop_0.push_back(vec_kstop_0[1]);
  
  TGraph *gr_Kstop_0;
  gr_Kstop_0 = new TGraph(vec_x_kstop_0.size(),&vec_x_kstop_0[0],&vec_y_kstop_0[0]);
  gr_Kstop_0->SetMarkerStyle(34);
  gr_Kstop_0->SetMarkerColor(1);
  gr_Kstop_0->SetMarkerSize(1.3);

  /////// PRUNED LEPTONS
  //****** Triangular pruning
  vector<double> vec_x_triangle_leptons;      vec_x_triangle_leptons.clear();
  vector<double> vec_y_triangle_leptons;      vec_y_triangle_leptons.clear();
  vector<double> vec_ex_triangle_leptons;     vec_ex_triangle_leptons.clear();
  vector<double> vec_ey_triangle_leptons;     vec_ey_triangle_leptons.clear();

  vector<double> vec_x_triangle_leptons_pr;   vec_x_triangle_leptons_pr.clear();
  vector<double> vec_y_triangle_leptons_pr;   vec_y_triangle_leptons_pr.clear();  

  for(unsigned int i=0; i<vec_triangle_leptons.size(); i++){
    vec_x_triangle_leptons.push_back(DG::Xloc[vec_triangle_leptons[i]]);
    vec_y_triangle_leptons.push_back(DG::Yloc[vec_triangle_leptons[i]]);
    vec_ex_triangle_leptons.push_back(DG::TARGET_Errors_X);
    vec_ey_triangle_leptons.push_back(DG::TARGET_Errors_Y);
    vec_x_triangle_leptons_pr.push_back(DG::Xloc[vec_triangle_leptons[i]]);
    vec_y_triangle_leptons_pr.push_back(DG::Yloc[vec_triangle_leptons[i]]);     
  }

  TGraph *gr_triangle_leptons;
  gr_triangle_leptons = new TGraphErrors(vec_triangle_leptons.size(),&vec_x_triangle_leptons[0],&vec_y_triangle_leptons[0],
                                         &vec_ex_triangle_leptons[0],&vec_ey_triangle_leptons[0]);
    
  gr_triangle_leptons->SetMarkerColor(2);
  gr_triangle_leptons->SetMarkerStyle(21);
  gr_triangle_leptons->SetMarkerSize(0.8);

  TGraph *gr_triangle_leptons_pr;
  gr_triangle_leptons_pr = new TGraph(vec_triangle_leptons.size(),&vec_x_triangle_leptons_pr[0],&vec_y_triangle_leptons_pr[0]);
    
  gr_triangle_leptons_pr->SetMarkerColor(3);
  gr_triangle_leptons_pr->SetMarkerStyle(21);
  gr_triangle_leptons_pr->SetMarkerSize(0.8);

  //Pruning Area
  TGraph *gr_pruning_area;
  gr_pruning_area = new TGraph(V_X_pruning_area.size(), &V_X_pruning_area[0], &V_Y_pruning_area[0]);
  gr_pruning_area->SetLineWidth(2);
  gr_pruning_area->SetLineColor(3);

  // ****** Linear pruning
  vector<double> vec_x_line_leptons;      vec_x_line_leptons.clear();
  vector<double> vec_y_line_leptons;      vec_y_line_leptons.clear();
  vector<double> vec_ex_line_leptons;     vec_ex_line_leptons.clear();
  vector<double> vec_ey_line_leptons;     vec_ey_line_leptons.clear();

  vector<double> vec_x_line_leptons_pr;   vec_x_line_leptons_pr.clear();
  vector<double> vec_y_line_leptons_pr;   vec_y_line_leptons_pr.clear();  

  for(unsigned int i=0; i<vec_line_leptons.size(); i++){
    vec_x_line_leptons.push_back(DG::Xloc[vec_line_leptons[i]]);
    vec_y_line_leptons.push_back(DG::Yloc[vec_line_leptons[i]]);
    vec_ex_line_leptons.push_back(DG::TARGET_Errors_X);
    vec_ey_line_leptons.push_back(DG::TARGET_Errors_Y);     
    vec_x_line_leptons_pr.push_back(DG::Xloc[vec_line_leptons[i]]);
    vec_y_line_leptons_pr.push_back(DG::Yloc[vec_line_leptons[i]]);     
  }

  TGraph *gr_line_leptons;
  gr_line_leptons = new TGraphErrors(vec_line_leptons.size(),&vec_x_line_leptons[0],&vec_y_line_leptons[0],
                                     &vec_ex_line_leptons[0],&vec_ey_line_leptons[0]);
   
  gr_line_leptons->SetMarkerColor(2);
  gr_line_leptons->SetMarkerStyle(21);
  gr_line_leptons->SetMarkerSize(0.8);

  TGraph *gr_line_leptons_pr;
  gr_line_leptons_pr = new TGraph(vec_line_leptons.size(),&vec_x_line_leptons_pr[0],&vec_y_line_leptons_pr[0]);
    
  gr_line_leptons_pr->SetMarkerColor(3);
  gr_line_leptons_pr->SetMarkerStyle(21);
  gr_line_leptons_pr->SetMarkerSize(0.8);

  gr_leptons_0->SetMarkerColor(2);
  gr_leptons_0->SetMarkerStyle(21);
  gr_leptons_0->SetMarkerSize(0.8);

  // Pruning Line
  TLine *pruning_line;
  pruning_line = new TLine(vec_pruning_line1[0], vec_pruning_line1[1], 
                           vec_pruning_line1[2], vec_pruning_line1[3]);
  
  pruning_line->SetLineWidth(2);
  pruning_line->SetLineColor(3);

  // Second Pruning Line if needed
  TLine *pruning_line2;     

  if(vec_pruning_line2.size()>0){
    pruning_line2 = new TLine(vec_pruning_line2[0], vec_pruning_line2[1], vec_pruning_line2[2], vec_pruning_line2[3]);
    pruning_line2->SetLineWidth(2);
    pruning_line2->SetLineColor(6);
  }
  else{
    pruning_line2 = new TLine(999., 999., 999., 999.);
  }


  // ****** Backtracking Method
  vector<double> vec_x_pruned_backtracking;         vec_x_pruned_backtracking.clear();
  vector<double> vec_y_pruned_backtracking;         vec_y_pruned_backtracking.clear();
  vector<double> vec_ex_pruned_backtracking;        vec_ex_pruned_backtracking.clear();
  vector<double> vec_ey_pruned_backtracking;        vec_ey_pruned_backtracking.clear();


  for(unsigned int i=0; i<vec_pruned_backtracking.size(); i++){
    vec_x_pruned_backtracking.push_back(DG::Xloc[vec_pruned_backtracking[i]]);
    vec_y_pruned_backtracking.push_back(DG::Yloc[vec_pruned_backtracking[i]]);
    vec_ex_pruned_backtracking.push_back(DG::TARGET_Errors_X);
    vec_ey_pruned_backtracking.push_back(DG::TARGET_Errors_Y);
  }

  TGraph *gr_backtracking;
  gr_backtracking = new TGraphErrors(vec_pruned_backtracking.size(), &vec_x_pruned_backtracking[0], &vec_y_pruned_backtracking[0],
                                     &vec_ex_pruned_backtracking[0], &vec_ey_pruned_backtracking[0]);
    
  gr_backtracking->SetMarkerColor(2);
  gr_backtracking->SetMarkerStyle(21);
  gr_backtracking->SetMarkerSize(0.8);


  TGraph *gr_pruned_backtracking;
  gr_pruned_backtracking = new TGraph(vec_pruned_backtracking.size(), &vec_x_pruned_backtracking[0], &vec_y_pruned_backtracking[0]);
    
  gr_pruned_backtracking->SetMarkerColor(3);
  gr_pruned_backtracking->SetMarkerStyle(21);
  gr_pruned_backtracking->SetMarkerSize(0.8);

  //gr_leptons_0->SetMarkerColor(2);
  //gr_leptons_0->SetMarkerStyle(21);
  //gr_leptons_0->SetMarkerSize(0.8);

  EventPlot* linearPlot = new EventPlot(Title_Pruning2[0]);
  EventPlot* triangularPlot = new EventPlot(Title_Pruning2[1]);
  EventPlot* backTrackingPlot = new EventPlot(Title_Pruning2[2]);


  /////// DRAWING 
  // PANEL 1  
  linearPlot->Frame(c_pruning,1);
  gr_kaons_final->Draw("sameP");
  line_fit_kaons->Draw("same");
  gr_leptons_0->Draw("sameP");
  line_fit_leptons->Draw("same");
  gr_Kstop_0->Draw("sameP");
 
  // PANEL 2
  linearPlot->Frame(c_pruning,2); 
  gr_kaons_final->Draw("sameP");
  line_fit_kaons->Draw("same");
  gr_leptons_0->Draw("sameP");
  line_fit_leptons->Draw("same");
  gr_line_leptons_pr->Draw("sameP");
  pruning_line->Draw("same");
  if(vec_pruning_line2.size()>0) pruning_line2->Draw("same");
  gr_Kstop_0->Draw("sameP");

  // PANEL 3
  linearPlot->Frame(c_pruning,3);
  gr_kaons_unfitted->Draw("sameP");
  gr_line_leptons->Draw("sameP");


  // PANEL 4
  triangularPlot->Frame(c_pruning,4);
  gr_kaons_final->Draw("sameP");
  line_fit_kaons->Draw("same");
  gr_leptons_0->Draw("sameP");
  line_fit_leptons->Draw("same");
  gr_Kstop_0->Draw("sameP");

  // PANEL 5
  triangularPlot->Frame(c_pruning,5);
  gr_kaons_final->Draw("sameP");
  line_fit_kaons->Draw("same");
  gr_leptons_0->Draw("sameP");
  line_fit_leptons->Draw("same");
  gr_triangle_leptons_pr->Draw("sameP");
  gr_pruning_area->Draw("same");
  gr_Kstop_0->Draw("sameP");

  // PANEL 6
  triangularPlot->Frame(c_pruning,6);
  gr_kaons_unfitted->Draw("sameP");
  gr_triangle_leptons->Draw("sameP");

  // PANEL 7
  backTrackingPlot->Frame(c_pruning,7);
  gr_kaons_final->Draw("sameP");
  line_fit_kaons->Draw("same");
  gr_leptons_0->Draw("sameP");
  line_fit_leptons->Draw("same");
  gr_Kstop_0->Draw("sameP");

  // PANEL 8
  backTrackingPlot->Frame(c_pruning,8);
  gr_kaons_final->Draw("sameP");
  line_fit_kaons->Draw("same");
  gr_leptons_0->Draw("sameP");
  line_fit_leptons->Draw("same");
  //gr_line_leptons_pr->Draw("sameP");
  gr_pruned_backtracking->Draw("sameP");
  //pruning_line->Draw("same");
  //if(vec_pruning_line2.size()>0) pruning_line2->Draw("same");
  gr_Kstop_0->Draw("sameP");

  // PANEL 9
  backTrackingPlot->Frame(c_pruning,9);
  gr_kaons_unfitted->Draw("sameP");
  gr_backtracking->Draw("sameP");

}

void drawFitting(bool to_rotate_leptons, bool to_rotate_kaons,
                 int Run_Number, int ievt, PruningType type,
                 TGraph *gr_leptons_fit1, TGraph *gr_leptons_fit2, TGraph *gr_leptons_fit3,
                 TGraph *gr_kaons_final, TLine *line_fit_kaons,
                 vector<double> vec_intersect_TOF1, 
                 double a1, double b1,
                 double a2, double b2,
                 double a3, double b3){

  TOF1_Detector_Attributes();

  char str_ctitle[100];
  if(type == line) sprintf(str_ctitle, "FITTING PROCEDURE  --  LINE PRUNING");
  else if(type == triangle) sprintf(str_ctitle, "FITTING PROCEDURE  --  TRIANGLE PRUNING");
  else if(type == backtracking) sprintf(str_ctitle, "FITTING PROCEDURE  --  BACKTRACKING METHOD");

  TCanvas *c_fitting;
  c_fitting = new TCanvas("Fitting",str_ctitle,0,200,700,700);
  c_fitting->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",0,0, "ProcEvent(Int_t,Int_t,Int_t,TObject*)");
  c_fitting->Divide(2,2);

  TGaxis *A1 = new TGaxis(-50,50,50,50,"pol1",510,"-U");
  TGaxis *A2 = new TGaxis(50,-50,50,50,"pol1",510,"+U");

  TEllipse *ell_Target = new TEllipse(0, 0, CP::R_TARGET, 0); 
  TEllipse *ell = new TEllipse(0, 0, CP::R_TOF1, 0);
  TEllipse *ell_L1 = new TEllipse(0, 0, CP::R_SFT_L1, 0);
  
  ell->SetFillStyle(0);  ell_Target->SetFillStyle(0);  ell_L1->SetFillStyle(0);
  ell->SetLineColor(6);  ell_Target->SetLineColor(1);  ell_L1->SetLineColor(4);
  ell->SetLineWidth(1);  ell_Target->SetLineWidth(1);  ell_L1->SetLineWidth(1);

  char str_leptons_fit1[100];
  char str_leptons_fit2[100];
  char str_leptons_fit3[100];
  char str_kaons_fit[100];

  if(type == line){
    sprintf(str_leptons_fit1,"Lepton Fit 1  |  Run %d  --  Event %d  |  Line Pruning",Run_Number,ievt);
    sprintf(str_leptons_fit2,"Lepton Fit 2  |  Run %d  --  Event %d  |  Line Pruning",Run_Number,ievt);
    sprintf(str_leptons_fit3,"Lepton Fit 3  |  Run %d  --  Event %d  |  Line Pruning",Run_Number,ievt);
  }
  else if(type == triangle){
    sprintf(str_leptons_fit1,"Lepton Fit 1  |  Run %d  --  Event %d  |  Triangle Pruning",Run_Number,ievt);
    sprintf(str_leptons_fit2,"Lepton Fit 2  |  Run %d  --  Event %d  |  Triangle Pruning",Run_Number,ievt);
    sprintf(str_leptons_fit3,"Lepton Fit 3  |  Run %d  --  Event %d  |  Triangle Pruning",Run_Number,ievt);
  }
  else if(type == backtracking){
    sprintf(str_leptons_fit1,"Lepton Fit 1  |  Run %d  --  Event %d  |  Backtracking Method",Run_Number,ievt);
    sprintf(str_leptons_fit2,"Lepton Fit 2  |  Run %d  --  Event %d  |  Backtracking Method",Run_Number,ievt);
    sprintf(str_leptons_fit3,"Lepton Fit 3  |  Run %d  --  Event %d  |  Backtracking Method",Run_Number,ievt);
  }
    
  sprintf(str_kaons_fit,"Kaon Fit  |  Run %d  --  Event %d",Run_Number,ievt);  

  TH2F *h_leptons_fit1 = new TH2F("Leptons Fit1", str_leptons_fit1, 500, -50, 50, 500, -50, 50);
  TH2F *h_leptons_fit2 = new TH2F("Lepton Fit2", str_leptons_fit2, 500, -50, 50, 500, -50, 50);
  TH2F *h_leptons_fit3 = new TH2F("Lepton Fit3", str_leptons_fit3, 500, -50, 50, 500, -50, 50);
  TH2F *h_kaons_fit = new TH2F("Kaon Fit", str_kaons_fit, 500, -50, 50, 500, -50, 50);

  //TARGET CENTER
  vector<double> vec_xx_Target_Center;  vec_xx_Target_Center.clear();
  vector<double> vec_yy_Target_Center;  vec_yy_Target_Center.clear();
  vec_xx_Target_Center.push_back(0.);
  vec_yy_Target_Center.push_back(0.);

  TGraph *gr_Target_Center = new TGraph(vec_xx_Target_Center.size(),&vec_xx_Target_Center[0],&vec_yy_Target_Center[0]);
  gr_Target_Center->SetMarkerStyle(5);
  gr_Target_Center->SetMarkerColor(1);
  gr_Target_Center->SetMarkerSize(1);


  //FIT2 INTERSECT WITH TOF1
  vector<double> vec_x_intersect_TOF1;        vec_x_intersect_TOF1.clear();
  vector<double> vec_y_intersect_TOF1;        vec_y_intersect_TOF1.clear();
  vector<double> vec_intersect_TOF1_reverse;  vec_intersect_TOF1_reverse.clear();

  if(vec_intersect_TOF1.size()>0){
    if(to_rotate_leptons){

      vec_x_intersect_TOF1.push_back(vec_intersect_TOF1[1]);
      vec_y_intersect_TOF1.push_back(-vec_intersect_TOF1[0]);
    }
    else{
      vec_x_intersect_TOF1.push_back(vec_intersect_TOF1[0]);
      vec_y_intersect_TOF1.push_back(vec_intersect_TOF1[1]);
    }
  }

  TGraph *gr_intersect_TOF1;
  gr_intersect_TOF1 = new TGraph(vec_x_intersect_TOF1.size(), 
                      &vec_x_intersect_TOF1[0], &vec_y_intersect_TOF1[0]);

  gr_intersect_TOF1->SetMarkerColor(4);
  gr_intersect_TOF1->SetMarkerStyle(20);
  gr_intersect_TOF1->SetMarkerSize(0.8);


  /// FITTING LINES
  vector<double> vec_fitLine1;
  vector<double> vec_fitLine2;
  vector<double> vec_fitLine3;
  
  TLine *fit1_line = nullptr;
  TLine *fit2_line = nullptr;
  TLine *fit3_line = nullptr;


  if(to_rotate_leptons){

    vec_fitLine1 = defineFitLine(a1, b1);
    vec_fitLine2 = defineFitLine(a2, b2);
    vec_fitLine3 = defineFitLine(a3, b3);

    fit1_line = new TLine(vec_fitLine1[0], vec_fitLine1[1],
                          vec_fitLine1[2], vec_fitLine1[3]);
    fit2_line = new TLine(vec_fitLine2[0], vec_fitLine2[1],
                          vec_fitLine2[2], vec_fitLine2[3]);
    fit3_line = new TLine(vec_fitLine3[0], vec_fitLine3[1],
                          vec_fitLine3[2], vec_fitLine3[3]);

    fit1_line->SetLineWidth(2);
    fit1_line->SetLineColor(2);
    fit2_line->SetLineWidth(2);
    fit2_line->SetLineColor(2);
    fit3_line->SetLineWidth(2);
    fit3_line->SetLineColor(2);
  }

  EventPlot* leptonFit1Plot = new EventPlot(str_leptons_fit1);
  EventPlot* leptonFit2Plot = new EventPlot(str_leptons_fit2);
  EventPlot* leptonFit3Plot = new EventPlot(str_leptons_fit3);
  EventPlot* kaonFitPlot = new EventPlot(str_kaons_fit);


  /// PANEL 1
  leptonFit1Plot->Frame(c_fitting, 1);
  leptonFit1Plot->DrawTOF1(c_fitting,1);
  leptonFit1Plot->DrawSFT_L1(c_fitting,1);
  gr_leptons_fit1->Draw("sameP");
  if(to_rotate_leptons) fit1_line->Draw("same");


  /// PANEL 2
  kaonFitPlot->Frame(c_fitting, 2);
  kaonFitPlot->DrawTOF1(c_fitting,2);
  kaonFitPlot->DrawSFT_L1(c_fitting,2);
  gr_kaons_final->Draw("sameP");
  if(to_rotate_kaons) line_fit_kaons->Draw("same");


  /// PANEL 3
  leptonFit2Plot->Frame(c_fitting, 3);
  leptonFit2Plot->DrawTOF1(c_fitting,3);
  leptonFit2Plot->DrawSFT_L1(c_fitting,3);
  gr_leptons_fit2->Draw("sameP");
  if(to_rotate_leptons) fit2_line->Draw("same");
  if(vec_intersect_TOF1.size()>0) gr_intersect_TOF1->Draw("sameP");


  /// PANEL 4
  leptonFit3Plot->Frame(c_fitting, 4);
  leptonFit3Plot->DrawTOF1(c_fitting,4);
  leptonFit3Plot->DrawSFT_L1(c_fitting,4);
  gr_leptons_fit3->Draw("sameP");
  if(to_rotate_leptons) fit3_line->Draw("same");
}


void drawTargetFrame(int Run_Number, int ievt,
                     bool has_ADC_TOF1_hit[12], bool has_TDC_TOF1_hit[12],
                     bool has_ADC_TOF2_hit[12], bool has_TDC_TOF2_hit[12]){

  TLine *hline1 = new TLine(0.38,0.14,0.62,0.14);    hline1->SetLineWidth(2);
  TLine *hline2 = new TLine(0.30,0.18,0.70,0.18);    hline2->SetLineWidth(2);
  TLine *hline3 = new TLine(0.26,0.22,0.74,0.22);    hline3->SetLineWidth(2);
  TLine *hline4 = new TLine(0.22,0.26,0.78,0.26);    hline4->SetLineWidth(2);
  TLine *hline5 = new TLine(0.18,0.30,0.82,0.30);    hline5->SetLineWidth(2);
  TLine *hline6 = new TLine(0.18,0.34,0.82,0.34);    hline6->SetLineWidth(2);
  TLine *hline7 = new TLine(0.14,0.38,0.86,0.38);    hline7->SetLineWidth(2);
  TLine *hline8 = new TLine(0.14,0.42,0.86,0.42);    hline8->SetLineWidth(2);
  TLine *hline9 = new TLine(0.14,0.46,0.86,0.46);    hline9->SetLineWidth(2);
  TLine *hline10 = new TLine(0.14,0.50,0.86,0.50);   hline10->SetLineWidth(2);
  TLine *hline11 = new TLine(0.14,0.54,0.86,0.54);   hline11->SetLineWidth(2);
  TLine *hline12 = new TLine(0.14,0.58,0.86,0.58);   hline12->SetLineWidth(2);
  TLine *hline13 = new TLine(0.14,0.62,0.86,0.62);   hline13->SetLineWidth(2);
  TLine *hline14 = new TLine(0.18,0.66,0.82,0.66);   hline14->SetLineWidth(2);
  TLine *hline15 = new TLine(0.18,0.70,0.82,0.70);   hline15->SetLineWidth(2);
  TLine *hline16 = new TLine(0.22,0.74,0.78,0.74);   hline16->SetLineWidth(2);
  TLine *hline17 = new TLine(0.26,0.78,0.74,0.78);   hline17->SetLineWidth(2);
  TLine *hline18 = new TLine(0.30,0.82,0.70,0.82);   hline18->SetLineWidth(2);
  TLine *hline19 = new TLine(0.38,0.86,0.62,0.86);   hline19->SetLineWidth(2);

  TLine *vline1 = new TLine(0.14,0.38,0.14,0.62);    vline1->SetLineWidth(2);
  TLine *vline2 = new TLine(0.18,0.30,0.18,0.70);    vline2->SetLineWidth(2);
  TLine *vline3 = new TLine(0.22,0.26,0.22,0.74);    vline3->SetLineWidth(2);
  TLine *vline4 = new TLine(0.26,0.22,0.26,0.78);    vline4->SetLineWidth(2);
  TLine *vline5 = new TLine(0.30,0.18,0.30,0.82);    vline5->SetLineWidth(2);
  TLine *vline6 = new TLine(0.34,0.18,0.34,0.82);    vline6->SetLineWidth(2);
  TLine *vline7 = new TLine(0.38,0.14,0.38,0.86);    vline7->SetLineWidth(2);
  TLine *vline8 = new TLine(0.42,0.14,0.42,0.86);    vline8->SetLineWidth(2);
  TLine *vline9 = new TLine(0.46,0.14,0.46,0.86);    vline9->SetLineWidth(2);
  TLine *vline10 = new TLine(0.50,0.14,0.50,0.86);   vline10->SetLineWidth(2);
  TLine *vline11 = new TLine(0.54,0.14,0.54,0.86);   vline11->SetLineWidth(2);
  TLine *vline12 = new TLine(0.58,0.14,0.58,0.86);   vline12->SetLineWidth(2);
  TLine *vline13 = new TLine(0.62,0.14,0.62,0.86);   vline13->SetLineWidth(2);
  TLine *vline14 = new TLine(0.66,0.18,0.66,0.82);   vline14->SetLineWidth(2);
  TLine *vline15 = new TLine(0.70,0.18,0.70,0.82);   vline15->SetLineWidth(2);
  TLine *vline16 = new TLine(0.74,0.22,0.74,0.78);   vline16->SetLineWidth(2);
  TLine *vline17 = new TLine(0.78,0.26,0.78,0.74);   vline17->SetLineWidth(2);
  TLine *vline18 = new TLine(0.82,0.30,0.82,0.70);   vline18->SetLineWidth(2);
  TLine *vline19 = new TLine(0.86,0.38,0.86,0.62);   vline19->SetLineWidth(2);

  TLine *vblue1 = new TLine(0.38,0.70,0.38,0.74);      vblue1->SetLineWidth(5);   vblue1->SetLineColor(kBlue-9);
  TLine *vblue2 = new TLine(0.42,0.62,0.42,0.66);      vblue2->SetLineWidth(5);   vblue2->SetLineColor(kBlue-9);
  TLine *vblue3 = new TLine(0.30,0.54,0.30,0.58);      vblue3->SetLineWidth(5);   vblue3->SetLineColor(kBlue-9);
  TLine *vblue4 = new TLine(0.86,0.50,0.86,0.54);      vblue4->SetLineWidth(5);   vblue4->SetLineColor(kBlue-9);
  TLine *vblue5 = new TLine(0.70,0.42,0.70,0.46);      vblue5->SetLineWidth(5);   vblue5->SetLineColor(kBlue-9);
  TLine *vblue6 = new TLine(0.58,0.34,0.58,0.38);      vblue6->SetLineWidth(5);   vblue6->SetLineColor(kBlue-9);
  TLine *vblue7 = new TLine(0.62,0.26,0.62,0.30);      vblue7->SetLineWidth(5);   vblue7->SetLineColor(kBlue-9);
  TLine *vblue8 = new TLine(0.62,0.14,0.62,0.18);      vblue8->SetLineWidth(5);   vblue8->SetLineColor(kBlue-9);

  hline1->Draw();     vline1->Draw();     vblue2->Draw();
  hline2->Draw();     vline2->Draw();     vblue4->Draw();
  hline3->Draw();     vline3->Draw();     vblue6->Draw();
  hline4->Draw();     vline4->Draw();     vblue8->Draw();
  hline5->Draw();     vline5->Draw();
  hline6->Draw();     vline6->Draw();
  hline7->Draw();     vline7->Draw();
  hline8->Draw();     vline8->Draw();
  hline9->Draw();     vline9->Draw();
  hline10->Draw();    vline10->Draw();
  hline11->Draw();    vline11->Draw();
  hline12->Draw();    vline12->Draw();
  hline13->Draw();    vline13->Draw();
  hline14->Draw();    vline14->Draw();
  hline15->Draw();    vline15->Draw();
  hline16->Draw();    vline16->Draw();
  hline17->Draw();    vline17->Draw();
  hline18->Draw();    vline18->Draw();
  hline19->Draw();    vline19->Draw();

  TLine *TOF_line1 = new TLine(0.8278461,0.8278461,0.62,0.9478461); TOF_line1->SetLineWidth(10);  TOF_line1->SetLineColor(17);
  TLine *TOF_line2 = new TLine(0.9478461,0.62,0.8278461,0.8278461); TOF_line2->SetLineWidth(10);  TOF_line2->SetLineColor(17);
  TLine *TOF_line3 = new TLine(0.9478461,0.38,0.9478461,0.62);    TOF_line3->SetLineWidth(10);  TOF_line3->SetLineColor(17);
  TLine *TOF_line4 = new TLine(0.8278461,0.172154,0.9478461,0.38);  TOF_line4->SetLineWidth(10);  TOF_line4->SetLineColor(17);
  TLine *TOF_line5 = new TLine(0.62,0.0521539,0.8278461,0.172154);  TOF_line5->SetLineWidth(10);  TOF_line5->SetLineColor(17);
  TLine *TOF_line6 = new TLine(0.38,0.0521539,0.62,0.0521539);    TOF_line6->SetLineWidth(10);  TOF_line6->SetLineColor(17);
  TLine *TOF_line7 = new TLine(0.172539,0.172154,0.38,0.0521539);   TOF_line7->SetLineWidth(10);  TOF_line7->SetLineColor(17);
  TLine *TOF_line8 = new TLine(0.172539,0.172154,0.052539,0.38);    TOF_line8->SetLineWidth(10);  TOF_line8->SetLineColor(17);
  TLine *TOF_line9 = new TLine(0.052539,0.38,0.052539,0.62);      TOF_line9->SetLineWidth(10);  TOF_line9->SetLineColor(17);
  TLine *TOF_line10 = new TLine(0.052539,0.62,0.172539,0.8278461);  TOF_line10->SetLineWidth(10); TOF_line10->SetLineColor(17);
  TLine *TOF_line11 = new TLine(0.38,0.9478461,0.172539,0.8278461); TOF_line11->SetLineWidth(10); TOF_line11->SetLineColor(17);
  TLine *TOF_line12 = new TLine(0.62,0.9478461,0.38,0.9478461);   TOF_line12->SetLineWidth(10); TOF_line12->SetLineColor(17);

  TLine *TOF_line13 = new TLine(0.8348214,0.8393338,0.625558,0.9620716);    TOF_line13->SetLineWidth(20); TOF_line13->SetLineColor(15);
  TLine *TOF_line14 = new TLine(0.9603795,0.627551,0.8394717,0.8369272);    TOF_line14->SetLineWidth(20); TOF_line14->SetLineColor(15);
  TLine *TOF_line15 = new TLine(0.961,0.38,0.961,0.62);                     TOF_line15->SetLineWidth(20); TOF_line15->SetLineColor(15);
  TLine *TOF_line16 = new TLine(0.8394717,0.1630728,0.9580543,0.372449);    TOF_line16->SetLineWidth(20); TOF_line16->SetLineColor(15);
  TLine *TOF_line17 = new TLine(0.6232329,0.040335,0.8324963,0.1606662);    TOF_line17->SetLineWidth(20); TOF_line17->SetLineColor(15);
  TLine *TOF_line18 = new TLine(0.38,0.039,0.62,0.039);                     TOF_line18->SetLineWidth(20); TOF_line18->SetLineColor(15);
  TLine *TOF_line19 = new TLine(0.1651786,0.1606662,0.3721168,0.040335);    TOF_line19->SetLineWidth(20); TOF_line19->SetLineColor(15);
  TLine *TOF_line20 = new TLine(0.1605283,0.1630728,0.03962054,0.372449);   TOF_line20->SetLineWidth(20); TOF_line20->SetLineColor(15);
  TLine *TOF_line21 = new TLine(0.04,0.38,0.04,0.62);                       TOF_line21->SetLineWidth(20); TOF_line21->SetLineColor(15);
  TLine *TOF_line22 = new TLine(0.03962054,0.6251444,0.1605283,0.8345206);  TOF_line22->SetLineWidth(20); TOF_line22->SetLineColor(15);
  TLine *TOF_line23 = new TLine(0.3721168,0.9572584,0.1605283,0.8369272);   TOF_line23->SetLineWidth(20); TOF_line23->SetLineColor(15);
  TLine *TOF_line24 = new TLine(0.62,0.96,0.38,0.96);                       TOF_line24->SetLineWidth(20); TOF_line24->SetLineColor(15);

  /// TOF1 COLOURS
  if (has_ADC_TOF1_hit[0]) TOF_line1->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[0]) TOF_line1->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[0] && has_TDC_TOF1_hit[0]) TOF_line1->SetLineColor(3);

  if (has_ADC_TOF1_hit[1]) TOF_line2->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[1]) TOF_line2->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[1] && has_TDC_TOF1_hit[1]) TOF_line2->SetLineColor(3);

  if (has_ADC_TOF1_hit[2]) TOF_line3->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[2]) TOF_line3->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[2] && has_TDC_TOF1_hit[2]) TOF_line3->SetLineColor(3);

  if (has_ADC_TOF1_hit[3]) TOF_line4->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[3]) TOF_line4->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[3] && has_TDC_TOF1_hit[3]) TOF_line4->SetLineColor(3);

  if (has_ADC_TOF1_hit[4]) TOF_line5->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[4]) TOF_line5->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[4] && has_TDC_TOF1_hit[4]) TOF_line5->SetLineColor(3);

  if (has_ADC_TOF1_hit[5]) TOF_line6->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[5]) TOF_line6->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[5] && has_TDC_TOF1_hit[5]) TOF_line6->SetLineColor(3);

  if (has_ADC_TOF1_hit[6]) TOF_line7->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[6]) TOF_line7->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[6] && has_TDC_TOF1_hit[6]) TOF_line7->SetLineColor(3);

  if (has_ADC_TOF1_hit[7]) TOF_line8->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[7]) TOF_line8->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[7] && has_TDC_TOF1_hit[7]) TOF_line8->SetLineColor(3);

  if (has_ADC_TOF1_hit[8]) TOF_line9->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[8]) TOF_line9->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[8] && has_TDC_TOF1_hit[8]) TOF_line9->SetLineColor(3);

  if (has_ADC_TOF1_hit[9]) TOF_line10->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[9]) TOF_line10->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[9] && has_TDC_TOF1_hit[9]) TOF_line10->SetLineColor(3);

  if (has_ADC_TOF1_hit[10]) TOF_line11->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[10]) TOF_line11->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[10] && has_TDC_TOF1_hit[10]) TOF_line11->SetLineColor(3);

  if (has_ADC_TOF1_hit[11]) TOF_line12->SetLineColor(kOrange+10);
  if (has_TDC_TOF1_hit[11]) TOF_line12->SetLineColor(kYellow);
  if (has_ADC_TOF1_hit[11] && has_TDC_TOF1_hit[11]) TOF_line12->SetLineColor(3);
  
  /// SET TOFs COLOURS
  if (has_TDC_TOF2_hit[0] || has_ADC_TOF2_hit[0]) TOF_line13->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[0] && has_ADC_TOF2_hit[0]) TOF_line13->SetLineColor(3);

  if (has_TDC_TOF2_hit[1] || has_ADC_TOF2_hit[1]) TOF_line14->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[1] && has_ADC_TOF2_hit[1]) TOF_line14->SetLineColor(3);

  if (has_TDC_TOF2_hit[2] || has_ADC_TOF2_hit[2]) TOF_line15->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[2] && has_ADC_TOF2_hit[2]) TOF_line15->SetLineColor(3);

  if (has_TDC_TOF2_hit[3] || has_ADC_TOF2_hit[3]) TOF_line16->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[3] && has_ADC_TOF2_hit[3]) TOF_line16->SetLineColor(3);

  if (has_TDC_TOF2_hit[4] || has_ADC_TOF2_hit[4]) TOF_line17->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[4] && has_ADC_TOF2_hit[4]) TOF_line17->SetLineColor(3);

  if (has_TDC_TOF2_hit[5] || has_ADC_TOF2_hit[5]) TOF_line18->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[5] && has_ADC_TOF2_hit[5]) TOF_line18->SetLineColor(3);

  if (has_TDC_TOF2_hit[6] || has_ADC_TOF2_hit[6]) TOF_line19->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[6] && has_ADC_TOF2_hit[6]) TOF_line19->SetLineColor(3);

  if (has_TDC_TOF2_hit[7] || has_ADC_TOF2_hit[7]) TOF_line20->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[7] && has_ADC_TOF2_hit[7]) TOF_line20->SetLineColor(3);

  if (has_TDC_TOF2_hit[8] || has_ADC_TOF2_hit[8]) TOF_line21->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[8] && has_ADC_TOF2_hit[8]) TOF_line21->SetLineColor(3);

  if (has_TDC_TOF2_hit[9] || has_ADC_TOF2_hit[9]) TOF_line22->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[9] && has_ADC_TOF2_hit[9]) TOF_line22->SetLineColor(3);

  if (has_TDC_TOF2_hit[10] || has_ADC_TOF2_hit[10]) TOF_line23->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[10] && has_ADC_TOF2_hit[10]) TOF_line23->SetLineColor(3);

  if (has_TDC_TOF2_hit[11] || has_ADC_TOF2_hit[11]) TOF_line24->SetLineColor(kOrange+10);
  if (has_TDC_TOF2_hit[11] && has_ADC_TOF2_hit[11]) TOF_line24->SetLineColor(3);


  TOF_line13->Draw();   TOF_line1->Draw();
  TOF_line14->Draw();   TOF_line2->Draw();
  TOF_line15->Draw();   TOF_line3->Draw();
  TOF_line16->Draw();   TOF_line4->Draw();
  TOF_line17->Draw();   TOF_line5->Draw();
  TOF_line18->Draw();   TOF_line6->Draw();
  TOF_line19->Draw();   TOF_line7->Draw();
  TOF_line20->Draw();   TOF_line8->Draw();
  TOF_line21->Draw();   TOF_line9->Draw();
  TOF_line22->Draw();   TOF_line10->Draw();
  TOF_line23->Draw();   TOF_line11->Draw();
  TOF_line24->Draw();   TOF_line12->Draw();


  TLatex *tex_Legend_TARGET[36];
  tex_Legend_TARGET[0] = new TLatex(0.36,0.83,"0");       tex_Legend_TARGET[9] = new TLatex(0.09,0.47,"128");
  tex_Legend_TARGET[1] = new TLatex(0.28,0.79,"6");       tex_Legend_TARGET[10] = new TLatex(0.09,0.43,"146");
  tex_Legend_TARGET[2] = new TLatex(0.225,0.75,"16");     tex_Legend_TARGET[11] = new TLatex(0.09,0.39,"164");
  tex_Legend_TARGET[3] = new TLatex(0.185,0.71,"28");     tex_Legend_TARGET[12] = new TLatex(0.13,0.35,"182");
  tex_Legend_TARGET[4] = new TLatex(0.145,0.67,"42");     tex_Legend_TARGET[13] = new TLatex(0.13,0.31,"198");
  tex_Legend_TARGET[5] = new TLatex(0.145,0.63,"58");     tex_Legend_TARGET[14] = new TLatex(0.17,0.27,"214");
  tex_Legend_TARGET[6] = new TLatex(0.1025,0.59,"74");    tex_Legend_TARGET[15] = new TLatex(0.21,0.23,"228");
  tex_Legend_TARGET[7] = new TLatex(0.1025,0.55,"92");    tex_Legend_TARGET[16] = new TLatex(0.25,0.19,"240");
  tex_Legend_TARGET[8] = new TLatex(0.09,0.51,"110");     tex_Legend_TARGET[17] = new TLatex(0.33,0.15,"250");

  tex_Legend_TARGET[18] = new TLatex(0.635,0.83,"5");     tex_Legend_TARGET[27] = new TLatex(0.87,0.47,"145");
  tex_Legend_TARGET[19] = new TLatex(0.71,0.79,"15");     tex_Legend_TARGET[28] = new TLatex(0.87,0.43,"163");
  tex_Legend_TARGET[20] = new TLatex(0.75,0.75,"27");     tex_Legend_TARGET[29] = new TLatex(0.87,0.39,"181");
  tex_Legend_TARGET[21] = new TLatex(0.79,0.71,"41");     tex_Legend_TARGET[30] = new TLatex(0.83,0.35,"197");
  tex_Legend_TARGET[22] = new TLatex(0.83,0.67,"57");     tex_Legend_TARGET[31] = new TLatex(0.83,0.31,"213");
  tex_Legend_TARGET[23] = new TLatex(0.83,0.63,"73");     tex_Legend_TARGET[32] = new TLatex(0.79,0.27,"227");
  tex_Legend_TARGET[24] = new TLatex(0.885,0.59,"91");    tex_Legend_TARGET[33] = new TLatex(0.75,0.23,"239");
  tex_Legend_TARGET[25] = new TLatex(0.87,0.55,"109");    tex_Legend_TARGET[34] = new TLatex(0.71,0.19,"249");
  tex_Legend_TARGET[26] = new TLatex(0.87,0.51,"127");    tex_Legend_TARGET[35] = new TLatex(0.64,0.15,"255");

  for(int i=0; i<36; i++){
    tex_Legend_TARGET[i]->SetTextSize(0.03);
    tex_Legend_TARGET[i]->SetLineWidth(2);
    tex_Legend_TARGET[i]->Draw();
  }

  TMarker *palette_TARGET[10];
  double flag_size_palette=1.6;

  palette_TARGET[0] = new TMarker(0.54,0.075,21);     palette_TARGET[0]->SetMarkerColor(kOrange+10);    palette_TARGET[0]->SetMarkerSize(flag_size_palette);
  palette_TARGET[1] = new TMarker(0.58,0.075,21);     palette_TARGET[1]->SetMarkerColor(kOrange+7);     palette_TARGET[1]->SetMarkerSize(flag_size_palette);
  palette_TARGET[2] = new TMarker(0.62,0.075,21);     palette_TARGET[2]->SetMarkerColor(kOrange+1);     palette_TARGET[2]->SetMarkerSize(flag_size_palette);
  palette_TARGET[3] = new TMarker(0.66,0.075,21);     palette_TARGET[3]->SetMarkerColor(kOrange-4);     palette_TARGET[3]->SetMarkerSize(flag_size_palette);
  palette_TARGET[4] = new TMarker(0.70,0.075,21);     palette_TARGET[4]->SetMarkerColor(kYellow-9);     palette_TARGET[4]->SetMarkerSize(flag_size_palette);
  palette_TARGET[5] = new TMarker(0.74,0.075,21);     palette_TARGET[5]->SetMarkerColor(kYellow-7);     palette_TARGET[5]->SetMarkerSize(flag_size_palette);
  palette_TARGET[6] = new TMarker(0.78,0.075,21);     palette_TARGET[6]->SetMarkerColor(kYellow-0);     palette_TARGET[6]->SetMarkerSize(flag_size_palette);
  palette_TARGET[7] = new TMarker(0.82,0.075,21);     palette_TARGET[7]->SetMarkerColor(kSpring-4);     palette_TARGET[7]->SetMarkerSize(flag_size_palette);
  palette_TARGET[8] = new TMarker(0.86,0.075,21);     palette_TARGET[8]->SetMarkerColor(kSpring-2);     palette_TARGET[8]->SetMarkerSize(flag_size_palette);
  palette_TARGET[9] = new TMarker(0.90,0.075,21);     palette_TARGET[9]->SetMarkerColor(kGreen-0);      palette_TARGET[9]->SetMarkerSize(flag_size_palette);
  
  for(int i=0; i<10; i++) palette_TARGET[i]->Draw();

  TLatex *tex_palette_TARGET[10];
  int ADC_palette_TARGET[10]={0,3,6,9,12,15,18,21,24,27};
  char ADC_palette_string_TARGET[10][100];
  for(int j=0; j<10; j++) sprintf(ADC_palette_string_TARGET[j],"%d",ADC_palette_TARGET[j]);
  sprintf(ADC_palette_string_TARGET[9],"%d+",ADC_palette_TARGET[9]);

  tex_palette_TARGET[0] = new TLatex(0.510,0.04,ADC_palette_string_TARGET[0]);      tex_palette_TARGET[0]->SetTextSize(0.02);
  tex_palette_TARGET[1] = new TLatex(0.545,0.04,ADC_palette_string_TARGET[1]);      tex_palette_TARGET[1]->SetTextSize(0.02);
  tex_palette_TARGET[2] = new TLatex(0.585,0.04,ADC_palette_string_TARGET[2]);      tex_palette_TARGET[2]->SetTextSize(0.02);
  tex_palette_TARGET[3] = new TLatex(0.625,0.04,ADC_palette_string_TARGET[3]);      tex_palette_TARGET[3]->SetTextSize(0.02);
  tex_palette_TARGET[4] = new TLatex(0.665,0.04,ADC_palette_string_TARGET[4]);      tex_palette_TARGET[4]->SetTextSize(0.02);
  tex_palette_TARGET[5] = new TLatex(0.705,0.04,ADC_palette_string_TARGET[5]);      tex_palette_TARGET[5]->SetTextSize(0.02);
  tex_palette_TARGET[6] = new TLatex(0.745,0.04,ADC_palette_string_TARGET[6]);      tex_palette_TARGET[6]->SetTextSize(0.02);
  tex_palette_TARGET[7] = new TLatex(0.785,0.04,ADC_palette_string_TARGET[7]);      tex_palette_TARGET[7]->SetTextSize(0.02);
  tex_palette_TARGET[8] = new TLatex(0.825,0.04,ADC_palette_string_TARGET[8]);      tex_palette_TARGET[8]->SetTextSize(0.02);
  tex_palette_TARGET[9] = new TLatex(0.865,0.04,ADC_palette_string_TARGET[9]);      tex_palette_TARGET[9]->SetTextSize(0.02);
  TLatex *tex_palette_TARGET_scale = new TLatex(0.905,0.04,"x 100");              tex_palette_TARGET_scale->SetTextSize(0.02);
    
  for(int j=0; j<10; j++) tex_palette_TARGET[j]->Draw();
  tex_palette_TARGET_scale->Draw();

  char event_string[100];
  sprintf(event_string,"Run %d ; Event %d",Run_Number,ievt);
  TLatex *tex_event_TARGET;
  tex_event_TARGET = new TLatex(0.036,0.0,event_string);
  tex_event_TARGET->SetTextSize(0.038);
  tex_event_TARGET->SetLineWidth(2);
  tex_event_TARGET->Draw();
}

void drawEventDisplay(const DetectorData &data, int Run_Number, int ievt, bool to_restore,
                      int TOF1_gap, int selected_section, TLine *restored_line,
                      int TDC_min, int TDC_max, int TDC_min_Kstop, int TDC_max_Kstop,
                      bool has_kaon_sub, int kaon_bar, bool b_bbar, vector<double> vec_bbar,
                      bool has_ADC_TOF1_hit[12], bool has_TDC_TOF1_hit[12], bool has_ADC_TOF2_hit[12], bool has_TDC_TOF2_hit[12],
                      bool has_TDC_hit[256], int TDC_min_TARGET, bool has_TDC_hit_Kstop[256],
                      double angle_final, double delta_phi_deg, double ChiS_final, int ndf_final,
                      vector<double> vec_X_int_SFT, vector<double> vec_Y_int_SFT,
                      vector<double> vec_X_int_TARGET, vector<double> vec_Y_int_TARGET,
                      vector<double> vec_X_int_TOF1, vector<double> vec_Y_int_TOF1,
                      vector<double> vec_kstop_FINAL, vector<double> vec_intersect_TARGET_final,
                      TGraph *gr_leptons_final, TGraph *gr_kaons_final, TLine *line_fit_kaons,
                      PruningType type){

  TOF1_Detector_Attributes();

  char ch_Title1[100];
  char ch_Title2[100];
  char ch_Title3[100];
  sprintf(ch_Title1,"ADC HG Cut");
  sprintf(ch_Title2,"ADC HG & TDC Cut");
  sprintf(ch_Title3,"K Stop Cuts");

  char ch_Subtitle1[100];
  char ch_Subtitle2[100];
  char ch_Subtitle3[100];
  sprintf(ch_Subtitle1,"(ADC offset = %d)", CW::TARGET_ADC_Thr_HG_Offset);
  sprintf(ch_Subtitle2,"(ADC offset = %d | %d #leq TDC #leq %d)",CW::TARGET_ADC_Thr_HG_Offset,TDC_min,TDC_max);
  sprintf(ch_Subtitle3,"(ADC: HG #geq %d, LG #geq %d | %d #leq TDC K Stop #leq %d)",CW::HG_KAON,CW::LG_KAON,TDC_min_Kstop,TDC_max_Kstop);

  TLatex *tex_Title_panel1;
  tex_Title_panel1 = new TLatex(0.01759134,0.9295171,ch_Title1);
  tex_Title_panel1->SetTextSize(0.07645875);
  tex_Title_panel1->SetLineWidth(2);

  TLatex *tex_Title_panel2;
  tex_Title_panel2 = new TLatex(0.01759134,0.9295171,ch_Title2);
  tex_Title_panel2->SetTextSize(0.07645875);
  tex_Title_panel2->SetLineWidth(2);

  TLatex *tex_Title_panel3 = new TLatex(0.01759134,0.9295171,ch_Title3);
  tex_Title_panel3->SetTextSize(0.07);
  tex_Title_panel3->SetLineWidth(2);

  char ch_Kbar[100];
  sprintf(ch_Kbar, "K_{stop} Bar = %d",kaon_bar);

  TLatex *tex_Subtitle_panel1;
  tex_Subtitle_panel1 = new TLatex(0.01759134,0.88,ch_Subtitle1);
  tex_Subtitle_panel1->SetTextSize(0.04);
  tex_Subtitle_panel1->SetLineWidth(2);

  TLatex *tex_Subtitle_panel2;
  tex_Subtitle_panel2 = new TLatex(0.01759134,0.88,ch_Subtitle2);
  tex_Subtitle_panel2->SetTextSize(0.04);
  tex_Subtitle_panel2->SetLineWidth(2);

  TLatex *tex_Subtitle_panel3;
  tex_Subtitle_panel3 = new TLatex(0.01759134,0.88,ch_Subtitle3);
  tex_Subtitle_panel3->SetTextSize(0.04);
  tex_Subtitle_panel3->SetLineWidth(2);

  TLatex *tex_Kbar;
  tex_Kbar = new TLatex(0.64,0.9295171,ch_Kbar);
  tex_Kbar->SetTextSize(0.05);
  tex_Kbar->SetLineWidth(2);
  if(has_kaon_sub) tex_Kbar->SetTextColor(6);

  char Version[100] = "Version X";
  TLatex *tex_version;
  tex_version = new TLatex(0.75,0.0,Version);
  tex_version->SetTextSize(0.04);
  tex_version->SetLineWidth(2);

  char str_ctitle[100];
  if(type == line) sprintf(str_ctitle, "DISPLAY EVENT  --  LINE PRUNING");
  else if(type == triangle) sprintf(str_ctitle, "DISPLAY EVENT  --  TRIANGLE PRUNING");
  else if(type == backtracking) sprintf(str_ctitle, "DISPLAY EVENT  --  BACKTRACKING METHOD");

  TCanvas *c_ED;
  c_ED = new TCanvas("Event Display",str_ctitle,0,200,1050,700);
  c_ED->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",0,0, "ProcEvent(Int_t,Int_t,Int_t,TObject*)");
  c_ED->Divide(3,2);

  /// MAX INDEXES
  int max_index = 0;
  int max_index2 = 0;
  int max_index3 = 0;
  int max_index4 = 0;

  int max_ADC = -100000000;
  int max_ADC2 = -100000000;
  int max_ADC3 = -100000000;
  int max_ADC4 = -100000000;

  for(Int_t q=0; q<256; q++){
    if(data.ADC_High_TARGET[q]>max_ADC){
      max_index = q;
      max_ADC = data.ADC_High_TARGET[q];
    }
  }

  for(Int_t q=0; q<256; q++){
    if (q == max_index) continue;
    else{
      if(data.ADC_High_TARGET[q]>max_ADC2){
        max_index2 = q;
        max_ADC2 = data.ADC_High_TARGET[q];
      }
    }
  }

  for(Int_t q=0; q<256; q++){
    if ((q == max_index) || (q == max_index2)) continue;
    else{
      if(data.ADC_High_TARGET[q]>max_ADC3) {
        max_index3 = q;
        max_ADC3 = data.ADC_High_TARGET[q];
      }
    }
  }

  for(Int_t q=0; q<256; q++){
    if ((q == max_index) || (q == max_index2) || (q == max_index3)) continue;
    else{
      if(data.ADC_High_TARGET[q]>max_ADC4) {
        max_index4 = q;
        max_ADC4 = data.ADC_High_TARGET[q];
      }
    }
  }



  //TARGET MARKERS
  TMarker *marker_ADC_TARGET[256];   
  TMarker *marker_ADCL_TARGET[256];   
  double flag_size_TARGET=1.35;
  
  for(Int_t i1=0; i1<6; i1++) marker_ADC_TARGET[i1] = new TMarker(0.40+0.04*i1,0.84,21);
  for(Int_t i2=0; i2<10; i2++) marker_ADC_TARGET[i2+6] = new TMarker(0.32+0.04*i2,0.80,21);
  for(Int_t i3=0; i3<12; i3++) marker_ADC_TARGET[i3+16] = new TMarker(0.28+0.04*i3,0.76,21);
  for(Int_t i4=0; i4<14; i4++) marker_ADC_TARGET[i4+28] = new TMarker(0.24+0.04*i4,0.72,21);
  for(Int_t i5=0; i5<16; i5++) marker_ADC_TARGET[i5+42] = new TMarker(0.20+0.04*i5,0.68,21);
  for(Int_t i6=0; i6<16; i6++) marker_ADC_TARGET[i6+58] = new TMarker(0.20+0.04*i6,0.64,21);
  for(Int_t i7=0; i7<18; i7++) marker_ADC_TARGET[i7+74] = new TMarker(0.16+0.04*i7,0.60,21);
  for(Int_t i8=0; i8<18; i8++) marker_ADC_TARGET[i8+92] = new TMarker(0.16+0.04*i8,0.56,21);
  for(Int_t i9=0; i9<18; i9++) marker_ADC_TARGET[i9+110] = new TMarker(0.16+0.04*i9,0.52,21);
  for(Int_t i10=0; i10<18; i10++) marker_ADC_TARGET[i10+128] = new TMarker(0.16+0.04*i10,0.48,21);
  for(Int_t i11=0; i11<18; i11++) marker_ADC_TARGET[i11+146] = new TMarker(0.16+0.04*i11,0.44,21);
  for(Int_t i12=0; i12<18; i12++) marker_ADC_TARGET[i12+164] = new TMarker(0.16+0.04*i12,0.40,21);
  for(Int_t i13=0; i13<16; i13++) marker_ADC_TARGET[i13+182] = new TMarker(0.20+0.04*i13,0.36,21);
  for(Int_t i14=0; i14<16; i14++) marker_ADC_TARGET[i14+198] = new TMarker(0.20+0.04*i14,0.32,21);
  for(Int_t i15=0; i15<14; i15++) marker_ADC_TARGET[i15+214] = new TMarker(0.24+0.04*i15,0.28,21);
  for(Int_t i16=0; i16<12; i16++) marker_ADC_TARGET[i16+228] = new TMarker(0.28+0.04*i16,0.24,21);
  for(Int_t i17=0; i17<10; i17++) marker_ADC_TARGET[i17+240] = new TMarker(0.32+0.04*i17,0.20,21);
  for(Int_t i18=0; i18<6; i18++) marker_ADC_TARGET[i18+250] = new TMarker(0.40+0.04*i18,0.16,21);
  for(Int_t iSize=0; iSize<256; iSize++)  marker_ADC_TARGET[iSize]->SetMarkerSize(flag_size_TARGET);

  for(Int_t i1=0; i1<6; i1++) marker_ADCL_TARGET[i1] = new TMarker(0.40+0.04*i1,0.84,21);     // TO MOVE
  for(Int_t i2=0; i2<10; i2++) marker_ADCL_TARGET[i2+6] = new TMarker(0.32+0.04*i2,0.80,21);
  for(Int_t i3=0; i3<12; i3++) marker_ADCL_TARGET[i3+16] = new TMarker(0.28+0.04*i3,0.76,21);
  for(Int_t i4=0; i4<14; i4++) marker_ADCL_TARGET[i4+28] = new TMarker(0.24+0.04*i4,0.72,21);
  for(Int_t i5=0; i5<16; i5++) marker_ADCL_TARGET[i5+42] = new TMarker(0.20+0.04*i5,0.68,21);
  for(Int_t i6=0; i6<16; i6++) marker_ADCL_TARGET[i6+58] = new TMarker(0.20+0.04*i6,0.64,21);
  for(Int_t i7=0; i7<18; i7++) marker_ADCL_TARGET[i7+74] = new TMarker(0.16+0.04*i7,0.60,21);
  for(Int_t i8=0; i8<18; i8++) marker_ADCL_TARGET[i8+92] = new TMarker(0.16+0.04*i8,0.56,21);
  for(Int_t i9=0; i9<18; i9++) marker_ADCL_TARGET[i9+110] = new TMarker(0.16+0.04*i9,0.52,21);
  for(Int_t i10=0; i10<18; i10++) marker_ADCL_TARGET[i10+128] = new TMarker(0.16+0.04*i10,0.48,21);
  for(Int_t i11=0; i11<18; i11++) marker_ADCL_TARGET[i11+146] = new TMarker(0.16+0.04*i11,0.44,21);
  for(Int_t i12=0; i12<18; i12++) marker_ADCL_TARGET[i12+164] = new TMarker(0.16+0.04*i12,0.40,21);
  for(Int_t i13=0; i13<16; i13++) marker_ADCL_TARGET[i13+182] = new TMarker(0.20+0.04*i13,0.36,21);
  for(Int_t i14=0; i14<16; i14++) marker_ADCL_TARGET[i14+198] = new TMarker(0.20+0.04*i14,0.32,21);
  for(Int_t i15=0; i15<14; i15++) marker_ADCL_TARGET[i15+214] = new TMarker(0.24+0.04*i15,0.28,21);
  for(Int_t i16=0; i16<12; i16++) marker_ADCL_TARGET[i16+228] = new TMarker(0.28+0.04*i16,0.24,21);
  for(Int_t i17=0; i17<10; i17++) marker_ADCL_TARGET[i17+240] = new TMarker(0.32+0.04*i17,0.20,21);
  for(Int_t i18=0; i18<6; i18++) marker_ADCL_TARGET[i18+250] = new TMarker(0.40+0.04*i18,0.16,21);
  for(Int_t iSize=0; iSize<256; iSize++)  marker_ADCL_TARGET[iSize]->SetMarkerSize(flag_size_TARGET);

  char Angle_string[30];
  char ChiS_string[30];
  
  sprintf(Angle_string,"#phi = %3.2f#circ#pm%3.2f", angle_final, delta_phi_deg);
  sprintf(ChiS_string,"#chi^{2}/ndf = %3.2f", ChiS_final/ndf_final);

  TLatex *tex_Angle;
  TLatex *tex_ChiS;
  
  tex_Angle = new TLatex(-45.,43.,Angle_string);
  tex_Angle->SetTextSize(0.05);
  tex_Angle->SetLineWidth(2);

  tex_ChiS = new TLatex(-45.,37.,ChiS_string);
  tex_ChiS->SetTextSize(0.05);
  tex_ChiS->SetLineWidth(2);

  TLatex *x_sft;
  TLatex *y_sft;
  TLatex *x_target;
  TLatex *y_target;

  char X_SFT_String[30];
  char Y_SFT_String[30];
  char X_TARGET_String[30];
  char Y_TARGET_String[30];

  sprintf(X_SFT_String,"X(41.6) = %4.2f", vec_X_int_SFT[0]);    //  X' = Y  ;  Y' = -X
  sprintf(Y_SFT_String,"Y(41.6) = %4.2f", vec_Y_int_SFT[0]);     //  X' = Y  ;  Y' = -X
  sprintf(X_TARGET_String,"X(29) = %4.2f", vec_X_int_TARGET[0]);               //  X' = Y  ;  Y' = -X
  sprintf(Y_TARGET_String,"Y(29) = %4.2f", vec_Y_int_TARGET[0]);               //  X' = Y  ;  Y' = -X

  x_sft = new TLatex(10.,42.,X_SFT_String);
  x_sft->SetTextSize(0.05);
  x_sft->SetLineWidth(2);

  y_sft = new TLatex(10.,37.,Y_SFT_String);
  y_sft->SetTextSize(0.05);
  y_sft->SetLineWidth(2);

  x_target = new TLatex(-45.,-40.,X_TARGET_String);
  x_target->SetTextSize(0.05);
  x_target->SetLineWidth(2);

  y_target = new TLatex(-45.,-45.,Y_TARGET_String);
  y_target->SetTextSize(0.05);
  y_target->SetLineWidth(2);

  char str_Kstop_X[200];
  char str_Kstop_Y[200];

  sprintf(str_Kstop_X,"X_{Ks} = %5.2f",vec_kstop_FINAL[0]);
  sprintf(str_Kstop_Y,"Y_{Ks} = %5.2f",vec_kstop_FINAL[1]);

  TLatex *tex_Kstop_X = new TLatex(18.,-40.,str_Kstop_X);
  tex_Kstop_X->SetTextSize(0.05);
  tex_Kstop_X->SetLineWidth(2);

  TLatex *tex_Kstop_Y = new TLatex(18.,-45.,str_Kstop_Y);
  tex_Kstop_Y->SetTextSize(0.05);
  tex_Kstop_Y->SetLineWidth(2);

  /////
  TGraph *gr_int_SFT = new TGraph(vec_Y_int_SFT.size(),&vec_X_int_SFT[0],&vec_Y_int_SFT[0]);
  gr_int_SFT->SetMarkerStyle(20);
  gr_int_SFT->SetMarkerColor(4);
  gr_int_SFT->SetMarkerSize(0.8);

  TGraph *gr_int_TARGET = new TGraph(vec_X_int_TARGET.size(),&vec_X_int_TARGET[0],&vec_Y_int_TARGET[0]);
  gr_int_TARGET->SetMarkerStyle(20);
  gr_int_TARGET->SetMarkerColor(4);
  gr_int_TARGET->SetMarkerSize(0.8);

  TGraph *gr_int_TOF1 = new TGraph(vec_X_int_TOF1.size(),&vec_X_int_TOF1[0],&vec_Y_int_TOF1[0]);
  gr_int_TOF1->SetMarkerStyle(20);
  gr_int_TOF1->SetMarkerColor(4);
  gr_int_TOF1->SetMarkerSize(0.8);

  
  /// BLUE ARROWS (GUIDE)
  TArrow *X_guide;
  TArrow *Y_guide;

  double X_arrow = -1.;
  double Y_arrow = -1.;
  int Axis_Vector_Length = 10;

  X_arrow = vec_intersect_TARGET_final[2];
  Y_arrow = vec_intersect_TARGET_final[3];

  X_guide = new TArrow(X_arrow, Y_arrow, X_arrow + Axis_Vector_Length, Y_arrow, 0.005, "|>");
  Y_guide = new TArrow(X_arrow, Y_arrow, X_arrow, Y_arrow + Axis_Vector_Length, 0.005, "|>");

  X_guide->SetLineWidth(2);     Y_guide->SetLineWidth(2);
  X_guide->SetLineColor(4);     Y_guide->SetLineColor(4);


  /// IF NO LEPTON LEFT
  //cout << "////// BBABR : " << b_bbar << endl;
  TLine *line_bbar;
  if(b_bbar){
    line_bbar = new TLine(vec_bbar[0], vec_bbar[1], vec_bbar[2], vec_bbar[3]);  
    line_bbar->SetLineWidth(2);
    line_bbar->SetLineColor(3);
  }
  else{
    line_bbar = new TLine(999., 999., 999., 999.);    
  }

  TGaxis *A1 = new TGaxis(-50,50,50,50,"pol1",510,"-U");
  TGaxis *A2 = new TGaxis(50,-50,50,50,"pol1",510,"+U");

  /// TARGET CIRCLE
  TEllipse *ell_Target = new TEllipse(0, 0, CP::R_TARGET, 0); 
  ell_Target->SetFillStyle(0);
  ell_Target->SetLineColor(1);
  ell_Target->SetLineWidth(1);

  /// TOF1 CIRCLE
  TEllipse *ell = new TEllipse(0, 0, CP::R_TOF1, 0);
  ell->SetFillStyle(0);
  ell->SetLineColor(6);
  ell->SetLineWidth(1);

  /// SFT CIRCLE
  TEllipse *ell_L1 = new TEllipse(0, 0, CP::R_SFT_L1, 0);
  ell_L1->SetFillStyle(0);
  ell_L1->SetLineColor(4);
  ell_L1->SetLineWidth(1);


  /// TARGET CENTER
  vector<double> vec_xx_Target_Center;  vec_xx_Target_Center.clear();
  vector<double> vec_yy_Target_Center;  vec_yy_Target_Center.clear();
  vec_xx_Target_Center.push_back(0.);
  vec_yy_Target_Center.push_back(0.);

  TGraph *gr_Target_Center = new TGraph(vec_xx_Target_Center.size(),&vec_xx_Target_Center[0],&vec_yy_Target_Center[0]);
  gr_Target_Center->SetMarkerStyle(5);
  gr_Target_Center->SetMarkerColor(1);
  gr_Target_Center->SetMarkerSize(1);

  ///TOF1
  vector<double> vec_x_TOF1;          vec_x_TOF1.clear();
  vector<double> vec_y_TOF1;          vec_y_TOF1.clear();
  vector<double> vec_x_TOF1_selected; vec_x_TOF1_selected.clear();
  vector<double> vec_y_TOF1_selected; vec_y_TOF1_selected.clear();

  if(selected_section != -1){
    for(int i=0; i<5; i++){
      if(i != selected_section){
        vec_x_TOF1.push_back(DG::TOF1_Xloc[TOF1_gap-1][i]);
        vec_y_TOF1.push_back(DG::TOF1_Yloc[TOF1_gap-1][i]);
      }
      else{
        vec_x_TOF1_selected.push_back(DG::TOF1_Xloc[TOF1_gap-1][i]);
        vec_y_TOF1_selected.push_back(DG::TOF1_Yloc[TOF1_gap-1][i]);
      }
    }
  }

  TGraph *gr_TOF1;
  gr_TOF1 = new TGraph(vec_x_TOF1.size(), &vec_x_TOF1[0], &vec_y_TOF1[0]);
  gr_TOF1->SetMarkerStyle(20);
  gr_TOF1->SetMarkerColor(2);
  gr_TOF1->SetMarkerSize(1.5);

  TGraph *gr_TOF1_selected;
  gr_TOF1_selected = new TGraph(vec_x_TOF1_selected.size(), &vec_x_TOF1_selected[0], &vec_y_TOF1_selected[0]);
  gr_TOF1_selected->SetMarkerStyle(20);
  gr_TOF1_selected->SetMarkerColor(3);
  gr_TOF1_selected->SetMarkerSize(1.5);

  /// LEPTON FINAL FIT
  char str_lepton_fit_final[100];   
  if(type == line) sprintf(str_lepton_fit_final,"Lepton Fit  |  Run %d  --  Event %d  |  Line Pruning",Run_Number,ievt);
  if(type == triangle) sprintf(str_lepton_fit_final,"Lepton Fit  |  Run %d  --  Event %d  |  Triangle Pruning",Run_Number,ievt);
  if(type == backtracking) sprintf(str_lepton_fit_final,"Lepton Fit  |  Run %d  --  Event %d  |  Backtracking Method",Run_Number,ievt);
  
  TH2F *h_lepton_fit_final;
  h_lepton_fit_final = new TH2F("Lepton Fit", str_lepton_fit_final, 500, -50, 50, 500, -50, 50);

  gr_leptons_final->SetMarkerStyle(21);
  gr_leptons_final->SetMarkerColor(2);
  gr_leptons_final->SetMarkerSize(0.8);
  gr_leptons_final->GetXaxis()->SetLimits(-50.,50.);
  gr_leptons_final->GetYaxis()->SetRangeUser(-50.,50.);

  
  /// KAON FINAL FIT
  char str_kaon_fit_final[100];
  sprintf(str_kaon_fit_final,"Kaon Fit  |  Run %d  --  Event %d",Run_Number,ievt);
  TH2F *h_kaon_fit_final;
  h_kaon_fit_final = new TH2F("Kaon Fit", str_kaon_fit_final, 500, -50, 50, 500, -50, 50);


  /// KSTOP FINAL
  vector<double>  vec_x_kstop_final;  vec_x_kstop_final.clear();
  vector<double>  vec_y_kstop_final;  vec_y_kstop_final.clear();
  vec_x_kstop_final.push_back(vec_kstop_FINAL[0]);
  vec_y_kstop_final.push_back(vec_kstop_FINAL[1]);

  TGraph *gr_kstop_final;
  gr_kstop_final = new TGraph(vec_x_kstop_final.size(), &vec_x_kstop_final[0], &vec_y_kstop_final[0]);
  gr_kstop_final->SetMarkerStyle(34);
  gr_kstop_final->SetMarkerColor(1);
  gr_kstop_final->SetMarkerSize(1.3);

  char str_final[100];
  if(type == line) sprintf(str_final,"Final Fit  |  Run %d  --  Event %d  |  Line Pruning",Run_Number,ievt);
  else if(type == triangle) sprintf(str_final,"Final Fit  |  Run %d  --  Event %d  |  Triangle Pruning",Run_Number,ievt);
  else if(type == backtracking) sprintf(str_final,"Final Fit  |  Run %d  --  Event %d  |  Backtracking Method",Run_Number,ievt);
  
  TH2F *h_final;  
  h_final = new TH2F("Final Fit", str_final, 500, -50, 50, 500, -50, 50);

  //////////////////////////////////////////////////////////////////////////////

  EventPlot* leptonPlot = new EventPlot(str_lepton_fit_final);
  EventPlot* kaonPlot = new EventPlot(str_kaon_fit_final);
  EventPlot* finalPlot = new EventPlot(str_final);


  /// PANEL 1
  c_ED->cd(1);
  drawTargetFrame(Run_Number, ievt,
                  has_ADC_TOF1_hit, has_TDC_TOF1_hit,
                  has_ADC_TOF2_hit, has_TDC_TOF2_hit
  );
  tex_Title_panel1->Draw();
  tex_Subtitle_panel1->Draw();

  for(Int_t icol=0; icol<256; icol++){
    if(data.ADC_High_TARGET[icol]>=0 && data.ADC_High_TARGET[icol]<300){ marker_ADC_TARGET[icol]->SetMarkerColor(kOrange+10); marker_ADC_TARGET[icol]->Draw();}
    if(data.ADC_High_TARGET[icol]>=300 && data.ADC_High_TARGET[icol]<600){ marker_ADC_TARGET[icol]->SetMarkerColor(kOrange+7); marker_ADC_TARGET[icol]->Draw();}
    if(data.ADC_High_TARGET[icol]>=600 && data.ADC_High_TARGET[icol]<900){ marker_ADC_TARGET[icol]->SetMarkerColor(kOrange+1); marker_ADC_TARGET[icol]->Draw();}
    if(data.ADC_High_TARGET[icol]>=900 && data.ADC_High_TARGET[icol]<1200){ marker_ADC_TARGET[icol]->SetMarkerColor(kOrange-4); marker_ADC_TARGET[icol]->Draw();}
    if(data.ADC_High_TARGET[icol]>=1200 && data.ADC_High_TARGET[icol]<1500){ marker_ADC_TARGET[icol]->SetMarkerColor(kYellow-9); marker_ADC_TARGET[icol]->Draw();}
    if(data.ADC_High_TARGET[icol]>=1500 && data.ADC_High_TARGET[icol]<1800){ marker_ADC_TARGET[icol]->SetMarkerColor(kYellow-7); marker_ADC_TARGET[icol]->Draw();}
    if(data.ADC_High_TARGET[icol]>=1800 && data.ADC_High_TARGET[icol]<2100){ marker_ADC_TARGET[icol]->SetMarkerColor(kYellow-0); marker_ADC_TARGET[icol]->Draw();}
    if(data.ADC_High_TARGET[icol]>=2100 && data.ADC_High_TARGET[icol]<2400){ marker_ADC_TARGET[icol]->SetMarkerColor(kSpring-4); marker_ADC_TARGET[icol]->Draw();}
    if(data.ADC_High_TARGET[icol]>=2400 && data.ADC_High_TARGET[icol]<2700){ marker_ADC_TARGET[icol]->SetMarkerColor(kSpring-2); marker_ADC_TARGET[icol]->Draw();}
    if(data.ADC_High_TARGET[icol]>=2700){ marker_ADC_TARGET[icol]->SetMarkerColor(kGreen-0); marker_ADC_TARGET[icol]->Draw();}

    if(data.ADC_High_TARGET[icol]<0 && data.ADC_Low_TARGET[icol]>0){
      if(has_TDC_hit[icol]) marker_ADC_TARGET[icol]->SetMarkerColor(11);
      else marker_ADC_TARGET[icol]->SetMarkerColor(kBlue);
      marker_ADC_TARGET[icol]->Draw();
    }
  }

  if(data.ADC_High_TARGET[max_index] > 0){
    marker_ADC_TARGET[max_index]->SetMarkerColor(kViolet+1);
    marker_ADC_TARGET[max_index]->Draw();
  }

  if(data.ADC_High_TARGET[max_index2] > 0){
    marker_ADC_TARGET[max_index2]->SetMarkerColor(1);
    marker_ADC_TARGET[max_index2]->Draw();
  }

  if(data.ADC_High_TARGET[max_index3] > 0){
    marker_ADC_TARGET[max_index3]->SetMarkerColor(1);
    marker_ADC_TARGET[max_index3]->Draw();
  }

  if(data.ADC_High_TARGET[max_index4] > 0){
    marker_ADC_TARGET[max_index4]->SetMarkerColor(1);
    marker_ADC_TARGET[max_index4]->Draw();
  }


  /// PANEL 2
  c_ED->cd(2);
  drawTargetFrame(Run_Number, ievt,
                  has_ADC_TOF1_hit, has_TDC_TOF1_hit,
                  has_ADC_TOF2_hit, has_TDC_TOF2_hit);

  tex_Title_panel2->Draw();
  tex_Subtitle_panel2->Draw();  

  for(Int_t icol=0; icol<256; icol++){           
    if(has_TDC_hit[icol]){
      if(data.ADC_High_TARGET[icol]>=0 && data.ADC_High_TARGET[icol]<300){ marker_ADC_TARGET[icol]->SetMarkerColor(kOrange+10); marker_ADC_TARGET[icol]->Draw();}
      if(data.ADC_High_TARGET[icol]>=300 && data.ADC_High_TARGET[icol]<600){ marker_ADC_TARGET[icol]->SetMarkerColor(kOrange+7); marker_ADC_TARGET[icol]->Draw();}
      if(data.ADC_High_TARGET[icol]>=600 && data.ADC_High_TARGET[icol]<900){ marker_ADC_TARGET[icol]->SetMarkerColor(kOrange+1); marker_ADC_TARGET[icol]->Draw();}
      if(data.ADC_High_TARGET[icol]>=900 && data.ADC_High_TARGET[icol]<1200){ marker_ADC_TARGET[icol]->SetMarkerColor(kOrange-4); marker_ADC_TARGET[icol]->Draw();}
      if(data.ADC_High_TARGET[icol]>=1200 && data.ADC_High_TARGET[icol]<1500){ marker_ADC_TARGET[icol]->SetMarkerColor(kYellow-9); marker_ADC_TARGET[icol]->Draw();}
      if(data.ADC_High_TARGET[icol]>=1500 && data.ADC_High_TARGET[icol]<1800){ marker_ADC_TARGET[icol]->SetMarkerColor(kYellow-7); marker_ADC_TARGET[icol]->Draw();}
      if(data.ADC_High_TARGET[icol]>=1800 && data.ADC_High_TARGET[icol]<2100){ marker_ADC_TARGET[icol]->SetMarkerColor(kYellow-0); marker_ADC_TARGET[icol]->Draw();}
      if(data.ADC_High_TARGET[icol]>=2100 && data.ADC_High_TARGET[icol]<2400){ marker_ADC_TARGET[icol]->SetMarkerColor(kSpring-4); marker_ADC_TARGET[icol]->Draw();}
      if(data.ADC_High_TARGET[icol]>=2400 && data.ADC_High_TARGET[icol]<2700){ marker_ADC_TARGET[icol]->SetMarkerColor(kSpring-2); marker_ADC_TARGET[icol]->Draw();}
      if(data.ADC_High_TARGET[icol]>=2700){ marker_ADC_TARGET[icol]->SetMarkerColor(kGreen-0); marker_ADC_TARGET[icol]->Draw();}
    }

    if(data.ADC_High_TARGET[icol]<0 && data.ADC_Low_TARGET[icol]>0 && TDC_min_TARGET){
      if(has_TDC_hit[icol]) marker_ADC_TARGET[icol]->SetMarkerColor(11);
      else marker_ADC_TARGET[icol]->SetMarkerColor(kBlue);
      marker_ADC_TARGET[icol]->Draw();
    }
  }
    
  if(has_TDC_hit[max_index]){
    marker_ADC_TARGET[max_index]->SetMarkerColor(kViolet+1);
    marker_ADC_TARGET[max_index]->Draw();
  }

  if(has_TDC_hit[max_index2]){
    marker_ADC_TARGET[max_index2]->SetMarkerColor(1);
    marker_ADC_TARGET[max_index2]->Draw();
  }

  if(has_TDC_hit[max_index3]){
    marker_ADC_TARGET[max_index3]->SetMarkerColor(1);
    marker_ADC_TARGET[max_index3]->Draw();
  }

  if(has_TDC_hit[max_index4]){
    marker_ADC_TARGET[max_index4]->SetMarkerColor(1);
    marker_ADC_TARGET[max_index4]->Draw();
  }

  /// PANEL 3
  c_ED->cd(3);
  drawTargetFrame(Run_Number, ievt,
                  has_ADC_TOF1_hit, has_TDC_TOF1_hit,
                  has_ADC_TOF2_hit, has_TDC_TOF2_hit);
    
  tex_Title_panel3->Draw();
  tex_Subtitle_panel3->Draw();
  tex_Kbar->Draw(); 
  tex_version->Draw();

  if(has_kaon_sub){
    marker_ADCL_TARGET[kaon_bar]->SetMarkerColor(6); 
    marker_ADCL_TARGET[kaon_bar]->Draw();
  }
  else{
    for(Int_t icol=0; icol<256; icol++){
      if(has_TDC_hit_Kstop[icol]){
        if(data.ADC_Low_TARGET[icol]>=CW::LG_KAON && data.ADC_High_TARGET[icol]>=CW::HG_KAON){
          marker_ADCL_TARGET[icol]->SetMarkerColor(12); marker_ADCL_TARGET[icol]->Draw();
        }
      }
    }
  }

  /// PANEL 4
  leptonPlot->Frame(c_ED, 4);
  leptonPlot->DrawTOF1(c_ED, 4);
  leptonPlot->DrawSFT_L1(c_ED,4);
    
  if(selected_section !=-1){
    gr_TOF1->Draw("sameP");
    gr_TOF1_selected->Draw("sameP");
  }

  gr_leptons_final->Draw("sameP");
  if(to_restore) restored_line->Draw("same");


  /// PANEL 5
  kaonPlot->Frame(c_ED, 5);
  kaonPlot->DrawTOF1(c_ED, 5);
  kaonPlot->DrawSFT_L1(c_ED,5);

  gr_kaons_final->Draw("sameP");
  line_fit_kaons->Draw("same");


  /// PANEL 6
  finalPlot->Frame(c_ED, 6);
  finalPlot->DrawTOF1(c_ED, 6);
  finalPlot->DrawSFT_L1(c_ED,6);

  if(selected_section !=-1){
    gr_TOF1->Draw("sameP");
    gr_TOF1_selected->Draw("sameP");
  }

  gr_leptons_final->Draw("sameP");
  if(to_restore) restored_line->Draw("same");
  gr_kaons_final->Draw("sameP");
  line_fit_kaons->Draw("same");
  gr_kstop_final->Draw("sameP");

  gr_int_TARGET->Draw("sameP");
  gr_int_SFT->Draw("sameP");
  gr_int_TOF1->Draw("sameP");

  tex_Angle->Draw("same");
  tex_ChiS->Draw("same");
  x_sft->Draw("same");
  y_sft->Draw("same");
  x_target->Draw("same");
  y_target->Draw("same");
  tex_Kstop_X->Draw("same");
  tex_Kstop_Y->Draw("same");

  X_guide->Draw();
  Y_guide->Draw();

  if(b_bbar) line_bbar->Draw("same");
}


void drawBacktracking(vector<TargetBar> primaryTrack, vector<TargetBar> secondaryTrackA, vector<TargetBar> secondaryTrackB, 
                      vector<TargetBar> allBars){

  TOF1_Detector_Attributes();

  char str_ctitle[100];
  sprintf(str_ctitle, "Backtracking Method (Meth. A vs Meth. B)");

  TCanvas *c_backtracking;
  c_backtracking = new TCanvas("Backtracking Method",str_ctitle,0,200,700,700);
  c_backtracking->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",0,0, "ProcEvent(Int_t,Int_t,Int_t,TObject*)");
  c_backtracking->Divide(2,2);

  TGaxis *A1 = new TGaxis(-50,50,50,50,"pol1",510,"-U");
  TGaxis *A2 = new TGaxis(50,-50,50,50,"pol1",510,"+U");

  TEllipse *ell_Target = new TEllipse(0, 0, CP::R_TARGET, 0); 
  TEllipse *ell = new TEllipse(0, 0, CP::R_TOF1, 0);
  TEllipse *ell_L1 = new TEllipse(0, 0, CP::R_SFT_L1, 0);
  
  ell->SetFillStyle(0);  ell_Target->SetFillStyle(0);  ell_L1->SetFillStyle(0);
  ell->SetLineColor(6);  ell_Target->SetLineColor(1);  ell_L1->SetLineColor(4);
  ell->SetLineWidth(1);  ell_Target->SetLineWidth(1);  ell_L1->SetLineWidth(1);

  char str_primary[100];
  char str_secondaryA[100];
  char str_secondaryB[100];
  char str_allBars[100];

  sprintf(str_primary, "Primary Track");
  sprintf(str_secondaryA, "Secondary Track A");
  sprintf(str_secondaryB, "Primary Track");
  sprintf(str_allBars, "Secondary Track B");
    
  TH2F *h_primary = new TH2F("Primary Track", str_primary, 500, -50, 50, 500, -50, 50);
  TH2F *h_secondaryA = new TH2F("Secondary Track A", str_secondaryA, 500, -50, 50, 500, -50, 50);
  TH2F *h_secondaryB = new TH2F("Secondary Track B", str_secondaryB, 500, -50, 50, 500, -50, 50);
  //TH2F *h_allBars = new TH2F("All Bars", str_allBars, 500, -50, 50, 500, -50, 50);

  //TARGET CENTER
  vector<double> vec_xx_Target_Center;  vec_xx_Target_Center.clear();
  vector<double> vec_yy_Target_Center;  vec_yy_Target_Center.clear();
  vec_xx_Target_Center.push_back(0.);
  vec_yy_Target_Center.push_back(0.);

  TGraph *gr_Target_Center = new TGraph(vec_xx_Target_Center.size(),&vec_xx_Target_Center[0],&vec_yy_Target_Center[0]);
  gr_Target_Center->SetMarkerStyle(5);
  gr_Target_Center->SetMarkerColor(1);
  gr_Target_Center->SetMarkerSize(1);

  vector<double> x_primary,       y_primary;
  vector<double> x_secondaryA,    y_secondaryA;
  vector<double> x_secondaryB,    y_secondaryB;
  vector<double> x_allBars,       y_allBars;

  for (auto b_primary : primaryTrack) {
    x_primary.push_back(b_primary.getCoord().x());
    y_primary.push_back(b_primary.getCoord().y());
  }

  for (auto b_secondaryA : secondaryTrackA) {
    x_secondaryA.push_back(b_secondaryA.getCoord().x());
    y_secondaryA.push_back(b_secondaryA.getCoord().y());
  }

  for (auto b_secondaryB : secondaryTrackB) {
    x_secondaryB.push_back(b_secondaryB.getCoord().x());
    y_secondaryB.push_back(b_secondaryB.getCoord().y());
  }

  for (auto b_allBars : allBars) {
    x_allBars.push_back(b_allBars.getCoord().x());
    y_allBars.push_back(b_allBars.getCoord().y());
  }


  // cout << "SIZE X : " << x_primary.size() << endl;
  // cout << "SIZE Y : " << y_primary.size() << endl;

  // for(unsigned int i=0; i<x_primary.size(); i++){
  //   cerr << x_primary[i] << "  " << y_primary[i] << endl;

  // }

  // cout << "SIZE X_secondaryA : " << x_secondaryA.size() << endl;
  // cout << "SIZE Y_secondaryA : " << y_secondaryA.size() << endl;

  // for(unsigned int i=0; i<x_secondaryA.size(); i++){
  //   cerr << x_secondaryA[i] << "  " << y_secondaryA[i] << endl;
  // }

  // cout << "SIZE X_secondaryB : " << x_secondaryB.size() << endl;
  // cout << "SIZE Y_secondaryB : " << y_secondaryB.size() << endl;

  // for(unsigned int i=0; i<x_secondaryB.size(); i++){
  //   cerr << x_secondaryB[i] << "  " << y_secondaryB[i] << endl;
  // }

  // cout << "SIZE X_allBars : " << x_allBars.size() << endl;
  // cout << "SIZE Y_allBars : " << y_allBars.size() << endl;

  // for(unsigned int i=0; i<x_allBars.size(); i++){
  //   cerr << x_allBars[i] << "  " << y_allBars[i] << endl;
  // }



  TGraph *gr_allBars;
  gr_allBars = new TGraph(x_allBars.size(),&x_allBars[0],&y_allBars[0]);
  gr_allBars->SetMarkerColor(1);
  gr_allBars->SetMarkerStyle(21);
  gr_allBars->SetMarkerSize(0.85);

  TGraph *gr_primary;
  gr_primary = new TGraph(x_primary.size(),&x_primary[0],&y_primary[0]);
  gr_primary->SetMarkerColor(2);
  gr_primary->SetMarkerStyle(21);
  gr_primary->SetMarkerSize(0.85);

  TGraph *gr_secondaryA;
  gr_secondaryA = new TGraph(x_secondaryA.size(),&x_secondaryA[0],&y_secondaryA[0]);
  gr_secondaryA->SetMarkerColor(3);
  gr_secondaryA->SetMarkerStyle(21);
  gr_secondaryA->SetMarkerSize(0.85);

  TGraph *gr_secondaryB;
  gr_secondaryB = new TGraph(x_secondaryB.size(),&x_secondaryB[0],&y_secondaryB[0]);
  gr_secondaryB->SetMarkerColor(3);
  gr_secondaryB->SetMarkerStyle(21);
  gr_secondaryB->SetMarkerSize(0.85);


  // gr_primaryA = new TGraphErrors(x_primaryA.size(),&x_primaryA[0],&y_primaryA[0],
  //                             ...,...);


  //FIT2 INTERSECT WITH TOF1
  // vector<double> vec_x_intersect_TOF1;        vec_x_intersect_TOF1.clear();
  // vector<double> vec_y_intersect_TOF1;        vec_y_intersect_TOF1.clear();
  // vector<double> vec_intersect_TOF1_reverse;  vec_intersect_TOF1_reverse.clear();

  // if(vec_intersect_TOF1.size()>0){
  //   if(to_rotate_leptons){

  //     vec_x_intersect_TOF1.push_back(vec_intersect_TOF1[1]);
  //     vec_y_intersect_TOF1.push_back(-vec_intersect_TOF1[0]);
  //   }
  //   else{
  //     vec_x_intersect_TOF1.push_back(vec_intersect_TOF1[0]);
  //     vec_y_intersect_TOF1.push_back(vec_intersect_TOF1[1]);
  //   }
  // }

  // TGraph *gr_intersect_TOF1;
  // gr_intersect_TOF1 = new TGraph(vec_x_intersect_TOF1.size(), 
  //                     &vec_x_intersect_TOF1[0], &vec_y_intersect_TOF1[0]);

  // gr_intersect_TOF1->SetMarkerColor(4);
  // gr_intersect_TOF1->SetMarkerStyle(20);
  // gr_intersect_TOF1->SetMarkerSize(0.8);


  /// FITTING LINES
  // vector<double> vec_fitLine1;
  // vector<double> vec_fitLine2;
  // vector<double> vec_fitLine3;
  
  // TLine *fit1_line = nullptr;
  // TLine *fit2_line = nullptr;
  // TLine *fit3_line = nullptr;


  // if(to_rotate_leptons){

  //   vec_fitLine1 = defineFitLine(a1, b1);
  //   vec_fitLine2 = defineFitLine(a2, b2);
  //   vec_fitLine3 = defineFitLine(a3, b3);

  //   fit1_line = new TLine(vec_fitLine1[0], vec_fitLine1[1],
  //                         vec_fitLine1[2], vec_fitLine1[3]);
  //   fit2_line = new TLine(vec_fitLine2[0], vec_fitLine2[1],
  //                         vec_fitLine2[2], vec_fitLine2[3]);
  //   fit3_line = new TLine(vec_fitLine3[0], vec_fitLine3[1],
  //                         vec_fitLine3[2], vec_fitLine3[3]);

  //   fit1_line->SetLineWidth(2);
  //   fit1_line->SetLineColor(2);
  //   fit2_line->SetLineWidth(2);
  //   fit2_line->SetLineColor(2);
  //   fit3_line->SetLineWidth(2);
  //   fit3_line->SetLineColor(2);
  // }

  EventPlot* primaryPlot = new EventPlot(str_primary);
  EventPlot* secondaryAPlot = new EventPlot(str_secondaryA);
  EventPlot* secondaryBPlot = new EventPlot(str_secondaryB);
  EventPlot* all_Bars = new EventPlot(str_allBars);


  /// PANEL 1
  primaryPlot->Frame(c_backtracking, 1);
  primaryPlot->DrawTOF1(c_backtracking,1);
  primaryPlot->DrawSFT_L1(c_backtracking,1);
  gr_allBars->Draw("sameP");
  gr_primary->Draw("sameP");
  //if(to_rotate_leptons) fit1_line->Draw("same");


  /// PANEL 2
  secondaryAPlot->Frame(c_backtracking, 2);
  secondaryAPlot->DrawTOF1(c_backtracking,2);
  secondaryAPlot->DrawSFT_L1(c_backtracking,2);
  gr_allBars->Draw("sameP");
  gr_secondaryA->Draw("sameP");
  //gr_kaons_final->Draw("sameP");
  //if(to_rotate_kaons) line_fit_kaons->Draw("same");


  /// PANEL 3
  secondaryBPlot->Frame(c_backtracking, 3);
  secondaryBPlot->DrawTOF1(c_backtracking,3);
  secondaryBPlot->DrawSFT_L1(c_backtracking,3);
  gr_allBars->Draw("sameP");
  gr_primary->Draw("sameP");
  //gr_leptons_fit2->Draw("sameP");
  //if(to_rotate_leptons) fit2_line->Draw("same");
  //if(vec_intersect_TOF1.size()>0) gr_intersect_TOF1->Draw("sameP");


  /// PANEL 4
  all_Bars->Frame(c_backtracking, 4);
  all_Bars->DrawTOF1(c_backtracking,4);
  all_Bars->DrawSFT_L1(c_backtracking,4);
  gr_allBars->Draw("sameP");
  gr_secondaryB->Draw("sameP");
  //gr_leptons_fit3->Draw("sameP");
  //if(to_rotate_leptons) fit3_line->Draw("same");
}
