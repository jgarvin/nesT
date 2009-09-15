#include <stdexcept>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

#include "rom.hpp"

Rom::Rom(std::ifstream& file)
{
	file.seekg(0, std::ios::end);
	std::streampos size = file.tellg();
    raw_nes_data_.reserve(size);

	std::cout << "File size: " << size << std::endl;

    file.seekg(std::ios::beg);
	std::copy(std::istream_iterator<char>(file), std::istream_iterator<char>(),
			  std::back_inserter(raw_nes_data_));
    file.close();

	// Read ROM according to docs at:
	// http://www.sadistech.com/nesromtool/romdoc.html

	char header[4];
	for(int i = 0; i < 3; ++i)
		header[i] = raw_nes_data_[i];
	header[3] = '\0';

	if(std::strcmp(header, "NES") != 0) {
		std::cout << "Header: " << header << std::endl;
		throw std::runtime_error("ROM Header check failed.");
	}

	std::cout << "Rom load success!" << std::endl;

	std::cout << toString();
}

int Rom::num_prg_banks() const
{
	// 4 is constant offset determined by .NES format
	return raw_nes_data_[4];
}

int Rom::num_chr_banks() const
{
	// 5 is constant offset determined by .NES format
	return raw_nes_data_[5];
}

std::string Rom::title() const
{
	const char* title_start = &(*(raw_nes_data_.end() - 122));
	return std::string(title_start);
}

std::string Rom::toString() const
{
	std::ostringstream o;

	o << "PRG Banks: " << num_prg_banks() << std::endl
	  << "CHR Banks: " << num_chr_banks() << std::endl
	  << "Title: " << title() << std::endl;

	return o.str();
}
