#ifndef __CINT__
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <TROOT.h>
#include "TSystem.h"
#include "TFile.h"
#include "TProfile.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TF1.h"
#include "TGaxis.h"
#include "TRandom.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TPolyLine.h"
#include "TLine.h"
#include "TArrow.h"
#include "TStyle.h"  
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TBranch.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TEllipse.h"
#include "TMarker.h"
#include "ANAPATH.h"
#include "ADC_Thresholds.h"
#include "TDC_Windows.h"
#include "Cuts_and_Windows.h"
#endif

void SFT_Analysis(int run_number=3994, int ievt=0)
{ 
 
	char source_mapping[] = "SFT_Mapping_Oct14.txt";  // Mapping file !!!

	Int_t HG_TARGET_ADC_Thr[256] = {0};
  	Int_t LG_TARGET_ADC_Thr[256] = {0};
  	Int_t HG_SFT_ADC_Thr[128] = {0};
  	Int_t LG_SFT_ADC_Thr[128] = {0};

  	for(int i=0; i<256; i++)  HG_TARGET_ADC_Thr[i] = round(TARGET_ADC_Thr_HG[i]) + TARGET_ADC_Thr_HG_Offset;
  	for(int i=0; i<256; i++)  LG_TARGET_ADC_Thr[i] = round(TARGET_ADC_Thr_LG[i]) + TARGET_ADC_Thr_LG_Offset;
  	for(int i=0; i<128; i++)  HG_SFT_ADC_Thr[i] = round(SFT_ADC_Thr_HG[i]) + SFT_ADC_Thr_HG_Offset;
  	for(int i=0; i<128; i++)  LG_SFT_ADC_Thr[i] = round(SFT_ADC_Thr_LG[i]) + SFT_ADC_Thr_LG_Offset;


	Int_t adc_high_sft[128];          	Int_t ADC_High_SFT[128];        Double_t ADC_High_SFT_corr[128];    
	Int_t adc_low_sft[128];           	Int_t ADC_Low_SFT[128];   
	Int_t tdc_le_sft[128][16];        	Int_t TDC_LE_SFT[128][6];         
	Int_t tdc_te_sft[128][16];        	Int_t TDC_TE_SFT[128][6];  

	Int_t ADC_High_SFT_L1_UP[15];		Int_t ADC_High_SFT_L1_DOWN[15];
	Int_t ADC_High_SFT_L2_UP[15];		Int_t ADC_High_SFT_L2_DOWN[15];
	Int_t ADC_High_SFT_L3_UP[17];		Int_t ADC_High_SFT_L3_DOWN[17];
	Int_t ADC_High_SFT_L4_UP[17];		Int_t ADC_High_SFT_L4_DOWN[17];

	Int_t ADC_Low_SFT_L1_UP[15];		Int_t ADC_Low_SFT_L1_DOWN[15];
	Int_t ADC_Low_SFT_L2_UP[15];		Int_t ADC_Low_SFT_L2_DOWN[15];
	Int_t ADC_Low_SFT_L3_UP[17];		Int_t ADC_Low_SFT_L3_DOWN[17];
	Int_t ADC_Low_SFT_L4_UP[17];		Int_t ADC_Low_SFT_L4_DOWN[17];

	Int_t TDC_LE_SFT_L1_UP[15][6];		Int_t TDC_LE_SFT_L1_DOWN[15][6];
	Int_t TDC_LE_SFT_L2_UP[15][6];		Int_t TDC_LE_SFT_L2_DOWN[15][6];
	Int_t TDC_LE_SFT_L3_UP[17][6];		Int_t TDC_LE_SFT_L3_DOWN[17][6];
	Int_t TDC_LE_SFT_L4_UP[17][6];		Int_t TDC_LE_SFT_L4_DOWN[17][6];

	Int_t SFT_TDC_L1_UP_min[15];	Int_t SFT_TDC_L1_UP_max[15];	Int_t SFT_TDC_L1_DOWN_min[15];	Int_t SFT_TDC_L1_DOWN_max[15];	
	Int_t SFT_TDC_L2_UP_min[15];	Int_t SFT_TDC_L2_UP_max[15];	Int_t SFT_TDC_L2_DOWN_min[15];	Int_t SFT_TDC_L2_DOWN_max[15];	
	Int_t SFT_TDC_L3_UP_min[17];	Int_t SFT_TDC_L3_UP_max[17];	Int_t SFT_TDC_L3_DOWN_min[17];	Int_t SFT_TDC_L3_DOWN_max[17];	
	Int_t SFT_TDC_L4_UP_min[17];	Int_t SFT_TDC_L4_UP_max[17];	Int_t SFT_TDC_L4_DOWN_min[17];	Int_t SFT_TDC_L4_DOWN_max[17];	

	Int_t SFT_L1[15]={0};		Int_t SFT_L2[15]={0};		Int_t SFT_L3[17]={0};		Int_t SFT_L4[17]={0};
	Int_t SFT_L1_counter=0;		Int_t SFT_L2_counter=0;		Int_t SFT_L3_counter=0;		Int_t SFT_L4_counter=0;


	char file_mapping[200];
	sprintf(file_mapping,"../Mapping");

	char par_finput[200];
	sprintf(par_finput,"%s/%s",file_mapping,source_mapping);

	Int_t par_temp[2][128];
  	ifstream fdat(par_finput,ios::in);
  	for(Int_t ii=0; ii<128; ii++) fdat >> par_temp[0][ii] >> par_temp[1][ii];
  	fdat.close();


  	char path_input[200];                   
  	sprintf(path_input,"%s",path_merged);       

  	char Name_finput[200];
  	sprintf(Name_finput,"%s/Run%dMS.root",path_input, run_number);

   
  	cout << "   " << endl;
  	cout << "   " << endl;
  	cout << "************************************************************************************************************" << endl;

  	//cout << "   " << endl;
  	cout << "File opened:  " << Name_finput << endl;
  	cout << "SFT Mapping File:  " << par_finput << endl;
  	cout << " " << endl;

	TChain *fChain= new TChain("Tree");   
  	fChain->Add(Name_finput);   
  	fChain->SetMakeClass(1);  

	fChain->SetBranchAddress("ADC_High_SFT",adc_high_sft);
  	fChain->SetBranchAddress("ADC_Low_SFT",adc_low_sft);
  	fChain->SetBranchAddress("TDC_LE_SFT",tdc_le_sft);
  	fChain->SetBranchAddress("TDC_TE_SFT",tdc_te_sft);
            
  	Int_t nentries = (Int_t)fChain->GetEntries();
  	cout << "Total Number of Events:  " << nentries <<endl;
  	cout << "************************************************************************************************************" << endl;
  	cout << "  " << endl;
  	cout << "  " << endl;

  	for(int ivt=ievt; ivt<ievt+1; ivt++){
    	fChain->GetEntry(ivt);  

        for(Int_t j_SFT=0; j_SFT<128; j_SFT++){
     		ADC_High_SFT[j_SFT]=adc_high_sft[j_SFT]-HG_SFT_ADC_Thr[j_SFT];		
       		ADC_Low_SFT[j_SFT]=adc_low_sft[j_SFT]-LG_SFT_ADC_Thr[j_SFT];

       		for(int j=0; j<6; j++){
       			TDC_LE_SFT[j_SFT][j]=tdc_le_sft[j_SFT][j];
       		}
       	}
	

		for(int il1=0; il1<15; il1++){
			ADC_High_SFT_L1_DOWN[il1] = ADC_High_SFT[par_temp[1][il1]];
			ADC_Low_SFT_L1_DOWN[il1] = ADC_Low_SFT[par_temp[1][il1]];
			for(int jl1=0; jl1<6; jl1++) TDC_LE_SFT_L1_DOWN[il1][jl1] = TDC_LE_SFT[par_temp[1][il1]][jl1];
			SFT_TDC_L1_DOWN_min[il1] = SFT_TDC_min[par_temp[1][il1]];
			SFT_TDC_L1_DOWN_max[il1] = SFT_TDC_max[par_temp[1][il1]];

			ADC_High_SFT_L1_UP[il1] = ADC_High_SFT[par_temp[1][il1+64]];
			ADC_Low_SFT_L1_UP[il1] = ADC_Low_SFT[par_temp[1][il1+64]];
			for(int jl1=0; jl1<6; jl1++) TDC_LE_SFT_L1_UP[il1][jl1] = TDC_LE_SFT[par_temp[1][il1+64]][jl1];
			SFT_TDC_L1_UP_min[il1] = SFT_TDC_min[par_temp[1][il1+64]];
			SFT_TDC_L1_UP_max[il1] = SFT_TDC_max[par_temp[1][il1+64]];
		}

		for(int il2=0; il2<15; il2++){
			ADC_High_SFT_L2_DOWN[il2] = ADC_High_SFT[par_temp[1][il2+15]];
			ADC_Low_SFT_L2_DOWN[il2] = ADC_Low_SFT[par_temp[1][il2+15]];
			for(int jl2=0; jl2<6; jl2++) TDC_LE_SFT_L2_DOWN[il2][jl2] = TDC_LE_SFT[par_temp[1][il2+15]][jl2];
			SFT_TDC_L2_DOWN_min[il2] = SFT_TDC_min[par_temp[1][il2+15]];
			SFT_TDC_L2_DOWN_max[il2] = SFT_TDC_max[par_temp[1][il2+15]];

			ADC_High_SFT_L2_UP[il2] = ADC_High_SFT[par_temp[1][il2+79]];
			ADC_Low_SFT_L2_UP[il2] = ADC_Low_SFT[par_temp[1][il2+79]];
			for(int jl2=0; jl2<6; jl2++) TDC_LE_SFT_L2_UP[il2][jl2] = TDC_LE_SFT[par_temp[1][il2+79]][jl2];
			SFT_TDC_L2_UP_min[il2] = SFT_TDC_min[par_temp[1][il2+79]];
			SFT_TDC_L2_UP_max[il2] = SFT_TDC_max[par_temp[1][il2+79]];
		}

		for(int il3=0; il3<17; il3++){
			ADC_High_SFT_L3_DOWN[il3] = ADC_High_SFT[par_temp[1][il3+30]];
			ADC_Low_SFT_L3_DOWN[il3] = ADC_Low_SFT[par_temp[1][il3+30]];
			for(int jl3=0; jl3<6; jl3++) TDC_LE_SFT_L3_DOWN[il3][jl3] = TDC_LE_SFT[par_temp[1][il3+30]][jl3];
			SFT_TDC_L3_DOWN_min[il3] = SFT_TDC_min[par_temp[1][il3+30]];
			SFT_TDC_L3_DOWN_max[il3] = SFT_TDC_max[par_temp[1][il3+30]];

			ADC_High_SFT_L3_UP[il3] = ADC_High_SFT[par_temp[1][il3+94]];
			ADC_Low_SFT_L3_UP[il3] = ADC_Low_SFT[par_temp[1][il3+94]];
			for(int jl3=0; jl3<6; jl3++) TDC_LE_SFT_L3_UP[il3][jl3] = TDC_LE_SFT[par_temp[1][il3+94]][jl3];
			SFT_TDC_L3_UP_min[il3] = SFT_TDC_min[par_temp[1][il3+94]];
			SFT_TDC_L3_UP_max[il3] = SFT_TDC_max[par_temp[1][il3+94]];
		}

		for(int il4=0; il4<17; il4++){
			ADC_High_SFT_L4_DOWN[il4] = ADC_High_SFT[par_temp[1][il4+47]];
			ADC_Low_SFT_L4_DOWN[il4] = ADC_Low_SFT[par_temp[1][il4+47]];
			for(int jl4=0; jl4<6; jl4++) TDC_LE_SFT_L4_DOWN[il4][jl4] = TDC_LE_SFT[par_temp[1][il4+47]][jl4];
			SFT_TDC_L4_DOWN_min[il4] = SFT_TDC_min[par_temp[1][il4+47]];
			SFT_TDC_L4_DOWN_max[il4] = SFT_TDC_max[par_temp[1][il4+47]];

			ADC_High_SFT_L4_UP[il4] = ADC_High_SFT[par_temp[1][il4+111]];
			ADC_Low_SFT_L4_UP[il4] = ADC_Low_SFT[par_temp[1][il4+111]];
			for(int jl4=0; jl4<6; jl4++) TDC_LE_SFT_L4_UP[il4][jl4] = TDC_LE_SFT[par_temp[1][il4+111]][jl4];
			SFT_TDC_L4_UP_min[il4] = SFT_TDC_min[par_temp[1][il4+111]];
			SFT_TDC_L4_UP_max[il4] = SFT_TDC_max[par_temp[1][il4+111]];
		}

		for(int i=0; i<15; i++){
			for(int j=0; j<6; j++){
				if((ADC_High_SFT_L1_DOWN[i]>=0 && (TDC_LE_SFT_L1_DOWN[i][j]>SFT_TDC_L1_DOWN_min[i] && TDC_LE_SFT_L1_DOWN[i][j]<SFT_TDC_L1_DOWN_max[i])) || 
		    	   (ADC_High_SFT_L1_UP[i]>=0 && (TDC_LE_SFT_L1_UP[i][j]>SFT_TDC_L1_UP_min[i] && TDC_LE_SFT_L1_UP[i][j]<SFT_TDC_L1_UP_max[i]))){
					cout << "  " << i+1 << "   " << j << "   " << ADC_High_SFT_L1_DOWN[i] << "   " << ADC_High_SFT_L1_UP[i] << "   " << TDC_LE_SFT_L1_DOWN[i][j] << "   " << TDC_LE_SFT_L1_UP[i][j] << endl;
					SFT_L1[i] = 1;
				}
			}
		}

		cout << " " << endl;
		cout << " ***************************************************************** " << endl;
		cout << " " << endl;

		for(int i=0; i<15; i++){
			for(int j=0; j<6; j++){
				if((ADC_High_SFT_L2_DOWN[i]>=0 && (TDC_LE_SFT_L2_DOWN[i][j]>SFT_TDC_L2_DOWN_min[i] && TDC_LE_SFT_L2_DOWN[i][j]<SFT_TDC_L2_DOWN_max[i])) || 
		    	   (ADC_High_SFT_L2_UP[i]>=0 && (TDC_LE_SFT_L2_UP[i][j]>SFT_TDC_L2_UP_min[i] && TDC_LE_SFT_L2_UP[i][j]<SFT_TDC_L2_UP_max[i]))){
					cout << "  " << i+1 << "   " << j << "   " << ADC_High_SFT_L2_DOWN[i] << "   " << ADC_High_SFT_L2_UP[i] << "   " << TDC_LE_SFT_L2_DOWN[i][j] << "   " << TDC_LE_SFT_L2_UP[i][j] << endl;
					SFT_L2[i] = 1;
				}
			}
		}

		cout << " " << endl;
		cout << " ***************************************************************** " << endl;
		cout << " " << endl;

		for(int i=0; i<17; i++){
			for(int j=0; j<6; j++){
				if((ADC_High_SFT_L3_DOWN[i]>=0 && (TDC_LE_SFT_L3_DOWN[i][j]>SFT_TDC_L3_DOWN_min[i] && TDC_LE_SFT_L3_DOWN[i][j]<SFT_TDC_L3_DOWN_max[i])) || 
		    	   (ADC_High_SFT_L3_UP[i]>=0 && (TDC_LE_SFT_L3_UP[i][j]>SFT_TDC_L3_UP_min[i] && TDC_LE_SFT_L3_UP[i][j]<SFT_TDC_L3_UP_max[i]))){
					cout << "  " << i+1 << "   " << j << "   " << ADC_High_SFT_L3_DOWN[i] << "   " << ADC_High_SFT_L3_UP[i] << "   " << TDC_LE_SFT_L3_DOWN[i][j] << "   " << TDC_LE_SFT_L3_UP[i][j] << endl;
					SFT_L3[i] = 1;
				}
			}
		}

		cout << " " << endl;
		cout << " ***************************************************************** " << endl;
		cout << " " << endl;

		for(int i=0; i<17; i++){
			for(int j=0; j<6; j++){
				if((ADC_High_SFT_L4_DOWN[i]>=0 && (TDC_LE_SFT_L4_DOWN[i][j]>SFT_TDC_L4_DOWN_min[i] && TDC_LE_SFT_L4_DOWN[i][j]<SFT_TDC_L4_DOWN_max[i])) || 
		    	   (ADC_High_SFT_L4_UP[i]>=0 && (TDC_LE_SFT_L4_UP[i][j]>SFT_TDC_L4_UP_min[i] && TDC_LE_SFT_L4_UP[i][j]<SFT_TDC_L4_UP_max[i]))){
					cout << "  " << i+1 << "   " << j << "   " << ADC_High_SFT_L4_DOWN[i] << "   " << ADC_High_SFT_L4_UP[i] << "   " << TDC_LE_SFT_L4_DOWN[i][j] << "   " << TDC_LE_SFT_L4_UP[i][j] << endl;
					SFT_L4[i] = 1;
				}
			}
		}	


		cout << "  " << endl;
		cout << "  " << endl;

		for(int i=0; i<15; i++){
			if(SFT_L1[i]>0){
				cout << "   " << i+1 << "   " << SFT_L1[i] << endl;
				SFT_L1_counter++;
			}
		}

		cout << "  " << endl;

		for(int i=0; i<15; i++){
			if(SFT_L2[i]>0){
				cout << "   " << i+1 << "   " << SFT_L2[i] << endl;
				SFT_L2_counter++;
			}
		}

		cout << "  " << endl;

		for(int i=0; i<17; i++){
			if(SFT_L3[i]>0){
				cout << "   " << i+1 << "   " << SFT_L3[i] << endl;
				SFT_L3_counter++;
			}
		}

		cout << "  " << endl;

		for(int i=0; i<17; i++){
			if(SFT_L4[i]>0){
				cout << "   " << i+1 << "   " << SFT_L4[i] << endl;
				SFT_L4_counter++;
			}
		}


		cout << "  " << SFT_L1_counter << "  " << SFT_L2_counter << "  " << SFT_L3_counter << "  " << SFT_L4_counter << "  " << endl;


	} // EndLoop over Events



}