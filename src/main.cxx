/*
 * main.cxx
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
#include <unistd.h>
#include <cerrno>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include "packing_method.h"
#include "compressor.h"
#include "decompressor.h"
#include "version.h"

using namespace std;

int main(int argc, char **argv)
{
    MODE mode;
    const char* inputFilePath;
    const char* outputFilePath;
	ifstream inputFile;
	ofstream outputFile;

    /* Parsing command arguments */
	if (argc < 2) {
		cerr << "No input arguments.\nUsage: " << PROGRAM_NAME << " [INPUT_FILE] [OUTPUT_FILE]\n";
		exit (EXIT_FAILURE);
	}
	else {
        int opt;
        opt = getopt (argc, argv, "d:");
        /* if parametr is not in input then compress */
        if (opt == -1) {
            inputFilePath = argv[1];
            if (argc == 3)
                outputFilePath = argv[2];
            else
                outputFilePath = genOutputFileName (inputFilePath, COMPRESS);
            openInputFile (inputFile, inputFilePath);
            openOutputFile (outputFile, outputFilePath);

            mode = COMPRESS;
        }
        /* else decompress */
        else {
            optind = 0;
            while ((opt = getopt (argc, argv, "d:")) != -1)
                switch (opt) {
                    case 'd' :
                        inputFilePath = optarg;
                        openInputFile(inputFile, inputFilePath);
                        outputFilePath = genOutputFileName (inputFilePath, DECOMPRESS);
                        openOutputFile(outputFile, outputFilePath);
                        break;
                }
            mode = DECOMPRESS;
        }

    }

    /* Depend on mode meaning Compress or Decomrpess input file */
    switch (mode) {
        case COMPRESS :
        {
            Compressor mainCompressor (inputFile, outputFile);
            clock_t beginTime = clock();
            mainCompressor.startCompression ();
            clock_t endTime = clock ();

            cout << "Compression successfull!\n" << endl;
            cout << "Input file: " << inputFilePath << " [" << inputFile.tellg() << " bytes]" << endl;
            cout << "Output file: " << outputFilePath << " [" << outputFile.tellp() << " bytes]" << endl;

            cout << endl << "Time: " << ((double)(endTime-beginTime)/CLOCKS_PER_SEC) << " sec" << endl;

            break;
        }
        case DECOMPRESS :
        {
            Decompressor mainDecompressor (inputFile, outputFile);
            mainDecompressor.startDecompression ();
            break;
        }
    }

    cout << endl << "To exit press Enter!";
	cin.get();
	return 0;
}
