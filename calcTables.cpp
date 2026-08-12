#include "calcTables.h"

int **calcMatrix(string *guesses, string *targets, int gc, int tc)
{
    int **matrix = new int *[gc];
    for (int i = 0; i < gc; i++)
    {
        matrix[i] = new int[tc];
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