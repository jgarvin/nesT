#ifndef INCLUDED_NEST_ROM_HPP
#define INCLUDED_NEST_ROM_HPP

#include <fstream>
#include <string>
#include <vector>

class Rom
{
public:
	Rom(std::ifstream& file);

	int num_prg_banks() const;
	int num_chr_banks() const;
	std::string title() const;

	std::string toString() const;

private:
	std::vector<char> raw_nes_data_;
};

#endif
