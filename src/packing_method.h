#ifndef PACKAGING_METHOD_H
#define PACKAGING_METHOD_H

#include "compressor.h"
#include <iostream>
#include <cerrno>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>

#define FILENAME_SUFFIX ".pack"

//#define char unsigned char

enum MODE {COMPRESS, DECOMPRESS};


void openOutputFile (std::ofstream& outputFile, const char* path);
const char* genOutputFileName (const char* inputFilePath, MODE mode);
void openInputFile (std::ifstream& inputFile, const char* path);

#endif
