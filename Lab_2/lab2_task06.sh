#!/bin/bash

# Check if an integer input is provided
if [ $# -eq 0 ]; then
  echo "Please provide an integer input."
  exit 1
fi

#Storing integer input in a variable
count=$1

# Function 
fibonacci() {
  a=0
  b=1
  for ((i=0; i<count; i++)); do
    echo -n "$a "
    fn=$((a + b))
    a=$b
    b=$fn
  done
  echo
}

#calling
fibonacci $count
