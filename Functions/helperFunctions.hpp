/*
 * Created by Sebastien Bianchin on 2018-07-20 (s.bianchin@triumf.ca)
 */

#ifndef MACROS_HELPERFUNCTIONS_H
#define MACROS_HELPERFUNCTIONS_H

#include <vector>

double distance(double x1, double y1, double x2, double y2);

vector<double> TwoLinesIntersect(double a1=99., double b1=99., double a2=99., double b2=99.);

float distanceToLine(float x=0., float y=0., float a=0., float b=0.);

//bool IsIn(int a=0, int l0=0, int l1=0, int l2=0, int l3=0, int l4=0, int l5=0, int l6=0, int l7=0,
//				   int l8=0, int l9=0, int l10=0, int l11=0);
//bool IsIn(int a, int l0, int l1, int l2, int l3, int l4, int l5, int l6, int l7,
//				   int l8, int l9, int l10, int l11);

vector<int> removeDoubles(vector<int> vec_in);

bool areNeighbours(int bar1, int bar2);

vector<double> getSlope(double x1, double y1, double x2, double y2);

double distanceBetweenTwoPoints(double x1, double y1, double x2, double y2);

vector<double> intersectCircle(double a=0., double b=0., double R=44.5, double xtof1=-1., double ytof1=-1.);

double angleCalculation(double slope, double xtof1, double ytof1, double xtarget, double ytarget);

double angleCalculation2(double slope, double xtof1, double ytof1, double xtarget, double ytarget);

bool goodTOF1(int TOF1_Gap, vector<double> vec_int);

vector<double> defineFitLine(double a, double b);

//vector<double> reverseXY(vector<double> vec_input);

#endif //MACROS_HELPERFUNCTIONS_H
