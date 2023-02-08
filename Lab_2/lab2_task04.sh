#!/bin/bash


touch fileNames.txt

find . -name "*.txt" -type f -print >> fileNames.txt

echo "Finished writing names of text files to fileNames.txt"