#!/bin/bash

outputfile="merge_alltextfiles"
touch $outputfile

find . -name "test.txt" -exec cat {} >> $outputfile \; 
