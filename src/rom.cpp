#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

#include <algorithm>

#include "rom.hpp"

const boost::array<char, 4> Rom::NORMAL_HEADER = { { 'N', 'E', 'S', 0x01a } };

Rom::Rom(std::ifstream& file)
{
	file.seekg(0, std::ios::end);
	std::streampos size = file.tellg();
    //raw_nes_data_.reserve(size);

	std::cout << "File size: " << size << std::endl;

    file.seekg(0, std::ios::beg);
	std::copy(std::istream_iterator<char>(file), std::istream_iterator<char>(),
			  std::back_inserter(raw_nes_data_));
    file.close();

	// Read ROM according to docs at:
	// http://www.sadistech.com/nesromtool/romdoc.html

	// array comparer only checks as many elements as are in the array
	if(!std::equal(NORMAL_HEADER.begin(), NORMAL_HEADER.begin() + 4, raw_nes_data_.begin()))
	{
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

int Rom::prg_bank_offset(int i) const
{
	return BANK_START_OFFSET + PRG_BANK_SIZE * i;
}

int Rom::chr_bank_offset(int i) const
{
	return prg_bank_offset(num_prg_banks()) + CHR_BANK_SIZE * i;
}

std::vector<char*> Rom::prg_banks()
{
	std::vector<char*> result;
	
	for(int i = 0; i < num_prg_banks(); ++i)
		result.push_back(&raw_nes_data_[prg_bank_offset(i)]);

	return result;
}

std::vector<char*> Rom::chr_banks()
{
	std::vector<char*> result;

	for(int i = 0; i < num_chr_banks(); ++i)
		result.push_back(&raw_nes_data_[chr_bank_offset(i)]);
	
	return result;
}

std::string Rom::title() const
{
	size_t title_offset = chr_bank_offset(num_chr_banks()) + 1;
	const char* title_start = &raw_nes_data_[title_offset];

	std::cout << title_offset << " " << ((size_t)title_start) - title_offset << std::endl;

	std::cout << raw_nes_data_.size() - 122 << std::endl;

	//  for(int i = -122; i <= 0; ++i)
	// 	 std::cout << size_t(&(raw_nes_data_[raw_nes_data_.size() + i]))
	// 			  << raw_nes_data_[raw_nes_data_.size() + i];

	// for(int i = 0; i < 30; i++)
	// 	std::cout << raw_nes_data_[title_offset + i] << std::endl;

	// for(int i = -100; i <= 100; ++i)
	// 	std::cout << title_start[i];
	std::cout << std::endl;
	//std::cout << title_start - 5 << std::endl;
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
