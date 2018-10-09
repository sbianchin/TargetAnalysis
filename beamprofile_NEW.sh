#!/bin/bash
if [ -z "$1" ]; then
	echo -e "No run number given."
	echo -e "Usage: $(basename $0) run_number"
	exit
fi

root -e ".x TARGET_BeamProf.C($1)"
