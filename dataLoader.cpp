#include "dataLoader.h"

string *readWords(const string &fname, const int &count)
{
    ifstream file{fname};
    if (!file.is_open())
    {
        throw runtime_error("Couldn't open the file!!");
    }

    string *words = new string[count];

    for (int i = 0; i < count; i++)
    {
        if (!getline(file, words[i]))
            throw runtime_error("file count mismatch!");
    }

    return words;
}