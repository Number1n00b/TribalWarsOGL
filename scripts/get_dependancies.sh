#!/bin/bash

# Gets the dependancies for all c and cpp files under src using g++.
# Outputs to dependancies/dependancies.txt

rm dependancies/dependancies.txt;
for f in src/*/*.c src/*/*.cpp; do
    g++ -MM $f >> dependancies/dependancies.txt;
done
