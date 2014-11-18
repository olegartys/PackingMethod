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

#include <string>
#include <vector>
#include <fstream>

class Alphabet
{
	std::vector<char> alphabetArr;
	size_t sizeOfOneElement;

	public:
		Alphabet (std::ifstream& inputFile);
		std::string getAlphabetString (void);
		std::vector<char> getAlphabet (void);
		size_t getSizeOfOneElement (void);

		/*void changeSizeOfOneElement (void);
		std::vector<char> getAlphabet (void);
		void addElementsToAlphabet (const std::string& s);*/
};
