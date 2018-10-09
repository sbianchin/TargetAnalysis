/*
 * Created by Sebastien Bianchin on 2018-07-17. (s.bianchin@triumf.ca)
 */

#include <iostream>

#include "findLeptons.hpp"
#include "CutsAndWindows.hpp"
#include "CommonParameters.hpp"
#include "DetectorGeometry.hpp"

namespace CW = CutsAndWindows;
namespace CP = CommonParameters;
namespace DG = DetectorGeometry;

vector<int> findLeptons(const DetectorData &data, bool is_kaon[256], bool has_TDC_hit[256], int kaon_substitute) {

	vector<int> lepton_bars;	lepton_bars.clear();
	vector<int> vec_TBR;		vec_TBR.clear();

	bool is_lepton[256] = {false};
	bool has_neighbours = false;

	for(int i=0; i<256; i++){
		//is_lepton[i] = false;
		if(!is_kaon[i]){
			if(data.ADC_High_TARGET[i] >= 0 && has_TDC_hit[i]){
				//cout << "TEST : " << i << "  " << has_TDC_hit[i] << endl;
				is_lepton[i] = true;
				lepton_bars.push_back(i);
			}
			else if(data.ADC_High_TARGET[i] < 0 && data.ADC_Low_TARGET[i]>0){
				is_lepton[i] = true;
				lepton_bars.push_back(i);
				//cout << "BLUE BARS : " << i << endl;
			}
		}
	}

	if(lepton_bars.size() > CP::lepton_cluster_size){
		for(unsigned int i=0; i<lepton_bars.size(); i++){
			has_neighbours = false;
			for(int j=0; j<8; j++){
				if((DG::TARGET_neighbours[lepton_bars[i]][j]>=0) && (is_lepton[DG::TARGET_neighbours[lepton_bars[i]][j]] || is_kaon[DG::TARGET_neighbours[lepton_bars[i]][j]])){
					has_neighbours = true;
				}
			}

			if(!has_neighbours && lepton_bars[i]!=kaon_substitute){
				vec_TBR.push_back(lepton_bars[i]);
			}
		}

		//Removal of singlets
		for(unsigned int i=0; i<vec_TBR.size(); i++){
			//cout << "TBR : " << vec_TBR[i] << endl;
			lepton_bars.erase(find(lepton_bars.begin(), lepton_bars.end(), vec_TBR[i]));
		}
	}

	return lepton_bars;
}
