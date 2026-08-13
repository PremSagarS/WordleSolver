#include "dataLoader.h"
#include "calcTables.h"

const auto TARGET_COUNT = 12972;
const auto TARGET_FNAME = "guesses.txt";
const auto GUESS_COUNT = 12972;
const auto GUESS_FNAME = "guesses.txt";

int main(void)
{
    prepareData(GUESS_FNAME, TARGET_FNAME, GUESS_COUNT, TARGET_COUNT);
    calcMatrix();
    calcEntropies();
    calcBestGuesses();

    for (auto var : result)
    {
        cout << get<0>(var) << " " << get<1>(var) << " " << get<2>(var) << endl;
    }

    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        cerr << "Peak mem: " << pmc.PeakWorkingSetSize << endl;
    }
}