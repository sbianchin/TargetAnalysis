/*
 * Created by Sebastien Bianchin on 2018-07-24 (s.bianchin@triumf.ca)
 */

#include <iostream>
#include <vector>
#include <math.h>
#include "TGraph.h"
#include "pruningFunctions.hpp"
#include "DetectorGeometry.hpp"
#include "CommonParameters.hpp"

namespace DG = DetectorGeometry;
namespace CP = CommonParameters;


vector<int> TOF1Neighbours(int TOF1_gap){
	
	vector<int> TOF1_neighbours;
	int TOF1_minus;
	int TOF1_plus;

	if(TOF1_gap-1 == 0){
		TOF1_minus = 11;
		TOF1_plus = 1;
	}
	else if(TOF1_gap-1==11){
		TOF1_minus = 10;
		TOF1_plus = 0;
	}
	else{
		TOF1_minus = (TOF1_gap-1) - 1;
		TOF1_plus = (TOF1_gap-1) + 1;
	}

	TOF1_neighbours.push_back(TOF1_minus);
	TOF1_neighbours.push_back(TOF1_plus);

	return TOF1_neighbours;
}

vector<double> PruningArea(double x1, double x2, double x3){

	vector<double> vec_xx_pruning_area;
	vec_xx_pruning_area.clear();

	vec_xx_pruning_area.push_back(x1);
	vec_xx_pruning_area.push_back(x2);
	vec_xx_pruning_area.push_back(x3);
	vec_xx_pruning_area.push_back(x1);

	return vec_xx_pruning_area;
}

vector<int> TriangularPruning(int TOF1_Gap, double x_kstop, double y_kstop, vector<int> kaon_bars, vector<int> lepton_bars){

	vector<int> vec_pruned_temp;
	vector<int> vec_pruned;
	vector<int> vec_temp;

	///DETERMINE TOF1 NEIGHBOURS USING THE "TOF1Neighbours" FUNCTION
	vector<int> vec_TOF1_neighbours;

	vec_TOF1_neighbours = TOF1Neighbours(TOF1_Gap);


	/// DETERMINE PRUNING AREA USING THE "PruningArea" FUNCTION
	vector<double> vec_xx_pruning_area;
	vector<double> vec_yy_pruning_area;

	vec_xx_pruning_area = PruningArea(x_kstop, DG::TOF1_Xloc[vec_TOF1_neighbours[0]][2], DG::TOF1_Xloc[vec_TOF1_neighbours[1]][2]);
	vec_yy_pruning_area = PruningArea(y_kstop, DG::TOF1_Yloc[vec_TOF1_neighbours[0]][2], DG::TOF1_Yloc[vec_TOF1_neighbours[1]][2]);

	TGraph *gr_pruning_area;
  	gr_pruning_area = new TGraph(vec_xx_pruning_area.size(), &vec_xx_pruning_area[0], &vec_yy_pruning_area[0]);

  	if(kaon_bars.size()==0){
  		for(unsigned int i=0; i<lepton_bars.size(); i++){
  			vec_pruned.push_back(lepton_bars[i]);
  		}
  	}
  	else{
  		for(unsigned int i=0; i<lepton_bars.size(); i++){
  			if(gr_pruning_area->IsInside(DG::Xloc[lepton_bars[i]], DG::Yloc[lepton_bars[i]])==1){
  				vec_pruned_temp.push_back(lepton_bars[i]);
  			}
  		}
  	}

  	if(vec_pruned_temp.size() >= 2){
  		vec_pruned = vec_pruned_temp;
  	}
  	else{
  		if(kaon_bars.size() > 0){
  			for(unsigned int i=0; i<lepton_bars.size(); i++){
  				vec_pruned.push_back(lepton_bars[i]);
  			}
  		}
  	}

  	vector<double> vec_xx_pruned;
  	vector<double> vec_yy_pruned;

  	for(unsigned int i=0; i<vec_pruned.size(); i++){
  		vec_xx_pruned.push_back(DG::Xloc[vec_pruned[i]]);
  		vec_yy_pruned.push_back(DG::Yloc[vec_pruned[i]]);
  	}

  	return vec_pruned;
}

