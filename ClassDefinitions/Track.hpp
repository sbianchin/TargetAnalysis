/* 
 * Created by Jack Hong on 2018-07-12. (jhong@alumni.ubc.ca)
 */
#pragma once 

#include <vector>
#include "TPrincipal.h"
#include "TLine.h"

class Track : public TObject {
private:
    double m_slope;
    double m_y_intercept;
    double m_angle;

    double m_slope_error;
    double m_y_intercept_error;
    double m_angle_error;

    //TPrincipal m_pca;

public:
    Track();
    Track(double slope, double y_intercept, double slope_error, double y_intercept_error);
    //Track(TPrincipal pca);

//    virtual double getSlope();
//    virtual double getYIntercept();
//    virtual double getAngle();
//    virtual double getSlopeError();
//    virtual double getYInterceptError();
//    virtual double getAngleError();
//    virtual double getCentroid();
//    virtual TVector getEigenvector();
//    virtual double getchi2();
//    virtual TLine getTLine();

    // line required to work with ROOT
    ClassDef(Track, 1);
};