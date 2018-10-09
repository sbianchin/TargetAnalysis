/*
 * Created by Sebastien Bianchin on 2018-07-25 (s.bianchin@triumf.ca)
 */

#include <iostream>

#include "leptonFitHelperFunctions.hpp"

#include "intersect.hpp"
#include "helperFunctions.hpp"
#include "DetectorGeometry.hpp"
#include "CommonParameters.hpp"

namespace DG = DetectorGeometry;
namespace CP = CommonParameters;

vector<int> selectLeptonsToFit(bool to_rotate, int gap_to_fit, vector<int> lepton_bars,
							   vector<double> vec_line_parameters, int EB_add_weight){

	vector<int> vec_temp;
	vector<int> vec_TBR;
	vector<int> vec_EB_pr;
	int TOF1_gap = -1;

	if(to_rotate){
		TOF1_gap = DG::TOF1_rotated[gap_to_fit-1] + 1;
		for(unsigned int i=0; i<lepton_bars.size(); i++){
			vec_temp.push_back(DG::TARGET_Rotated_index[lepton_bars[i]]);
		}
	}
	else{
		TOF1_gap = gap_to_fit;
		vec_temp = lepton_bars;
	}

	/// Remove leptons to far from the fit linevec_temp
	if(vec_line_parameters.size() > 0){
		for(unsigned int i=0; i<vec_temp.size(); i++){
			if(distanceToLine(DG::Xloc[vec_temp[i]],DG::Yloc[vec_temp[i]],vec_line_parameters[0],vec_line_parameters[1]) >= CP::max_dist){
				vec_TBR.push_back(vec_temp[i]);
			}
		}

		for(unsigned int i=0; i<vec_TBR.size(); i++){
			vec_temp.erase(find(vec_temp.begin(), vec_temp.end(), vec_TBR[i]));
		}
	}	

	/// Add weight on Edge Bars
	for(unsigned int i=0; i<vec_temp.size(); i++){
    	if(IsIn(vec_temp[i], DG::channel[TOF1_gap-1][0], DG::channel[TOF1_gap-1][1], DG::channel[TOF1_gap-1][2],
    			DG::channel[TOF1_gap-1][3], DG::channel[TOF1_gap-1][4], DG::channel[TOF1_gap-1][5], 
    			DG::channel[TOF1_gap-1][6], DG::channel[TOF1_gap-1][7], DG::channel[TOF1_gap-1][8], 
    			DG::channel[TOF1_gap-1][9], DG::channel[TOF1_gap-1][10], DG::channel[TOF1_gap-1][11])){

    		vec_EB_pr.push_back(vec_temp[i]);
    	}
	}

	for(unsigned int i=0; i<vec_EB_pr.size(); i++){
		for(int j=0; j<EB_add_weight; j++){
			vec_temp.push_back(vec_EB_pr[i]);
		}
	}

	return vec_temp;
}

vector<int> rotateVector(vector<int> vec_input){

	vector<int> vec_output;		vec_output.clear();
	vector<int>	vec_temp;		vec_temp.clear();

	for(unsigned int i=0; i<vec_input.size(); i++){
		vec_temp.push_back(DG::TARGET_Rotated_index[vec_input[i]]);
	}

	vec_input.clear();
	vec_input = vec_temp;

	return vec_input;
}

vector<double> intersectTOF1(int TOF1_Gap, double m_fit_line, double b_fit_line){

	double TOF1_x1, TOF1_x2;
	double TOF1_y1, TOF1_y2;
	double m_TOF1, b_TOF1;
	vector<double> vec_output;         vec_output.clear();
	vector<double> vec_output_rotate;  vec_output_rotate.clear();

	TOF1_x1 = DG::X_TOF1_line[TOF1_Gap][0];
	TOF1_x2 = DG::X_TOF1_line[TOF1_Gap][1];
	TOF1_y1 = DG::Y_TOF1_line[TOF1_Gap][0];
	TOF1_y2 = DG::Y_TOF1_line[TOF1_Gap][1];

	m_TOF1 = (TOF1_y1 - TOF1_y2)/(TOF1_x1 - TOF1_x2);
	b_TOF1 = DG::TOF1_Yloc[TOF1_Gap][1] - m_TOF1*DG::TOF1_Xloc[TOF1_Gap][1];

	if(TOF1_Gap==2 || TOF1_Gap==8){
		vec_output.push_back(TOF1_x1);
		vec_output.push_back(m_fit_line*TOF1_x1+b_fit_line);
	}
    else{
    	vec_output = TwoLinesIntersect(m_fit_line, b_fit_line, m_TOF1, b_TOF1);
    }

    return vec_output;
}

