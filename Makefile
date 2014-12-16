CC=g++ 
FLAGS=-std=c++11
INSTALL_PATH=/usr/share
SRCDIR=./src
FILES=$(SRCDIR)/main.cxx $(SRCDIR)/packing_method.cxx $(SRCDIR)/alphabet.cxx $(SRCDIR)/compressor.cxx $(SRCDIR)/decompressor.cxx

PackingMethod:
	$(CC) $(FLAGS) $(FILES) -o packing_method
	
