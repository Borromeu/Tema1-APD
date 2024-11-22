#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

// Function declarations
bool fileExists(char *filename);
void checkArguments(int argc, char **argv);
size_t findSize(char *fileName);
bool checkExistenceNewLine(char *buffer);
std::map<std::string, ssize_t> processFile(char *fileName, ssize_t counter);
std::string removeSpecialCharacter(std::string input);
std::map<std::string, std::vector<ssize_t>> processInputFiles(char *inputFileName);

#endif // MAIN_HPP