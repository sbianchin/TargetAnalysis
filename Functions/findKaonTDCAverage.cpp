/*
 * Created by Sebastien Bianchin on 2018-07-17. (s.bianchin@triumf.ca)
 */
#include <iostream>

#include "findKaonTDCAverage.hpp"
#include "CutsAndWindows.hpp"

namespace CW = CutsAndWindows;

vector<int> findKaonTDCAverage(const DetectorData &data, bool printout=false){

	vector<int> vec_candidates;
	vector<int> vec_output;

	int T_limit = 3;

	int max1 = -100;	int kaon_max1 = -1;
	int max2 = -100;	int kaon_max2 = -1;
	int kaon_sub = -1;

	int TDC_output = -1;
	int TDC_max1 = -1;
	int TDC_max2 = -1;

	for(int i=0; i<256; i++){
		if(data.ADC_High_TARGET[i] > CW::HG_KAON){
			for(int j=0; j<6; j++){
				if(data.TDC_LE_TARGET[i][j] >= CW::TDC_Thr_min && data.TDC_LE_TARGET[i][j] <= CW::TDC_Thr_max){
					vec_candidates.push_back(i);
				}
			}
		}
	}


	if(vec_candidates.size()==0){
		for(int i=0; i<256; i++){
			if(data.ADC_High_TARGET[i]>max1){
				for(int j=0; j<6; j++){
					if(data.TDC_LE_TARGET[i][j] >= CW::TDC_Thr_min && data.TDC_LE_TARGET[i][j] <= CW::TDC_Thr_max){
						max1 = data.ADC_High_TARGET[i];
						kaon_max1 = i;
						kaon_sub = i;
					}
				}
			}
		}

		for(int j=0; j<6; j++){
			if(data.TDC_LE_TARGET[kaon_max1][j] >= CW::TDC_Thr_min && data.TDC_LE_TARGET[kaon_max1][j] <= CW::TDC_Thr_max){
				TDC_output = data.TDC_LE_TARGET[kaon_max1][j];
				TDC_max1 = data.TDC_LE_TARGET[kaon_max1][j];
			}
		}

		if(printout){
      		std::cout << "NO KAON !" << endl;
      		std::cout << endl;
      		printf("                  Fiber  ADC(HG)  ADC(LG)   TDC\n");
      		printf("Kaon 1st Max. :   %4d    %4d     %4d    %4d\n",kaon_max1, data.ADC_High_TARGET[kaon_max1], data.ADC_Low_TARGET[kaon_max1], TDC_max1);
      		printf("Kaon 2nd Max. :    ---    ----     ----    ----\n");
      		printf("TDC Average   :  %4d\n",TDC_output);
      		std::cout << "KAON SUBSTITUTE : " << kaon_sub << endl;
      		std::cout << endl;
		}
	}
	else if(vec_candidates.size()==1){
		max1 = data.ADC_Low_TARGET[vec_candidates[0]];
		kaon_max1 = vec_candidates[0];

		for(int j=0; j<6; j++){
			if(data.TDC_LE_TARGET[kaon_max1][j] >= CW::TDC_Thr_min && data.TDC_LE_TARGET[kaon_max1][j] <= CW::TDC_Thr_max){
				TDC_output = data.TDC_LE_TARGET[kaon_max1][j];
				TDC_max1 = data.TDC_LE_TARGET[kaon_max1][j];
			}
		}

		if(max1<CW::LG_KAON ||
		  (TDC_max1<CW::TDC_Thr_min || TDC_max1>CW::TDC_Thr_max)) kaon_sub = vec_candidates[0];

		if(printout){
      		std::cout << "ONLY 1 KAON !" << endl;
      		std::cout << endl;
      		printf("                  Fiber  ADC(HG)  ADC(LG)   TDC\n");
      		printf("Kaon 1st Max. :   %4d    %4d     %4d    %4d\n",kaon_max1, data.ADC_High_TARGET[kaon_max1], data.ADC_Low_TARGET[kaon_max1], TDC_max1);
      		printf("Kaon 2nd Max. :    ---    ----     ----    ----\n");
      		printf("TDC Average   :  %4d\n",TDC_output);
      		std::cout << "KAON SUBSTITUTE : " << kaon_sub << endl;
      		std::cout << endl;
		}

	}
	else if(vec_candidates.size()>1){

		for(unsigned int i=0; i<vec_candidates.size(); i++){
			if(data.ADC_Low_TARGET[vec_candidates[i]]>max1){
				max1 = data.ADC_Low_TARGET[vec_candidates[i]];
				kaon_max1 = vec_candidates[i];
			}
		}

		vec_candidates.erase(remove(vec_candidates.begin(), vec_candidates.end(), kaon_max1), vec_candidates.end());

		for(unsigned int i=0; i<vec_candidates.size(); i++){
			if(data.ADC_Low_TARGET[vec_candidates[i]]>max2){
				max2 = data.ADC_Low_TARGET[vec_candidates[i]];
				kaon_max2 = vec_candidates[i];
			}
		}

		for(int j=0; j<6; j++){
			if(data.TDC_LE_TARGET[kaon_max1][j] >= CW::TDC_Thr_min && data.TDC_LE_TARGET[kaon_max1][j] <= CW::TDC_Thr_max){
				TDC_max1 = data.TDC_LE_TARGET[kaon_max1][j];
			}
			if(data.TDC_LE_TARGET[kaon_max2][j] >= CW::TDC_Thr_min && data.TDC_LE_TARGET[kaon_max2][j] <= CW::TDC_Thr_max){
				TDC_max2 = data.TDC_LE_TARGET[kaon_max2][j];
			}
		}

		if(abs(TDC_max1 - TDC_max2) <= T_limit) TDC_output = (TDC_max1 + TDC_max2)/2;
		else if(max1 > max2) TDC_output = TDC_max1;
		else if(max1 < max2) TDC_output = TDC_max2;

		if(max1 < CW::LG_KAON ||
		   (TDC_max1 < CW::TDC_Thr_min || TDC_max1 > CW::TDC_Thr_max)) kaon_sub = kaon_max1;

		if(printout){
      		std::cout << "MORE THAN ONE KAON !" << endl;
      		std::cout << endl;
      		printf("                  Fiber  ADC(HG)  ADC(LG)   TDC\n");
      		printf("Kaon 1st Max. :   %4d    %4d     %4d    %4d\n",kaon_max1, data.ADC_High_TARGET[kaon_max1], data.ADC_Low_TARGET[kaon_max1], TDC_max1);
      		printf("Kaon 2nd Max. :   %4d    %4d     %4d    %4d\n",kaon_max2, data.ADC_High_TARGET[kaon_max2], data.ADC_Low_TARGET[kaon_max2], TDC_max2);
      		printf("TDC Average   :  %4d\n",TDC_output);
      		std::cout << "KAON SUBSTITUTE : " << kaon_sub << endl;
      		std::cout << endl;	
		}

	}

	vec_output.push_back(TDC_output);
	vec_output.push_back(kaon_sub);

	return vec_output;
}
