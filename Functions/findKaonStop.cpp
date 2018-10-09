/*
 * Created by Sebastien Bianchin on 2018-07-20 (s.bianchin@triumf.ca)
 */

#include <iostream>

#include "findKaonStop.hpp"
#include "helperFunctions.hpp"
#include "CutsAndWindows.hpp"
#include "CommonParameters.hpp"
#include "DetectorGeometry.hpp"

namespace CW = CutsAndWindows;
namespace CP = CommonParameters;
namespace DG = DetectorGeometry;

vector<double> findKaonStop_0(const DetectorData &data, vector<int> kaon_bars, vector<int> lepton_bars, vector<double> vec_centroid,
							  double a1, double b1, double a2, double b2){

    vector<double> vec_kstop_0;		
	vector<double> vec_intersect_pr;	

	double distance_to_kaon;
	double distance_min = 999.;
	int K_closest = 999;

	int N_kaon_adc_LG_max = -999;
	int N_kaon_LG_max = -1; 

	if(kaon_bars.size()>0){
		if(lepton_bars.size()==0){
			vec_kstop_0.push_back(vec_centroid[0]);
			vec_kstop_0.push_back(vec_centroid[1]);
		}
		else if(kaon_bars.size() < CP::kaon_cluster_size){
			for(unsigned int i=0; i<kaon_bars.size(); i++){
				if(data.ADC_Low_TARGET[kaon_bars[i]] + CW::TARGET_ADC_Thr_LG_Offset>N_kaon_adc_LG_max){
					N_kaon_adc_LG_max = data.ADC_Low_TARGET[kaon_bars[i]]+CW::TARGET_ADC_Thr_LG_Offset;
					N_kaon_LG_max = kaon_bars[i];

				}
			}
				
			vec_kstop_0.push_back(DG::Xloc[N_kaon_LG_max]);
			vec_kstop_0.push_back(DG::Yloc[N_kaon_LG_max]);
		}
		else{
			vec_intersect_pr = TwoLinesIntersect(a1,b1,a2,b2);

			for(unsigned int i=0; i<kaon_bars.size(); i++){
				distance_to_kaon = sqrt(pow(DG::Xloc[kaon_bars[i]] - vec_intersect_pr[0],2) + pow(DG::Yloc[kaon_bars[i]] - vec_intersect_pr[1],2));
				if(distance_to_kaon < distance_min){
					distance_min = distance_to_kaon;
					K_closest = kaon_bars[i];
				}	
			}

			if(distance_min < CP::DISTANCE_MAX_TO_KAON_PRUNED){
				vec_kstop_0.push_back(vec_intersect_pr[0]);
				vec_kstop_0.push_back(vec_intersect_pr[1]);
			}
			else{
				vec_kstop_0.push_back(vec_centroid[0]);
				vec_kstop_0.push_back(vec_centroid[1]);
			}
		}
	}
	else{
		vec_kstop_0.push_back(999.);
		vec_kstop_0.push_back(999.);
	}

	return vec_kstop_0;
}

