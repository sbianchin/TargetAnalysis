#ifndef __CINT__
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip> 
#include <stdlib.h>
#endif

using namespace std;

void Comp(){ 

	gStyle->SetOptStat(1111111);

	ifstream finput_line("TREK_vs_KEKCC_line.csv", ios::in);
	ifstream finput_triangle("TREK_vs_KEKCC_triangle.csv", ios::in);
	ifstream finput_backtracking("TREK_vs_KEKCC_backtracking.csv", ios::in);
	//ifstream Name_finput("test.csv", ios::in);

	string s_RunNum;			int RunNum;
	string s_EvNum;				int EvNum;
	string s_KEKCC_SFT_X;		double KEKCC_SFT_X;
	string s_KEKCC_SFT_Y;		double KEKCC_SFT_Y;
	string s_TREK_SFT_X;		double TREK_SFT_X;
	string s_TREK_SFT_Y;		double TREK_SFT_Y;
	string s_distance_SFT;		double distance_SFT;
	string s_angle_TREK;		double angle_TREK;
	string s_angle_KEKCC;		double angle_KEKCC;
	string s_diff_angle;		double diff_angle;

	int print_status_interval = 10000;
	int counter = 0;

	TH1D *h_SFT_TREK_vs_KEKCC_line;	
	h_SFT_TREK_vs_KEKCC_line = new TH1D("Line Pruning","TRIUMF vs KEKCC | SFT intersect",220,-10,100);

	TH1D *h_SFT_TREK_vs_KEKCC_triangle;	
	h_SFT_TREK_vs_KEKCC_triangle = new TH1D("Triangular Pruning","TRIUMF vs KEKCC | SFT intersect",220,-10,100);

	TH1D *h_SFT_TREK_vs_KEKCC_backtracking;	
	h_SFT_TREK_vs_KEKCC_backtracking = new TH1D("Backtracking Meth.","TRIUMF vs KEKCC | SFT intersect",220,-10,100);


	TH1D *h_ANGLE_TREK_vs_KEKCC_line;	
	h_ANGLE_TREK_vs_KEKCC_line = new TH1D("Line Pruning","TRIUMF vs KEKCC | Angle Difference",220,-10,100);

	TH1D *h_ANGLE_TREK_vs_KEKCC_triangle;	
	h_ANGLE_TREK_vs_KEKCC_triangle = new TH1D("Triangular Pruning","TRIUMF vs KEKCC | Angle Difference",220,-10,100);

	TH1D *h_ANGLE_TREK_vs_KEKCC_backtracking;	
	h_ANGLE_TREK_vs_KEKCC_backtracking = new TH1D("Backtracking Meth.","TRIUMF vs KEKCC | Angle Difference",220,-10,100);

	TH2D *h_line_2D;	
	h_line_2D = new TH2D("Line Pruning","TRIUMF vs KEKCC | #Deltad vs #Delta#phi",220,-10,100, 220,-10,100);
	
	TH2D *h_triangle_2D;	
	h_triangle_2D = new TH2D("Triangular Pruning","TRIUMF vs KEKCC | #Deltad vs #Delta#phi",220,-10,100,220,-10,100);
	
	TH2D *h_backtracking_2D;	
	h_backtracking_2D = new TH2D("Backtracking Meth.","TRIUMF vs KEKCC | #Deltad vs #Delta#phi",220,-10,100,220,-10,100);

	counter = 0;

	cout << endl;
	cout << "Line Pruning..." << endl;
	cout << endl;

	while(finput_line.good()){

		counter++;

		getline(finput_line,s_RunNum,',');
		getline(finput_line,s_EvNum,',');
		getline(finput_line,s_KEKCC_SFT_X,',');
		getline(finput_line,s_KEKCC_SFT_Y,',');
		getline(finput_line,s_TREK_SFT_X,',');
		getline(finput_line,s_TREK_SFT_Y,',');
		getline(finput_line,s_distance_SFT,',');
		getline(finput_line,s_angle_TREK,',');
		getline(finput_line,s_angle_KEKCC,',');
		getline(finput_line,s_diff_angle,'\n');

		RunNum = stoi(s_RunNum);
		EvNum = stoi(s_EvNum);
		KEKCC_SFT_X = stod(s_KEKCC_SFT_X);
		KEKCC_SFT_Y = stod(s_KEKCC_SFT_Y);
		TREK_SFT_X = stod(s_TREK_SFT_X);
		TREK_SFT_Y = stod(s_TREK_SFT_Y);
		distance_SFT = stod(s_distance_SFT);
		angle_TREK = stod(s_angle_TREK);
		angle_KEKCC = stod(s_angle_KEKCC);
		diff_angle = stod(s_diff_angle);

		// cout << fixed;
		// cout << setw(4) << RunNum << "  ";
		// cout << setw(7) << EvNum << "  ";
		// cout << setw(10) << setprecision(3) << KEKCC_SFT_X << "  ";
		// cout << setw(10) << setprecision(3) << KEKCC_SFT_Y << "  ";
		// cout << setw(7) << setprecision(3) << TREK_SFT_X << "  ";
		// cout << setw(7) << setprecision(3) << TREK_SFT_Y << "  ";
		// cout << setw(10) << setprecision(3) << distance_SFT << "  ";
		// cout << setw(6) << setprecision(2) << angle_TREK << "  ";
		// cout << setw(6) << setprecision(2) << angle_KEKCC << "  ";
		// cout << setw(6) << setprecision(2) << diff_angle << "  ";
 	// 	cout << endl;

 		h_SFT_TREK_vs_KEKCC_line->Fill(distance_SFT);
 		h_ANGLE_TREK_vs_KEKCC_line->Fill(diff_angle);
 		h_line_2D->Fill(diff_angle,distance_SFT);

 		if(counter % print_status_interval == 0) {
        	cout << counter << " events processed" << endl;
       	}
	}
	cout << endl;

	counter = 0;

	cout << endl;
	cout << "Triangle Pruning..." << endl;
	cout << endl;

	while(finput_triangle.good()){
	
		counter++;

		getline(finput_triangle,s_RunNum,',');
		getline(finput_triangle,s_EvNum,',');
		getline(finput_triangle,s_KEKCC_SFT_X,',');
		getline(finput_triangle,s_KEKCC_SFT_Y,',');
		getline(finput_triangle,s_TREK_SFT_X,',');
		getline(finput_triangle,s_TREK_SFT_Y,',');
		getline(finput_triangle,s_distance_SFT,',');
		getline(finput_triangle,s_angle_TREK,',');
		getline(finput_triangle,s_angle_KEKCC,',');
		getline(finput_triangle,s_diff_angle,'\n');

		RunNum = stoi(s_RunNum);
		EvNum = stoi(s_EvNum);
		KEKCC_SFT_X = stod(s_KEKCC_SFT_X);
		KEKCC_SFT_Y = stod(s_KEKCC_SFT_Y);
		TREK_SFT_X = stod(s_TREK_SFT_X);
		TREK_SFT_Y = stod(s_TREK_SFT_Y);
		distance_SFT = stod(s_distance_SFT);
		angle_TREK = stod(s_angle_TREK);
		angle_KEKCC = stod(s_angle_KEKCC);
		diff_angle = stod(s_diff_angle);

		// cout << fixed;
		// cout << setw(4) << RunNum << "  ";
		// cout << setw(7) << EvNum << "  ";
		// cout << setw(10) << setprecision(3) << KEKCC_SFT_X << "  ";
		// cout << setw(10) << setprecision(3) << KEKCC_SFT_Y << "  ";
		// cout << setw(7) << setprecision(3) << TREK_SFT_X << "  ";
		// cout << setw(7) << setprecision(3) << TREK_SFT_Y << "  ";
		// cout << setw(10) << setprecision(3) << distance_SFT << "  ";
		// cout << setw(6) << setprecision(2) << angle_TREK << "  ";
		// cout << setw(6) << setprecision(2) << angle_KEKCC << "  ";
		// cout << setw(6) << setprecision(2) << diff_angle << "  ";
 	// 	cout << endl;

 		h_SFT_TREK_vs_KEKCC_triangle->Fill(distance_SFT);
 		h_ANGLE_TREK_vs_KEKCC_triangle->Fill(diff_angle);
 		h_triangle_2D->Fill(diff_angle,distance_SFT);

 		if(counter % print_status_interval == 0) {
        	cout << counter << " events processed" << endl;
       	}
	}
	cout << endl;

	counter = 0;

	cout << endl;
	cout << "Backtracking Method..." << endl; 
	cout << endl;

	while(finput_backtracking.good()){
	
		counter++;

		getline(finput_backtracking,s_RunNum,',');
		getline(finput_backtracking,s_EvNum,',');
		getline(finput_backtracking,s_KEKCC_SFT_X,',');
		getline(finput_backtracking,s_KEKCC_SFT_Y,',');
		getline(finput_backtracking,s_TREK_SFT_X,',');
		getline(finput_backtracking,s_TREK_SFT_Y,',');
		getline(finput_backtracking,s_distance_SFT,',');
		getline(finput_backtracking,s_angle_TREK,',');
		getline(finput_backtracking,s_angle_KEKCC,',');
		getline(finput_backtracking,s_diff_angle,'\n');

		RunNum = stoi(s_RunNum);
		EvNum = stoi(s_EvNum);
		KEKCC_SFT_X = stod(s_KEKCC_SFT_X);
		KEKCC_SFT_Y = stod(s_KEKCC_SFT_Y);
		TREK_SFT_X = stod(s_TREK_SFT_X);
		TREK_SFT_Y = stod(s_TREK_SFT_Y);
		distance_SFT = stod(s_distance_SFT);
		angle_TREK = stod(s_angle_TREK);
		angle_KEKCC = stod(s_angle_KEKCC);
		diff_angle = stod(s_diff_angle);

		// cout << fixed;
		// cout << setw(4) << RunNum << "  ";
		// cout << setw(7) << EvNum << "  ";
		// cout << setw(10) << setprecision(3) << KEKCC_SFT_X << "  ";
		// cout << setw(10) << setprecision(3) << KEKCC_SFT_Y << "  ";
		// cout << setw(7) << setprecision(3) << TREK_SFT_X << "  ";
		// cout << setw(7) << setprecision(3) << TREK_SFT_Y << "  ";
		// cout << setw(10) << setprecision(3) << distance_SFT << "  ";
		// cout << setw(6) << setprecision(2) << angle_TREK << "  ";
		// cout << setw(6) << setprecision(2) << angle_KEKCC << "  ";
		// cout << setw(6) << setprecision(2) << diff_angle << "  ";
 	// 	cout << endl;

 		h_SFT_TREK_vs_KEKCC_backtracking->Fill(distance_SFT);
 		h_ANGLE_TREK_vs_KEKCC_backtracking->Fill(diff_angle);
 		h_backtracking_2D->Fill(diff_angle,distance_SFT);

 		if(counter % print_status_interval == 0) {
        	cout << counter << " events processed" << endl;
      	}
	}
	cout << endl;

	TCanvas* cc1 = new TCanvas("TREK vs KEKCC", "TREK vs KEKCC", 500,300,1300,600);
    cc1->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",0,0, "ProcEvent(Int_t,Int_t,Int_t,TObject*)");
	cc1->Divide(3,3);


	cc1->cd(1);
	h_SFT_TREK_vs_KEKCC_line->Draw();

	cc1->cd(2);
	h_SFT_TREK_vs_KEKCC_triangle->Draw();
		
	cc1->cd(3);
	h_SFT_TREK_vs_KEKCC_backtracking->Draw();

	cc1->cd(4);
	h_ANGLE_TREK_vs_KEKCC_line->Draw();

	cc1->cd(5);
	h_ANGLE_TREK_vs_KEKCC_triangle->Draw();
		
	cc1->cd(6);
	h_ANGLE_TREK_vs_KEKCC_backtracking->Draw();
	
	cc1->cd(7);	
	h_line_2D->Draw();

	cc1->cd(8);
	h_triangle_2D->Draw();

	cc1->cd(9);
	h_backtracking_2D->Draw();


	TCanvas* cc2 = new TCanvas("TREK vs KEKCC (2D Plot)", "TREK vs KEKCC (2D Plot)", 500,300,1300,600);
    cc2->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",0,0, "ProcEvent(Int_t,Int_t,Int_t,TObject*)");
	cc2->Divide(3,1);

	cc2->cd(1);	
	h_line_2D->Draw();

	cc2->cd(2);
	h_triangle_2D->Draw();

	cc2->cd(3);
	h_backtracking_2D->Draw();

}	





