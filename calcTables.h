#ifndef CALC_TABLES_H
#define CALC_TABLES_H

#include "libraries.h"

#include "logicHelpers.h"

void prepareData(string guessesFileName, string targetsFileName, int GUESS_COUNT, int TARGET_COUNT);
void calcMatrix();
void calcEntropies();
void calcBestGuesses();

extern vector<tuple<uint16_t, string, float>> result;

#endif