vector<double> PruningLine(int TOF1_Gap, double x_kstop, double y_kstop){

	double x1, y1;
	double x2, y2;
	double b;
	double a_out = -1;
	double b_out = -1;

	vector<double> vec_pruning_line;
	vector<double> vec_pruning_line_coordinates;

	///DEFINE MIN AND MAX
	if(TOF1_Gap == 3 || TOF1_Gap == 9){
		x1 = x_kstop;
		y1 = -50;

		x2 = x_kstop;
		y2 = 50.;

		a_out = 999.99;
		b_out = 999.99;
	}
	else{
		b = y_kstop - DG::TOF1_line_slope[TOF1_Gap-1] * x_kstop;

		x1 = -50.;
		y1 = DG::TOF1_line_slope[TOF1_Gap-1] * x1 + b;

		x2 = 50.;
		y2 = DG::TOF1_line_slope[TOF1_Gap-1] * x2 + b;

		a_out = DG::TOF1_line_slope[TOF1_Gap-1];
		b_out = b;
	}

	vec_pruning_line_coordinates.push_back(x1);
	vec_pruning_line_coordinates.push_back(y1);
	vec_pruning_line_coordinates.push_back(x2);
	vec_pruning_line_coordinates.push_back(y2);

	vec_pruning_line.push_back(x1);
	vec_pruning_line.push_back(y1);
	vec_pruning_line.push_back(x2);
	vec_pruning_line.push_back(y2);
	vec_pruning_line.push_back(a_out);
	vec_pruning_line.push_back(b_out);

	return vec_pruning_line;
}

vector<double> PruningLine2(int TOF1_Gap, double distance, double x_kstop, double y_kstop){

	double d_angle = 999.99;
	double ddx = 999.99;
	double ddy = 999.99;

	double a_out = 999.99;
	double b_out = 999.99;

	vector<double> vec_temp;
	vector<double> vec_output;

	if(TOF1_Gap==1)  d_angle =  60. - 90.;
    if(TOF1_Gap==2)  d_angle =  30. - 90.;
    if(TOF1_Gap==3)  d_angle =   0. - 90.;
    if(TOF1_Gap==4)  d_angle = 330. - 90.;
    if(TOF1_Gap==5)  d_angle = 300. - 90.;
    if(TOF1_Gap==6)  d_angle = 270. - 90.;
    if(TOF1_Gap==7)  d_angle = 240. - 90.;
    if(TOF1_Gap==8)  d_angle = 210. - 90.;
    if(TOF1_Gap==9)  d_angle = 180. - 90.;
    if(TOF1_Gap==10) d_angle = 150. - 90.;
    if(TOF1_Gap==11) d_angle = 120. - 90.;
    if(TOF1_Gap==12) d_angle =  90. - 90.;

    ddx = distance * sin(d_angle * TMath::Pi() / 180.);
    ddy = distance * cos(d_angle * TMath::Pi() / 180.);

    vec_temp = PruningLine(TOF1_Gap, x_kstop, y_kstop);

    a_out = ((vec_temp[1]-ddy) - (vec_temp[3]-ddy)) / ((vec_temp[0]+ddx) - (vec_temp[2]+ddx));
    b_out = (vec_temp[1]-ddy) - a_out * (vec_temp[0]+ddx);

    vec_output.push_back(vec_temp[0]+ddx);
    vec_output.push_back(vec_temp[1]-ddy);
    vec_output.push_back(vec_temp[2]+ddx);
    vec_output.push_back(vec_temp[3]-ddy);
    vec_output.push_back(a_out);
    vec_output.push_back(b_out);

    return vec_output;
}


