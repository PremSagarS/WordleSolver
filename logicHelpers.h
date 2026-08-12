#ifndef LOGIC_HELPERS_H
#define LOGIC_HELPERS_H

#include "libraries.h"

enum class Color;
array<Color, 5> matchWords(const string &guess, const string &target);
int colorToInt(const array<Color, 5> &result);

#endif