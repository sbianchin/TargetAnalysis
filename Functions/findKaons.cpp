/*
 * Created by Sebastien Bianchin on 2018-07-17 (s.bianchin@triumf.ca)
 */

#include <iostream>

#include "findKaons.hpp"
#include "CutsAndWindows.hpp"
#include "CommonParameters.hpp"
#include "DetectorGeometry.hpp"

namespace CW = CutsAndWindows;
namespace CP = CommonParameters;
namespace DG = DetectorGeometry;

vector<int> findKaons(const DetectorData &data, bool has_TDC_hit_Kstop[256], bool has_kaon_sub, int kaon_substitute) {
    
    vector<int> kaon_bars;
    vector<int> vec_TBR;
    bool is_kaon[256] = {false};
    bool has_neighbours = false;

     for(int i=0; i<256; i++){
        if (data.ADC_High_TARGET[i] >= CW::HG_KAON
            && data.ADC_Low_TARGET[i] >= CW::LG_KAON
            && has_TDC_hit_Kstop[i]){
        	is_kaon[i] = true;
            kaon_bars.push_back(i);
        }
    }

    if(kaon_bars.size() > CP::kaon_cluster_size){
    	for(unsigned int i=0; i<kaon_bars.size(); i++){
    		has_neighbours = false;
    		for(int j=0; j<8; j++){
    			if(is_kaon[DG::TARGET_neighbours[kaon_bars[i]][j]]){
    				has_neighbours = true;
    			}
    		}

    		if(!has_neighbours && kaon_bars[i]!=kaon_substitute){
    			vec_TBR.push_back(kaon_bars[i]);
    		}
    	}
    

    	// Removal of singlets
    	//for(unsigned int i=0; i<vec_TBR.size(); i++){
    	//	kaon_bars.erase(find(kaon_bars.begin(), kaon_bars.end(), vec_TBR[i]));
    	//}
    }
    // Add kaon substitute if kaon_bars in EMPTY
    else if(kaon_bars.size()==0 && has_kaon_sub){
    	kaon_bars.push_back(kaon_substitute);
    }

    return kaon_bars;
}

