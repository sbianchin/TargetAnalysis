/* 
 * Created by Jack Hong on 2018-07-05. (jhong@alumni.ubc.ca)
 */
#pragma once

#include <vector>
#include "DetectorData.hpp"

struct uncertainty {
    double dx;
    double dy;
};

void _NEED_TO_ROTATE(vector<int> vec_myVector);

void _ADC_HG_SUM(vector<int> vec_myVector);

vector<double> SFT_Test_CR_Event(DetectorData data, double phi, double C2X_centroid, double length_in_target);

int kaon_fiber(double x_bar, double y_bar);

uncertainty calculate_uncertainty(double x, double y, double m, double b, double dm, double db);

bool check_vertical_kaon(vector<double> vec_xx_kaon);