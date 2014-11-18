/*
 * packing_method.cxx
 *
 * Copyright 2014 olegartys <olegartys@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <iostream>
#include <cerrno>
#include <string>
#include <fstream>
#include <cstdlib>
#include "packing_method.h"
#include "compressor.h"

/* Opens an input file */
void openInputFile (std::ifstream& inputFile, const char *path)
{
	/*inputFile.exceptions(std::ios::failbit);
	try {
		inputFile.open (path, std::ifstream::in);
	} catch (std::ios_base::failure &fail) {
		std::cerr << "Can't open file " << path <<"!\n";
		exit (EXIT_FAILURE);
	}*/
	inputFile.open (path, std::ifstream::in | std::ifstream::binary);
	if (inputFile == NULL) {
		perror (path);
		exit (EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		std::cerr << "No input arguments.\nUsage: " << PROGRAM_NAME << " [FILE]\n";
		exit (EXIT_FAILURE);
	}
	const char *path = argv[1];

	std::ifstream inputFile;
	openInputFile (inputFile, path);

	Alphabet mainAlphabet (inputFile);

	std::string s = mainAlphabet.getAlphabetString ();
	/*for (std::string::iterator it = s.begin (); it != s.end(); it++)
		std::cout << static_cast<int>(*it) << " : " << *it << std::endl;*/
	//std::cout << alphabet.getAlphabetString () << std::endl << alphabet.getSizeOfOneElement () << std::endl;
	//std::cout << "Size of one element: " << alphabet.getSizeOfOneElement () << std::endl;

	Compressor mainCompressor (mainAlphabet);
    mainCompressor.getCodingTable ();
	int i;
	std::cin >> i;
	return 0;
}

