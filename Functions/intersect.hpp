/* 
 * Created by Jack Hong on 2018-07-05. (jhong@alumni.ubc.ca)
 */
#pragma once

double intersectx1(double a=0., double b=0., double R=44.5);

double intersectx2(double a=0., double b=0., double R=44.5);

double y1_int(double x1=0., double a=0., double b=0.);

double y2_int(double x2=0., double a=0., double b=0.);

double y_int2(double x=0.,double a=0., double b=0.);

//double distance(double x1=0., double y1=0., double x2=0., double y2=0.);

// Line is given by equation y=a*x + b;
double distance_to_line(double x=0., double y=0., double a=0., double b=0.);

double points_to_slope(double x1 = 0.0, double y1 = 0.0, double x2 = 1.0, double y2 = 1.0);

double points_to_y_int(double x1 = 0.0, double y1 = 0.0, double x2 = 1.0, double y2 = 1.0);

double C2_intersect(double a = 0.0, double b = 0.0, double R = 40.0);

bool IsIn(int a=0, int l0=0, int l1=0, int l2=0, int l3=0, int l4=0, int l5=0, int l6=0, int l7=0,
          int l8=0, int l9=0, int l10=0, int l11=0);

double rotate_by_angle(double x=0, double y=0, int theta=0, char coord='x');

vector<double> _2lines_intersect(double a1=99., double b1=99., double a2=99., double b2=99.);

//vector<double> _intersect_TOF1(int TOF1_Gap, double m_fit_line, double b_fit_line);

//bool _Good_TOF1(int TOF1_Gap, vector<double> vec_int);

vector<double> _perp_line(double m1, double x_int, double y_int);
