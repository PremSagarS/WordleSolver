#include "dataLoader.h"
#include "calcTables.h"

const auto TARGET_COUNT = 12972;
const auto TARGET_FNAME = "guesses.txt";
const auto GUESS_COUNT = 12972;
const auto GUESS_FNAME = "guesses.txt";

int **matrix;

void calcEntropies()
{
    int *patternTable = new int[243]();
    float *entropies = new float[GUESS_COUNT](); // int -> float

    for (int gid = 0; gid < GUESS_COUNT; gid++)
    {
        fill(patternTable, patternTable + 243, 0);
        for (int j = 0; j < TARGET_COUNT; j++)
            patternTable[matrix[gid][j]] += 1;

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

    auto guesses = readWords(GUESS_FNAME, GUESS_COUNT); // moved above sort

    int *idx = new int[GUESS_COUNT]; // NEW: index array
    for (int i = 0; i < GUESS_COUNT; i++)
        idx[i] = i;
    sort(idx, idx + GUESS_COUNT, [&](int a, int b) { // sort indices by entropy
        return entropies[a] < entropies[b];
    });

    for (int i = 0; i < GUESS_COUNT; i++)
        cout << guesses[idx[i]] << " " << entropies[idx[i]] << "\n";

    delete[] idx;
}

int main(void)
{
    auto guesses = readWords(GUESS_FNAME, GUESS_COUNT);
    auto targets = readWords(TARGET_FNAME, TARGET_COUNT);

    matrix = calcMatrix(guesses, targets, GUESS_COUNT, TARGET_COUNT);
    calcEntropies();
}