vector<int> LinearPruning(int TOF1_Gap, double x_kstop, double y_kstop, vector<int> lepton_bars, double distance){

	///Determine Pruning Line using "PruningLine" function
	vector<double> vec_pruning_line;  vec_pruning_line.clear();
	vec_pruning_line = PruningLine(TOF1_Gap, x_kstop, y_kstop);


	///Pruning the data
	vector<int> vec_temp;
	vector<int> vec_TBR;
	vector<int> vec_pruned;

	vec_temp = lepton_bars;

	if(TOF1_Gap==1 || TOF1_Gap==2 || TOF1_Gap == 10 || TOF1_Gap == 11 || TOF1_Gap == 12){
		for(unsigned int i=0; i<vec_temp.size(); i++){
			if(DG::Yloc[vec_temp[i]] < DG::Xloc[vec_temp[i]] * vec_pruning_line[4] + vec_pruning_line[5]){
				vec_TBR.push_back(vec_temp[i]);
			}
		}
	}
	else if(TOF1_Gap==4 || TOF1_Gap==5 || TOF1_Gap==6|| TOF1_Gap==7 || TOF1_Gap==8){     
		for(unsigned int i=0; i<vec_temp.size(); i++){
			if(DG::Yloc[vec_temp[i]] > DG::Xloc[vec_temp[i]] * vec_pruning_line[4] + vec_pruning_line[5]){
				vec_TBR.push_back(vec_temp[i]);
			}
		}
	}
	else if(TOF1_Gap == 3){
		for(unsigned int i=0; i<vec_temp.size(); i++){
			if(DG::Xloc[vec_temp[i]] < x_kstop){
				vec_TBR.push_back(vec_temp[i]);
			}
		}
	}
	else if(TOF1_Gap == 9){
		for(unsigned int i=0; i<vec_temp.size(); i++){
			if(DG::Xloc[vec_temp[i]] > x_kstop){
				vec_TBR.push_back(vec_temp[i]);
			}
		}
	}

	vector<double> vec_xx_temp;
	vector<double> vec_yy_temp;

	for(unsigned i=0; i<vec_TBR.size(); i++){
		vec_temp.erase(find(vec_temp.begin(), vec_temp.end(), vec_TBR[i]));
	}

	for(unsigned j=0; j<vec_temp.size(); j++){
		vec_xx_temp.push_back(DG::Xloc[vec_temp[j]]);
		vec_yy_temp.push_back(DG::Yloc[vec_temp[j]]);
	}


	/// REPRUNING IF TOO FEW LEPTONS
	vector<double> vec_line2;

	if(vec_temp.size() <= CP::lepton_cluster_size){

		vec_temp.clear();
		vec_TBR.clear();

		vec_line2 = PruningLine2(TOF1_Gap, distance, x_kstop, y_kstop);

		vec_temp = lepton_bars;

		if(TOF1_Gap==1 || TOF1_Gap==2 || TOF1_Gap==10 || TOF1_Gap==11 || TOF1_Gap==12){
			for(unsigned int i=0; i<vec_temp.size(); i++){
				if(DG::Yloc[vec_temp[i]] < DG::Xloc[vec_temp[i]] * vec_line2[4] + vec_line2[5]){
					vec_TBR.push_back(vec_temp[i]);
				}
			}
		}
		else if(TOF1_Gap==4 || TOF1_Gap==5 || TOF1_Gap==6|| TOF1_Gap==7 || TOF1_Gap==8){
			for(unsigned int i=0; i<vec_temp.size(); i++){
				if(DG::Yloc[vec_temp[i]] > DG::Xloc[vec_temp[i]] * vec_line2[4] + vec_line2[5]){
					vec_TBR.push_back(vec_temp[i]);
				}
			}
		}  
		else if(TOF1_Gap==3){
			for(unsigned int i=0; i<vec_temp.size(); i++){
				if(DG::Xloc[vec_temp[i]] < vec_line2[0]){
					vec_TBR.push_back(vec_temp[i]);
				}
			}
		}
		else if(TOF1_Gap==9){
			for(unsigned int i=0; i<vec_temp.size(); i++){
				if(DG::Xloc[vec_temp[i]] > vec_line2[0]){
					vec_TBR.push_back(vec_temp[i]);
				}
			}
		}

		for(unsigned int i=0; i<vec_TBR.size(); i++){
			vec_temp.erase(find(vec_temp.begin(), vec_temp.end(), vec_TBR[i]));
		}

		vec_xx_temp.clear();
		vec_yy_temp.clear();

		for(unsigned int j=0; j<vec_temp.size(); j++){
			vec_xx_temp.push_back(DG::Xloc[vec_temp[j]]);
			vec_yy_temp.push_back(DG::Yloc[vec_temp[j]]);
		}
	}

	vector<double> vec_xx_pruned;
	vector<double> vec_yy_pruned;

	if(vec_temp.size() <= CP::lepton_cluster_size){
		vec_pruned = lepton_bars;
	}
	else{
		vec_pruned = vec_temp;
	}

	for(unsigned int i=0; i<vec_pruned.size(); i++){
		vec_xx_pruned.push_back(DG::Xloc[vec_pruned[i]]);
		vec_yy_pruned.push_back(DG::Yloc[vec_pruned[i]]);
	}

	vector<int> vec_pruned_output;
	vec_pruned_output = vec_pruned;

	return vec_pruned_output;
}


