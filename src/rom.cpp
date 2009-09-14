#include <fstream>
#include <stdexcept>
#include <cstring>
#include <iostream>

#include "rom.hpp"

Rom::Rom(std::ifstream& file)
{
	file.seekg(0, std::ios::end);
	std::streampos size = file.tellg();
    char* raw_nes_data = new char [size];

	std::cout << "File size: " << size << std::endl;

    file.seekg(std::ios::beg);
    file.read(raw_nes_data, size);
    file.close();

	// Read ROM according to docs at:
	// http://www.sadistech.com/nesromtool/romdoc.html

	char header[4];
	for(int i = 0; i < 3; ++i)
		header[i] = raw_nes_data[i];
	header[3] = '\0';

	if(std::strcmp(header, "NES") != 0) {
		std::cout << "Header: " << header << std::endl;
		throw std::runtime_error("ROM Header check failed.");
	}

	std::cout << "Rom load success!" << std::endl;
}
