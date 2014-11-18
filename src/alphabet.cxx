/*
 * alphabet.cxx
 * 18.11.14
 * Created by Oleg Lyovin <olegartys@gmail.com>
 *
 */

#include "alphabet.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

bool sort_func (int i, int j) {return i < j;}

Alphabet::Alphabet (std::ifstream& inputFile)
{
	std::string s;

	/* Getting information by blocks from a file and adding new elements
	 * alphabetArr if necessary
	 */
	size_t size = 1024 * sizeof(char);
	char* memblock = new char [size];
	while (!inputFile.eof()) {
		inputFile.read (memblock, size);
		s = static_cast<std::string> (memblock);
		for (std::string::const_iterator it = s.begin(); it != s.end(); it++) {
			std::vector<char>::iterator it1 = std::find (this->alphabetArr.begin(), this->alphabetArr.end(), static_cast<char>(*it));
			if (it1 == this->alphabetArr.end())
				this->alphabetArr.push_back (static_cast<char>(*it));
		}
	}

	/*Counting size of one element for a new alphabet*/
	unsigned int i = 1;
	while (pow(2, i) < this->alphabetArr.size()) {
		i++;
	}
	this->sizeOfOneElement = i;


	//std::sort (alphabetArr.begin(), alphabetArr.end(), sort_func);
}

std::vector<char> Alphabet::getAlphabet (void)
{
    return this->alphabetArr;
}

std::string Alphabet::getAlphabetString (void)
{
	std::string s;
	for (std::vector<char>::iterator it = alphabetArr.begin(); it != alphabetArr.end(); it++)
		s += *it;
	return s;
}

size_t Alphabet::getSizeOfOneElement (void)
{
	return this->sizeOfOneElement;
}

/*void Alphabet::addElementsToAlphabet (const std::string& s)
{
	for (std::string::const_iterator it = s.begin(); it != s.end(); it++) {
		std::vector<char>::iterator it1 = std::find (this->Alphabet.begin(), this->Alphabet.end(), static_cast<char>(*it));
		if (it1 == this->Alphabet.end())
			this->Alphabet.push_back (static_cast<char>(*it));
	}
	Alphabet::changeSizeOfOneElement ();
}

void Alphabet::changeSizeOfOneElement (void)
{
	unsigned int i = 1;
	while (pow(2, i) < this->Alphabet.size()) {
		i++;
	}
	this->sizeOfOneElement = i;
}*/
