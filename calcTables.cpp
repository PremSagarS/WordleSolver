#include "calcTables.h"
#include "dataLoader.h"

uint8_t **matrix;
string *guesses;
string *targets;

unordered_set<uint16_t> invalidTargets;

int gc, tc;

void prepareData(string guessesFileName, string targetsFileName, int GUESS_COUNT, int TARGET_COUNT)
{
    gc = GUESS_COUNT;
    tc = TARGET_COUNT;
    guesses = readWords(guessesFileName, gc);
    targets = readWords(targetsFileName, tc);
}

void calcMatrix()
{
    matrix = new uint8_t *[gc];
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
}

float *calcEntropies()
{
    uint16_t *patternTable = new uint16_t[243]();
    float *entropies = new float[gc](); // int -> float

    for (int gid = 0; gid < gc; gid++)
    {
        fill(patternTable, patternTable + 243, 0);
        for (int j = 0; j < tc; j++)
        {
            if (invalidTargets.find(j) == invalidTargets.end())
                patternTable[matrix[gid][j]] += 1;
        }

        float sum = 0;
        int totalCount = 0;

        for (int i = 0; i < 243; i++)
            totalCount += patternTable[i];

        for (int i = 0; i < 243; i++)
        {
            float px = static_cast<float>(patternTable[i]) / totalCount;
            if (px == 0)
                continue;
            sum += -px * log2(px);
        }

        entropies[gid] = sum;
    }

    delete[] patternTable;

    return entropies;
}

void adjustForResult(uint16_t gid, uint8_t result)
{
    for (int tid = 0; tid < tc; tid++)
    {
        if (matrix[gid][tid] != result)
        {
            invalidTargets.insert(tid);
        }
    }
}