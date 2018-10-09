/* 
 * Created by Jack Hong on 2018-08-17. (jhong@alumni.ubc.ca)
 */
#pragma once

#include "TargetBar.hpp"
#include <stdio.h>
#include <iostream>
#include <string>

using std::cout; using std::endl;

ClassImp(TargetBar);

TargetBar::TargetBar(int bar_number, BarType bar_type, int adc_hg, int adc_lg, int tdc_le)
    : m_bar_number(bar_number), m_type(bar_type), m_ADC_HG(adc_hg), m_ADC_LG(adc_lg), m_TDC_LE(tdc_le) {
    m_coord = {0, 0};
}

TargetBar::TargetBar(point_t p, int bar_number, BarType bar_type, int adc_hg, int adc_lg, int tdc_le)
    :  m_coord(p), m_bar_number(bar_number), m_type(bar_type), m_ADC_HG(adc_hg), m_ADC_LG(adc_lg), m_TDC_LE(tdc_le) {
}

void TargetBar::setBarType(BarType bar_type) {
    m_type = bar_type;
}

void TargetBar::printBarType() {
    switch (m_type) {
        case empty : cout << "empty";
        break;

        case lepton : cout << "lepton";
        break;

        case kaon : cout << "kaon";
        break;
    }
}

int TargetBar::getBarNumber() {
    return m_bar_number;
}

point_t TargetBar::getCoord() {
    return m_coord;
}

BarType TargetBar::getBarType() {
    return m_type;
}

int TargetBar::getADC_HG() {
    return m_ADC_HG;
}

int TargetBar::getADC_LG() {
    return m_ADC_LG;
}

int TargetBar::getTDC_LE() {
    return m_TDC_LE;
}

void TargetBar::printInfo() {
    cout << "=============================" << endl;
    cout << "BarInd  = " << m_bar_number << endl;
    printf( "(x, y)  = (%.2f, %.2f) \n", m_coord.x(), m_coord.y());
    cout << "ADC_HG  = " << m_ADC_HG << endl;
    cout << "ADC_LG  = " << m_ADC_LG << endl;
    cout << "TDC_LE  = " << m_TDC_LE << endl;
    cout << "BarType = ";
    printBarType();
    cout << endl;
    cout << "============================" << endl;
}