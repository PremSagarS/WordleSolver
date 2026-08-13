#!/bin/bash

g++ -O3 calcTables.cpp dataLoader.cpp logicHelpers.cpp main.cpp -o main.exe -lpsapi
./main.exe