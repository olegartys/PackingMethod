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

#include "packing_method.h"

using namespace std;

/* Opens an input file */
void openInputFile (ifstream& inputFile, const char* path)
{
	inputFile.exceptions(std::ios::failbit);
	try {
		inputFile.open (path, std::ifstream::in);
	} catch (std::ios_base::failure &fail) {
        perror (path);
		exit (EXIT_FAILURE);
	}
	/*inputFile.open (path, ifstream::in | ifstream::binary);
	if (inputFile == NULL) {
		perror (path);
		exit (EXIT_FAILURE);
	}*/
}

/* Open an output file */
//FIXME : ADD CHECK FOR EXISTANCE
void openOutputFile (ofstream& outputFile, const char* path)
{
    try {
        outputFile.open (path, ofstream::out | ofstream::binary);
    } catch (std::ios_base::failure &fail) {
        perror (path);
        exit (EXIT_FAILURE);
    }
}

/* Generate output file name path */
const char* genOutputFileName (const char* inputFilePath, MODE mode)
{
    char* t = NULL;
    switch (mode) {
        case COMPRESS :
        {
            //Add FILENAME_SUFFIX to th end of file name
            const size_t SIZE = sizeof(char) * (strlen (inputFilePath) + strlen (FILENAME_SUFFIX)) + sizeof(char);
            t = new char[SIZE];
            memcpy (t, inputFilePath, strlen (inputFilePath));
            strcat (t, FILENAME_SUFFIX);
            t[SIZE] = '\0';
            break;
        }

        case DECOMPRESS :
        {
            t = new char[sizeof(char) * (strlen (inputFilePath))];
            memcpy (t, inputFilePath, strlen(FILENAME_SUFFIX));
            t[strlen(t)-1] = 'M';
            t[strlen(t)+1] = '\0';
            break;
        }
    }
    return t;
}

