#include "calcTables.h"

uint8_t **calcMatrix(string *guesses, string *targets, int gc, int tc)
{
    uint8_t **matrix = new uint8_t *[gc];
    for (int i = 0; i < gc; i++)
    {
        matrix[i] = new uint8_t[tc];
    }

    for (int i = 0; i < gc; i++)
    {
        for (int j = 0; j < tc; j++)
        {
            matrix[i][j] = colorToInt(matchWords(guesses[i], targets[j]));
        }
    }

    return matrix;
}