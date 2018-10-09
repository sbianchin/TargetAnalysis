/*
 * Created by Sebastien Bianchin on 2018-07-24 (s.bianchin@triumf.ca)
 */

#ifndef MACROS_PRUNINGFUNCTIONS_H
#define MACROS_PRUNINGFUNCTIONS_H

#include <vector>

vector<int> TOF1Neighbours(int TOF1_gap);

vector<double> PruningArea(double x1, double x2, double x3);

vector<int> TriangularPruning(int TOF1_Gap, double x_kstop, double y_kstop, vector<int> kaon_bars, vector<int> lepton_bars);

vector<double> PruningLine(int TOF1_Gap, double x_kstop, double y_kstop);

vector<double> PruningLine2(int TOF1_Gap, double distance, double x_kstop, double y_kstop);

vector<int> LinearPruning(int TOF1_Gap, double x_kstop, double y_kstop, vector<int> lepton_bars, double distance);

vector<double> pruningLines(int TOF1_Gap, double x_kstop, double y_kstop, vector<int> lepton_bars, double distance);


#endif //MACROS_PRUNINGFUNCTIONS_H
