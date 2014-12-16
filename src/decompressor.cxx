/*
 * compressor.cxx
 * 18.11.14
 * Created by Oleg Lyovin <olegartys@gmail.com>
 *
 */

 #include "decompressor.h"

Decompressor::Decompressor (std::ifstream& inputFile, std::ofstream& outputFile)
{
    this->inputFile = &inputFile;
    this->outputFile = &outputFile;
}

void Decompressor::getCodingTable (void)
{
    this->inputFile->read ((char *)&this->codingTableSize, sizeof(char));
    for (int i = 0; i < this->codingTableSize; i++) {
        char* memblock = new char [2*sizeof(char)];
        this->inputFile->read (memblock, sizeof(char) * 2);
        this->codingTable[memblock[0]] = memblock[1];
        delete []memblock;
    }
    this->inputFile->read ((char *)&this->sizeOfOneElement, sizeof(char));
    this->inputFile->read ((char *)&this->magicNumber, sizeof(char));
    //std::cout << (int) this->magicNumber;

    for (std::map<char, char>::const_iterator it = this->codingTable.begin (); it != codingTable.end(); it++)
        std::cout << static_cast<int>(it->first) << " : " << static_cast<int>(it->second) << std::endl;
    std::cout << "*****************"<< std::endl;
    std::cout << "codingTableSize : " << this->codingTableSize << std::endl;
}

void Decompressor::getEncodedInformation (void)
{
    char c;
	while (this->inputFile->read (&c, sizeof(char))) {
		//this->encodedInfromation.push_back (c);
		this->encodedInformation += decodeSymbol (c);
		//std::cout << (int)c << " ";
	}
}

std::string Decompressor::decodeSymbol (const unsigned char c)
{
    std::string decodedSymbol;
    int t = static_cast<int>(c);
    while (t != 0) {
        decodedSymbol += t % 2 + '0';
        t /= 2;
    }

    for (int i = decodedSymbol.length(); i < 8; i++)
        decodedSymbol += '0';

    std::reverse (decodedSymbol.begin(), decodedSymbol.end());

    //std::cout << "c = " << (int) c << " " << decodedSymbol << std::endl;

    return decodedSymbol;
}

void Decompressor::writeEncodedInformation (void)
{
    int k = this->sizeOfOneElement - 1;
    int x = 0;
    std::vector<char> v;
    std::string::const_iterator it = this->encodedInformation.begin () + this->magicNumber;
    for (int i = 0; i < this->encodedInformation.length() - this->magicNumber; i++) {
        if (k < 0)  {
            v.push_back(x);
            x = 0;
            k = this->sizeOfOneElement - 1;
        }
        //std::cout << "k = " << k << " " << std::endl;
        int t = pow(2, k) * (*it - '0');
        x += t;
        k--;
        it++;

    }

    v.push_back (x);

    for (int i = 0; i < v.size(); i++)
        for (std::map<char, char>::const_iterator it = this->codingTable.begin(); it != this->codingTable.end(); it++)
            if (it->second == v[i])
                this->outputFile->write ((char *)&it->first, sizeof(char));
            //std::cout << (int)v[i];
    //std::cout << x << " ";
}

int Decompressor::startDecompression (void)
{
    int err_code = 0;
    getCodingTable ();
    getEncodedInformation ();
    writeEncodedInformation ();

    stdoutCodingTable();
    return err_code;
}

/***************************************DEBUG********************************/
void Decompressor::stdoutCodingTable (void)
{
    std::cout << "Map size: " << this->codingTable.size() << std::endl;
    for (std::map<char, char>::const_iterator it = this->codingTable.begin (); it != codingTable.end(); it++)
        std::cout << static_cast<int>(it->first) << " : " << static_cast<int>(it->second) << std::endl;

    std::cout << "*****************" << std::endl;
    std::cout << "Size of one element: " << (int)this->sizeOfOneElement << std::endl;
    std::cout << "Magic number: " << (int)this->magicNumber << std::endl;
    std::cout << this->encodedInformation << std::endl;
    std::cout << "*****************"<< std::endl;
}

