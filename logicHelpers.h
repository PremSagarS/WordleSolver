#ifndef LOGIC_HELPERS_H
#define LOGIC_HELPERS_H

#include "libraries.h"

enum class Color : uint8_t;
array<Color, 5> matchWords(const string &guess, const string &target);
uint8_t colorToInt(const array<Color, 5> &result);

#endif