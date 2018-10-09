/*
 * Created by Sebastien Bianchin on 2018-08-03 (s.bianchin@triumf.ca)
 */
#include <iostream>

#include "findMWPCClusters.hpp"
#include "CommonStructs.hpp"
#include "DetectorData.hpp"
#include "printFunctions.hpp"

#include "CommonParameters.hpp"
#include "DetectorGeometry.hpp"

namespace CP = CommonParameters;
namespace DG = DetectorGeometry;

double findMWPCClusters(const DetectorData &data, bool is_good_event,
					  int selected_TOF2, bool print_to_console){

	double C2X_L[56] = {0.};
    double C2X_R[56] = {0.};
    double C2Y_L[16] = {0.};
    double C2Y_R[16] = {0.};
    double C3X_L[64] = {0.};
    double C3X_R[64] = {0.};
    double C3Y_L[16] = {0.};
    double C3Y_R[16] = {0.};
    double C4X_L[72] = {0.};
    double C4X_R[72] = {0.};
    double C4Y_L[16] = {0.};
    double C4Y_R[16] = {0.};

    double C2X_centroid = 0.0;

    //C2 Counters
    for (int i = 0; i < 56; i++) {
        if (is_good_event && data.ADC_C2X_L[i] > 0) C2X_L[i] = data.ADC_C2X_L[i];
        if (is_good_event && data.ADC_C2X_R[i] > 0) C2X_R[i] = data.ADC_C2X_R[i];
    }

    for (int i = 0; i < 64; i++) {
        if (is_good_event && data.ADC_C3X_L[i] > 0) C3X_L[i] = data.ADC_C3X_L[i];
        if (is_good_event && data.ADC_C3X_R[i] > 0) C3X_R[i] = data.ADC_C3X_R[i];
    }

    for (int i = 0; i < 72; i++) {
        if (is_good_event && data.ADC_C4X_L[i] > 0) C4X_L[i] = data.ADC_C4X_L[i];
        if (is_good_event && data.ADC_C4X_R[i] > 0) C4X_R[i] = data.ADC_C4X_R[i];
    }

    for (int i = 0; i < 16; i++) {
        if (is_good_event && data.ADC_C2Y_L[i] > 0) C2Y_L[i] = data.ADC_C2Y_L[i];
        if (is_good_event && data.ADC_C2Y_R[i] > 0) C2Y_R[i] = data.ADC_C2Y_R[i];
        if (is_good_event && data.ADC_C3Y_L[i] > 0) C3Y_L[i] = data.ADC_C3Y_L[i];
        if (is_good_event && data.ADC_C3Y_R[i] > 0) C3Y_R[i] = data.ADC_C3Y_R[i];
        if (is_good_event && data.ADC_C4Y_L[i] > 0) C4Y_L[i] = data.ADC_C4Y_L[i];
        if (is_good_event && data.ADC_C4Y_R[i] > 0) C4Y_R[i] = data.ADC_C4Y_R[i];
    }

    // Find clustering of mwpcs
    ////////////////////////////
    bool first_cluster = true;
    int cluster_spacing = 0;
    int cluster_length_count = 0;

    int C2X_clusters = 0;
    int C2Y_clusters = 0;
    int C3X_clusters = 0;
    int C3Y_clusters = 0;
    int C4X_clusters = 0;
    int C4Y_clusters = 0;

    vector<int> C2X_cluster_index;
    vector<int> C2X_cluster_length;
    vector<int> C2Y_cluster_index;
    vector<int> C2Y_cluster_length;

    vector<int> C3X_cluster_index;
    vector<int> C3X_cluster_length;
    vector<int> C3Y_cluster_index;
    vector<int> C3Y_cluster_length;

    vector<int> C4X_cluster_index;
    vector<int> C4X_cluster_length;
    vector<int> C4Y_cluster_index;
    vector<int> C4Y_cluster_length;

    if(selected_TOF2 > 6){  // LEFT
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

    	for (int i = 0; i < 56; i++) {
        	if(C2X_L[i] > 0. && first_cluster){
            	cluster_spacing = CP::MWPC_cluster_separation + 1;
            	first_cluster = false;
    		}

        	if(C2X_L[i] > 0.){
            	if (cluster_spacing > CP::MWPC_cluster_separation){
                	C2X_clusters++;
                	C2X_cluster_index.push_back(i);
            	}
            	cluster_length_count++;
            	cluster_spacing = 0;

            	if (i + 2 < 56 && C2X_L[i + 1] <= 0. && C2X_L[i + 2] <= 0.)
                	C2X_cluster_length.push_back(cluster_length_count);
                	else if (i + 2 == 56 && C2X_L[i + 1] <= 0.) C2X_cluster_length.push_back(cluster_length_count);
                	else if (i + 1 == 56) C2X_cluster_length.push_back(cluster_length_count);
        	} 
        	else{
            	cluster_spacing++;
            	if(i != 0 && C2X_L[i - 1] <= 0.) cluster_length_count = 0;
            	else if (i != 0) cluster_length_count++;
        	}
    	}

        // count C2Y clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 16; i++) {
            if (C2Y_L[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C2Y_L[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C2Y_clusters++;
                    C2Y_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 16 && C2Y_L[i + 1] <= 0 && C2Y_L[i + 2] <= 0)
                    C2Y_cluster_length.push_back(cluster_length_count);
                else if (i + 2 == 16 && C2Y_L[i + 1] <= 0) C2Y_cluster_length.push_back(cluster_length_count);
                else if (i + 1 == 16) C2Y_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C2Y_L[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }

        // count C3X clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 64; i++) {
            if (C3X_L[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C3X_L[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C3X_clusters++;
                    C3X_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 64 && C3X_L[i + 1] <= 0 && C3X_L[i + 2] <= 0)
                    C3X_cluster_length.push_back(cluster_length_count);
                else if (i + 2 == 64 && C3X_L[i + 1] <= 0) C3X_cluster_length.push_back(cluster_length_count);
                else if (i + 1 == 64) C3X_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C3X_L[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }

        // count C3Y clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 16; i++) {
            if (C3Y_L[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C3Y_L[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C3Y_clusters++;
                    C3Y_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 16 && C3Y_L[i + 1] <= 0 && C3Y_L[i + 2] <= 0)
                    C3Y_cluster_length.push_back(cluster_length_count);
                else if (i + 2 == 16 && C3Y_L[i + 1] <= 0) C3Y_cluster_length.push_back(cluster_length_count);
                else if (i + 1 == 16) C3Y_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C3Y_L[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }

        // count C4X clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 72; i++) {
            if (C4X_L[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C4X_L[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C4X_clusters++;
                    C4X_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 72 && C4X_L[i + 1] <= 0 && C4X_L[i + 2] <= 0)
                    C4X_cluster_length.push_back(cluster_length_count);
                else if (i == 70 && C4X_L[71] <= 0) C4X_cluster_length.push_back(cluster_length_count);
                else if (i == 71) C4X_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C4X_L[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }

        // count C4Y clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 16; i++) {
            if (C4Y_L[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C4Y_L[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C4Y_clusters++;
                    C4Y_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 16 && C4Y_L[i + 1] <= 0 && C4Y_L[i + 2] <= 0)
                    C4Y_cluster_length.push_back(cluster_length_count);
                else if (i + 2 == 16 && C4Y_L[i + 1] <= 0) C4Y_cluster_length.push_back(cluster_length_count);
                else if (i + 1 == 16) C4Y_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C4Y_L[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }
    } 
    else {  // RIGHT
        // count C2X clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 56; i++) {
            if (C2X_R[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C2X_R[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C2X_clusters++;
                    C2X_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 56 && C2X_R[i + 1] <= 0 && C2X_R[i + 2] <= 0)
                    C2X_cluster_length.push_back(cluster_length_count);
                else if (i + 2 == 56 && C2X_R[i + 1] <= 0) C2X_cluster_length.push_back(cluster_length_count);
                else if (i + 1 == 56)C2X_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C2X_R[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }

        // count C2Y clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 16; i++) {
            if (C2Y_R[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C2Y_R[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C2Y_clusters++;
                    C2Y_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 16 && C2Y_R[i + 1] <= 0 && C2Y_R[i + 2] <= 0)
                    C2Y_cluster_length.push_back(cluster_length_count);
                else if (i + 2 == 16 && C2Y_R[i + 1] <= 0) C2Y_cluster_length.push_back(cluster_length_count);
                else if (i + 1 == 16) C2Y_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C2Y_R[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }

        // count C3X clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 64; i++) {
            if (C3X_R[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C3X_R[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C3X_clusters++;
                    C3X_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 64 && C3X_R[i + 1] <= 0 && C3X_R[i + 2] <= 0)
                    C3X_cluster_length.push_back(cluster_length_count);
                else if (i + 2 == 64 && C3X_R[i + 1] <= 0) C3X_cluster_length.push_back(cluster_length_count);
                else if (i + 1 == 64) C3X_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C3X_R[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }

        // count C3Y clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 16; i++) {
            if (C3Y_R[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C3Y_R[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C3Y_clusters++;
                    C3Y_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 16 && C3Y_R[i + 1] <= 0 && C3Y_R[i + 2] <= 0)
                    C3Y_cluster_length.push_back(cluster_length_count);
                else if (i + 2 == 16 && C3Y_R[i + 1] <= 0) C3Y_cluster_length.push_back(cluster_length_count);
                else if (i + 1 == 16) C3Y_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C3Y_R[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }

        // count C4X clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 72; i++) {
            if (C4X_R[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C4X_R[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C4X_clusters++;
                    C4X_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 72 && C4X_R[i + 1] <= 0 && C4X_R[i + 2] <= 0)
                    C4X_cluster_length.push_back(cluster_length_count);
                else if (i == 70 && C4X_R[71] <= 0) C4X_cluster_length.push_back(cluster_length_count);
                else if (i == 71) C4X_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C4X_R[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }

        // count C4Y clusters
        first_cluster = true;
        cluster_spacing = 0;
        cluster_length_count = 0;

        for (int i = 0; i < 16; i++) {
            if (C4Y_R[i] > 0 && first_cluster) {
                cluster_spacing = CP::MWPC_cluster_separation + 1;
                first_cluster = false;
            }

            if (C4Y_R[i] > 0) {
                if (cluster_spacing > CP::MWPC_cluster_separation) {
                    C4Y_clusters++;
                    C4Y_cluster_index.push_back(i);
                }
                cluster_length_count++;
                cluster_spacing = 0;

                if (i + 2 < 16 && C4Y_R[i + 1] <= 0 && C4Y_R[i + 2] <= 0)
                    C4Y_cluster_length.push_back(cluster_length_count);
                else if (i + 2 == 16 && C4Y_R[i + 1] <= 0) C4Y_cluster_length.push_back(cluster_length_count);
                else if (i + 1 == 16) C4Y_cluster_length.push_back(cluster_length_count);
            } else {
                cluster_spacing++;
                if (i != 0 && C4Y_R[i - 1] <= 0) cluster_length_count = 0;
                else if (i != 0) cluster_length_count++;
            }
        }
    }
   
    double C2_centroid_num = 0.;
    double C2_centroid_den = 0.;

    if (C2X_clusters == 1) {
        if (selected_TOF2 >= 7) {
            for (int i = 0; i < 56; i++) {
                if (C2X_L[i] > 0.) {
                    C2_centroid_num += C2X_L[i] * DG::C2_ZLoc[i];
                    C2_centroid_den += C2X_L[i];
                }
            }
        } else {
            for (int i = 0; i < 56; i++) {
                if (C2X_R[i] > 0) {
                    C2_centroid_num += C2X_R[i] * DG::C2_ZLoc[i];
                    C2_centroid_den += C2X_R[i];
                }
            }
        }


        C2X_centroid = double(C2_centroid_num) / C2_centroid_den;
    }

    if(print_to_console){  
    	printMWPCInfo(data, selected_TOF2, is_good_event, 
        	          C2X_clusters, C2Y_clusters,
            	      C3X_clusters, C3Y_clusters,
                	  C4X_clusters, C4Y_clusters);

    }

    return C2X_centroid; 
}
