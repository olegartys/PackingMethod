/*
 * alphabet.cxx
 * 18.11.14
 * Created by Oleg Lyovin <olegartys@gmail.com>
 *
 */

#include "alphabet.h"

using namespace std;

// FIXME : READIN FILE BY BLOCKS
/* Parsing input file and init alphabet (all different symbols are included once a time) */
Alphabet::Alphabet (ifstream& inputFile)
{
	stringstream buffer;
	buffer << inputFile.rdbuf();

	string s = buffer.str();
	buffer.clear();

	for (char c : s) {
        vector<char>::const_iterator symbol = find (alphabetArr.begin(), alphabetArr.end(), c);
        if (symbol == alphabetArr.end())
            alphabetArr.push_back (c);
	}

	/* Counting size of one element for a new alphabet */
	uint8_t i = 1;
	while (pow(2, i++) < alphabetArr.size());

	sizeOfOneElement = i-1;
}


string Alphabet::getAlphabetString (void)
{
	string s;
	for_each (alphabetArr.begin(), alphabetArr.end(), [&](char c) {s.push_back(c);});
	return s;
}
