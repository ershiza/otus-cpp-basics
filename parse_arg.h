#pragma once

#include <map>

static std::map<int, int> maxValueByLevel = {{1, 10}, {2, 50}, {3, 100}};

int parseArguments(int, char**);
bool isValidMaxArg(int, char**);
bool isValidLevelArg(int, char**);
bool isValidTableArg(int, char**);