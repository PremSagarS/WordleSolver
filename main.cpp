#include "dataLoader.h"
#include "calcTables.h"

const auto TARGET_COUNT = 12972;
const auto TARGET_FNAME = "guesses.txt";
const auto GUESS_COUNT = 12972;
const auto GUESS_FNAME = "guesses.txt";

uint8_t **matrix;
string *guesses;
string *targets;

unordered_set<int> invalidTargets;

void calcEntropies()
{
    uint16_t *patternTable = new uint16_t[243]();
    float *entropies = new float[GUESS_COUNT](); // int -> float

    for (int gid = 0; gid < GUESS_COUNT; gid++)
    {
        fill(patternTable, patternTable + 243, 0);
        for (int j = 0; j < TARGET_COUNT; j++)
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

    uint16_t *idx = new uint16_t[GUESS_COUNT]; // NEW: index array
    for (int i = 0; i < GUESS_COUNT; i++)
        idx[i] = i;
    sort(idx, idx + GUESS_COUNT, [&](int a, int b) { // sort indices by entropy
        return entropies[a] > entropies[b];
    });

    for (int i = 0; i < GUESS_COUNT; i++)
        cout << guesses[idx[i]] << " " << entropies[idx[i]] << "\n";

    delete[] idx;
}

void adjustForResult(uint16_t gid, uint8_t result)
{
    for (int tid = 0; tid < TARGET_COUNT; tid++)
    {
        if (matrix[gid][tid] != result)
        {
            invalidTargets.insert(tid);
        }
    }
}

int main(void)
{
    guesses = readWords(GUESS_FNAME, GUESS_COUNT);
    targets = readWords(TARGET_FNAME, TARGET_COUNT);

    matrix = calcMatrix(guesses, targets, GUESS_COUNT, TARGET_COUNT);
    calcEntropies();

    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        cerr << "Peak mem: " << pmc.PeakWorkingSetSize << endl;
    }
}