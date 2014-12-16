/*
 *
 * compressor.h
 * 18.11.14
 * Created by Oleg Lyovin <olegartys@gmail.com>
 *
 * Class that realizes compression of input information
 *
 */

#ifndef COMPRESSOR_H
#define COMPRESSOR_H

//#define DEBUG

#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <sstream>
#include "alphabet.h"

class Compressor
{
    Alphabet* alphabet;
    std::ifstream* inputFile;
    std::ofstream* outputFile;

	std::map<char, char> codingTable;
	std::string encodedInformation;

	uint8_t magicNumber;

	void createCodingTable (void);
	void writeCodingTable (void);
	void createEncodedInformation (void);
	std::string encodeSymbol (const char c);
	void writeEncodedInformation (void);

public:
	Compressor (std::ifstream& inputFile, std::ofstream& outputFile);
	void stdoutCodingTable (void);
	int startCompression (void);
};
#endif
