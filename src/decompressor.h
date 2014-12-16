/*
 *
 * decompressor.h
 * 22.11.14
 * Created by Oleg Lyovin <olegartys@gmail.com>
 *
 * Class that realizes decompression of input information
 *
 */


#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Decompressor
{
    std::ifstream* inputFile;
    std::ofstream* outputFile;

    char codingTableSize;
    std::map<char, char> codingTable;
    char sizeOfOneElement;
    char magicNumber;

    std::string encodedInformation;

    void getCodingTable (void);
    void getEncodedInformation (void);
    std::string decodeSymbol (const unsigned char c);
    void writeEncodedInformation (void);

public :
    Decompressor (std::ifstream& inputFile, std::ofstream& outputFile);
    int startDecompression (void);
    void stdoutCodingTable (void);
};

#endif // DECOMPRESSOR_H
