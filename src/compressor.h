#include <map>
#include <string>
#include "alphabet.h"

class Compressor
{
    Alphabet alphabet;
	std::map<char, char> codingTable;
	std::string codedInformation;

	void createCodingTable (void);
	public:
		Compressor (Alphabet &alphabet);
		void getCodingTable (void);
};
