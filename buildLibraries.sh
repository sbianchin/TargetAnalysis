#!/bin/sh

# Run in Macros directory
rm -r build
mkdir build
cd build
cmake ..
make
rootcling ./lib/libDetectorData_Dict.C -c ../ClassDefinitions/DetectorData.h ../ClassDefinitions/LinkDef.h