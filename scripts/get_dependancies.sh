#!/bin/bash

# Gets the dependancies for all c and cpp files under src using g++.
# Outputs to scripts/dependancies.txt

rm scripts/dependancies.txt;
for f in src/*/*.c src/*/*.cpp; do
    g++ -MM $f >> scripts/dependancies.txt;
done