vector<double> getKstopFinal(const DetectorData &data, bool to_restore,
 							 vector<int> vec_leptons, vector<int> vec_kaons, vector<double> vec_kaon_centroid,
 					  		 double a_kaons, double b_kaons, double a_fit3, double b_fit3,
 					  		 bool has_kaon_sub, int kaon_substitute){

//vector<double> getKstopFinal(){

	vector<double> vec_kstop;		vec_kstop.clear();
 	vector<double> vec_intersect;	vec_intersect.clear();

	double A=0.0, B=0.0;

	int kaon_LG_max = -1;
	int kaon_ADC_LG_max = -1;

	double dist_intersect_to_kaon = 999.;
  	double smallest_kaon_distance = 999.;


	if(to_restore){
		A = -1/a_fit3;
		B = b_fit3/a_fit3;
	}

	if(vec_leptons.size()==0){
		vec_intersect.push_back(999.99);
		vec_intersect.push_back(999.99);

		if(vec_kaons.size()==0){
			vec_kstop.push_back(999.99);
			vec_kstop.push_back(999.99);
		}
		else if(vec_kaons.size() >= CP::kaon_cluster_size){
        	vec_kstop.push_back(vec_kaon_centroid[0]);
        	vec_kstop.push_back(vec_kaon_centroid[1]);
		}
		else{
			if(has_kaon_sub){
				kaon_LG_max = kaon_substitute;
			}
			else{
        		for(unsigned int i=0; i<vec_kaons.size(); i++){
          			if(data.ADC_Low_TARGET[vec_kaons[i]] + CW::TARGET_ADC_Thr_LG_Offset > kaon_ADC_LG_max){
            			kaon_ADC_LG_max = data.ADC_Low_TARGET[vec_kaons[i]] + CW::TARGET_ADC_Thr_LG_Offset;
            			kaon_LG_max = vec_kaons[i];
          			}
   				}
   			}

   			vec_kstop.push_back(DG::Xloc[kaon_LG_max]);
   			vec_kstop.push_back(DG::Yloc[kaon_LG_max]);
   		}
   	}
   	else{
   		if(vec_kaons.size()==0){
			vec_kstop.push_back(999.99); 
			vec_kstop.push_back(999.99);
		}
		else if(vec_kaons.size() >= CP::kaon_cluster_size){
			if(to_restore){
				if(a_fit3 == 0 && a_kaons!=0){
					if(b_fit3==0){
						vec_intersect.push_back(0.);
						vec_intersect.push_back(a_kaons * 0. + b_kaons);
					}
					else{
						vec_intersect.push_back(-b_fit3);
						vec_intersect.push_back(a_kaons * (-b_fit3) + b_kaons);					
					}
				}
				else if(a_fit3 != 0 && a_kaons==0){
					if(b_kaons==0){
						vec_intersect.push_back(0.);
						vec_intersect.push_back(a_fit3 * 0. + b_fit3);
					}
					else{
						vec_intersect.push_back(-b_kaons);
						vec_intersect.push_back(a_fit3 * (-b_kaons) + b_fit3);					
					}
				}
				else if(a_fit3 == 0 && a_kaons==0){
					cout << "ERROR -- lepton fit line AND kaon fit line are PARALLEL !" << endl;
				}
				else{
					vec_intersect = TwoLinesIntersect(a_kaons, b_kaons, A, B);			
				}
			}
			else vec_intersect = TwoLinesIntersect(a_kaons, b_kaons, a_fit3, b_fit3);

			for(unsigned int j=0; j<vec_kaons.size(); j++){
          		dist_intersect_to_kaon = sqrt(pow((DG::Xloc[vec_kaons[j]]-vec_intersect[0]),2) + pow((DG::Yloc[vec_kaons[j]]-vec_intersect[1]),2));
          		if(dist_intersect_to_kaon < smallest_kaon_distance){
            		smallest_kaon_distance = dist_intersect_to_kaon;
            		//closest_kaon = vec_kaon_bars[j];
          		}
        	}

        	if(smallest_kaon_distance < CP::DISTANCE_MAX_TO_KAON_FINAL){
          		vec_kstop.push_back(vec_intersect[0]);
          		vec_kstop.push_back(vec_intersect[1]);
        	}
       	 	else{
          		vec_kstop.push_back(vec_kaon_centroid[0]);
          		vec_kstop.push_back(vec_kaon_centroid[1]);
        	}
		}
		else{
			if(has_kaon_sub){
				kaon_LG_max = kaon_substitute;
			}
			else{
				for(unsigned int i=0; i<vec_kaons.size(); i++){
          			if(data.ADC_Low_TARGET[vec_kaons[i]] + CW::TARGET_ADC_Thr_LG_Offset > kaon_ADC_LG_max){
            			kaon_ADC_LG_max = data.ADC_Low_TARGET[vec_kaons[i]] + CW::TARGET_ADC_Thr_LG_Offset;
            			kaon_LG_max = vec_kaons[i];
          			}
				}
			}
   			
   			vec_kstop.push_back(DG::Xloc[kaon_LG_max]);
   			vec_kstop.push_back(DG::Yloc[kaon_LG_max]);
	
   		}
   	}

   	return vec_kstop;
}
