/* 
 * Created by Jack Hong on 2018-07-24. (jhong@alumni.ubc.ca)
 */
#pragma once

#include <vector>
#include "TargetBar.hpp"
#include "boost_geometry.hpp"
#include "DetectorData.hpp"

class Target : public TObject {
private:
    const static double Xcoords[256];
    const static double Ycoords[256];
    vector<TargetBar> m_bars;

    virtual void assignBarTypes();

public:
    Target();
    Target(DetectorData &data);
    virtual vector<TargetBar> getAllBars();
    virtual TargetBar getBar(int bar_index);
    virtual vector<TargetBar> getLeptonBars();
    virtual vector<TargetBar> getKaonBars();
    virtual void printBar(int bar_number);

ClassDef(Target, 1);
};