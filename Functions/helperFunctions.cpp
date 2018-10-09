/*
 * Created by Sebastien Bianchin on 2018-07-20 (s.bianchin@triumf.ca)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "DetectorGeometry.hpp"
#include "CommonParameters.hpp"

namespace DG = DetectorGeometry;
namespace CP = CommonParameters;


double distance(double x1, double y1, double x2, double y2){

	double dist = 0;
	dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

	return dist;

}

vector<double> TwoLinesIntersect(double a1=99., double b1=99., double a2=99., double b2=99.){

	vector<double> vec_2lines_intersect;

	vec_2lines_intersect.push_back((b2 - b1) / (a1 - a2));
	vec_2lines_intersect.push_back((a1*b2 - a2*b1) / (a1 - a2));

	return vec_2lines_intersect;
}

float distanceToLine(float x=0., float y=0., float a=0., float b=0.){ // Line is given by equation y=a*x + b;

	float dist = 0.;
	
	if((-a*x+y-b) < 0) dist = -(-a*x+y-b)/sqrt(a*a+1);
	else dist = (-a*x+y-b)/sqrt(a*a+1);
	
	return dist;
}	

//bool IsIn(int a=0, int l0=0, int l1=0, idouble distance_2points(double x1, double y1, double x2, double y2){
//				   int l8=0, int l9=0, int l10=0, int l11=0){
// bool IsIn(int a, int l0, int l1, int l2, int l3, int l4, int l5, int l6, int l7,
// 				   int l8, int l9, int l10, int l11){

// 	bool output = false;

// 		if(a==l0 || a==l1 || a==l2 || a==l3 || a==l4 || a==l5 || a==l6 || a==l7 || a==l8 || a==l9 || a==l10 || a==l11){
// 			output = true;
// 		}

// 	return output;
// }

vector<int> removeDoubles(vector<int> vec_in){
	vector<int> vec_out;	vec_out.clear();

	vec_out = vec_in;

   sort(vec_out.begin(), vec_out.end());
   vec_out.erase(unique(vec_out.begin(), vec_out.end()), vec_out.end());

   return vec_out; 
}

bool areNeighbours(int bar1, int bar2){

  bool bar_has_neighbours = false;

  for(int i=0; i<8; i++){
    if(DG::TARGET_neighbours[bar1][i]==bar2) bar_has_neighbours = true;
  }
  
  return bar_has_neighbours;
}

vector<double> getSlope(double x1, double y1, double x2, double y2){

  vector<double> v_output;
  double a;
  double b;
  
  a = (y2-y1)/(x2-x1);
  b = y1 - a*x1;

  v_output.push_back(a);
  v_output.push_back(b);

  return v_output;
}

double distanceBetweenTwoPoints(double x1, double y1, double x2, double y2){

  double dist;
  dist = sqrt(pow((x1-x2),2)+pow((y1-y2),2));
  return dist;
}

vector<double> intersectCircle(double a=0., double b=0., double R=44.5, double xtof1=-1., double ytof1=-1.){

  vector<double> intersect;
  double x1, y1;
  double x2, y2;
  double dist1, dist2;

  x1 = (-2*a*b - sqrt(4*a*a*b*b - 4*(a*a+1)*(b*b-R*R))) / (2*(a*a+1));
  y1 = a*x1+b;
  x2 = (-2*a*b + sqrt(4*a*a*b*b - 4*(a*a+1)*(b*b-R*R))) / (2*(a*a+1));
  y2 = a*x2+b;

  dist1 = distanceBetweenTwoPoints(x1, y1, xtof1, ytof1);
  dist2 = distanceBetweenTwoPoints(x2, y2, xtof1, ytof1);

  if(dist1 <= dist2){
    intersect.push_back(x1);
    intersect.push_back(y1);
    intersect.push_back(x2);
    intersect.push_back(y2);
  }
  else{
    intersect.push_back(x2);
    intersect.push_back(y2);
    intersect.push_back(x1);
    intersect.push_back(y1);
  }

  return intersect;
}

double angleCalculation(double slope, double xtof1, double ytof1, double xtarget, double ytarget){

  double angle = -1.;
  double alpha = -1.;

  double angle2 = -1.;

  bool quad1 = false;
  bool quad2 = false;
  bool quad3 = false;
  bool quad4 = false;


  if((xtof1 >= 0 && xtof1 <= CP::R_TOF1) && (ytof1 >= 0 && ytof1 <= CP::R_TOF1)) quad1 = true;
  if((xtof1 >= -CP::R_TOF1 && xtof1 <= 0) && (ytof1 >= 0 && ytof1 <= CP::R_TOF1)) quad2 = true;
  if((xtof1 >= -CP::R_TOF1 && xtof1 <= 0) && (ytof1 >= -CP::R_TOF1 && ytof1 <= 0)) quad3 = true;
  if((xtof1 >= 0 && xtof1 <= CP::R_TOF1) && (ytof1 >= -CP::R_TOF1 && ytof1 <= 0)) quad4 = true;

  if(!quad1 && !quad2 && !quad3 && !quad3){
    if((round(xtof1) == round(CP::R_TOF1)) && (round(ytof1) == round(0.))) quad1 = true;
    if((round(xtof1) == round(0.)) && (round(ytof1) == round(CP::R_TOF1))) quad2 = true;
    if((round(xtof1) == round(-CP::R_TOF1)) && (round(ytof1) == round(0.))) quad3 = true;
    if((round(xtof1) == round(0.)) && (round(ytof1) == round(-CP::R_TOF1))) quad4 = true;
  }

  // if(slope>=0 && xtof1-xstop>=0 && ytof1-ystop>=0) quad1 = true;
  // if(slope<=0 && xtof1-xstop<=0 && ytof1-ystop>=0) quad2 = true;
  // if(slope>=0 && xtof1-xstop<=0 && ytof1-ystop<=0) quad3 = true;
  // if(slope<=0 && xtof1-xstop>=0 && ytof1-ystop<=0) quad4 = true;

  cout << "Q1 : " << quad1 << endl;
  cout << "Q2 : " << quad2 << endl;
  cout << "Q3 : " << quad3 << endl;
  cout << "Q4 : " << quad4 << endl;
 
  alpha = atan(slope)*(180/TMath::Pi());
  cout << "alpha : " << alpha << endl;

  // if(quad1){
  //   if(slope >= 0) angle = alpha;
  //   else angle = alpha + 360.;
  // }
  // else if(quad2){
  //   if(slope >= 0) angle = alpha;
  //   else angle = alpha + 180.;
  // }
  // else if(quad3){
  //   if(slope >= 0) angle = alpha + 180.;
  //   else angle = alpha + 180.;
  // }
  // else if(quad4){
  //   if(slope >= 0) angle = alpha;
  //   else angle = alpha + 360.;
  // }

  if(quad1) angle = alpha;
  else if(quad2) angle = alpha + 180.;
  else if(quad3) angle = alpha + 180.;
  else if(quad4) angle = alpha + 360.;

  if((xtof1 - xtarget) < 0) angle2 = alpha + 180.;
    else{
      if((ytof1 - ytarget) >= 0) angle2 = alpha;
      else angle2 = alpha + 360.;
  }

  if(angle2 > 360.) angle2 -= 360.;
  //if(empty_lepton3) angle_final_guide = 999.;

  return angle;
}

double angleCalculation2(double slope, double xtof1, double ytof1, double xtarget, double ytarget){

  double angle = -1.;
  double alpha = -1.;

  alpha = atan(slope)*(180/TMath::Pi());

  if((xtof1 - xtarget) < 0) angle = alpha + 180.;
    else{
      if((ytof1 - ytarget) >= 0) angle = alpha;
      else angle = alpha + 360.;
  }

  if(angle > 360.) angle -= 360.;
  //if(empty_lepton3) angle_final_guide = 999.;

  return angle;
}


bool goodTOF1(int TOF1_Gap, vector<double> vec_int){  // TO MODIFY (DOESN'T WORK FOR EVENT #6)
	
	double X_min, X_max;
	double Y_min, Y_max;
	bool Good_TOF1 = false;

	if(DG::X_TOF1_line[TOF1_Gap][0] >= DG::X_TOF1_line[TOF1_Gap][1]){
		X_max = DG::X_TOF1_line[TOF1_Gap][0];
		X_min = DG::X_TOF1_line[TOF1_Gap][1];
	}
	else{
		X_max = DG::X_TOF1_line[TOF1_Gap][1];
		X_min = DG::X_TOF1_line[TOF1_Gap][0];
	}

	if(DG::Y_TOF1_line[TOF1_Gap][0] >= DG::Y_TOF1_line[TOF1_Gap][1]){
		Y_max = DG::Y_TOF1_line[TOF1_Gap][0];
		Y_min = DG::Y_TOF1_line[TOF1_Gap][1];
	}
	else{
		Y_max = DG::Y_TOF1_line[TOF1_Gap][1];
		Y_min = DG::Y_TOF1_line[TOF1_Gap][0];
	}

	if((vec_int[0] >= X_min && vec_int[0] <= X_max) &&
	   (vec_int[1] >= Y_min && vec_int[1] <= Y_max)) Good_TOF1 = true;

	return Good_TOF1;
}

vector<double> defineFitLine(double a, double b){

  vector<double> vec_line_parameters;

  if(a==0){
    vec_line_parameters.push_back(b); 
    vec_line_parameters.push_back(-50.); 
    vec_line_parameters.push_back(b); 
    vec_line_parameters.push_back(50.); 
  }
  else{
    vec_line_parameters.push_back(-50.);
    vec_line_parameters.push_back((-1/a)*(-50.) + (b/a));
    vec_line_parameters.push_back(50.);
    vec_line_parameters.push_back((-1/a)*(50.) + (b/a));
  }

  return vec_line_parameters;
}

// vector<double> reverseX(vector<double> vec_input){

//   vector<double> vec_output;

//   vec_output.push_back(vec_input[1]);
//   vec_output.push_back(-vec_input[0]);

//   return vec_output;
// }