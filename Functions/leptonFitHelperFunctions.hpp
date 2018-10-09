/*
 * Created by Sebastien Bianchin on 2018-07-25 (s.bianchin@triumf.ca)
 */

#ifndef MACROS_LEPTONFITHELPERFUNCTIONS_H
#define MACROS_LEPTONFITHELPERFUNCTIONS_H

#include <vector>


vector<int> selectLeptonsToFit(bool to_rotate, int gap_to_fit, vector<int> lepton_bars,
							   vector<double> vec_line_parameters, int EB_add_weight);

vector<int> rotateVector(vector<int> vec_input);

vector<double> intersectTOF1(int TOF1_Gap, double m_fit_line, double b_fit_line);

vector<double> goodIntersectWithCircle(double a, double b, double R, int TOF1_gap);

int whichTOF1Section(int TOF1_gap, vector<double> vec_intersect);

vector<double> restoreFitLine(double a, double b);

vector<double> lineLeptonToTOF1(vector<int> vec_in, int TOF1_gap, double X_Kstop, double Y_Kstop);

#endif //MACROS_LEPTONFITHELPERFUNCTIONS_H
