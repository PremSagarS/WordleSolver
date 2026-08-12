#!/bin/bash
mkdir -p results

g++ -pg -g -O2 -fno-inline main.cpp logicHelpers.cpp dataLoader.cpp calcTables.cpp -o main.exe
{ time ./main.exe > results/out.txt; } 2> results/timing.txt
gprof main.exe gmon.out > results/analysis.txt
rm -f gmon.out