vector<double> pruningLines(int TOF1_Gap, double x_kstop, double y_kstop, vector<int> lepton_bars, double distance){

	vector<double> vec_output;

	///Determine Pruning Line using "PruningLine" function
	vector<double> vec_pruning_line1;  vec_pruning_line1.clear();
	vector<double> vec_pruning_line2;  vec_pruning_line2.clear();
	
	vec_pruning_line1 = PruningLine(TOF1_Gap, x_kstop, y_kstop);
	
	vec_output.push_back(vec_pruning_line1[0]);
	vec_output.push_back(vec_pruning_line1[1]);
	vec_output.push_back(vec_pruning_line1[2]);
	vec_output.push_back(vec_pruning_line1[3]);


	///Pruning the data
	vector<int> vec_temp;
	vector<int> vec_TBR;
	vector<int> vec_pruned;

	vec_temp = lepton_bars;

	if(TOF1_Gap==1 || TOF1_Gap==2 || TOF1_Gap == 10 || TOF1_Gap == 11 || TOF1_Gap == 12){
		for(unsigned int i=0; i<vec_temp.size(); i++){
			if(DG::Yloc[vec_temp[i]] < DG::Xloc[vec_temp[i]] * vec_pruning_line1[4] + vec_pruning_line1[5]){
				vec_TBR.push_back(vec_temp[i]);
			}
		}
	}
	else if(TOF1_Gap==4 || TOF1_Gap==5 || TOF1_Gap==6|| TOF1_Gap==7 || TOF1_Gap==8){     
		for(unsigned int i=0; i<vec_temp.size(); i++){
			if(DG::Yloc[vec_temp[i]] > DG::Xloc[vec_temp[i]] * vec_pruning_line1[4] + vec_pruning_line1[5]){
				vec_TBR.push_back(vec_temp[i]);
			}
		}
	}
	else if(TOF1_Gap == 3){
		for(unsigned int i=0; i<vec_temp.size(); i++){
			if(DG::Xloc[vec_temp[i]] < x_kstop){
				vec_TBR.push_back(vec_temp[i]);
			}
		}
	}
	else if(TOF1_Gap == 9){
		for(unsigned int i=0; i<vec_temp.size(); i++){
			if(DG::Xloc[vec_temp[i]] > x_kstop){
				vec_TBR.push_back(vec_temp[i]);
			}
		}
	}

	for(unsigned i=0; i<vec_TBR.size(); i++){
		vec_temp.erase(find(vec_temp.begin(), vec_temp.end(), vec_TBR[i]));
	}

	/// REPRUNING IF TOO FEW LEPTONS
	if(vec_temp.size() <= CP::lepton_cluster_size){
		vec_pruning_line2 = PruningLine2(TOF1_Gap, distance, x_kstop, y_kstop);

		vec_output.push_back(vec_pruning_line2[0]);
		vec_output.push_back(vec_pruning_line2[1]);
		vec_output.push_back(vec_pruning_line2[2]);
		vec_output.push_back(vec_pruning_line2[3]);
	}

	return vec_output;
}