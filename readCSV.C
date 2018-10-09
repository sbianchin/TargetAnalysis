#ifndef __CINT__
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip> 
#include <stdlib.h>
#endif

using namespace std;


int main(){

	const long double PI = 3.141592653589793238;

	// OPEN TREK FILE
    int readEvent, readIndex;
    double readPmu, readPspec, readKplus[3], readLvec[3], readSFT[3];

    int RunNum, EvNum, EvFlag, gap_to_fit, selected_TOF2, extra_TOF1, ndf_final, Lepton_counter;
    int i_kaon_bar, kaon_bars_size, Ck_size, Cpi_size, sum_ADC_HG_lepton, HasEdgeBars, IsGoodTOF1;

    double angle_final, delta_phi_deg, delta_X, delta_Y, ChiS_final, ReducedChiS;
    double vec_int_TARGET[2], N_centroid[2], vec_intersect[2], vec_kstop[2], R_Kstop;
    double ReducedChiS_kaon, length_in_target, C2X_centroid, TDC_diff, Average_TDC_lepton, Average_TDC_kaon;
    double vec_int_SFT[2];

    double distance_SFT;
    int print_status_interval = 1000;
    int counter = 0;

	ifstream fdat_kekcc("Run_3994_KEKCC_78.csv", ios::in);
	
	//ifstream fdat_trek("Run_3994_LINE_TREK.csv", ios::in);
	//ifstream fdat_trek("Run_3994_TR_TREK.csv", ios::in);
	ifstream fdat_trek("Run_3994_BK_TREK.csv", ios::in);

    ofstream fout_csv;
    ofstream fout_csv_outliers;
    //fout_csv.open("TREK_vs_KEKCC_line.csv");			fout_csv_outliers.open("TREK_vs_KEKCC_line_outliers.csv");
    //fout_csv.open("TREK_vs_KEKCC_triangle.csv");		fout_csv_outliers.open("TREK_vs_KEKCC_triangle_outliers.csv");
    fout_csv.open("TREK_vs_KEKCC_backtracking.csv");	fout_csv_outliers.open("TREK_vs_KEKCC_backtracking_outliers.csv");

    ofstream fout_angle;
    //fout_angle.open("TREK_vs_KEKCC_line_ANGLE.csv");
    //fout_angle.open("TREK_vs_KEKCC_triangle_ANGLE.csv");
    fout_angle.open("TREK_vs_KEKCC_backtracking_ANGLE.csv");

	string s_readEvent;
	string s_readIndex;
	string s_readPmu;
	string s_readPspec;
	string s_readKplus_x;
	string s_readKplus_y;
	string s_readKplus_z;
	string s_readLvec_x;
	string s_readLvec_y;
	string s_readLvec_z;
	string s_readSFT_x;
	string s_readSFT_y;
	string s_readSFT_z;

    string s_RunNum;
    string s_EvNum;
    string s_EvFlag;
    string s_gap_to_fit;
    string s_selected_TOF2;
    string s_extra_TOF1;
    string s_ndf_final;
    string s_Lepton_counter;

    string s_i_kaon_bar;
    string s_kaon_bars_size;
    string s_Ck_size;
    string s_Cpi_size;
    string s_sum_ADC_HG_lepton;
    string s_HasEdgeBars;
    string s_IsGoodTOF1;

    string s_angle_final;
    string s_delta_phi_deg;
    string s_delta_X;
    string s_delta_Y;
    string s_ChiS_final;
    string s_ReducedChiS;
    string s_vec_int_TARGET_x, s_vec_int_TARGET_y, s_N_centroid_x, s_N_centroid_y;
    string s_vec_intersect_x, s_vec_intersect_y, s_vec_kstop_x, s_vec_kstop_y, s_R_Kstop;
    string s_ReducedChiS_kaon, s_length_in_target, s_C2X_centroid, s_TDC_diff, s_Average_TDC_lepton, s_Average_TDC_kaon;
    string s_vec_int_SFT_x, s_vec_int_SFT_y;
    //string s_vec_int_SFT_x, vec_int_SFT_y;

    double slope, angle_KEKCC;
    double diff_angle;

	while(fdat_kekcc.good()){

		counter++;

		getline(fdat_kekcc,s_readEvent,',');
		getline(fdat_kekcc,s_readIndex,',');
		getline(fdat_kekcc,s_readPmu,',');
		getline(fdat_kekcc,s_readPspec,',');
		getline(fdat_kekcc,s_readKplus_x,',');
		getline(fdat_kekcc,s_readKplus_y,',');
		getline(fdat_kekcc,s_readKplus_z,',');
		getline(fdat_kekcc,s_readLvec_x,',');
		getline(fdat_kekcc,s_readLvec_y,',');
		getline(fdat_kekcc,s_readLvec_z,',');
		getline(fdat_kekcc,s_readSFT_x,',');
		getline(fdat_kekcc,s_readSFT_y,',');
		getline(fdat_kekcc,s_readSFT_z,'\n');


    	readEvent = stoi(s_readEvent);
    	readLvec[0] = stod(s_readLvec_x);
    	readLvec[1] = stod(s_readLvec_y);
    	readSFT[0] = stod(s_readSFT_x);
    	readSFT[1] = stod(s_readSFT_y);
    	readSFT[2] = stod(s_readSFT_z);

    	

    	slope = readLvec[1]/readLvec[0];
    	//slope = readLvec[0]/readLvec[1];
    	angle_KEKCC = atan(slope) * (180/PI);

    	// if(readLvec[0] > 0 && readLvec[1] > 0) angle_KEKCC = angle_KEKCC + 0.;
    	// else if(readLvec[0] < 0 && readLvec[1] > 0) angle_KEKCC = angle_KEKCC + 90.;
    	// else if(readLvec[0] < 0 && readLvec[1] < 0) angle_KEKCC = angle_KEKCC + 180.;
    	// else if(readLvec[0] > 0 && readLvec[1] < 0) angle_KEKCC = angle_KEKCC + 270.;
    	// else cout << "///////////////////////////////////////////////////////////////////" << endl;

    	if(readLvec[0] > 0 && readLvec[1] > 0) angle_KEKCC = angle_KEKCC + 0.;
    	else if(readLvec[0] < 0 && readLvec[1] > 0) angle_KEKCC = 180 - fabs(angle_KEKCC);
    	else if(readLvec[0] < 0 && readLvec[1] < 0) angle_KEKCC = angle_KEKCC + 180.;
    	else if(readLvec[0] > 0 && readLvec[1] < 0) angle_KEKCC = 360 - fabs(angle_KEKCC);
    	else cout << "///////////////////////////////////////////////////////////////////" << endl;


		while(fdat_trek.good()){
			

			getline(fdat_trek,s_RunNum,',');
			getline(fdat_trek,s_EvNum,',');
			getline(fdat_trek,s_EvFlag,',');
			getline(fdat_trek,s_gap_to_fit,',');
			getline(fdat_trek,s_selected_TOF2,',');
			getline(fdat_trek,s_extra_TOF1,',');
	
			getline(fdat_trek,s_angle_final,',');
			getline(fdat_trek,s_delta_phi_deg,',');
			getline(fdat_trek,s_delta_X,',');
			getline(fdat_trek,s_delta_Y,',');
			getline(fdat_trek,s_ChiS_final,',');
			getline(fdat_trek,s_ndf_final,',');

			getline(fdat_trek,s_ReducedChiS,',');
			getline(fdat_trek,s_Lepton_counter,',');
			getline(fdat_trek,s_vec_int_TARGET_x,',');
			getline(fdat_trek,s_vec_int_TARGET_y,',');

    		getline(fdat_trek,s_vec_int_SFT_x,',');
    		getline(fdat_trek,s_vec_int_SFT_y,',');

			getline(fdat_trek,s_N_centroid_x,',');
			getline(fdat_trek,s_N_centroid_y,',');
			getline(fdat_trek,s_vec_intersect_x,',');
			getline(fdat_trek,s_vec_intersect_y,',');

			getline(fdat_trek,s_vec_kstop_x,',');
			getline(fdat_trek,s_vec_kstop_y,',');
			getline(fdat_trek,s_R_Kstop,',');
			getline(fdat_trek,s_i_kaon_bar,',');
			getline(fdat_trek,s_kaon_bars_size,',');

			getline(fdat_trek,s_ReducedChiS_kaon,',');
			getline(fdat_trek,s_Ck_size,',');
			getline(fdat_trek,s_Cpi_size,',');
			getline(fdat_trek,s_length_in_target,',');
			getline(fdat_trek,s_C2X_centroid,',');

			getline(fdat_trek,s_TDC_diff,',');
			getline(fdat_trek,s_sum_ADC_HG_lepton,',');
			getline(fdat_trek,s_Average_TDC_lepton,',');
			getline(fdat_trek,s_Average_TDC_kaon,',');

			getline(fdat_trek,s_HasEdgeBars,',');
			getline(fdat_trek,s_IsGoodTOF1,'\n');
		
			if(s_RunNum == ""){
				//cout << "ALBANE EST BELLE !" << endl;
				break;
			}

			RunNum = stoi(s_RunNum);
			EvNum = stoi(s_EvNum);
			vec_int_SFT[0] = stod(s_vec_int_SFT_x);
			vec_int_SFT[1] = stod(s_vec_int_SFT_y);
			angle_final = stod(s_angle_final);
			//cout << "####  " << EvNum << endl;

			// if(angle_KEKCC > 300 && angle_final > 300){
			//  	diff_angle = fabs(angle_final - angle_KEKCC);
			// }
			// else if(angle_KEKCC > 300 && angle_final <= 300){
			//  	diff_angle = fabs(angle_final - (360 - angle_KEKCC));

			//  	if(EvNum == 12){
			//  		cout << "EVENT 12 : " << endl;
			//  		cout << "KEK : " << angle_KEKCC << endl;
			//  		cout << "TRIUMF : " << angle_final << endl;
			//  		cout << "DIFF : " << diff_angle << endl;
			//  	}

			// }



			//else if(angle_KEKCC <= 300 && angle_final > 300){   ////
			// 	diff_angle = fabs(angle_final - (360 - angle_KEKCC));
			//}
			// else{
			// 	diff_angle = fabs(angle_final - angle_KEKCC);
			// }

			diff_angle = fabs(angle_final - angle_KEKCC);

			if(diff_angle > 300.){
				// if(angle_KEKCC > 300 && angle_final <= 300){
				// 	diff_angle = fabs(angle_final - (360 - angle_KEKCC));	
				// }
				// else if(angle_KEKCC <= 300 && angle_final > 300){
				// 	diff_angle = fabs(angle_final - (360 - angle_KEKCC));
				// }
					diff_angle = fabs(angle_final - (360 - angle_KEKCC));
			}

			//if(diff_angle > 300) cout << "ANGLE : " << EvNum << "  " << diff_angle << endl;

			if(readEvent == EvNum){

				distance_SFT = sqrt( pow((readSFT[0]*10-vec_int_SFT[0]),2) + pow((readSFT[1]*10-vec_int_SFT[1]),2));

				// cout << fixed;
				// cout << setw(4) << RunNum << "  ";
				// cout << setw(7) << EvNum << "  ";
				// cout << setw(10) << setprecision(3) << readSFT[0]*10 << "  ";
				// cout << setw(10) << setprecision(3) << readSFT[1]*10 << "  ";
				// cout << setw(7) << setprecision(3) << vec_int_SFT[0] << "  ";
				// cout << setw(7) << setprecision(3) << vec_int_SFT[1] << "  ";
				// cout << setw(10) << setprecision(3) << distance_SFT << "  ";
				// cout << setw(6) << setprecision(2) << angle_final << "  ";
				// cout << setw(6) << setprecision(2) << angle_KEKCC << "  ";
				// cout << setw(6) << setprecision(2) << diff_angle << "  ";
 				// 	cout << endl;
				
				if(angle_KEKCC == 225.){
					fout_csv_outliers << RunNum << ",";
					fout_csv_outliers << EvNum << ",";
					fout_csv_outliers << readSFT[0]*10 << ",";
					fout_csv_outliers << readSFT[1]*10 << ",";
					fout_csv_outliers << vec_int_SFT[0] << ",";
					fout_csv_outliers << vec_int_SFT[1] << ",";
					fout_csv_outliers << distance_SFT << ",";
					fout_csv_outliers << angle_final << ",";
					fout_csv_outliers << angle_KEKCC << ",";
					fout_csv_outliers << diff_angle;
					fout_csv_outliers << endl;
				}
				else{
					//if(angle_KEKCC > 300 && angle_final <= 300){
					if(diff_angle > 250){
   		 				fout_angle << RunNum << ",";
						fout_angle << EvNum << ",";
						fout_angle << readSFT[0]*10 << ",";
						fout_angle << readSFT[1]*10 << ",";
						fout_angle << vec_int_SFT[0] << ",";
						fout_angle << vec_int_SFT[1] << ",";
						fout_angle << distance_SFT << ",";
						fout_angle << angle_final << ",";
						fout_angle << angle_KEKCC << ",";
						fout_angle << fabs(angle_final - angle_KEKCC) << ",";
						fout_angle << diff_angle;
						fout_angle << endl;
					}
					//else{
   						fout_csv << RunNum << ",";
						fout_csv << EvNum << ",";
						fout_csv << readSFT[0]*10 << ",";
						fout_csv << readSFT[1]*10 << ",";
						fout_csv << vec_int_SFT[0] << ",";
						fout_csv << vec_int_SFT[1] << ",";
						fout_csv << distance_SFT << ",";
						fout_csv << angle_final << ",";
						fout_csv << angle_KEKCC << ",";
						fout_csv << diff_angle;
						fout_csv << endl;
					//}
				}
				break;
			}
			//else if(readEvent > EvNum) break;
		}

		if(counter % print_status_interval == 0) {
            cout << counter << " events processed" << endl;
        }
	}

	fout_csv.close();

}