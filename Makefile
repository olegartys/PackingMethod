CC=g++
INSTALL_PATH=/usr/share
SRCDIR=./src
FILES=$(SRCDIR)/packing_method.cxx $(SRCDIR)/alphabet.cxx $(SRCDIR)/compressor.cxx

EasyExam:
	$(CC) $(FILES) -o packing_method
	
clear:
	rm -rf *.o
	
install:
	sudo rm -rf $(INSTALL_PATH)/easyexam
	sudo cp -R ./data/easyexam $(INSTALL_PATH)/easyexam
	
	sudo chmod 755 $(INSTALL_PATH)/easyexam
	sudo chmod 755 $(INSTALL_PATH)/easyexam/data 
	sudo chmod -R 755 $(INSTALL_PATH)/easyexam/

