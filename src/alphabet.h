/*
 *
 * alphabet.h
 * 18.11.14
 * Created by Oleg Lyovin <olegartys@gmail.com>
 *
 * Class that realizes an alphabet of symbols for a compressing information.
 * In alphabetArr we have alphabet itself, in sizeOfOneElement we have a minimal
 * count of bits that we need to encode one symbol.
 *
 */

#ifndef ALPHABET_H
#define ALPHABET_H

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>

class Alphabet
{
    public:
        std::vector<char> alphabetArr;
        uint8_t sizeOfOneElement;

		Alphabet (std::ifstream& inputFile);
		std::string getAlphabetString (void);
};
#endif
