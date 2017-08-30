#!/bin/bash

# ========= Important =========
# Run with bash shell not cmd.
# ==== ==== ==== ==== ==== ====

# Gets the dependancies for all c and cpp files under src using g++.
# Outputs to scripts/dependancies.txt

rm scripts/dependancies.txt;
for f in src/*/*.c src/*/*.cpp; do
    g++ -std=c++11 -MM $f >> scripts/dependancies.txt;
done
