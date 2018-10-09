/*
 *  Created by Jack Hong on 2018-05-25. (jhong@alumni.ubc.ca)
 *  Macro to directly load libraries. If the library files are not yet created, you must first use the included CMAKE
 *  file to build the libraries. In a shell, you can run the included shell script by typing "./buildLibraries.sh"
 *  to automatically generate the make file and build the library.
 */

void LoadLibraries() {
    gSystem->Load("./build/lib/libDetectorData");
}
