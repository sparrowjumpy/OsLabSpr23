#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Please provide an integer input."
  exit 1
fi

count=$1

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

fibonacci $count
