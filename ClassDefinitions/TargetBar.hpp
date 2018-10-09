/* 
 * Created by Jack Hong on 2018-08-17. (jhong@alumni.ubc.ca)
 */
#pragma once

#include "boost_geometry.hpp"

enum BarType {
    empty, lepton, kaon
};

class TargetBar : public TObject {
private:
    point_t m_coord;   // (x, y) coordinate
    int m_bar_number;

    BarType m_type;
    int m_ADC_HG;      // high gain energy
    int m_ADC_LG;      // low gain energy
    int m_TDC_LE;      // time

    void printBarType();

public:
    TargetBar(int bar_number=0, BarType bar_type=empty, int adc_hg=-1, int adc_lg=-1, int tdc_le=-1);
    TargetBar(point_t p, int bar_number=-1, BarType bar_type=empty, int adc_hg=-1, int adc_lg=-1, int tdc_le=-1);

    virtual void setBarType(BarType bar_type);
    virtual int getBarNumber();
    virtual point_t getCoord();
    virtual BarType getBarType();
    virtual int getADC_HG();
    virtual int getADC_LG();
    virtual int getTDC_LE();
    virtual void printInfo();

    ClassDef(TargetBar, 1);
};