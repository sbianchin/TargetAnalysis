/*
 * Created by Jack Hong on 2018-06-28. (jhong@alumni.ubc.ca)
 *
 * Calculate the threshold by adding the offset to the pedestal.
 * Return the result in the given threshold array.
 *
 */

#include "calculateThreshold.hpp"
#include <iostream>

//void calculateThreshold(int num_elements, double* threshold, double* pedestal, int offset) {
void calculateThreshold(int num_elements, int* threshold, const double* pedestal, int offset) {

    for (int k=0; k<num_elements; k++) {
        threshold[k] = static_cast<int> (round(pedestal[k])) + offset;
    }
}

