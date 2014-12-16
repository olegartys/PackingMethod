/*
 * compressor.cxx
 * 18.11.14
 * Created by Oleg Lyovin <olegartys@gmail.com>
 *
 */

#include "compressor.h"

using namespace std;

/* Create coding table depending on the alphabet */
void Compressor::createCodingTable (void)
{
    char index = 0;
    for (auto it = alphabet->alphabetArr.begin (); it != alphabet->alphabetArr.end (); it++) {
       codingTable[*it] = index;
       index++;
    }
}

/* Write coding table to an output file */
void Compressor::writeCodingTable (void)
{
    /* Writing size of map */
    const size_t t = codingTable.size();
    const size_t MAX_LENGTH_OF_SIZE_DIGIT = 3; //max coding table size is 256 (length=3)
    char s[MAX_LENGTH_OF_SIZE_DIGIT+1] = {0};
    sprintf(s, "%ld", t);
    outputFile->write (s, sizeof(char)*MAX_LENGTH_OF_SIZE_DIGIT);

    /* Writing map */
    for (auto it = codingTable.begin(); it != codingTable.end (); it++) {
        outputFile->write ((char *)&it->first, sizeof (char));
        outputFile->write ((char *)&it->second, sizeof (char));
    }
}

/* Search for a pair for symbol c in codingTable and translate it into bin.
   The length of the result string equal to size of one element in alphabet */
string Compressor::encodeSymbol (const char c)
{
    /*Init string with 0*/
    string encodedSymbol(alphabet->sizeOfOneElement, '0');

    /*Find what number in codingTable pair for symbol c*/
    map<char, char>::const_iterator it = codingTable.find(c);
    unsigned char t = static_cast<unsigned char>(it->second);

    /*Translate this number to a binary form*/
    string::iterator it1 = encodedSymbol.begin();
    while (t != 0) {
        *it1 = t % 2 + '0';
        t /= 2;
        it1++;
    }
    reverse (encodedSymbol.begin(), encodedSymbol.end());

    return encodedSymbol;
}

/* Encode all symbols from inputFile */
void Compressor::createEncodedInformation (void)
{
    /* Set pointer to the begining of the input file */
    inputFile->clear ();
    inputFile->seekg (0, ios::beg);

    /*
        Reading symbols from file to memblock and then encode all the symbols with
        codingTable and push it into this->encodedInformation
    */
    stringstream buffer;
    buffer << inputFile->rdbuf();

	string s = buffer.str();
	buffer.clear();
	for (char c : s)
        encodedInformation.append(encodeSymbol(c));
}

/* Write encoded string into output file */
void Compressor::writeEncodedInformation(void)
{
    //FIXME : какой sizeof ставить при записи размера и magicNumber?
    /* Writing size of one element */
    outputFile->write((char*)&alphabet->sizeOfOneElement, sizeof(char));

    /* Magic Number */
    size_t x = encodedInformation.length();
    if (x % 8 == 0)
        magicNumber = 0;
    else
        magicNumber = (8 - x % 8);

    outputFile->write((char*)&magicNumber, sizeof(char));


    /* Vector that contains bytes of encoded string translated to dec */
    vector<char> v;

    /* Translate encoded string into bytes and adds them to v */
    int i = 0, res = 0;
    for (auto it = encodedInformation.end()-1; it >= encodedInformation.begin(); --it) {
        if (i < 8) {
            res += pow(2, i) * (*it - '0');
            i++;
        }
        else {
            v.push_back(res);
            res = 0;
            i = 0;
            it++;
        }
    }
    if (i <= 8)
        v.push_back(res);

    /* It is neccessary because we have parsed string from end to begin */
    reverse (v.begin(), v.end());

    /* Write reversed vector into file */
    for_each (v.begin(), v.end(), [this](char c){outputFile->write((char*)&c, sizeof(char));});
}

Compressor::Compressor (std::ifstream& inputFile, std::ofstream& outputFile)
{
    this->inputFile = &inputFile;

    /* Creating new alphabet */
    this->alphabet = new Alphabet (*(this->inputFile));

    this->outputFile = &outputFile;
}

/* Runs all functions to compress information */
int Compressor::startCompression (void)
{
    int err_code = 1;

    createCodingTable ();
    writeCodingTable ();
    createEncodedInformation ();
    writeEncodedInformation ();
#ifdef DEBUG
    cout << "Length: " << encodedInformation.length() << endl;
    stdoutCodingTable();
cout << encodedInformation;
#endif

    return err_code;
}

/***************************************DEBUG********************************/
void Compressor::stdoutCodingTable (void)
{
    cout << "Map size: " << codingTable.size() << endl;
    for (auto it = codingTable.begin (); it != codingTable.end(); it++)
        cout << static_cast<int>(it->first) << " : " << static_cast<int>(it->second) << endl;

    cout << "*****************" << endl;
    cout << "Size of one element: " << (int)alphabet->sizeOfOneElement << endl;
    cout << "Magic number: " << (int)magicNumber << endl;
    int k = 0;
   /* for (int i = 0; i < encodedInformation.length(); i++) {
        k++;
        cout << encodedInformation[i];
        if (k % alphabet->sizeOfOneElement== 0) cout << endl;
    }*/

    cout << "*****************"<< endl;
}
