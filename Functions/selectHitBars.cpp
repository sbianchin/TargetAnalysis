/*
 * Created by Jack Hong on 2018-06-21. (jhong@alumni.ubc.ca)
 */

#include "selectHitBars.hpp"
#include "CommonParameters.hpp"
#include "DetectorGeometry.hpp"

/*
 * Update some variables in CommonParameters.h to select the hit bars.
 */
 namespace CP = CommonParameters;
 namespace DG = DetectorGeometry;

void selectHitBars(const DetectorData &data, Double_t minADC) {
    for (Int_t ii = 0; ii < CP::nBars; ii++) {
        if (data.ADC_High_TARGET[ii] > minADC
            && data.TDC_LE_TARGET[ii][0] > 0) {
            CP::Xhit[ii] = DG::Xloc[ii];
            CP::Yhit[ii] = DG::Yloc[ii];
            CP::Ehit[ii] = data.ADC_High_TARGET[ii];
            CP::Thit[ii] = data.TDC_LE_TARGET[ii][0];
            CP::hit_bars[ii] = ii;
            CP::nhits++;
        }
    }
}
