//
// Created by Jack Hong on 2018-05-24.
//

#include <iostream>
#include <cstdlib>

#include "TROOT.h"

#include "DetectorData.h"

int main(int argc, char *argv[]) {
    std::cout << "Tests started" << std::endl;

    DetectorData data(3994);
    std::cout << data.GetEntries() << std::endl;
    return 0;
}