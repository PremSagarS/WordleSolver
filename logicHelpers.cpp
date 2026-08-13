#include "logicHelpers.h"

enum class Color : uint8_t
{
    GREY,
    YELLOW,
    GREEN
};

array<Color, 5> matchWords(const string &guess, const string &target)
{
    array<Color, 5> result = {Color::GREY, Color::GREY, Color::GREY, Color::GREY, Color::GREY};

    uint8_t counts[26] = {0};
    for (int i = 0; i < 5; i++)
        counts[target[i] - 'a']++;

    for (int i = 0; i < 5; i++)
    {
        if (target[i] == guess[i])
        {
            result[i] = Color::GREEN;
            counts[target[i] - 'a']--;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (result[i] == Color::GREEN)
            continue;
        int idx = guess[i] - 'a';
        if (counts[idx] > 0)
        {
            counts[idx]--;
            result[i] = Color::YELLOW;
        }
    }

    return result;
}

uint8_t colorToInt(const array<Color, 5> &result)
{
    int value = 0;
    for (int i = 0; i < 5; i++)
        value = value * 3 + static_cast<int>(result[i]);
    return value;
}