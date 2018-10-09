#!/bin/bash

sed 's/ \+/,/g' $1 > $1.csv		    # CONVERT TXT TO CSV
sed -i 's/^.//' $1.csv				# REMOVE FIRST CHARACTER
sed -i 's/.$//' $1.csv				# REMOVE LAST CHARACTER
find . -type f -name "*.txt.csv" -exec rename -f 's/\.txt.csv$/.csv/' {} \;

