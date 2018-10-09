/*
 * Created by Sebastien Bianchin on 2018-07-20 (s.bianchin@tiumf.ca)
 */

#ifndef MACROS_FINDKAONSTOP_H
#define MACROS_FINDKAONSTOP_H

#include "CommonStructs.hpp"
#include "DetectorData.hpp"
#include <vector>

vector<double> findKaonStop_0(const DetectorData &data, vector<int> kaon_bars, vector<int> lepton_bars, vector<double> vec_centroid,
							  double a1, double b1, double a2, double b2);


vector<double> getKstopFinal(const DetectorData &data, bool to_restore,
							 vector<int> vec_leptons, vector<int> vec_kaons, vector<double> vec_kaon_centroid,
					  		 double a_kaons, double b_kaons, double a_fit3, double b_fit3,
					  		 bool has_kaon_sub, int kaon_substitute);


#endif //MACROS_FINDKAONSTOP_H
