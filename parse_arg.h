#pragma once

#include <map>

static std::map<int, int> getMaxValue = {{1, 10}, {2, 50}, {3, 100}};

bool parseArguments(int, char**);
bool parseMax(int, char**);
bool parseLevel(int, char**);
bool parseTable(int, char**);