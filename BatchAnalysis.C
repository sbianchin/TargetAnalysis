#ifndef __CINT__
#include "BatchAnalysis.h"
#include <iostream>
#include <fstream>
#include "DetectorData.hpp"
#include "KEKCCFile.hpp"
//#include "AnalyzeEvent.h"
#include <stdio.h>
#include <chrono>
#include <string>
#include "TH1F.h"
#include "TStyle.h"
#include <signal.h>

#endif

#define MIN(a, b) ((a < b) ? a : b)

using std::cout;
using std::endl;

volatile sig_atomic_t flag = 0;

namespace KEKCC = KEKCCFile;

//void sigint(int signal) {
//    flag = 1;
//}

void BatchAnalysis(int run_number, PruningType type, int min_event, int max_event,
                   bool print_to_console, bool print_to_file){

    DetectorData *data = new DetectorData(run_number);

    gROOT->SetBatch(1);
    gROOT->ProcessLine("gErrorIgnoreLevel = 3001");
    TH1::AddDirectory(kFALSE);
    gStyle->SetOptStat(11);

    string usekekcc;
    bool useKEKCC_file = false;
    cout << endl;
    cout << endl;

    do{
        cout << "Do you want to use KEKCC file ? (y)es / (n)o :   ";
        cin >> usekekcc;  
    } 
    while(usekekcc != "y" && usekekcc != "yes" && usekekcc != "n" && usekekcc != "no");

    if(usekekcc == "y" || usekekcc == "yes") useKEKCC_file = true;


    int readEvent;
    //char file_batch[100] = "kekcc_all_merged_78_evt.txt";
    ifstream fdat_read(KEKCC::kekcc_file, ios::in);
    
    if(useKEKCC_file && !fdat_read.good()){
        cout << endl;
        cout << endl;
        cout << "THIS KEKCC FILE DOESN'T EXIST !" << endl;
        cout << "(please edit Parameters/KEKCCFile.cpp)" << endl;
        cout << endl;
        cout << endl;
        return;
    }

    int n_events = data->getNumberOfEvents();

    max_event = MIN(n_events, max_event);

    char csv_file[100];
    if(!print_to_file) sprintf(csv_file, "---");
    else{
        sprintf(csv_file, "Run_%d_Batch_output.csv", data->RunNum);

        if (std::ifstream(csv_file)) {
            std::remove(csv_file);
            cout << endl;
            cout << endl;
            cout << "PREVIOUS .CSV FILE HAS BEEN DELETED !" << endl;
            cout << endl;
            cout << endl;

        }
    }

    int print_status_interval = 1000;

    std::chrono::high_resolution_clock::time_point t1, t2, time;
    t1 = std::chrono::high_resolution_clock::now();

    //signal(SIGINT, sigint);
    int k = min_event;
    int counter = 0;

    // CTRL-C EXISTS THIS LOOP

    if(useKEKCC_file){
        while (k <= max_event && fdat_read.good() && !flag){
            fdat_read >> readEvent;
            if(readEvent < min_event || readEvent > max_event) continue;
            counter++;
            k = readEvent;
            if(counter % print_status_interval == 0) {
                time = std::chrono::high_resolution_clock::now();
                cout << counter << " events processed in " <<
                std::chrono::duration_cast<std::chrono::seconds>(time-t1).count() << " seconds" << endl;
            }
            data->getEvent(k);
            //AnalyzeEvent(data, type, true, 0, false, print_to_console, print_to_file);
            DisplayEvent(data, type, true, 0, false, print_to_console, print_to_file, useKEKCC_file);
        }

        t2 = std::chrono::high_resolution_clock::now();
        cout << endl;
        cout << endl;
        cout << "Run number: " << run_number << endl;
        //cout << "Events analyzed: " << min_event << "-" << counter-1 << endl;
        cout << "Events analyzed: " << min_event << "-" << max_event << endl;
        cout << "Total number processed: " << counter << endl;
        cout << "Time taken: "
             << std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count()
             << " seconds" << endl;
        cout << "Output file: " << csv_file << endl;
        cout << "KEKCC File : " << KEKCC::kekcc_file << endl;
        if(type == line) cout << "Pruning Type : LINE" << endl; 
        if(type == triangle) cout << "Pruning Type : TRIANGLE" << endl; 
        if(type == backtracking) cout << "Pruning Type : BACKTRACKING" << endl; 
        cout << endl;
    }
    else{
        while (k <= max_event && !flag){       
            if(k % print_status_interval == 0) {
                time = std::chrono::high_resolution_clock::now();
                cout << k-min_event << " events processed in " <<  
                std::chrono::duration_cast<std::chrono::seconds>(time-t1).count() << " seconds" << endl;
            }
            data->getEvent(k);
            //AnalyzeEvent(data, type, true, 0, false, print_to_console, print_to_file);
            DisplayEvent(data, type, true, 0, false, print_to_console, print_to_file, useKEKCC_file);
            k++;
        }

        t2 = std::chrono::high_resolution_clock::now();
        cout << endl;
        cout << endl;
        cout << "Run number: " << run_number << endl;
        cout << "Events analyzed: " << min_event << "-" << k-1 << endl;
        cout << "Total number processed: " << k-min_event << endl;
        cout << "Time taken: "
         << std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count()
         << " seconds" << endl;
        cout << "Output file: " << csv_file << endl;
        cout << "KEKCC File : " << "---" << endl;
        if(type == line) cout << "Pruning Type : LINE" << endl; 
        if(type == triangle) cout << "Pruning Type : TRIANGLE" << endl; 
        if(type == backtracking) cout << "Pruning Type : BACKTRACKING" << endl; 
        cout << endl;
    }

    flag = 0;
    delete data;
    data = nullptr;
}