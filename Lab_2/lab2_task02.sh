#!/bin/bash

for i in {01..05}; do
  mkdir "test$i"
  for j in {01..02}; do
    mkdir "test$i/$j"
    date > "test$i/$j/test.txt"
  done
done
