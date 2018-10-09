/*
 * Created by Sebastien Bianchin on 2018-07-20 (s.bianchin@triumf.ca)
 */

#include <iostream>

#include "findKaonCentroid.hpp"
#include "DetectorGeometry.hpp"

namespace DG = DetectorGeometry;

vector<double> findKaonCentroid(const DetectorData &data, vector<int> kaon_bars) {

	double X_weight = 0.;
	double Y_weight = 0.;
	double total_energy = 0.;

	vector<double> K_centroid;

	if(kaon_bars.size()>0){
		for(unsigned int i=0; i<kaon_bars.size(); i++){
			X_weight += data.ADC_Low_TARGET[kaon_bars[i]] * DG::Xloc[kaon_bars[i]];
			Y_weight += data.ADC_Low_TARGET[kaon_bars[i]] * DG::Yloc[kaon_bars[i]];
			total_energy += data.ADC_Low_TARGET[kaon_bars[i]];
		}
	}

	if(kaon_bars.size()>0 && total_energy!=0){
		K_centroid.push_back(X_weight/total_energy);
		K_centroid.push_back(Y_weight/total_energy);
	}
	else{
		K_centroid.push_back(0.);
		K_centroid.push_back(0.);
	}

	return K_centroid;
}
