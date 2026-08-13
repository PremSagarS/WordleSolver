#!/bin/bash
mkdir -p results

g++ -O3 calcTables.cpp dataLoader.cpp logicHelpers.cpp main.cpp -o main.exe -lpsapi
{ time ./main.exe > results/out.txt; } 2> results/timing.txt