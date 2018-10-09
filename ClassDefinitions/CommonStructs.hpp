/*
 * Created by Jack Hong on 2018-06-08. (jhong@alumni.ubc.ca)
 *
 * Defines common structures used throughout the code.
 * For structures used only in a particular function or ROOT macro,
 * please define them in the function or ROOT macro header file.
 *
 */

#ifndef MACROS_STRUCTURES_H
#define MACROS_STRUCTURES_H

#include <map>

struct Coordinate {
    double x;
    double y;
    double ex;
    double ey;

    Coordinate(double x_coord=0., double y_coord=0., double ex_coord=0., double ey_coord=0.) :
            x(x_coord), y(y_coord), ex(ex_coord), ey(ey_coord){};
};

struct FitParams {
    double m;
    double b;
    double chiSq;
    double dof;
};

struct Lepton {
    vector<double> vec_xx_lepton;
    vector<double> vec_yy_lepton;
    vector <double> vec_ex_lepton;
    vector <double> vec_ey_lepton;
    vector <double> vec_xx_lepton_rotate;
    vector <double> vec_yy_lepton_rotate;
    vector <double> vec_xx_kaon;
    vector <double> vec_yy_kaon;
    vector <double> vec_ex_kaon;
    vector <double> vec_ey_kaon;
    vector <int> lepton_hit_bars;
    vector <int> kaon_hit_bars;
    vector <double> vec_xx_lepton_low_energy;
    vector <double> vec_yy_lepton_low_energy;
    vector <double> vec_xx_kaon_low_energy;
    vector <double> vec_yy_kaon_low_energy;
    vector <double> vec_ex_lepton_low_energy;
    vector <double> vec_ey_lepton_low_energy;
    vector <double> vec_ex_kaon_low_energy;
    vector <double> vec_ey_kaon_low_energy;
    double dv_x;
    double dv_y;
    int tof1N[5];
    double reduced_loss = 0;
    double reduced_ChiS = 0;
    int ndf = 0;
    double two_track_reduced_loss = 0;
    double first_track_ChiS;
    double second_track_ChiS;
    bool y_event, high_chi_square_high_bar;
    double k_stop_x,k_stop_y;
    double angle_lepton_all;
    double angle_lepton_1;
    double angle_lepton_2;
    bool no_leptons = false;
    bool no_kaons = false;
    std::map<int, vector<int>> kaon_time_energy_map;
};

#endif //MACROS_STRUCTURES_H
