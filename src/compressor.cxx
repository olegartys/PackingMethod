#include "compressor.h"
#include <map>
#include <vector>
#include <iostream>

void Compressor::createCodingTable (void)
{
    char index = 0;

    for (std::vector<char>::iterator it = this->alphabet.alphabetArr.begin (); it != this->alphabet.alphabetArr.end (); it++) {
       this->codingTable[*it] = index;
       index++;
    }
}

Compressor::Compressor (Alphabet& alphabet)
{
    this->alphabet = alphabet;
    createCodingTable ();
}

void Compressor::getCodingTable (void)
{
    for (std::map<char, char>::const_iterator it = this->codingTable.begin (); it != codingTable.end(); it++)
        std::cout << static_cast<int>(it->first) << " : " << static_cast<int>(it->second) << std::endl;
}

