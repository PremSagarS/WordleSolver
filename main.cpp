#include "dataLoader.h"
#include "calcTables.h"

const auto TARGET_COUNT = 12972;
const auto TARGET_FNAME = "guesses.txt";
const auto GUESS_COUNT = 12972;
const auto GUESS_FNAME = "guesses.txt";

uint16_t getChoice()
{
    for (uint16_t i = 0; i < result.size(); i++)
    {
        cout << i << ": " << get<0>(result[i]) << " " << get<1>(result[i]) << " " << get<2>(result[i]) << endl;
    }
    cout << "Enter choice (-1 to exit): ";
    uint16_t choice;
    cin >> choice;
    return get<0>(result[choice]);
}

uint8_t parseResult()
{
    cout << "Enter Result: ";
    string res;
    cin >> res;

    uint8_t value = 0;
    for (char c : res)
    {
        value = value * 3 + (c - '0');
    }
    return value;
}

int main(void)
{
    prepareData(GUESS_FNAME, TARGET_FNAME, GUESS_COUNT, TARGET_COUNT);
    calcMatrix();

    for (int i = 0; i < 6; i++)
    {
        calcEntropies();
        calcBestGuesses();
        uint16_t choice = getChoice();
        if (choice == -1)
            exit(0);
        uint8_t resForChoice = parseResult();
        adjustForResult(choice, resForChoice);
    }

    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        cerr << "Peak mem: " << pmc.PeakWorkingSetSize << endl;
    }
}