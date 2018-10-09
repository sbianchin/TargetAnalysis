#ifndef __CINT__

#include "intersect.hpp"
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <TROOT.h>
#include "TSystem.h"
#include "TFile.h"
#include "TProfile.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TF1.h"
#include "TRandom.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TPolyLine.h"
#include "TLine.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TBranch.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TEllipse.h"
#include "TMarker.h"
#include "DetectorGeometry.hpp"
#endif

using namespace CommonParameters; // TODO: Remove using statements.
using namespace DetectorGeometry;

double intersectx1(double a, double b, double R)
{
	double x1 = 0.;

	x1 = (-2*a*b - sqrt(4*a*a*b*b - 4*(a*a+1)*(b*b-R*R))) / (2*(a*a+1));


	return x1;
}

double intersectx2(double a, double b, double R)
{
	double x2 = 0.;

	x2 = (-2*a*b + sqrt(4*a*a*b*b - 4*(a*a+1)*(b*b-R*R))) / (2*(a*a+1));


	return x2;
}

double y1_int(double x1, double a, double b)
{
	double y1 = 0.;
	y1 = a * x1 + b;

	return y1;
}

double y2_int(double x2, double a, double b)
{
	double y2 = 0.;
	y2 = a * x2 + b;

	return y2;
}


double y_int2(double x,double a, double b)
{
	double y = 0.;

	y = a * x + b;

	return y;
}

// double distance(double x1, double y1, double x2, double y2)
// {
// 	double dist = 0;
// 	dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

// 	return dist;

// }


double distance_to_line(double x, double y, double a, double b) // Line is given by equation y=a*x + b;
{
	double dist = 0.;
	  
	if((-a*x+y-b) < 0) dist = -(-a*x+y-b)/sqrt(a*a+1);
	else dist = (-a*x+y-b)/sqrt(a*a+1);
	
	return dist;
}	


double points_to_slope(double x1, double y1, double x2, double y2) {
	double slope = 0.0;

	slope = (y2-y1)/(x2-x1);

	return slope;
}
	
double points_to_y_int(double x1, double y1, double x2, double y2){
	double y_int = 0;

	y_int = y1 - x1*(y2-y1)/(x2-x1);

	return y_int;
}


double C2_intersect(double a, double b, double R){
	return (R-b)/a;
}
	


bool IsIn(int a, int l0, int l1, int l2, int l3, int l4, int l5, int l6, int l7,
				   int l8, int l9, int l10, int l11)
{

	bool output = false;

		if(a==l0 || a==l1 || a==l2 || a==l3 || a==l4 || a==l5 || a==l6 || a==l7 || a==l8 || a==l9 || a==l10 || a==l11){
			output = true;
		}

	return output;
}


double rotate_by_angle(double x, double y, int theta, char coord){

	double new_coordinate = 0;

	if(!(theta==0 || theta==30 || theta==60 || theta==90 || theta==120 || theta==150 || theta==180 ||
		theta==-30 || theta==-60 || theta==-90 || theta==-120 || theta==-150)){
		return x;
	}


	if(coord=='x'){

		new_coordinate = cos(theta*M_PI/180.0)*x - sin(theta*M_PI/180.0)*y;

	}
	else if(coord=='y'){

		new_coordinate = sin(theta*M_PI/180.0)*x + cos(theta*M_PI/180.0)*y;

	}

	return new_coordinate;
}

vector<double> _2lines_intersect(double a1, double b1, double a2, double b2){

	vector<double> vec_2lines_intersect;

	vec_2lines_intersect.push_back((b2 - b1) / (a1 - a2));
	vec_2lines_intersect.push_back((a1*b2 - a2*b1) / (a1 - a2));

	return vec_2lines_intersect;
}


/*vector<double> _intersect_TOF1(int TOF1_Gap, double m_fit_line, double b_fit_line){

	double TOF1_x1, TOF1_x2;
	double TOF1_y1, TOF1_y2;
	double m_TOF1, b_TOF1;
	vector<double> vec_output;         vec_output.clear();
	vector<double> vec_output_rotate;  vec_output_rotate.clear();

	TOF1_x1 = X_TOF1_line[TOF1_Gap][0];
	TOF1_x2 = X_TOF1_line[TOF1_Gap][1];
	TOF1_y1 = Y_TOF1_line[TOF1_Gap][0];
	TOF1_y2 = Y_TOF1_line[TOF1_Gap][1];

	m_TOF1 = (TOF1_y1 - TOF1_y2)/(TOF1_x1 - TOF1_x2);
	b_TOF1 = TOF1_Yloc[TOF1_Gap][1] - m_TOF1*TOF1_Xloc[TOF1_Gap][1];

	if(TOF1_Gap==2 || TOF1_Gap==8){
		vec_output.push_back(TOF1_x1);
		vec_output.push_back(m_fit_line*TOF1_x1+b_fit_line);
	}
    else vec_output = _2lines_intersect(m_fit_line, b_fit_line, m_TOF1, b_TOF1);

    return vec_output;
}*/

// bool _Good_TOF1(int TOF1_Gap, vector<double> vec_int){
// 	double X_min, X_max;
// 	double Y_min, Y_max;
// 	bool Good_TOF1 = false;

// 	if(X_TOF1_line[TOF1_Gap][0]>=X_TOF1_line[TOF1_Gap][1]){
// 		X_max = X_TOF1_line[TOF1_Gap][0];
// 		X_min = X_TOF1_line[TOF1_Gap][1];
// 	}
// 	else{
// 		X_max = X_TOF1_line[TOF1_Gap][1];
// 		X_min = X_TOF1_line[TOF1_Gap][0];
// 	}

// 	if(Y_TOF1_line[TOF1_Gap][0]>=Y_TOF1_line[TOF1_Gap][1]){
// 		Y_max = Y_TOF1_line[TOF1_Gap][0];
// 		Y_min = Y_TOF1_line[TOF1_Gap][1];
// 	}
// 	else{
// 		Y_max = Y_TOF1_line[TOF1_Gap][1];
// 		Y_min = Y_TOF1_line[TOF1_Gap][0];
// 	}

// 	if((vec_int[0]>=X_min && vec_int[0]<=X_max) &&
// 	   (vec_int[1]>=Y_min && vec_int[1]<=Y_max)) Good_TOF1 = true;


// 	return Good_TOF1;
// }

vector<double> _perp_line(double m1, double x_int, double y_int){

	double m2;
	double b2;

	double y2_left;
	double y2_right;

	vector<double> y2;
	y2.clear();

	m2 = -1/m1;
	b2 = y_int - m2*x_int;

	y2_left = m2*(-50.) + b2;
	y2_right = m2*(50.) + b2;

/*	cerr << "FUNCTION " << endl;
	cerr << "m2 = " << m2 << endl;
	cerr << "b2 = " << b2 << endl;
	cerr << "y_l = " << y2_left << endl;
	cerr << "y_r = " << y2_right << endl;
	cerr << endl; 
*/
	y2.push_back(y2_left);
	y2.push_back(y2_right);

	return y2;
}