vector<double> goodIntersectWithCircle(double a, double b, double R, int TOF1_gap){
	double intersect1[2] = {999.99, 999.99};
	double intersect2[2] = {999.99, 999.99};

	double dist1, dist2 = 999.99;
	vector<double> vec_intersect_XY;	vec_intersect_XY.clear();

	intersect1[0] = intersectx1(a, b, R);
	intersect2[0] = intersectx2(a, b, R);

	intersect1[1] = y1_int(intersect1[0], a, b);
	intersect2[1] = y1_int(intersect2[0], a, b);

	dist1 = distance(intersect1[0], intersect1[1], DG::TOF1_Xloc[TOF1_gap-1][2], DG::TOF1_Yloc[TOF1_gap-1][2]);
	dist2 = distance(intersect2[0], intersect2[1], DG::TOF1_Xloc[TOF1_gap-1][2], DG::TOF1_Yloc[TOF1_gap-1][2]);

	if(dist1 < dist2){
		vec_intersect_XY.push_back(intersect1[0]);
		vec_intersect_XY.push_back(intersect1[1]);
	}
	else{
		vec_intersect_XY.push_back(intersect2[0]);
		vec_intersect_XY.push_back(intersect2[1]);	
	}

	return vec_intersect_XY;
}

int whichTOF1Section(int TOF1_gap, vector<double> vec_intersect){

	double d0, d1, d2, d3, d4;
	double dist_min = 999.99;
	double dist = 999.99;
	int closest_section = -1;

	for(int i=0; i<5; i++){
		dist = distance(vec_intersect[0], vec_intersect[1], DG::TOF1_Xloc[TOF1_gap-1][i], DG::TOF1_Yloc[TOF1_gap-1][i]);

		if(dist < dist_min){
			dist_min = dist;
			closest_section = i;
		}
	}

	return closest_section;
}

vector<double> restoreFitLine(double a, double b){

	vector<double> vec_out;
	vec_out.clear();

	vec_out.push_back(50.*a + b);
	vec_out.push_back(-50.);
	vec_out.push_back(-50*a + b);
	vec_out.push_back(50.);

	return vec_out;
}



vector<double> lineLeptonToTOF1(vector<int> vec_in, int TOF1_gap, double X_Kstop, double Y_Kstop){

  vector<double> vec_out;
  
  bool bars_are_neighbours = false;
  bool b_bar1 = false;
  bool b_bar2 = false;
  double dist1 = -1;
  double dist2 = -1;


  if(vec_in.size() == 0){
    vec_out.push_back(X_Kstop);
    vec_out.push_back(Y_Kstop);
    vec_out.push_back(DG::TOF1_Xloc[TOF1_gap-1][2]);
    vec_out.push_back(DG::TOF1_Yloc[TOF1_gap-1][2]);
  }

  if(vec_in.size() == 1){
    vec_out.push_back(DG::Xloc[vec_in[0]]);
    vec_out.push_back(DG::Yloc[vec_in[0]]);
    vec_out.push_back(DG::TOF1_Xloc[TOF1_gap-1][2]);
    vec_out.push_back(DG::TOF1_Yloc[TOF1_gap-1][2]);
  }

  if(vec_in.size() == 2){

    bars_are_neighbours = areNeighbours(vec_in[0], vec_in[1]);

    if(bars_are_neighbours){
      vec_out.push_back(0.5*(DG::Xloc[vec_in[0]] + DG::Xloc[vec_in[1]]));
      vec_out.push_back(0.5*(DG::Yloc[vec_in[0]] + DG::Yloc[vec_in[1]]));
      vec_out.push_back(DG::TOF1_Xloc[TOF1_gap-1][2]);   
      vec_out.push_back(DG::TOF1_Yloc[TOF1_gap-1][2]);   
    }
    else{
      dist1 = sqrt(pow(DG::Xloc[vec_in[0]] - X_Kstop,2)+pow(DG::Yloc[vec_in[0]] - Y_Kstop,2));
      dist2 = sqrt(pow(DG::Xloc[vec_in[1]] - X_Kstop,2)+pow(DG::Yloc[vec_in[1]] - Y_Kstop,2));

      if(dist1 <= 10.) b_bar1 = true;
      if(dist2 <= 10.) b_bar2 = true;

      if(b_bar1 && !b_bar2){
        vec_out.push_back(DG::Xloc[vec_in[0]]);
        vec_out.push_back(DG::Yloc[vec_in[0]]);
      }
      else if(!b_bar1 && b_bar2){
        vec_out.push_back(DG::Xloc[vec_in[1]]);
        vec_out.push_back(DG::Yloc[vec_in[1]]);
      }
      else if(b_bar1 && b_bar2){
        if(dist1 < dist2){
          vec_out.push_back(DG::Xloc[vec_in[0]]);
          vec_out.push_back(DG::Yloc[vec_in[0]]);
        }
        else{
          vec_out.push_back(DG::Xloc[vec_in[1]]);
          vec_out.push_back(DG::Yloc[vec_in[1]]);        
        }
      }
      else if(!b_bar1 && !b_bar2){
        vec_out.push_back(X_Kstop);
        vec_out.push_back(Y_Kstop);
      }
    }

    vec_out.push_back(DG::TOF1_Xloc[TOF1_gap-1][2]);
    vec_out.push_back(DG::TOF1_Yloc[TOF1_gap-1][2]);
  }

  return vec_out;
}
