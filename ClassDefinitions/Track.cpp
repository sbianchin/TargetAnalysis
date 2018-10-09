/* 
 * Created by Jack Hong on 2018-07-12. (jhong@alumni.ubc.ca)
 */
#pragma once

#include "Track.hpp"
#include <iostream>

ClassImp(Track);

Track::Track() {

}

Track::Track(double slope, double y_intercept, double slope_error, double y_intercept_error)
    : m_slope(slope), m_y_intercept(y_intercept), m_slope_error(slope_error), m_y_intercept_error(y_intercept_error){

}
//
//Track::Track(TPrincipal pca) : m_pca(pca) {
//
//}

//double Track::getAngle() {
//    return m_angle;
//}
//
//double Track::getAngleError() {
//    return m_angle_error;
//}