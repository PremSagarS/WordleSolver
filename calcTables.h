#ifndef CALC_TABLES_H
#define CALC_TABLES_H

#include "libraries.h"

#include "logicHelpers.h"

void prepareData(string guessesFileName, string targetsFileName, int GUESS_COUNT, int TARGET_COUNT);
void calcMatrix();
void calcEntropies();
void calcBestGuesses();
void adjustForResult(uint16_t gid, uint8_t result);
bool shortCircuitBestGuess();

extern vector<tuple<uint16_t, string, float>> result;

#endif