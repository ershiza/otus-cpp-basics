#pragma once

#include <string>

static const char* scores_filename = "../scores.txt";
static const char* high_scores_filename = "../high_scores.txt";

bool writeScore(std::string, int);
bool writeHighScore(std::string, int);
bool readScoreTable();
bool readHighScoreTable();